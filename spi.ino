#include<SPI.h> 
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define TRIG 9
#define ECHO 8
#define speaker 7

int song[ ] = { NOTE_G4, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_G4, 0, // ???????????????(??????)
NOTE_G4, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_A4, 0, // ???????????????(??????)
NOTE_A4, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_B4, 0, // ???????????????(??????)
NOTE_G5, NOTE_G5, NOTE_F5, NOTE_D5, NOTE_E5, NOTE_C5, 0 }; // ??????????????????(??????)

int time[ ] = { 250, 250, 250, 250, 750, 250, // 8????????? = 250ms
250, 250, 250, 250, 750, 250,
250, 250, 250, 250, 750, 250,
250, 250, 250, 250, 500, 250, 250 };

#define OBJECT 0xA0 // ?????? ?????? ????????? 
#define SENSOR 0xA1 // ?????? ?????? ????????? 
const int chipSelectPin = 10; 
unsigned char Timer1_Flag = 0;; 
int iOBJECT, iSENSOR; // ?????? 2byte ?????? ?????? ???
void setup() { 
 /* Setting SCE & SPI */ 
digitalWrite(chipSelectPin , HIGH); // SCE High Level 
pinMode(chipSelectPin , OUTPUT); // SCE OUTPUT Mode 
 SPI.setDataMode(SPI_MODE3); // SPI Mode 
 SPI.setClockDivider(SPI_CLOCK_DIV16); // 16MHz/16 = 1MHz 
 SPI.setBitOrder(MSBFIRST); // MSB First 
SPI.begin(); // Initialize SPI 
delay(500); // Sensor initialization time 
Timer1_Init(); // Timer1 setup : 500ms(2Hz) interval 
Serial.begin(9600); 
interrupts(); // enable all interrupts 
} 
int SPI_COMMAND (unsigned char cCMD){ 
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
 
 return (T_high_byte<<8 | T_low_byte); // ????????? return 
} 
ISR(TIMER1_OVF_vect) { // interrupt service routine (Timer1 overflow) 
 TCNT1 = 34286; // preload timer : ??? ?????? ????????? ?????????. 
 Timer1_Flag = 1; // Timer 1 Set Flag 
}
void Timer1_Init(void){ 
 TCCR1A = 0; 
 TCCR1B = 0; 
 TCNT1 = 34286; // preload timer 65536-16MHz/256/2Hz 
 TCCR1B |= (1 << CS12); // 256 prescaler 
 TIMSK1 |= (1 << TOIE1); // enable timer overflow interrupt 
} 
void loop() {

if(Timer1_Flag){ // 500ms ?????? ?????? ??????(Timer 1 Flag check) 
 iOBJECT= SPI_COMMAND(OBJECT); // ?????? ?????? Read 
 delayMicroseconds(10); // delay(10us) 
 iSENSOR = SPI_COMMAND(SENSOR); // ?????? ?????? Read 
Serial.print("Object Temp : "); // ?????????????????? ?????? 
 Serial.print(float(iOBJECT)/100); 
 Serial.print(" Sensor Temp : "); 
 Serial.println(float(iSENSOR)/100, 2); 
tone (speaker,500,100);
delay(1000);
if((iOBJECT)/100 > 37)
{
  Serial.print("the value of temp is :");
  Serial.print((iOBJECT)/100);
  Serial.print("\n");
  int i;
pinMode(speaker, OUTPUT); // PIEZO ???????????? ??????
delay(100); // ????????? ?????? 0.1????????? ?????? ??????
for (i=0; i<25; i++) // ?????? ???????????? ?????? ??????
{
tone(speaker, song[i], time[i]); // ??????????????? ?????? ??????
delay(time[i]);
}
  delay(3000);
  }

 } 
}
