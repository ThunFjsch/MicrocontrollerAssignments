#define MaxTries = 3;

// running light LEDS Pin Layout
const int ledOne = 13;
const int ledTwo = 12;
const int ledThree = 11;
const int ledFour = 10;
const int ledFive = 9;
const int ledSix = 8;

// Button Pin
const int inBuiltButton = 20;

// Secret pin
const long int secretCode = 5053;

// wip
String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
int currentTries = 0;
bool correctCodeInput = false;
bool triesExceeded = false;
long newInput = 0;
bool newInputDetected = false;
bool newData = false;

const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data



void setup() {
  // Serial Communication start
  Serial.begin(9600);
  Serial.println("Frieda Artz Lopez");
  Serial.println(2127357);
  Serial.println("Week 4. Communication");
  Serial.println("Please input the secret code");

  // LED PinModes
  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
  pinMode(ledThree, OUTPUT);
  pinMode(ledFour, OUTPUT);
  pinMode(ledFive, OUTPUT);
  pinMode(ledSix, OUTPUT);

  // initial LED setup
  digitalWrite(ledOne, LOW);
  digitalWrite(ledTwo, HIGH);
  digitalWrite(ledThree, HIGH);
  digitalWrite(ledFour, LOW);
  digitalWrite(ledFive, LOW);
  digitalWrite(ledSix, LOW);

  // Button PinModes
  pinMode(inBuiltButton, INPUT);

  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop(){
  if (Serial.available()) {
    newInput = inputString.toInt();
    Serial.println(newInput);
    newData = true;
  }

  if(inputString.toInt() == secretCode && !correctCodeInput && newData){
    correctCodeInput = true;
    Serial.println("secret code inputeedesded");
  }
  else if(currentTries == 1 && newData){
    Serial.println("Two tries left.");
    digitalWrite(ledSix, HIGH);

  }
  else if(currentTries == 2 && newData){
    Serial.println("One Try left");
    digitalWrite(ledFive, HIGH);
  }
  else if(currentTries == 3 && newData){
    digitalWrite(ledFour, HIGH);
    Serial.println("The Application is locked and a reset is required.");
  }

  if(newData && newInput != secretCode){
    newData = false;
    currentTries++;
    Serial.println(currentTries);
  }

  // button press resets the program
  if(digitalRead(inBuiltButton) == 0){
    digitalWrite(ledFour, LOW);
    digitalWrite(ledFive, LOW);
    digitalWrite(ledSix, LOW);
    currentTries = 0;
    correctCodeInput = false;
    Serial.println("Frieda Artz Lopez");
    Serial.println(2127357);
    Serial.println("Week 4. Communication");
    Serial.println("Please input the secret code");
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      Serial.println(inputString);
      Serial.println(inputString.toInt());
    }
  }
}