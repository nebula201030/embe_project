#include <SPI.h> //설치 필요
#include <DHT.11>
#include <LiquidCrystal_i2c.h
//#include <Wire.h>

#define OBJECT 0xA0 // 대상 온도 커맨드 
#define SENSOR 0xA1 // 센서 온도 커맨드 
#define dht11 A1 //온습도 핀 설정
#define TRIG 9
#define ECHO 8

LiquidCrustal_I2C lcd(0x3F,16,2);

const int chipSelectPin = 10; 
unsigned char Timer1_Flag = 0;; 
int iOBJECT, iSENSOR; // 부호 2byte 온도 저장 변수

void setup() { 
 /* Setting SCE & SPI */ 
    //Wire.begin
    pinMode(TRIG,OUTPUT);
    pinMode(ECHO,INPUT);
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
    lcd.init();
    lcd.backlight();
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
    return (T_high_byte<<8 | T_low_byte); // 온도값 return 
} 
ISR(TIMER1_OVF_vect) { // interrupt service routine (Timer1 overflow) 
    TCNT1 = 34286; // preload timer : 이 값을 바꾸지 마세요. 
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
    if(Timer1_Flag){ // 500ms 마다 반복 실행(Timer 1 Flag check) 
        iOBJECT= SPI_COMMAND(OBJECT); // 대상 온도 Read 
        delayMicroseconds(10); // delay(10us) 
        iSENSOR = SPI_COMMAND(SENSOR); // 센서 온도 Read 
        Serial.print("Object Temp : "); // 하이퍼터미널 출력 
        Serial.print(float(iOBJECT)/100, 2); 
        Serial.print(" Sensor Temp : "); 
        Serial.println(float(iSENSOR)/100, 2);        
    } 

    int i;
    float humi. temp;
    if((i = dht11.read(humi, temp))==0){
        Serial.print(humi);
        Serial.print(temp);
    }
    else{
        Serial.print("Error");
    }

    int value = random(0,3);

    if(value == 0){
        lcd.setCursor(0,0);
        lcd.print("ready...");
    }

    else if (value == 1){
        lcd.setCursor(0,1);
        lcd.print("helloworld");
    }
    else if (value == 2){
        lcd.setCursor(0,0);
        lcd.print("ready...");
        lcd.setCursor(0,1);
        lcd.print("hello world");
    }
    delay(1000);
    lcd.clear();

    long duration,distance;

    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    duration - puleIn(ECHO,HIGH);
     //물체에 반사되어돌아온 초음파의 시간을 변수에 저장합니다.
    //34000*초음파가 물체로 부터 반사되어 돌아오는시간 /1000000 / 2(왕복값이아니라 편도값이기때문에 나누기2를 해줍니다.)
     //초음파센서의 거리값이 위 계산값과 동일하게 Cm로 환산되는 계산공식 입니다. 수식이 간단해지도록 적용했습니다.
    distance = duration * 17 / 1000; 
    delay (1000);
    
    // byte error,address;
    // int nDevices;
    // Serial.PrintLn("Scanning..");
    // nDevicec = 0;
    // for(address=1;address<127;address++)
    // {
    //     Wire.begineTransmission(address);
    //     error = Wire.endTransmission();

    //     if(error == 0)
    //     {
    //         Serial.print("ready...");
    //         if(address<16)
    //             Serial.print("0");
    //         Serial.print(address,HEX);
    //         Serial.println("!");
    //         nDevices++;
    //     }
    //     else if(error == 4)
    //     {
    //         Serial.print("ready...");
    //         if(address < 16)
    //             Serial.print("0");
    //         Serial.println(address,HEX);
    //     }
    // }

    // if(nDevices == 0)
    //     Serial.println("read...");
    // else
    //     Serial.println("done\n");
    // delay(5000);
}