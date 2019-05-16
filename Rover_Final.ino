//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
// This sketch is a good place to start if you're just getting started with 
// Pixy and Arduino.  This program simply prints the detected object blocks 
// (including color codes) through the serial console.  It uses the Arduino's 
// ICSP SPI port.  For more information go here:
//
// https://docs.pixycam.com/wiki/doku.php?id=wiki:v2:hooking_up_pixy_to_a_microcontroller_-28like_an_arduino-29
//
  
#include <Pixy2.h>

//includes for motors
#include <Wire.h>
#include <Adafruit_MotorShield.h>

// This is the main Pixy object 
Pixy2 pixy;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1 and M2
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);

void setup()
{
  Serial.begin(9600);
  Serial.print("Starting...\n");

  AFMS.begin();  // create with the default frequency 1.6KHz

  pixy.init();

  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor1->setSpeed(25);
  myMotor2->setSpeed(25);
  myMotor1->run(FORWARD);
  myMotor2->run(FORWARD);
  // turn on motor
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
}

void loop()
{ 
  int i; 
  // grab blocks!
  pixy.ccc.getBlocks();

  myMotor1->run(FORWARD);
  myMotor2->run(FORWARD);
  
  // If there are blocks, print them!
  if (pixy.ccc.numBlocks)
  {
    //Serial.println("Object detected");

    uint8_t i;
  
    //myMotor->run(FORWARD);
    for (i=0; i<150; i++) {
      myMotor1->setSpeed(i); 
      myMotor2->setSpeed(i);  
      delay(4);
    }
  }
  else
  {
    Serial.print("tech");
    myMotor1->run(RELEASE);
    myMotor2->run(RELEASE);
    delay(1000);  
  }
}
