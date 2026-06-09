#include <Servo.h>
#define TRIG 8
#define ECHO 9
#define LED  11

Servo servo;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);
  servo.attach(10);
  Serial.begin(9600);
}

long getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000); // 30 ms timeout

  if (duration == 0) return -1;  // no echo

  return duration * 0.034 / 2;   // distance in cm
}
int state=0;
int oldstate=0;
void loop() {
  long distance = getDistance();
  if (distance > 0 && distance <= 10) {
    servo.write(120);
    state=1;   // door open
    digitalWrite(LED,HIGH);
  } else {
    servo.write(0);
    state=0; // door close
    digitalWrite(LED,LOW);
  }

  if (oldstate!=state){
    Serial.print(state);
    Serial.print(",");
    Serial.println(distance);
    oldstate=state;
  }

  delay(300);
}
