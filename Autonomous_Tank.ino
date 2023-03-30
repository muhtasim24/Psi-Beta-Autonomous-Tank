#include <Servo.h>      // library for Servo
#include <SoftwareSerial.h>     //  library for Bluetooth module

SoftwareSerial BTSerial(0, 1); // RX, TX pins of HC-05 Bluetooth module 
// RX for receiving 
// TX for transmitting

//  L298N Motor Driver #1 pin definitions
int enablePinA = 6; // PWM pin for controlling motor1 speed
int in1Pin = 8;    // input pin 1 for motor1 direction
int in2Pin = 9;    // input pin 2 for motor1 direction

int enablePinB = 7;   // PWM pin for controlling motor2 speed
int in3Pin = 10;   // input pin 3 for Motor2 Direction
int in4Pin = 11;   // input pin 4 for Motor2 Direction

int servoPin = 12; // pin to control servo 
Servo Servo1;

//  L298N Motor Driver #2 pin definitions
int enablePinC = 5;   //  PWM pin for controlling load motor speed
int in5Pin = 4;    // input pin 1 for positive side of load motor 
int in6Pin = 3;    // input pin 2 for negative side of load motor

void setup() {
  Serial.begin(9600); // initialize serial Baud Rate
  BTSerial.begin(9600);  // initialize bluetooth Baud Rate
  //  Baud Rate = Rate at which information travels in communication, 9600 bits per second
  // Initialize All the pins 
  pinMode(enablePinA, OUTPUT);
  pinMode(enablePinB, OUTPUT);
  pinMode(enablePinC, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  pinMode(in5Pin, OUTPUT);
  pinMode(in6Pin, OUTPUT);
  Servo1.attach(servoPin);
}

void loop() {
  if (BTSerial.available()) { // Has to check for bluetooth connection before arduino can take any commands
    Servo1.write(90);       // Initialize servo angle 

    char command = BTSerial.read();     // A variable to store the commands we will send to the Bluetooth module
    Serial.print("Received command: ");   //  print what command its recieving
    Serial.println(command);  //  display command key

    // Move forward
    if (command == 'W') {       
      Serial.println("Moving forward"); //  print what command its carrying out
      Servo1.write(90); //  intial servo angle
      analogWrite(enablePinA, 255);   // the Enable Pins control the speed of the motors, we made it max speed
      analogWrite(enablePinB, 255);   // the Enable Pins control the speed of the motors, we made it max speed

      // One pin is HIGH AND LOW so then electricity can flow one direction from pin1 to 2 or 2 to 1
      //  both motors spin in opposite directions of each other to move forward
      digitalWrite(in1Pin, HIGH);     // Turning on Pin 1 of Motor 1 
      digitalWrite(in2Pin, LOW);      // Turning off Pin 2 of Motor 1


      digitalWrite(in3Pin, LOW);     // Turning On Pin3 of Motor 2
      digitalWrite(in4Pin, HIGH);      // Turning on Pin4 of Motor 2
      delay(1000);      //  wait 1 second before accepting next command
    }

    // Move backward 
    else if (command == 'S') {      // Command to move backward
      Servo1.write(90);
      Serial.println("Moving backward");  //  print what command its carrying out
      analogWrite(enablePinA, 255); //  setting motors to run at max speed
      analogWrite(enablePinB, 255);
      //both moth spin in opposite directions of each other, reversed of 'W', to move backward
      digitalWrite(in1Pin, LOW);    // Turning Off Pin1 of Motor 1
      digitalWrite(in2Pin, HIGH);   // Turning On Pin2 of Motor 1

      digitalWrite(in3Pin, HIGH);    // Turning Off Pin 3 of Motor 2
      digitalWrite(in4Pin, LOW);   // Turning ON PIN 4 of Motor 2
      delay(1000);    //  wait 1 second before accepting next command
    }
// Moving Left
    else if (command == 'A') {      // Command to move left
      Servo1.write(90);
      Serial.println("Moving left");  //  print what command its carrying out
      analogWrite(enablePinA, 255); //  setting motors to run at max speed
      analogWrite(enablePinB, 255);

      // Need motors turning in same direction to turn left

      digitalWrite(in1Pin, HIGH);
      digitalWrite(in2Pin, LOW);

      digitalWrite(in3Pin, HIGH);
      digitalWrite(in4Pin, LOW);
      delay(1000);    //  wait 1 second before accepting next command
    }
    // Moving Right
    else if (command == 'D') {
      Servo1.write(90);
      Serial.println("Moving right"); //  print what command its carrying out
      analogWrite(enablePinA, 255);
      analogWrite(enablePinB, 255);

      // Need motors turning in same direction, reversed of 'A', to turn right

      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, HIGH);

      digitalWrite(in3Pin, LOW);
      digitalWrite(in4Pin, HIGH);
      delay(1000);  //  wait 1 second before accepting next command
    }
    // SERVO
    else if (command == 'P') {    // Command to turn the servo, this will press the trigger of the nerf gun
      Servo1.write(90);
      Serial.println("Firing Weapon");  //  print what command its carrying out
      Servo1.write(-90);       // We mounted it this way so it starts at 90 degress and when command P is sent, it goes to -90 degress to push the trigger, then back to starting position of 90 degrees
      delay(500); // wait half a second to turn servo back
      Serial.println("Releasing Weapon"); //debugging purposes
      Servo1.write(90);
    }
    else if (command == 'L') {
      Servo1.write(90);
      analogWrite(enablePinC, 255);

      Serial.println("Loading Weapon"); //  print what command its carrying out
      digitalWrite(in5Pin, LOW);
      digitalWrite(in6Pin, HIGH);
      delay(5000); // spin motor for 4.6 seconds to complete 1 full rotation to load gun
      //delay(100); //  debugging purposes
      digitalWrite(in5Pin, LOW);
      digitalWrite(in6Pin, LOW);
    }
    else if (command == 'H') {
      Servo1.write(90);
      Serial.println("Stop moving");  //  print what command its carrying out
      digitalWrite(in1Pin, LOW);    // LOW TURNS OFF THE PINS
      digitalWrite(in2Pin, LOW);
      digitalWrite(in3Pin, LOW);
      digitalWrite(in4Pin, LOW);
      digitalWrite(in5Pin, LOW);
      digitalWrite(in6Pin, LOW);
      analogWrite(enablePinA, 0);   // SETTING THE SPEED OF THE MOTORS TO 0
      analogWrite(enablePinB, 0);
      analogWrite(enablePinC, 0);
      delay(1000);  //  wait 1 second before accepting next command
    }

    // Stop
    else {      // If NO COMMAND IS SENT, THE TANK WILL STOP
      Servo1.write(90);
      Serial.println("Stop moving");  //  print what command its carrying out
      digitalWrite(in1Pin, LOW);    // LOW TURNS OFF THE PINS
      digitalWrite(in2Pin, LOW);
      digitalWrite(in3Pin, LOW);
      digitalWrite(in4Pin, LOW);
      digitalWrite(in5Pin, LOW);
      digitalWrite(in6Pin, LOW);
      analogWrite(enablePinA, 0);   // SETTING THE SPEED OF THE MOTORS TO 0
      analogWrite(enablePinB, 0);
      analogWrite(enablePinC, 0);
      delay(1000);  //  wait 1 second before accepting next command
    }
  }
}
