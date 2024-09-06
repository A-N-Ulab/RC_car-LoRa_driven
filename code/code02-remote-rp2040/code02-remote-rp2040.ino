/* 
Transmiter/remote's code for ANUlab's RC car mode
6.05.2024 - v1 by ANUlab&Glinek
Copyright(C)2024 www.github.com/A-N-Ulab 
*/

//--- Inculde libraries ---
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <RadioLib.h>

//--- Pin definitions for SX1278 LoRa module ---
#define LoRa_MOSI 11
#define LoRa_MISO 12
#define LoRa_SCK 14
#define LoRa_nss 13
#define LoRa_dio0 3
#define LoRa_rst 2

//--- Pin definitions for joystick and button ---
#define xPin 26
#define yPin 27
#define swPin 8

//--- creating radio object ---
SX1278 radio = new Module(13, 3, 2); 

//--- Value declarations ---
int analogReadX, analogReadY, fixedX, fixedY, valSw;
String sendValues;


void setup(){
  Serial.begin(9600); //Serial for debugging 

  //--- piModes ---
  pinMode(xPin, INPUT); //joystick X
  pinMode(yPin, INPUT); //joystick Y
  pinMode(swPin, INPUT_PULLUP); //joystick SW

  //--- initialize SX1262 with default settings, print if unable to connect ---
  if (radio.begin() != RADIOLIB_ERR_NONE){
    Serial.print("Failed to connect");
  }
}
void loop(){
  //==== Operations on analog pins ====
  //|
  //--- Reading X and Y values ---
  analogReadX = analogRead(xPin);
  analogReadY = analogRead(yPin);
  //|
  //--- Mapping pins to values from -500 to 500
  fixedX = map(analogReadX, 0, 1023, -500, 500);
  fixedY = map(analogReadY, 0, 1023, -500, 500);
  
  //--- Reading value of button ---
  valSw = digitalRead(swPin); 

  //--- Concatenating values into one string for sending
  sendValues = '[' + String(fixedX) + ',' + String(fixedY) + ',' + String(valSw) + ']'; 

  //--- Sending string of values, if LoRa timeout print it ---
  int state = radio.transmit(sendValues);
  if(state == RADIOLIB_ERR_TX_TIMEOUT) Serial.println("timeOut");
}