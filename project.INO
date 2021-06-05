// 온도 측정 센서
#include "fn_Dr.hs"


void setup(){
    digitalWirte(chipSelectPin,HIGH);
    pinMode(chipSelectPin,OUTPUT);
    SPI.setDataMode(SPI_MODE3);
    SPI.setClockDivider(SPI_CLOCK_DIV16);
    SPI.setBitOrder(MSBFIRST);
    SPI.begin();

    delay(500);
    Timer1_Init();
    Serial.begine(9600);
    interrupts();
}

void loop(){
    if(Timer1_Flag){ // 500ms 마다 반복 실행(Timer 1 Flag check) 
        iOBJECT= SPI_COMMAND(OBJECT); // 대상 온도 Read 
        delayMicroseconds(10); // delay(10us) 
        iSENSOR = SPI_COMMAND(SENSOR); // 센서 온도 Read 

        Serial.print("Object Temp : "); // 하이퍼터미널 출력 
        Serial.print(float(iOBJECT)/100, 2); 
        Serial.print(" Sensor Temp : "); 
        Serial.println(float(iSENSOR)/100, 2); 
    }
}