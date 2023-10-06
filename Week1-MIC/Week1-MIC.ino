int ledOne, ledTwo, ledThree, ledFour, ledFive, ledSix;

void setup() {
  // put your setup code here, to run once:
  ledOne = 13;
  ledTwo = 12;
  ledThree = 11;
  ledFour = 10;
  ledFive = 9;
  ledSix = 8;

  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
  pinMode(ledThree, OUTPUT);
  pinMode(ledFour, OUTPUT);
  pinMode(ledFive, OUTPUT);
  pinMode(ledSix, OUTPUT);

  Serial.begin(9600);
  Serial.println("Frieda Artz Lopez");
  Serial.println("2127357");
  Serial.println("Week 1. basics");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledOne, HIGH);
  delay(100);
  digitalWrite(ledOne, LOW);
  digitalWrite(ledTwo, HIGH);
  delay(100);
  digitalWrite(ledTwo, LOW);
  digitalWrite(ledThree, HIGH);
  delay(100);
  digitalWrite(ledThree, LOW);
  digitalWrite(ledFour, HIGH);
  delay(100);
  digitalWrite(ledFour, LOW);
  digitalWrite(ledFive, HIGH);
  delay(100);
  digitalWrite(ledFive, LOW);
  digitalWrite(ledSix, HIGH);
  delay(100);
  digitalWrite(ledSix, LOW);
}
