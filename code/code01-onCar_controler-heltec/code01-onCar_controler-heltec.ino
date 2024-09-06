/* 
 * Reciver/car's code for ANUlab's RC car mode
 * 
 * Copyright(C)2024 www.github.com/A-N-Ulab 
 */

//--- Inculde libraries ---
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <RadioLib.h>
#include <Servo.h>

//--- Pin definitions for SX1278 LoRa module ---
#define LoRa_MOSI 11
#define LoRa_MISO 12
#define LoRa_SCK 13
#define LoRa_nss 10
#define LoRa_dio0 3
#define LoRa_rst 4

//--- Define other pins ---
#define servo_pin 9
#define enable 8
#define forward 5
#define backward 6

//--- creating radio object ---
//SPISettings spiSettings(2000000, MSBFIRST, SPI_MODE0);
SX1278 radio = new Module(LoRa_nss, LoRa_dio0, LoRa_rst); 

//--- create servo object ---
Servo servoMotor;

//--- Value declarations ---
int x, y, bt, state;
String data;
int servoAngle, pwmFill;

void setup(){
    //--- Basic init ---
    Serial.begin(9600);

    //--- Servo init ---
    servoMotor.attach(servo_pin);  //Attach servo to pin

    //--- Initialize H-bridge pins ---
    pinMode(forward, OUTPUT);
    pinMode(backward, OUTPUT);
    pinMode(enable, OUTPUT);

    radio.begin();
}

void loop(){
    //==== read data from remote ====
    state = radio.receive(data);

    //==== If no error got from trying to read data, decode it and control the car. If error got print it ====
    if (state == RADIOLIB_ERR_NONE) {
        //--- Converting recived data to usable data ---
        convertData(data);
        //|
        //--- Turning right and left ---
        servoAngle = map(y, -500, 500, 110, 10);
        servoMotor.write(servoAngle);
        //|
        //--- Moving forward and backward ---
        pwmFill = map(x, -500, 500, -255, 255);
        if(x > 15){
            digitalWrite(enable, HIGH);
            analogWrite(forward, pwmFill);
            analogWrite(backward, 0);
        }
        else if(x < -15){
            digitalWrite(enable, HIGH);
            analogWrite(backward, abs(pwmFill));
            analogWrite(forward, 0);
        }
        else{
            digitalWrite(enable, LOW);
            analogWrite(forward, 0);
            analogWrite(backward, 0);
        }

        Serial.print(x);
        Serial.print(' ');
        Serial.println(y);
    }
    //else if(state == RADIOLIB_ERR_RX_TIMEOUT) errorMsg = "et";
}

void convertData(String data){
    /*Function used to convert recived string of values into a usable global variables X, Y, BT*/
    //--- Value declarations ---
    String strFixed, xStr, yStr, btStr;
    int endString, begString = 0, commaIndex1, commaIndex2;

    //==== String processing ====
    //--- remove [] from both ends of string
    endString = data.length(); 
    strFixed = data.substring(1, endString-1);
    //|
    //--- Read x value ---
    commaIndex1 = strFixed.indexOf(',');
    xStr = strFixed.substring(0, commaIndex1);
    strFixed = strFixed.substring(commaIndex1+1);
    x = xStr.toInt();
    //|
    //--- Read y value ---
    commaIndex2 = strFixed.indexOf(',');
    yStr = strFixed.substring(0, commaIndex2);
    y = yStr.toInt();
    //|
    //--- Read bt value ---
    btStr = strFixed.substring(commaIndex2+1);
    bt = btStr.toInt();
}
