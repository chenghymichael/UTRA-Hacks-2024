// Main!!!
// task 1,2

// LED
const int ledR = A5;
const int ledG = A4;
const int ledB = A3;

// Motor R connections
const int enA = 9;
const int in1 = 8;
const int in2 = 7;
// Motor L connections
const int enB = 3;
const int in3 = 5;
const int in4 = 4;

// IR
const int ir1a = A0;
const int ir1d = 10;
const int ir2a = A1;
const int ir2d = 11;

int value_1A0;
bool value_1D0;
int value_2A0;
bool value_2D0;

int irthreshold = 100;
int rtime = 2300;

// Ultrasonic
#include <NewPing.h>

int TRIGGER_PIN = 12;
int ECHO_PIN = 13;
int MAX_DISTANCE = 400;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
int distance = 0;

// Button
const int button = A2;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(2400);

  // LED
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);

  // Motor Driver
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  // IR
  pinMode(ir1a, INPUT);
  pinMode(ir1d, INPUT);
  pinMode(ir2a, INPUT);
  pinMode(ir2d, INPUT);

  //
  led(ledR, HIGH);
  led(ledG, HIGH);
  led(ledB, HIGH);

  while (digitalRead(button) == 0) {
  }
  led(ledR, LOW);
  led(ledG, LOW);
  led(ledB, LOW);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

  // value_1A0 = analogRead(ir1a);
  // value_1D0 = digitalRead(ir1d);
  // value_2A0 = analogRead(ir2a);
  // value_2D0 = digitalRead(ir2d);
  // distance = sonar.ping_cm();

  // Serial.print("1 Analog: ");
  // Serial.print(value_1A0);
  // Serial.print(" Digital: ");
  // Serial.print(value_1D0);
  // Serial.print(" | 2 Analog: ");
  // Serial.print(value_2A0);
  // Serial.print(" Digital: ");
  // Serial.print(value_2D0);
  // Serial.print(" | button: ");
  // Serial.print(digitalRead(button));
  // Serial.print(" | distance: ");
  // Serial.print(distance);
  // Serial.println();

  // if (value_1A0 > 512) {
  //   led(ledR, HIGH);
  // } else {
  //   led(ledR, LOW);
  // }

  // if (value_2A0 > 512) {
  //   led(ledG, HIGH);
  // } else {
  //   led(ledG, LOW);
  // }

  // if (distance < 12) {
  //   led(ledB, HIGH);
  // } else {
  //   led(ledB, LOW);
  // }

  while (digitalRead(button) == 0) {
    if ((analogRead(ir1a) <= irthreshold) && (analogRead(ir2a) <= irthreshold)) {
      led(ledR, HIGH);
      led(ledG, LOW);
      led(ledB, LOW);
      motor(150, 150);
    } else if ((analogRead(ir1a) > irthreshold) && (analogRead(ir2a) <= irthreshold)) {
      led(ledR, LOW);
      led(ledG, HIGH);
      led(ledB, LOW);
      motor(-150, 120);
    } else if ((analogRead(ir1a) <= irthreshold) && (analogRead(ir2a) > irthreshold)) {
      led(ledR, LOW);
      led(ledG, HIGH);
      led(ledB, LOW);
      motor(120, -150);
    } else if ((analogRead(ir1a) > irthreshold) && (analogRead(ir2a) > irthreshold)){  // line line
      led(ledR, LOW);
      led(ledG, LOW);
      led(ledB, HIGH);
      motor(150, 75);
      // long tint = millis();
      // long t = tint;
      // while ((analogRead(ir1a) <= irthreshold) && (analogRead(ir2a) <= irthreshold) && ((t - tint) < rtime)) {
      //   motor(-100, 150);
      //   t = millis();
      // }
      // if ((t - tint) < rtime) {
      //   continue;
      // } else {
      //   while ((analogRead(ir1a) <= irthreshold) && (analogRead(ir2a) <= irthreshold)) {
      //     motor(150, -100);
      //   }
      // }
    }
    delay(5);
    
  }
  motor(0, 0);
  while (digitalRead(button) == 1) {
    led(ledR, HIGH);
    led(ledG, HIGH);
    led(ledB, HIGH);
  }
  while (digitalRead(button) == 0) {
  }
  led(ledR, LOW);
  led(ledG, LOW);
  led(ledB, LOW);
  delay(1000);
}

void motor(int L, int R) {
  // motor speed (+-ve)
  if (L > 0) {
    analogWrite(enB, L);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  if (L < 0) {
    analogWrite(enB, (-1) * L);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  if (L == 0) {
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }

  if (R > 0) {
    analogWrite(enA, R);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  if (R < 0) {
    analogWrite(enA, (-1) * R);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  if (R == 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}

void led(int port, int on) {
  // turn LED on/off
  digitalWrite(port, on);
}