#include<LiquidCrystal.h>
#include<Servo.h>
#define RedPin 12
#define BluePin 3
#define GreenPin 13
#define Force A0

int Force_VAL = 0;
unsigned long blueToGreenStartTime = 0;
unsigned long lastBlueOnTime = 0;
const unsigned long delayTime = 2000;

LiquidCrystal lcd(6,7,8,9,10,11);

int manualPin = 2;
int buttonState = 0;
int servoPin = 4;

Servo Servo1;

int S = 59; 
int M = 59; 
int H = 05; 

void setup()

{
  tone(5, 1000, 30);
  
  pinMode(manualPin, INPUT_PULLUP);
  
  Servo1.attach(servoPin);
  pinMode(servoPin, OUTPUT);
  Servo1.write(0);
  
  pinMode(Force, INPUT);
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(" Automatic  Pet ");
  lcd.setCursor(0,1);
  lcd.print("     Feeder     ");
  delay(2000);
  lcd.clear();
  lcd.print("  Dante B.   ");
  delay(2000);
  lcd.setCursor(0,1);
  lcd.print("  System Ready  ");
  delay(2000);
  lcd.clear();
  
  tone(5, 2000, 50);

}

void RedLight() {
  digitalWrite(RedPin, HIGH);
  digitalWrite(GreenPin, LOW);
  digitalWrite(BluePin, LOW);
}

void BlueToGreen() {
  if (blueToGreenStartTime == 0) {
    digitalWrite(RedPin, LOW);
    digitalWrite(GreenPin, LOW);
    digitalWrite(BluePin, HIGH);
    blueToGreenStartTime = millis();
  }

  // Check if 2 seconds have passed
  if (millis() - blueToGreenStartTime >= delayTime) {
    digitalWrite(BluePin, LOW);
    digitalWrite(GreenPin, HIGH);
  }
}

void Green() {
  digitalWrite(RedPin, LOW);
  digitalWrite(GreenPin, HIGH);
  digitalWrite(BluePin, LOW);
}

void CheckForceAndLight() {
  Force_VAL = analogRead(Force);

  if (Force_VAL < 300) {
    RedLight();
    blueToGreenStartTime = 0; // Reset the timer when Force_VAL is below 300
  } else if (Force_VAL < 500 && Force_VAL > 300) {
    BlueToGreen();
  } else if (Force_VAL > 500) {
    // Check if the blue light is not currently on
    if (millis() - lastBlueOnTime > delayTime) {
      BlueToGreen();
      lastBlueOnTime = millis(); // Record the time when the blue light was turned on
    }
  } else if (Force_VAL > 300) {
    // Reset the timer when Force_VAL is above 300
    blueToGreenStartTime = 0;
  }
}

void loop()
  
{  
  CheckForceAndLight();
  
  //set countdown counter
  lcd.setCursor(0,0);
  lcd.print("Feeding time in:");
  lcd.setCursor(6,1);
  lcd.print(":");
  lcd.setCursor(9,1);
  lcd.print(":");
  
 S--;
 delay(1000);
  
 if(S<0)
 {
 M--;
 S=59;
 }
 if(M<0)
 {
 H--;
 M=59;
 }
 if(H<0)
 {
 H=05;
 M=59;
 S=59;
 }
 if(M>9)
 {
 lcd.setCursor(7,1);
 lcd.print(M);
 }
 else
 {
 lcd.setCursor(7,1);
 lcd.print("0"); 
 lcd.setCursor(8,1);
 lcd.print(M);
 lcd.setCursor(9,1);
 lcd.print(":");
 }
  
 if(S>9)
 {
 lcd.setCursor(10,1);
 lcd.print(S);
 }
 else
 {
 lcd.setCursor(10,1);
 lcd.print("0"); 
 lcd.setCursor(11,1);
 lcd.print(S);
 lcd.setCursor(12,1);
 lcd.print(" ");
 }
  
 if(H>9)
 {
 lcd.setCursor(4,1);
 lcd.print (H);
 }
 else
 {
 lcd.setCursor(4,1);
 lcd.print("0"); 
 lcd.setCursor(5,1);
 lcd.print(H);
 lcd.setCursor(6,1);
 lcd.print(":");
 }
 
 if ((H==0)&&(M==0)&&(S==0))//if countdown comes to 0,
 {
 tone(5, 3000, 3000);
 lcd.setCursor(0,0);
 lcd.print("      I'ts      ");
 lcd.setCursor(0,1);
 lcd.print("Feeding  Time!!!");
 Servo1.write(0);
 delay(3000);
 Servo1.write(180);
 lcd.clear();
 }

  
 buttonState = digitalRead(manualPin);
  
 if (buttonState == LOW)
 {
 tone(5, 3000, 1000);
 lcd.setCursor(0,0);
 lcd.print("    OVERRIDE    ");
 lcd.setCursor(0,1);
 lcd.print("(manual feeding)");
 Servo1.write(200);
 delay(2000);
 Servo1.write(0);
 lcd.clear();
   
 }
 
}

/* if (Force_VAL < 200) {
    // Force_VAL is lower than 200, light up RedPin
    digitalWrite(RedPin, HIGH);
    digitalWrite(GreenPin, LOW);
    digitalWrite(BluePin, LOW);
    blueTurnedOn = false;
    greenTurnedOn = false;
  } else if (Force_VAL > 500 && !blueTurnedOn) {
    // Force_VAL is more than 500, light up BluePin for 2 seconds
    digitalWrite(RedPin, LOW);
    digitalWrite(GreenPin, LOW);
    digitalWrite(BluePin, HIGH);
    delay(2000);

    // Turn off BluePin
    digitalWrite(BluePin, LOW);
    blueTurnedOn = true;
    greenTurnedOn = false;  // Ensure green is turned off
  } else if (!greenTurnedOn && Force_VAL > 500 && Force_VAL != lastForce_VAL) {
    // Force_VAL is between 200 and 500, and green was previously turned off, turn on GreenPin
    digitalWrite(RedPin, LOW);
    digitalWrite(GreenPin, HIGH);
    digitalWrite(BluePin, LOW);
    greenTurnedOn = true;
    blueTurnedOn = false;  // Ensure blue is turned off
  } else {
    // Force_VAL is between 200 and 500, light up GreenPin
    digitalWrite(RedPin, LOW);
    digitalWrite(GreenPin, HIGH);
    digitalWrite(BluePin, LOW);
    blueTurnedOn = false;
  }

  lastForce_VAL = Force_VAL;
  // Add a delay to prevent rapid changes
  delay(100);
  */