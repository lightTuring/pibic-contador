#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <ThingSpeak.h>
WiFiClient client;
LiquidCrystal_I2C lcd(0x27, 16, 2);

int count = 0;
int a = D5;
int b = D7;
int stateA = 0;
int stateB = 1;
int limit = 220;
int la = 0, lb = 0;
int r = A0;
//char id[] = "Galaxy A11b53c";
//char pass[] = "mtng6618";
char str[20]; 

void change();
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
  Serial.begin(115200);
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

  pinMode(b, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(r, INPUT);
  //setCount(0);
  Serial.println(count);
  show(count);
}

void loop() {  
  updated();
  while (la < limit) {
    delay(20);
    updated();
    if(la > limit && lb < limit) {
      count++;
      Serial.println(count);
      show(count);
      //setCount(count);
    }
  }
  while (lb < limit) {
    delay(20);
    updated();
    if(lb > limit && la < limit) {
      count--;
      Serial.println(count);
      show(count);
      //setCount(count);
    }      
  }
  delay(20);
}

void change(){
  if(stateB && !stateA) {
    stateB = !stateB;
    stateA = !stateA;
    digitalWrite(b, LOW);
    digitalWrite(a, HIGH);
  }
  else if(stateA && !stateB) {
    stateB = !stateB;
    stateA = !stateA;
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
  }
}

void updated() {
  change();
  //stateB = 0; stateA = 1; a medição é de A
  int x = analogRead(r);
  la = x;   
  change();
  //stateB = 1; stateA = 0; a medição é de B
  x = analogRead(r);
  lb = x;  
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
