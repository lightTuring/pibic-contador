#include <LiquidCrystal_I2C.h>

int s[] = {D1, D2, D6, D7}; 
int reader = A0;
int limit = 100;
int la = 0, lb = 0;
int count = 0;
//char id[] = "Galaxy A11b53c";
//char pass[] = "mtng6618";
char str[20]; 

LiquidCrystal_I2C lcd(0x27, 20, 4);

void updated();
void setCount(int);
void pins(int);
void show(int);
int outp(int);

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();
  /*
  lcd.begin();
  //ThingSpeak.begin(client);
  sprintf(str, "%d", count);
  lcd.setCursor(0,0);
  lcd.print("Conectando:");*/
  for (int i = 0; i<4; i++) {
    pinMode(s[i], OUTPUT);
  }
  pinMode(reader, INPUT);
  
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
  //setCount(0);
}

void loop() {
  updated();
  while (la < limit) {
    delay(10);
    updated();
    if(la > limit && lb < limit) {
      count++;
      show(count);
      //setCount(count);
    }
  }
  while (lb < limit) {
    delay(10);
    updated();
    if(lb > limit && la < limit) {
      count--;
      show(count);
      //setCount(count);
    }
  }
  delay(10);
}

void updated() {
  la = outp(0);
  lb = outp(1);
}

void show(int i) {
   lcd.clear();
   sprintf(str, "%d", count);
   lcd.setCursor(0,0);
   lcd.print("Pessoas: ");
   lcd.print(str);   
}
//x in [0, 15]
void pins (int x) {
  x = (x > 15 || x<0) ? 0 : x;
  for (int i = 0; i<4; i++) {
    digitalWrite(s[i], (x % 2));
    x = (x >> 1);
  }   
}

int outp(int x) {
  pins(x);
  return (analogRead(reader));
}

/*
void setCount(int i) {
  ThingSpeak.writeField(1183027, 1, count, "LZ3FSO5YX2MPY4WQ");
}*/
