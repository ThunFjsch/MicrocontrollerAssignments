#include <LiquidCrystal.h>

// Pin definition LCD
#define RegisterSelectPin 12
#define EnablePin 11
#define DataPinFour 5
#define DataPinFive 4
#define DataPinSix 3
#define DataPinSeven 2

// Distance definition
#define MinDistance 10
#define MaxDistance 180

// Pin definition Sonar
#define EchoPin 6   // Echo pin for ultrasonic sensor as input
#define TriggerPin 7   // Trigger pin for ultrasonic sensor as output

// Pin definition
#define InBuildLED 13   // LED as indicator for exceeding 180 distance
#define InBuildButton 20   // Button for resetting the LED

// Sonar logic variables
#define Interval 360
long elapsedTime = 0;
long previousElapsedTime = 0;

// button Debounce
bool buttonReady = true;

// Student name
const String userName = "Frieda Artz Lopez";

// Initialize LCD
LiquidCrystal lcd(RegisterSelectPin, EnablePin, DataPinFour, DataPinFive, DataPinSix, DataPinSeven);

void setup() {
  Serial.begin(9600); 
  Serial.println(userName); 
  Serial.println("2127357");
  Serial.println("week 6: Sensors and Actuators"); 

  lcd.begin(16, 2); // beign lcd

  // Set initial text on the LCD
  lcd.setCursor(0, 0);
  lcd.print(userName); 
  lcd.setCursor(0, 1);
  lcd.print("distance:     cm"); 

  // PinMode initialization
  pinMode(InBuildLED, OUTPUT);
  pinMode(InBuildButton, INPUT_PULLUP);
  pinMode(EchoPin, INPUT);
  pinMode(TriggerPin, OUTPUT);
}

void loop() {
  // trigger Sonar with 2 microsecond pulse
  digitalWrite(TriggerPin, HIGH); 
  delayMicroseconds(2); 
  digitalWrite(TriggerPin, LOW); 

  float timePassed = pulseIn(EchoPin, HIGH); // Measure the duration of the pulse
  int distanceCalculation = (timePassed*0.0343)/2;// results in the calculated distance depending on the pulse duration
  Serial.println(distanceCalculation);
  elapsedTime = millis();

  if(elapsedTime - previousElapsedTime >= Interval){
    // Clears LCD
    lcd.setCursor(10, 1);
    lcd.print("      ");
    lcd.setCursor(10, 1);

    // Display distance information on the LCD based on certain conditions and set LED light
    if(distanceCalculation < MinDistance){
      lcd.print("<10 cm");    // Displays the MinDistance
      buttonReady = true;
    }
    else if(distanceCalculation > MaxDistance){
      lcd.print(">180cm");    // Displays the MaxDistance
      digitalWrite(InBuildLED, HIGH);
      buttonReady = true;
    } 
    else if(digitalRead(InBuildButton) == HIGH && buttonReady){
      buttonReady = false;
      digitalWrite(InBuildLED, LOW);
      lcd.print(distanceCalculation); // Display the calculated distance
      lcd.print("cm");
    }
    else{
      lcd.print(distanceCalculation); // Display the calculated distance
      lcd.print("cm");
      buttonReady = true;
    }

    previousElapsedTime = elapsedTime; 
  }
}
