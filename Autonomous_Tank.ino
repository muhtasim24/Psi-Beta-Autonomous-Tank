#include <Servo.h>      // library for Servo
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(0, 1); // RX, TX pins of HC-05 Bluetooth module 
// RX for receiving 
// TX for transmitting

// L298N Motor Driver pin definitions
int enablePinA = 6; // PWM pin for controlling motor1 speed
int in1Pin = 8;    // input pin 1 for motor1 direction
int in2Pin = 9;    // input pin 2 for motor1 direction

int enablePinB = 7;   // PWM pin for controlling motor2 speed

int in3Pin = 4;   // input pin 3 for Motor2 Direction
int in4Pin = 5;   // input pin 4 for Motor2 Direction

int servoPin = 3; // pin to control servo 
Servo Servo1;

void setup() {
  Serial.begin(9600); // initialize serial communication
  BTSerial.begin(9600);  // initilize bluetooth Baud Rate -> frequency channel that it communicates

  // Initlize All the pins 
  pinMode(enablePinA, OUTPUT);
  pinMode(enablePinB, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  Servo1.attach(servoPin);
}

void loop() {
  if (BTSerial.available()) { // Has to check for bluetooth connection before arduino can take any commands
    Servo1.write(90);       // Initlize servo angle 

    char command = BTSerial.read();     // A variable to store the commands we will send to the Bluetooth module
    Serial.print("Received command: ");   
    Serial.println(command);

    // Move forward
    if (command == 'W') {       
      Serial.println("Moving forward");
      analogWrite(enablePinA, 255);   // the Enable Pins control the speed of the motors, we made it max speed
      analogWrite(enablePinB, 255);   // the Enable Pins control the speed of the motors, we made it max speed

      // One pin is HIGH AND LOW so then electricity can flow one direction from pin1 to 2 or 2 to 1
      digitalWrite(in1Pin, HIGH);     // Turning on Pin 1 of Motor 1 
      digitalWrite(in2Pin, LOW);      // Turning off Pin 2 of Motor 1


      digitalWrite(in3Pin, HIGH);     // Turning On Pin3 of Motor 2
      digitalWrite(in4Pin, LOW);      // Turning on Pin4 of Motor 2
      delay(3000);      // Putting a delay so the command lasts for 3 seconds 
    }

    // Move backward 
    else if (command == 'S') {      // Command to move backward
      Serial.println("Moving backward");
      analogWrite(enablePinA, 255);
      analogWrite(enablePinB, 255);

      digitalWrite(in1Pin, LOW);    // Turning Off Pin1 of Motor 1
      digitalWrite(in2Pin, HIGH);   // Turning On Pin2 of Motor 1

      digitalWrite(in3Pin, LOW);    // Turning Off Pin 3 of Motor 2
      digitalWrite(in4Pin, HIGH);   // Turning ON PIN 4 of Motor 2
      delay(3000);    // Delay to make the command last for 3 seconds before it stops
    }
// Moving Left
    else if (command == 'A') {      // Command to move left
      Serial.println("Moving left");  // Debugging purposes
      analogWrite(enablePinA, 255);
      analogWrite(enablePinB, 255);

      // Need motors turning in opposite directions to turn, One motor will move backwards, another moves foward 

      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, HIGH);

      digitalWrite(in3Pin, HIGH);
      digitalWrite(in4Pin, LOW);
      delay(3000);    // Delay to make the command last for 3 seconds before it stops
    }
    // Moving Right
    else if (command == 'D') {
      Serial.println("Moving right");
      analogWrite(enablePinA, 255);
      analogWrite(enablePinB, 255);

      // Need motors turning in opposite directions to turn, One motor will move backwards, another moves foward 

      digitalWrite(in1Pin, HIGH);
      digitalWrite(in2Pin, LOW);

      digitalWrite(in3Pin, LOW);
      digitalWrite(in4Pin, HIGH);
      delay(3000);
    }
    // SERVO
    else if (command == 'P') {    // Command to move the servo, this will press the trigger of the nerf gun
      Serial.println("Moving servo");
      Servo1.write(-135);       // We mounted it this way so it starts at 90 degress and when command P is sent, it goes to -135 degress to push the trigger
      delay(3000);
    }
    // Stop
    else {      // If NO COMMAND IS SENT, THE TANK WILL STOP
      Serial.println("Stop moving");
      digitalWrite(in1Pin, LOW);    // LOW TURNS OFF THE PINS
      digitalWrite(in2Pin, LOW);
      digitalWrite(in3Pin, LOW);
      digitalWrite(in4Pin, LOW);
      analogWrite(enablePinA, 0);   // SETTING THE SPEED OF THE MOTORS TO 0
      analogWrite(enablePinB, 0);
      delay(1000);
      Serial.println("Motor turned on!"); // print message to indicate motor is turned on
    }
  }
}
