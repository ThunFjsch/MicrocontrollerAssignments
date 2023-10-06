const int ledOne = 8;
const int ledTwo = 9;
const int ledThree = 10;
const int ledFour = 11;
const int ledFive = 12;
const int ledSix = 13;

int currentLedPin = 7;  // The current LED that should be on
const int minLedPin = 7;
const int maxLedPin = 14;

const int potiPin = A0;
const int builtInButton = 20;

// Control State values
bool isButtonPressed = false;
int interval = 100;
bool direction = true; // true adds false subtracs

// Communication values
bool stringComplete = false;
String inputString = "";

void setup() {
  Serial.begin(9600);
  Serial.println("Frieda Artz Lopez");
  Serial.println("2127357");
  Serial.println("Week 5. Control Structures");

  // Pin setup
  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
  pinMode(ledThree, OUTPUT);
  pinMode(ledFour, OUTPUT);
  pinMode(ledFive, OUTPUT);
  pinMode(ledSix, OUTPUT);

  pinMode(potiPin, INPUT);
  pinMode(builtInButton, INPUT);

  digitalWrite(ledOne, LOW);
  digitalWrite(ledTwo, LOW);
  digitalWrite(ledThree, LOW);
  digitalWrite(ledFour, LOW);
  digitalWrite(ledFive, LOW);
  digitalWrite(ledSix, LOW);
}


void loop() {
  int tmp = analogRead(potiPin);
  interval = constrain(tmp, 10, 1000);

  if(stringComplete){
    stringComplete = false;
    // If u is inputted chase from pin 8 to 13 is active
    if(inputString == "u\n"){
      direction = true;
      inputString = "";
    }
    // if d is inputted chase from pin 13 to 8 is active
    else if(inputString == "d\n"){
      direction = false;
      inputString = "";
    }
    else {
      // if invalid input resets inputString
      inputString = "";
    }
  }

  // Stops the chasing lights when pressed
  if(digitalRead(builtInButton) != 1){
    isButtonPressed = true;
  } else{
    isButtonPressed = false;
  }

  // interval milli check
  if (!isButtonPressed) {
    digitalWrite(currentLedPin, LOW);
    delay(interval/2);  // Half the interval off

    // Check of Direction
    if (direction == false){
      currentLedPin -= 1;
    }
    else {
      currentLedPin += 1; 
    }

    // Checking range of Led pins    
    switch(currentLedPin){
      case maxLedPin:
        currentLedPin = minLedPin;
        break;
      case minLedPin:
        currentLedPin = maxLedPin;
        break;
    } 
    
    digitalWrite(currentLedPin, HIGH);
    delay(interval/2); // Half the interval on
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
    }
  }
}