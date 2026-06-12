# 🚪 Automatic Door System

An Arduino-based automatic door system that detects nearby objects using an ultrasonic sensor and automatically opens/closes the door using a servo motor.  
The project also includes a web dashboard for real-time monitoring of distance and door status.

---

## 📌 Project Overview

This project is a smart contactless door automation system designed to improve convenience and hygiene.

The ultrasonic sensor detects a person/object approaching the door. The Arduino Uno processes the sensor data and controls the servo motor to operate the door mechanism.

A web dashboard displays live system information received from Arduino through serial communication.

---

## ✨ Features

✅ Automatic door opening and closing  
✅ Object detection using ultrasonic sensor  
✅ Servo motor based door movement  
✅ LED status indication  
✅ Real-time distance monitoring  
✅ Adjustable detection threshold  
✅ Serial communication dashboard  

---

## 🛠️ Technologies Used

### Hardware

- Arduino Uno
- HC-SR04 Ultrasonic Sensor
- SG90 Servo Motor
- LED
- Breadboard
- Jumper Wires
- USB Cable

### Software

- Arduino IDE
- C++ (Arduino Code)
- HTML
- CSS
- JavaScript

---

## ⚙️ Working Principle

1. The HC-SR04 ultrasonic sensor continuously measures distance.
2. Arduino Uno receives the sensor values.
3. If the detected distance is within the set limit:
   - Servo motor rotates
   - Door opens
   - LED indicates activity
4. After the object moves away:
   - Door closes automatically
5. Arduino sends live data to the dashboard using serial communication.

---

## 🔄 System Architecture

```
    HC-SR04 Ultrasonic Sensor
            |
            ↓
       Arduino Uno
            |
            ↓
    Distance Calculation
            |
            ↓
        Servo Motor
            |
            ↓
       Door Movement


Arduino Serial Output
            |
            ↓
      Web Dashboard

```

## 🔌 Circuit Connections

### Ultrasonic Sensor

| HC-SR04 | Arduino Uno |
|---|---|
| VCC | 5V |
| GND | GND |
| TRIG | Digital Pin |
| ECHO | Digital Pin |

### Servo Motor

| Servo Wire | Arduino |
|---|---|
| VCC | 5V |
| GND | GND |
| Signal | Digital Pin |

### LED

| LED | Arduino |
|---|---|
| Positive | Digital Pin |
| Negative | GND |

---

## 🖥️ Dashboard

The dashboard provides:

- 🚪 Door status
- 📏 Live distance value
- 🎚️ Detection threshold control
- 🔌 Arduino connection status

---

## 🚀 How To Run

### Arduino Setup

1. Install Arduino IDE
2. Connect Arduino Uno
3. Open the Arduino code
4. Select:
   - Board → Arduino Uno
   - Correct COM Port
5. Upload the program

### Dashboard Setup

1. Open the Dashboard folder
2. Run `index.html`
3. Connect Arduino serial port
4. Monitor live door activity

---

## 🎯 Applications

- Smart homes
- Offices
- Hospitals
- Contactless entry systems
- Automated gates
- Accessibility solutions

---

## 🔮 Future Improvements

- WiFi based IoT communication
- Mobile application control
- RFID security access
- Cloud data storage
- AI-based visitor detection
- Better power optimization
