#include <Arduino.h> 
#include <LiquidCrystal.h> // include the library code

//analog pins///////////////////////////////////////////////////////////////////
int buzzerPin=0;// initialize analog pin 0 for buzzer
int potentiometer =1; //initialize analog pin 1 for potentiometer


//digital pins///////////////////////////////////////////////////////////////////////
int firstServo = 13; //first servor motor that has range sensor on top
int buttonpin=18; //button that starts the game
int echoPin = 2;    // ECHO pin (ultrasonic sensor)
int trigPin = 3;    // TRIG pin (ultrasonic sensor)
int greenledpin=4; //initialize pin 4
int redledpin=5;// initialize pin 5
int buzzer=6;// select digital IO pin for the buzzer

///LCD Pin set up/////////////////////////////////////////////////////////////////////////////
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12; // initialize the library by associating any needed LCD interface pin
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // with the arduino pin number it is connected to

/// 1st servo variable set up//////////////////////////////////////////////////////////////////////
int firstServoVal;// define val for 1st servo motor 
int firstServoAngle; //define val that holds angle for 1st servo motor
Servo myFirstServo; //defines 1st servo variable name

///Sonic range sensor variable set up/////////////////////////////////////////////////////////////
float duration_us, distance_cm; // get the distance for the ultrasonic sensor

/// start button variable set up//////////////////////////////////////////////////////
int buttonVal;// define val of button

void INT0_ISR(){ //interrupt for start of game (pin 18) button
	

}

void INT1_ISR(){// interrupt game clock countdown (pin 19)  button
	


}

void setup() {

  

    Serial.begin(9600);// set baud rate at 9600

    lcd.begin(16, 2); // set up the LCD's number of columns and rows:
    myFirstServo.attach(firstServo);


    pinMode(buttonPin, INPUT); //set button pin as input
    pinMode(buzzer,OUTPUT);// set digital IO pin pattern, OUTPUT to be output(pin 8)
    pinMode(greenledpin, OUTPUT);// set green LED pin as "output"
    pinMode(redledpin,OUTPUT);// set red LED pin as “output”

    pinMode(trigPin, OUTPUT); // Configure the trigger pin as an output for ultrasonic sensor
    pinMode(echoPin, INPUT);  // Configure the echo pin as an input ultrasonic sensor
    
  attachInterrupt(digitalPinToInterrupt(buttonpin), INT0_ISR, RISING);

}

void loop() {

////LCD PART////////////////////////////////////////////////////////////////////////
      val = analogRead(potpin); 
      lcd.clear();
      lcd.setCursor(0,0);

    if(val == 0){
      lcd.print("Water Level:Dry");
    }

////Buzzer Part///////////////////////////////////////////////////////////////////////////////////////////////////

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

////Ultrasonic range sensor part ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Generate a 10-microsecond pulse to  trigger the ultrasonic sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  delay(500);

////First Servo motor part ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  motorAngle = map(firstServoVal,0,1023,0,180);
  myservo.write(firstServoAngle);// set rotation angle of the motor
  Serial.print("1st Servor Angle ");
  Serial.println(firstServoAngle);





}

