#define TRIG 9
#define ECHO 10
#define LED_PIN 11
#include <Servo.h>

Servo servo;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED_PIN,OUTPUT)
  Serial.begin(9600);
  servo.attach(9);
}

void loop() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000); // 30 ms timeout

  if (duration == 0) {
  } else {
    float distance = duration * 0.034 / 2;
  }

  if (distance <= 3) {
      digitalWrite(LED_PIN, HIGH);
      servo.write(90);
      Serial.println("open"); 
  }else {
    digitalWrite(LED_PIN, LOW); 
    servo.write(0);
    Serial.println("closed");
  }

  delay(500);
}
