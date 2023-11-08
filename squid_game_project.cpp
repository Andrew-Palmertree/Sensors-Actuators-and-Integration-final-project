#include <Arduino.h>

int greenledpin=9; //initialize pin 9
int redledpin=11;// initialize pin 11
int buzzer=8;// select digital IO pin for the buzzer
int buzzerPin=0;// initialize analog pin 0

int myFunction(int, int);

void setup() {
  

    Serial.begin(9600);// set baud rate at 9600
    pinMode(buzzer,OUTPUT);// set digital IO pin pattern, OUTPUT to be output(pin 8)
    pinMode(greenledpin, OUTPUT);// set green LED pin as "output"
    pinMode(redledpin,OUTPUT);// set red LED pin as “output”

  int result = myFunction(2, 3); 
}

void loop() {

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

