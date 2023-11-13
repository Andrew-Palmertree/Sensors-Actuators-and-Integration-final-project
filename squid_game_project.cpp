#include <Arduino.h> 
#include <LiquidCrystal.h> // include the library code
#include <Servo.h>

//analog pins///////////////////////////////////////////////////////////////////

int potentiometer =0; //initialize analog pin 1 for potentiometer


//digital pins///////////////////////////////////////////////////////////////////////

int echoPin = 2;    // ECHO pin (ultrasonic sensor)
int trigPin = 3;    // TRIG pin (ultrasonic sensor)
int greenledpin=4; //initialize pin 4
int redledpin=5;// initialize pin 5
int buzzerPin=6;// select digital IO pin for the buzzer
int firstServo = 13; //first servor motor that has range sensor on top
int secondServo =22;//2nd servor motor that sweeps field when a player loses
int buttonpin=18; //button that starts the game

///Buzzer setup///////////////////////////////////////////////////////////////////
int buzzerFreq;
int buzzerPeriod;
int buzzerVal;


///LCD Pin set up/////////////////////////////////////////////////////////////////////////////
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12; // initialize the library by associating any needed LCD interface pin
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // with the arduino pin number it is connected to
int potVal = 0;

/// 1st servo variable set up//////////////////////////////////////////////////////////////////////
int firstMotorAngle;
int firstServoVal;// define val for 1st servo motor 
int firstServoAngle; //define val that holds angle for 1st servo motor
Servo myFirstServo; //defines 1st servo variable name

///2nd servo variable set up////////////////////////////////////////////////////////////
int secondMotorAngle;
int secondServoVal;// define val for 1st servo motor 
int secondServoAngle; //define val that holds angle for 1st servo motor
Servo mySecondServo; //defines 1st servo variable name

///Sonic range sensor variable set up/////////////////////////////////////////////////////////////
float duration, distance_cm, distance_inch;// distance for the ultrasonic sensor

/// start button variable set up//////////////////////////////////////////////////////
int buttonVal;// define val of button

///game variable setup//////////////////////////////////////////////////////////////

int greenLight = 0;

void INT0_ISR(){ //interrupt for start of game (pin 18) button
	

}

void INT1_ISR(){// interrupt game clock countdown (pin 19)  button
	

}

void setup() {

  

    Serial.begin(9600);// set baud rate at 9600

    lcd.begin(16, 2); // set up the LCD's number of columns and rows:
    myFirstServo.attach(firstServo);
    mySecondServo.attach(secondServo);


    
    pinMode(buzzerPin,OUTPUT);// set digital IO pin pattern, OUTPUT to be output(pin 8)
    pinMode(greenledpin, OUTPUT);// set green LED pin as "output"
    pinMode(redledpin,OUTPUT);// set red LED pin as “output”

    pinMode(trigPin, OUTPUT); // Configure the trigger pin as an output for ultrasonic sensor
    pinMode(echoPin, INPUT);  // Configure the echo pin as an input ultrasonic sensor

  attachInterrupt(digitalPinToInterrupt(buttonpin), INT0_ISR, RISING);

}

void LEDs(int LED_switch){

  if (LED_switch == 1){
    digitalWrite(greenledpin, LOW);
    digitalWrite(redledpin, HIGH);
  } else{
    digitalWrite(redledpin, LOW);
    digitalWrite(greenledpin, HIGH);
  }

}

void buzzer_noise(int noiseMode){

    if(noiseMode == 1){

    
      for(int i = 0; i < 2000; i++){
        digitalWrite(buzzerPin, HIGH);// sound
        delayMicroseconds(1e6 / 60);//delay1ms
        digitalWrite(buzzerPin,LOW);//not sound
        delayMicroseconds(1e6 / 60);//ms delay  
      }

    }
     else{

      for(int i = 0; i < 2000; i++){
        digitalWrite(buzzerPin, HIGH);// sound
        delayMicroseconds(1e6 / 10000);//delay1ms
        digitalWrite(buzzerPin,LOW);//not sound
        delayMicroseconds(1e6 / 10000);//ms delay  
      }

    }
  
}

void Ultrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance_cm = (duration * 2) / 29.1;
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
}

void LCD_screen(){

  // Display the time left on the LCD
  // if (timeLeft >= 0){
  //   lcd.setCursor(0, 0);
  //   lcd.print("Time Left");
  //   lcd.setCursor(0, 1);
  //   lcd.print(timeLeft);
  //   lcd.print(" Seconds");
  // }

  // if (timeLeft <= -1){
  //   lcd.setCursor(0, 0);
  //   lcd.print("      Game      ");
  //   lcd.setCursor(0, 1);
  //   lcd.print("      Over      ");
  //   game_active = 0;
  // }
}





void servo1(int servoMode) {


  int currentAngle = myFirstServo.read(); // myservo1.read(); 

   myFirstServo.write(servoMode);
  
     Serial.print("Servo1 Angle ");
     Serial.println(currentAngle);


}

void servo2(int winMode) {


  int currentAngle = mySecondServo.read(); // myservo1.read(); 

   mySecondServo.write(winMode);
  
    // Serial.print("Servo2 Angle ");
    // Serial.println(currentAngle);


}



void loop() {

  //*********************GREEN LIGHT**********************************************************
while(1){
  greenLight = 1;

    LEDs(greenLight);
    servo1(0);
    buzzer_noise(greenLight);
    //Ultrasonic();  
    
   


   delay(2000);

//*********************RED LIGHT***************************************************************************

  greenLight = 0;

  
    LEDs(greenLight);
    servo1(180);
    buzzer_noise(greenLight);   
   // Ultrasonic();
     
    delay(3000);


}

}