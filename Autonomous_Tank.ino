#include <Servo.h>

#include <SoftwareSerial.h> 

#include <Servo.h> 



SoftwareSerial BTSerial(0, 1); // RX, TX pins of HC-05 Bluetooth module 

// L298N Motor Driver pin definitions
int enablePinA = 6; // PWM pin for controlling motor speed
int in1Pin = 8;    // input pin 1 for motor direction
int in2Pin = 9;    // input pin 2 for motor direction

int enablePinB = 7;
int in3Pin = 4;
int in4Pin = 5;

int servoPin = 3;

Servo Servo1;

void setup() {
  Serial.begin(9600); // initialize serial communication
  BTSerial.begin(9600); 

  pinMode(enablePinA, OUTPUT);
  pinMode(enablePinB, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  Servo1.attach(servoPin);

}

void loop() {
  if (BTSerial.available()) { 

  Servo1.write(90);
  char command = BTSerial.read(); 

    // Move forward
    if (command == 'w') {
      analogWrite(enablePinA, 255);
      analogWrite(enablePinB, 255); 
      digitalWrite(in1Pin, HIGH);
      digitalWrite(in2Pin, LOW);
      digitalWrite(in3Pin, HIGH);
      digitalWrite(in4Pin, LOW);
      delay(3000);
    }
      // Move backward 
    else if (command == 's') { 
      analogWrite(enablePinA, 255);
      analogWrite(enablePinB, 255);
      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, HIGH);
      digitalWrite(in3Pin, LOW);
      digitalWrite(in4Pin, HIGH);

      delay(3000);
    }
    
    // Moving Left
    else if (command == 'a'){
      analogWrite(enablePinA, 255);
      analogWrite(enablePinB, 255);
      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, HIGH);
      digitalWrite(in3Pin, HIGH);
      digitalWrite(in4Pin, LOW);

      delay(3000);
    }

        // Moving RIGHT
    else if (command == 'd'){
      analogWrite(enablePinA, 255);
      analogWrite(enablePinB, 255);
      digitalWrite(in1Pin, HIGH);
      digitalWrite(in2Pin, LOW);
      digitalWrite(in3Pin, LOW);
      digitalWrite(in4Pin, HIGH);

      delay(3000);
    }
    // SERVO
    else if (command == 'p'){
      Serial.println("MOVE SERVO");
      Servo1.write(-135);
      delay(3000);

      //Servo1.write(90);
    }
    // stop

    else {
      Serial.println("STOP MOVING");
      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, LOW);
      digitalWrite(in3Pin, LOW);
      digitalWrite(in4Pin, LOW);

      analogWrite(enablePinA, 0);
      analogWrite(enablePinB, 0);
      delay(1000);
      Serial.println("Motor turned on!"); // print message to indicate motor is turned on
}
}

}
