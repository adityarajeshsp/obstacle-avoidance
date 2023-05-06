#include <AFMotor.h>
#include <Adafruit_MotorShield.h>
#include <AFMotor.h> // Include the AFMotor library
#include <Servo.h>   // Include the Servo library

#define trigPin 10   // Define the trig pin of the ultrasonic sensor
#define echoPin 11   // Define the echo pin of the ultrasonic sensor

AF_DCMotor motor1(1); // Create an instance of the first motor on channel 1
AF_DCMotor motor2(2); // Create an instance of the second motor on channel 2
Servo servo;          // Create an instance of the servo motor

void setup() {
  pinMode(trigPin, OUTPUT); // Set the trig pin as output
  pinMode(echoPin, INPUT);  // Set the echo pin as input
  servo.attach(9);          // Attach the servo to pin 9
  Adafruit_MotorShield AFMS = Adafruit_MotorShield();   // Initialize the motor driver
}

void loop() {
  int distance = measureDistance();  // Measure the distance to the nearest obstacle
  if (distance < 30) {               // If there is an obstacle within 30 cm
    motor1.run(RELEASE);             // Stop the first motor
    motor2.run(RELEASE);             // Stop the second motor
    servo.write(90);                 // Set the servo to look forward
  } else {                           // If there is no obstacle
    motor1.setSpeed(150);            // Set the speed of the first motor to 150 (out of 255)
    motor1.run(FORWARD);             // Set the direction of the first motor to forward
    motor2.setSpeed(150);            // Set the speed of the second motor to 150 (out of 255)
    motor2.run(FORWARD);             // Set the direction of the second motor to forward
    if (distance > 60) {             // If the obstacle is far away
      servo.write(0);                // Turn the servo to the left
    } else {                         // If the obstacle is close
      servo.write(180);              // Turn the servo to the right
    }
  }
  delay(1000);  // Wait for 50ms
}

int measureDistance() {
  digitalWrite(trigPin, LOW);   // Set the trig pin to low for 2 us
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);  // Set the trig pin to high for 10 us
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);   // Set the trig pin to low
  
  long duration = pulseIn(echoPin, HIGH);  // Measure the duration of the echo pulse
  int distance = duration * 0.034 / 2;     // Convert the duration to distance in cm
  return distance;                         // Return the distance
}
