// Alarm related
bool alarm = false;
const int alarmThreshold = 75;

// Button state and pin
bool buttonPressed = false;
const int inBuiltButton = 20;

// LED
const int pinLed = 13;

// Poti hardware with reading values
const int variableResistorPinOne = A0;
const int variableResistorPinTwo = A1;  // In my circuit I use one for both signals
int resistorReadOne, resistorReadTwo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Frieda Artz Lopez");
  Serial.println("2127357");
  Serial.println("Week 3. Analog");

  pinMode(pinLed, OUTPUT);
  pinMode(variableResistorPinOne, INPUT);
  pinMode(variableResistorPinTwo, INPUT);
  pinMode(inBuiltButton, INPUT);

  // initial resistorRead value
  resistorReadOne = 0;
  resistorReadTwo = 0;
} 

void loop() {
  // Resistor Readintgs + constraining and Serial output
  resistorReadOne = constrain(analogRead(variableResistorPinOne) / 10, 0, 99);
  resistorReadTwo = constrain(analogRead(variableResistorPinTwo) / 10, 0, 99);
  Serial.println(resistorReadOne);
  Serial.println(resistorReadTwo);

  if (resistorReadOne >= alarmThreshold && resistorReadTwo >= alarmThreshold){
    alarm = true;
  }

  // Sets the buttonPress
  if(digitalRead(inBuiltButton) == 0){
    buttonPressed = true;
  }
  
  if (alarm){
    digitalWrite(pinLed, HIGH);
    delay(100);
    digitalWrite(pinLed, LOW);

    if(buttonPressed && alarm){
      alarm = false;
      buttonPressed = false;
    }
  } else {
    digitalWrite(pinLed, HIGH);
    delay(500);
    digitalWrite(pinLed, LOW);
    delay(500);
  }

  buttonPressed = false;
}
