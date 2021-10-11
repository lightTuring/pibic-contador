#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

int limit = 0;
int la = 0, lb = 0;
int count = 0;
char id[] = "MotoGWiFiZ";
char pass[] = "conectaufpe2016";
WiFiClient client;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void updated();
void show();
void setCount();

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();
  ThingSpeak.begin(client);
  
  lcd.setCursor(0,0);
  lcd.print("Conectando:");
  
  WiFi.begin(id, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  
  setCount();
  
  lcd.clear();
 
  lcd.setCursor(0,0);
  lcd.print("Pessoas: ");
}

void loop() {
  updated();
  while (la == limit) {
    delay(10);
    updated();
    if(la != limit && lb == limit) {
      count++;
      show();
      setCount();
    }
  }
  while (lb == limit) {
    delay(10);
    updated();
    if(lb != limit && la == limit) {
      (count == 0) ? count : count--;
      show();
      setCount();
    }
  }
  delay(10);
}

void updated() {
  la = digitalRead(D8);
  lb = digitalRead(D2);
}

void show() {
  
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.printf("pessoas: %d", count);
   
}

void setCount() {
  ThingSpeak.writeField(1183027, 1, count, "LZ3FSO5YX2MPY4WQ");
}
/*
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
}*/
