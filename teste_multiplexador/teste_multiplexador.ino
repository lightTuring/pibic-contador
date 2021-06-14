int s[] = {D2, D3, D4, D5}; 
void pins (int);

void setup()
{
  for (int i = 0; i<4; i++) {
    pinMode(s[i], OUTPUT);
  }
  pinMode(D1, OUTPUT);
  pins(0);
  digitalWrite(D1, HIGH);
}

void loop() {
  delay(500);
  pins(1);
  delay(500);
  pins(0);
}

void pins (int x) {
  x = (x > 15 || x<0) ? 0 : x;
  for (int i = 0; i<4;i++) {
    digitalWrite(s[i], (x % 2));
    x = (x >> 1);
  }   
}
