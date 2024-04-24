#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <RadioLib.h>

#define LoRa_MOSI 11
#define LoRa_MISO 12
#define LoRa_SCK 14
#define LoRa_nss 13
#define LoRa_dio0 3
#define LoRa_rst 2

SX1278 radio = new Module(13, 3, 2);

void setup(){
  Serial.begin(9600);


  // initialize SX1262 with default settings
  if (radio.begin() != RADIOLIB_ERR_NONE){
    Serial.print("Failed to connect");
  }
}


void loop(){
  int state = radio.transmit("Hello World!");
  if(state == RADIOLIB_ERR_TX_TIMEOUT) Serial.println("timeOut");
}