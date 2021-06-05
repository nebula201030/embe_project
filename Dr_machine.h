#ifndef _DR_H_
#define _DR_H_

#include <SPI.h>
#include <DHT11>
#include <LiquidCrystal_I2c.h>

#define OBJECT 0xA0 // 대상 온도 커맨드 
#define SENSOR 0xA1 // 센서 온도 커맨드 
#define dht11 A1 //온습도 핀 설정
#define TRIG 9
#define ECHO 8

LiquidCrustal_I2C lcd(0x3F,16,2);
int iOBJECT, iSENSOR; // 부호 2byte 온도 저장 변수
const int chipSelectPin = 10; 
unsigned char Timer1_Flag = 0;; 

int iOBJECT, iSENSOR; // 부호 2byte 온도 저장 변수 
#endif