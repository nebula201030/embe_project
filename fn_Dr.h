#include "Dr_machine.h"

int SPI_COMMAND(unsigned char cCMD){
    unsigned char T_high_byte, T_low_byte;

    digitalWrite(chipSelectPin , LOW); // SCE Low Level 
    delayMicroseconds(10); // delay(10us) 
    SPI.transfer(cCMD); // transfer 1st Byte 
    delayMicroseconds(10); // delay(10us) 
    T_low_byte = SPI.transfer(0x22); // transfer 2nd Byte 
    delayMicroseconds(10); // delay(10us) 
    T_high_byte = SPI.transfer(0x22); // transfer 3rd Byte 
    delayMicroseconds(10); // delay(10us) 
    digitalWrite(chipSelectPin , HIGH); // SCE High Level 

    return (T_high_byte<<8 | T_low_byte); // 온도값 return 
}

ISR(TIMER1_OVF_vect){   //interrupt service routine(Timer1 overflow)
    TCNT1 = 34286;      //preload timer :never change
    Timer1_Flag = 1;    //Timer 1 Set Flag
}

void Timer1_Init(void){
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 34286;
    TCCR18 |= (1<<CS12);
    TIMSK1 |= (1<<TOIE1);
}