int l1 = D2;
int l2 = D8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  Serial.printf("%d", digitalRead(l1));
  Serial.println(" ");
  Serial.printf("%d", digitalRead(l2));
  Serial.println(" ");
}
