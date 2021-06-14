#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <Ultrasonic.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int count = 0;
int a = D5; //echo de B
int b = D6; //trig de B
int c = D10; //trig de A
int d = D11; //echo de A
int la = 0, lb = 0;
Ultrasonic u1(d, c);//A
Ultrasonic u2(b, a);//B

void setup()
{
  Serial.begin(9600);
}

void loop() { 
   Serial.printf("A: %d\n", u2.read());
   delay(100);
}
