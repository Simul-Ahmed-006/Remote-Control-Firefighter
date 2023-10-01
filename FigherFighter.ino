#include <Servo.h>
Servo s1;

#define pump 12 // Pump output pin
#define IN1R 8
#define IN2R 9
#define IN3L 10
#define IN4L 11

int data; // Variable for receiving data
#define LS 4
#define MS 3
#define RS 2
int LSVALUE;
int MSVALUE;
int RSVALUE;

void forword() {
  digitalWrite(IN1R, HIGH);
  digitalWrite(IN2R, LOW);
  digitalWrite(IN3L, LOW);
  digitalWrite(IN4L, HIGH);
}

void backword() {
  digitalWrite(IN1R, LOW);
  digitalWrite(IN2R, HIGH);
  digitalWrite(IN3L, HIGH);
  digitalWrite(IN4L, LOW);
}

void left() {
  digitalWrite(IN1R, HIGH);
  digitalWrite(IN2R, LOW);
  digitalWrite(IN3L, HIGH);
  digitalWrite(IN4L, LOW);
}

void right() {
  digitalWrite(IN3L, LOW);
  digitalWrite(IN4L, HIGH);
  digitalWrite(IN1R, LOW);
  digitalWrite(IN2R, HIGH);
}

void stop() {
  digitalWrite(IN1R, LOW);
  digitalWrite(IN2R, LOW);
  digitalWrite(IN3L, LOW);
  digitalWrite(IN4L, LOW);
}

void setup() {
  s1.attach(6);

  // Pinmode for heat sensor
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);
  pinMode(MS, INPUT);
  // Pinmode for pump output
  pinMode(pump, OUTPUT);
  digitalWrite(pump, HIGH); // Turn off the pump
  // Pinmode for motor driver
  pinMode(IN1R, INPUT);
  pinMode(IN1R, OUTPUT);
  pinMode(IN2R, OUTPUT);
  pinMode(IN3L, OUTPUT);
  pinMode(IN4L, OUTPUT);
  // Start with both motors off
  stop();

  // Bluetooth communication setup
  Serial.begin(9600);
  delay(100);
}

void loop() {
  robotControl(); // Forward function works, Bluetooth communication works, but condition doesn't work with Bluetooth communication
  fireControl();  // All sensor readings in one function
}

void fireControl() {
  LSVALUE = digitalRead(LS);
  MSVALUE = digitalRead(MS);
  RSVALUE = digitalRead(RS);
  Serial.print("LSVALUE: ");
  Serial.print(LSVALUE);
  Serial.print(" MSVALUE: ");
  Serial.print(MSVALUE);
  Serial.print(" RSVALUE: ");
  Serial.println(RSVALUE);
  delay(1000);
  
  if (LSVALUE == HIGH) {
    s1.write(25);
    digitalWrite(pump, HIGH);
    stop();
  } else {
    digitalWrite(pump, LOW);
  }

  if (RSVALUE == HIGH) {
    s1.write(145);
    digitalWrite(pump, HIGH);
    stop();
  } else {
    digitalWrite(pump, LOW);
  }

  if (MSVALUE == HIGH) {
    s1.write(90);
    digitalWrite(pump, HIGH);
    stop();
  } else {
    digitalWrite(pump, LOW);
  }
}

void robotControl() {
  if (Serial.available() > 0) {
    data = Serial.read();
    Serial.println(data);
  }

  if (data == '1') {
    while (1) {
      forword();
      Serial.println("Forward");
      if (data == '2' || data == '3' || data == '4') {
        break;
      }
    }
  } else if (data == '2') {
    backword();
    Serial.println("Backward");
  } else if (data == '4') {
    left();
    Serial.println("Left");
  } else if (data == '3') {
    right();
    Serial.println("Right");
  } else {
    stop();
    Serial.println("Stop");
  }
}
