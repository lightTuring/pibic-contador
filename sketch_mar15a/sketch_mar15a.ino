#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int a = D5;
int b = D7;
int stateA = 0;
int stateB = 1;
int limit = 150;
int la = 0, lb = 0;
int r = A0;
char stra[20]; 
char strb[20];

void change();
void updated();
void show();

void setup()
{
  lcd.begin();
  lcd.setCursor(0,0);
  pinMode(b, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(r, INPUT);
}

void loop() {  
  updated();
  show();
  delay(200);
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

void show() {
   lcd.clear();
   sprintf(stra, "%d", la);
   sprintf(strb, "%d", lb);
   lcd.setCursor(0,0);
   lcd.print("A: ");
   lcd.print(stra);
   lcd.setCursor(0,1);
   lcd.print("B: ");
   lcd.print(strb);   
}
