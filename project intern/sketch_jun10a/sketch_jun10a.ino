 #include <Servo.h>
Servo doorServo;







// Pin definitions



const int trigPin = 8;



const int echoPin = 9;



const int ledPin = 7;



const int servoPin = 10;







// Default threshold distance (cm)



int threshold = 203;







// Door positions



const int DOOR_CLOSED = 0;



const int DOOR_OPEN = 90;







bool doorOpen = false;







// Variables for LED blinking



unsigned long previousMillis = 0;



const long blinkInterval = 500;



bool ledState = LOW;







void setup() {



  Serial.begin(9600);







  pinMode(trigPin, OUTPUT);



  pinMode(echoPin, INPUT);



  pinMode(ledPin, OUTPUT);







  doorServo.attach(servoPin);







  // Door closed by default



  doorServo.write(DOOR_CLOSED);



  digitalWrite(ledPin, LOW);







}







void loop() {







  // Check if threshold update is received



  if (Serial.available()) {



    int newThreshold = Serial.parseInt();







    if (newThreshold > 0) {



      threshold = newThreshold;







      Serial.print("Threshold updated to: ");



      Serial.print(threshold);



      Serial.println(" cm");



    }



  }







  long distance = getDistance();







  // Open door if object is within threshold



  if (distance > 0 && distance <= threshold) {



    if (!doorOpen) {



      doorServo.write(DOOR_OPEN);



      doorOpen = true;



      Serial.print("Door Opened,");



      Serial.print(" Distance: ");



      Serial.print(distance);



      Serial.println(" cm");



    }



  }



  else {



    if (doorOpen) {



      doorServo.write(DOOR_CLOSED);



      doorOpen = false;



      digitalWrite(ledPin, LOW);



      Serial.print("Door Closed,");



      Serial.print("Distance: ");



      Serial.print(distance);



      Serial.println(" cm");



    }



  }







  // Blink LED when door is open



  if (doorOpen) {



    unsigned long currentMillis = millis();







    if (currentMillis - previousMillis >= blinkInterval) {



      previousMillis = currentMillis;







      ledState = !ledState;



      digitalWrite(ledPin, ledState);



    }



  }







  delay(100);



}







// Function to measure distance



long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);



  delayMicroseconds(10);







  digitalWrite(trigPin, LOW);







  long duration = pulseIn(echoPin, HIGH);







  long distance = duration * 0.034 / 2;







  return distance;



}
