// running light LEDS Pin Layout
const int ledOne = 13;
const int ledTwo = 12;
const int ledThree = 11;
const int ledFour = 10;
const int ledFive = 9;
const int ledSix = 8;

// Control value for the LEDs
int currentLedPin = 7;  // The current LED that should be on
const int minLedPin = 7;
const int maxLedPin = 14;

// Control Buttons Pin Layout
const int buttonIntervalHighSpeed = 6;
const int buttonIntervalLowSpeed = 5;
const int buttonDirectionBottomTop = 4;
const int buttonDirectionTopBottom = 3;

// timing and behaviour control
unsigned long previousMillis = 0;  // will store last time LED was updated
int interval = 100;  // interval at which to blink (milliseconds)
bool direction = true; // true adds false subtracs
int ioGroundPin = 7;  // GRND for the buttons

// Button Delay
unsigned int buttonDebounceTime = 0;
bool buttonReady = true;

void setup() {
  // Print on Screen
  Serial.begin(9600);
  Serial.println("Frieda Artz Lopez");
  Serial.println("2127357");
  Serial.println("Week 2. basics");

  // LED PinModes
  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
  pinMode(ledThree, OUTPUT);
  pinMode(ledFour, OUTPUT);
  pinMode(ledFive, OUTPUT);
  pinMode(ledSix, OUTPUT);

  // Button PinModes
  pinMode(buttonIntervalHighSpeed, INPUT_PULLUP);
  pinMode(buttonIntervalLowSpeed, INPUT_PULLUP);
  pinMode(buttonDirectionBottomTop, INPUT_PULLUP);
  pinMode(buttonDirectionTopBottom, INPUT_PULLUP);

  // Setting the ground Pin
  pinMode(ioGroundPin, OUTPUT);
  digitalWrite(ioGroundPin, LOW);
}

void loop() {
  unsigned long currentMillis = millis();

  // ButtonReady is when the button can again be pressed
  if(buttonDebounceTime == 400){
    buttonReady = true;
    buttonDebounceTime = 0;
  }
  buttonDebounceTime++;

  if(buttonReady && (digitalRead(buttonIntervalLowSpeed) == 0 || 
    digitalRead(buttonIntervalHighSpeed) == 0 || 
    digitalRead(buttonDirectionBottomTop) == 0 || 
    digitalRead(buttonDirectionTopBottom) == 0)){
      // Button Input checks
      if(digitalRead(buttonIntervalLowSpeed) == 0){
      interval += 100;
      }
      else if(digitalRead(buttonIntervalHighSpeed) == 0){
        interval -= 100;
      }
      else if(digitalRead(buttonDirectionBottomTop) == 0){
        direction = true;
      }
      else if(digitalRead(buttonDirectionTopBottom) == 0){
        direction = false;
      }
      buttonReady = false;
  }

  // values in ms max and min are 100 & 1000
  if(interval < 100){
    interval = 100;
  } else if(interval > 1000){
    interval = 1000;
  }
  
  // interval milli check
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    digitalWrite(currentLedPin, LOW);

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
  }
}


  