const express = require('express');
const http = require('http');
const { Server } = require('socket.io');
const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');

const app = express();
const server = http.createServer(app);
const io = new Server(server, { cors: { origin: "*" } });

// Serve our HTML page automatically from the current folder
app.use(express.static(__dirname));

let arduinoPort = null;

io.on('connection', (socket) => {
    console.log('🔗 Dashboard web page opened in browser.');

    // Listen for connection commands from the browser UI
    socket.on('connect-hardware', ({ comPort }) => {
        try {
            if (arduinoPort && arduinoPort.isOpen) {
                arduinoPort.close();
            }

            console.log(`🔌 Attempting serial connection to ${comPort}...`);
            arduinoPort = new SerialPort({ path: comPort, baudRate: 9600 });
            const parser = arduinoPort.pipe(new ReadlineParser({ delimiter: '\r\n' }));

            arduinoPort.on('open', () => {
                console.log('✅ Hardware successfully synced up!');
                socket.emit('status', { connected: true });
            });

            // Read live streams arriving from Arduino and broadcast them to the web page
            parser.on('data', (data) => {
                console.log(`📡 Arduino Serial: ${data}`);
                io.emit('arduino-data', data);
            });

            arduinoPort.on('error', (err) => {
                socket.emit('status', { connected: false, error: err.message });
            });

        } catch (e) {
            socket.emit('status', { connected: false, error: e.message });
        }
    });

    // Listen for slider threshold updates from the browser UI
    socket.on('update-threshold', (val) => {
        if (arduinoPort && arduinoPort.isOpen) {
            arduinoPort.write(`T:${val}\n`);
            console.log(`📤 Sent threshold payload to hardware: T:${val}`);
        }
    });
});

server.listen(5000, () => {
    console.log('🚀 Server is active! Open http://localhost:5000 in your browser');
});