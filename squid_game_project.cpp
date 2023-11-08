#include <Arduino.h>
#include <LiquidCrystal.h> // include the library code

//analog pins
int buzzerPin=0;// initialize analog pin 0
int potentiometer =1; //initialize analog pin 1 for potentiometer

//digital pins
int greenledpin=4; //initialize pin 4
int redledpin=5;// initialize pin 5
int buzzer=6;// select digital IO pin for the buzzer

const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12; // initialize the library by associating any needed LCD interface pin
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // with the arduino pin number it is connected to


int myFunction(int, int);

void setup() {
  

    Serial.begin(9600);// set baud rate at 9600
    lcd.begin(16, 2); // set up the LCD's number of columns and rows:

    pinMode(buzzer,OUTPUT);// set digital IO pin pattern, OUTPUT to be output(pin 8)
    pinMode(greenledpin, OUTPUT);// set green LED pin as "output"
    pinMode(redledpin,OUTPUT);// set red LED pin as “output”

  int result = myFunction(2, 3); 
}

void loop() {

      val = analogRead(potpin); 
      lcd.clear();
      lcd.setCursor(0,0);

    if(val == 0){
      lcd.print("Water Level:Dry");
    }


      val = analogRead(buzzerPin); // read the analog value from the sensor and assign it to val
      buzzerFreq = map(val, 0, 1023, 60, 10000);
      buzzerPeriod = 1e6 / buzzerFreq;
      halfPeriod = buzzerPeriod /2;

      for(int i = 0; i < 200; i++){
        digitalWrite(buzzer, HIGH);// sound
        delayMicroseconds(buzzerPeriod);//delay1ms
        digitalWrite(buzzer,LOW);//not sound
        delayMicroseconds(buzzerPeriod);//ms delay  
      }
        Serial.print("Frequency is ");
        Serial.println(buzzerFreq);


}

