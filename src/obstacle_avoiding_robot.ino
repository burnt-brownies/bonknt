#include <Servo.h>
Servo Myservo;

#define trigPin 9
#define echoPin 8
#define MLa 4
#define MLb 5
#define MRa 6
#define MRb 7

int servoAngle = 90;
int servoStep = 5;
long lastDist = 999;

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long dur = pulseIn(echoPin, HIGH, 20000);
  if (dur == 0) return 999;
  return dur / 58.2;
}

void moveForward() {
  digitalWrite(MRb, HIGH); digitalWrite(MRa, LOW);
  digitalWrite(MLb, HIGH); digitalWrite(MLa, LOW);
}

void moveBackward() {
  digitalWrite(MRb, LOW); digitalWrite(MRa, HIGH);
  digitalWrite(MLb, LOW); digitalWrite(MLa, HIGH);
}

void turnLeft() {
  digitalWrite(MRb, HIGH); digitalWrite(MRa, LOW);
  digitalWrite(MLb, LOW);  digitalWrite(MLa, LOW);
}

void turnRight() {
  digitalWrite(MLb, HIGH); digitalWrite(MLa, LOW);
  digitalWrite(MRb, LOW);  digitalWrite(MRa, LOW);
}

void stopMotors() {
  digitalWrite(MRb, LOW); digitalWrite(MRa, LOW);
  digitalWrite(MLb, LOW); digitalWrite(MLa, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(MLa, OUTPUT);
  pinMode(MLb, OUTPUT);
  pinMode(MRa, OUTPUT);
  pinMode(MRb, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Myservo.attach(10);
  Myservo.write(90);
  delay(1000);
}

void loop() {
  servoAngle += servoStep;
  if (servoAngle >= 160 || servoAngle <= 20) {
    servoStep = -servoStep;
  }
  Myservo.write(servoAngle);
  delay(30);
  long dist = getDistance();
  Serial.print("Angle: "); Serial.print(servoAngle);
  Serial.print("  Dist: "); Serial.println(dist);

  if (servoAngle > 60 && servoAngle < 120 && dist < 20) {
    stopMotors();
    delay(300);
    Myservo.write(0);   delay(600);
    long rightDist = getDistance();
    Serial.print("Right: "); Serial.println(rightDist);
    Myservo.write(180); delay(600);
    long leftDist = getDistance();
    Serial.print("Left: "); Serial.println(leftDist);
    Myservo.write(90);  delay(400);
    moveBackward();
    delay(400);
    stopMotors();
    delay(200);
    if (leftDist >= rightDist) {
      turnLeft();
    } else {
      turnRight();
    }
    delay(450);
    stopMotors();
    delay(200);
  } else {
    moveForward();
  }
}
