#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <Ultrasonic.h>
WiFiClient client;
LiquidCrystal_I2C lcd(0x27, 16, 2);

int count = 0;
int a = D5; //echo de B
int b = D6; //trig de B
int c = D10; //trig de A
int d = D11; //echo de A
int limit = 30;
int la = 0, lb = 0;
//char id[] = "Galaxy A11b53c";
//char pass[] = "mtng6618";
char str[20]; 
Ultrasonic u1(d, c);//A
Ultrasonic u2(b, a);//B

void updated();
void setCount(int);
void show(int);

void setup()
{
  lcd.begin();
  //ThingSpeak.begin(client);
  sprintf(str, "%d", count);
  lcd.setCursor(0,0);
  lcd.print("Conectando:");
  Serial.begin(9600);
  Serial.println();
  
  /*WiFi.begin(id, pass);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());*/
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  //setCount(0);
  Serial.println(count);
  show(count);
}

void loop() {  
  updated();
  while (la < limit) {
    delay(1);
    updated();
    if(la > limit && lb < limit) {
      count++;
      Serial.println(count);
      show(count);
      //setCount(count);
    }
  }
  while (lb < limit) {
    delay(1);
    updated();
    if(lb > limit && la < limit) {
      count--;
      Serial.println(count);
      show(count);
      //setCount(count);
    }
  }
  delay(1);
}

void updated() {
  la = u1.read(); 
  delayMicroseconds(100);
  lb = u2.read();
  Serial.printf("la = %d\n lb = %d\n", la, lb);
  delayMicroseconds(100);
  if (la < limit) {digitalWrite(D0, HIGH);}
  else {digitalWrite(D0, LOW);}
  if(lb < limit) {digitalWrite(D1, HIGH);}
  else {digitalWrite(D1, LOW);}
}

void show(int i) {
   lcd.clear();
   sprintf(str, "%d", count);
   lcd.setCursor(0,0);
   lcd.print("Pessoas: ");
   lcd.print(str);
}
/*
void setCount(int i) {
  ThingSpeak.writeField(1183027, 1, count, "LZ3FSO5YX2MPY4WQ");
}*/
