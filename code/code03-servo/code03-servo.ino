#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <RadioLib.h>
#include <Servo.h>

#define servoPin 15

Servo servo;


void setup(){
  Serial.begin(9600);
  servo.attach(servoPin);
}

void loop(){
  servo.write(60);
}