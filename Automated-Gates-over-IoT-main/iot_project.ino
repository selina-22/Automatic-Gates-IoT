#define pirPin 2
int calibrationTime = 10;
long unsigned int lowIn;
long unsigned int pause = 500;
boolean lockLow = true;
boolean takeLowTime;
int PIRValue = 0;
//motor driver
const int motorPin2  = 10; // Pin  7 of L293
const int motorPin1  = 9;  // Pin  2 of L293

void setup() 
{
//Set pins as outputs
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
//This code  will turn Motor clockwise 
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
//This code will turn Motor counter-clockwise 
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);

   Serial.begin(9600);
   pinMode(pirPin, INPUT);
}

void loop() {
   PIRSensor();
}

void PIRSensor() {
   if(digitalRead(pirPin) == HIGH) {
      if(lockLow) {
         PIRValue = 1;
         lockLow = false;
         Serial.println("Motion detected.");
         digitalWrite(motorPin1, LOW);
         digitalWrite(motorPin2, LOW);
         delay(50);
      }
      takeLowTime = true;
   }
   if(digitalRead(pirPin) == LOW) {
      if(takeLowTime){
         lowIn = millis();takeLowTime = false;
      }
      if(!lockLow && millis() - lowIn > pause) {
         PIRValue = 0;
         lockLow = true;
         Serial.println("Motion ended.");
         digitalWrite(motorPin1, HIGH);
         digitalWrite(motorPin2, LOW);
         delay(50);
      }
   }
}
