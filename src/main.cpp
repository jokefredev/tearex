#include <Arduino.h>
#include <Stepper.h>
// #include <Servo.h>

// Servo myservo;  // create servo object to control a servo
// // twelve servo objects can be created on most boards

// int pos = 0;    // variable to store the servo position

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor
bool phaseOneFinished = false;
bool phaseTwoFinished = false;
int stepHistory = 0;
int dcHistory = 0;

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void startMotor(int motor) {

    if (!phaseTwoFinished) {
      switch(motor){
        case 1:
            myStepper.step(stepsPerRevolution);
            stepHistory++;
          break;
        case 2:
            digitalWrite(3, HIGH);
            delay(2000);
            digitalWrite(3, LOW);
            dcHistory++;
          break;
        default:
          break;
      }
    }
}

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(99); // topspeed = 99
  // initialize the serial port:
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  // myservo.attach(12);  // attaches the servo on pin 9 to the servo object
}

void loop() {

  if (stepHistory >= 80) {
    phaseOneFinished = true;
  }
  if (dcHistory >= 1) {
    phaseTwoFinished = true;
  }

  if (!phaseOneFinished) {
    startMotor(1);
  } else {
    startMotor(2);
  }

}
