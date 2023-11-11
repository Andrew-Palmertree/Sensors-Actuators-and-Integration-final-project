#include <LiquidCrystal.h>
#include <Servo.h>
#include <Arduino.h>
#include <TimerOne.h>

Servo myservo1;

//analog pins (0-15 pins)
int buzzerPin = 0;// initialize analog pin 0
int potentiometer = 1; //initialize analog pin 1 for potentiometer
// analog pin 2 is used by the servo motor 1 to control the ultrasonic sensor


//digital pins (0-52 pins)
int echoPin = 2;    // ECHO pin (ultrasonic sensor)
int trigPin = 3;    // TRIG pin (ultrasonic sensor)
int greenledpin = 4; //initialize pin 4
int redledpin = 5;// initialize pin 5
int buzzer = 6;// select digital IO pin for the buzzer

const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int res_game_B = 18;

float duration, distance_cm, distance_inch;

volatile bool buttonPressed = false; // A flag to indicate whether the button has been pressed
unsigned long previousMillis = 0;
unsigned long servoInterval = 2;  // Initial interval of 2 seconds
int i = 0;
int previous_i = -1; // Initialize to a value that 'i' cannot be initially
bool isServoMoving = false; // Flag to track servo movement status
int game_active = 1;
volatile int timeLeft = 60;
int counter=0;
int servo_counter=0;

void (*resetFunc) (void) = 0; // Declare reset function at address 0


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


void LEDs(int LED_switch){
  if (LED_switch == 1){
    digitalWrite(greenledpin, LOW);
    digitalWrite(redledpin, HIGH);
  } else{
    digitalWrite(redledpin, LOW);
    digitalWrite(greenledpin, HIGH);
  }
}

void LCD_screen(){

  // Display the time left on the LCD
  if (timeLeft >= 0){
    lcd.setCursor(0, 0);
    lcd.print("Time Left");
    lcd.setCursor(0, 1);
    lcd.print(timeLeft);
    lcd.print(" Seconds");
  }

  if (timeLeft <= -1){
    lcd.setCursor(0, 0);
    lcd.print("      Game      ");
    lcd.setCursor(0, 1);
    lcd.print("      Over      ");
    game_active = 0;
  }
}

void timerIsr() {
  // This function is called every time Timer1 overflows
  // You can control your servo here
  counter++;
  lcd.clear();
  timeLeft--;
  LCD_screen(); // Sets the servo position to 90 degrees
  }

void buzzer_noise(int noise){
  if(noise == 1){
    for(int i = 0; i < 100; i++) {
    digitalWrite(buzzer, HIGH); // Turn the buzzer on
    delayMicroseconds(1000000 / 60); // Delay for half the period (to create a square wave)
    digitalWrite(buzzer, LOW); // Turn the buzzer off
    delayMicroseconds(1000000 / 60); // Delay for half the period (to complete the wave cycle)
  }

  }else{

    for(int i = 0; i < 100; i++) {
    digitalWrite(buzzer, HIGH); // Turn the buzzer on
    delayMicroseconds(1000000 / 140000); // Delay for half the period (to create a square wave)
    digitalWrite(buzzer, LOW); // Turn the buzzer off
    delayMicroseconds(1000000 / 140000); // Delay for half the period (to complete the wave cycle)
    }
  }
}

void servo1(int i) {
  isServoMoving = true; // The servo is about to start moving
  int currentAngle = myservo1.read();
  int targetAngle = (i == 0) ? 180 : 0;
  int angleIncrement = 1;
  unsigned long servoStartTime = millis();

  // Gradually move the servo to the target angle
  while (currentAngle != targetAngle) {

    if (currentAngle < targetAngle) {
      currentAngle += angleIncrement;
    } else {
      currentAngle -= angleIncrement;
    }
    // Serial.println(targetAngle);
    myservo1.write(currentAngle);
     // Check if the specified interval has passed

     delay(1); // Add a delay to slow down the servo movement
  }
  // The servo has stopped moving
  isServoMoving = false;
  servo_counter = millis() / 1000;
}

void restart_game(){
  resetFunc(); // Call reset function
}


void setup() {
  Timer1.initialize(1000000); // Initializes Timer1 to overflow in 1 seconds
  Timer1.attachInterrupt(timerIsr); // Attaches the ISR function

  pinMode(res_game_B, INPUT_PULLUP); // Set the button pin as an input
  attachInterrupt(digitalPinToInterrupt(res_game_B), restart_game, CHANGE); // Attach the interrupt

  // Initialize serial communication
  Serial.begin(9600);
  myservo1.attach(A2); //servo motor 1 to control the ultrasonic sensor position
  myservo1.write(0); // set the current angle of the servo motor to 0

  // Configure the trigger pin as an output
  pinMode(trigPin, OUTPUT);
  // Configure the echo pin as an input
  pinMode(echoPin, INPUT);

  // Red and Green LEDs
  pinMode(greenledpin, OUTPUT);
  pinMode(redledpin, OUTPUT);
  // Preset the LEDs color
  digitalWrite(redledpin, LOW);
  digitalWrite(greenledpin, HIGH);

  //LCD screen set up for number of columns and rows:
  lcd.begin(16, 2);

  pinMode(buzzer,OUTPUT);// set digital IO pin pattern, OUTPUT to be output 

}



void loop() {
  // Ultrasonic();
  if (game_active == 1){

    // Check if the servo motor is at 180 degrees and not moving
    if (myservo1.read() == 180 && !isServoMoving) {
      Ultrasonic();
      LEDs(1);
      buzzer_noise(1);

    }
    else{
      LEDs(0);
      buzzer_noise(0);
    }

    // Get the current time in seconds
    unsigned long currentTime = millis() / 1000;

    if (i != previous_i) {
      if (currentTime - servo_counter >= servoInterval) {
        servo1(i);
        previous_i = i;
        previousMillis = currentTime;

        // Adjust servoInterval based on the value of i
        servoInterval = (i == 0) ? 3 : 2;

        // Reset the servo counter for the next interval
        servo_counter = currentTime;
      }
    }

    // Toggle the value of i between 0 and 1
    i = (i == 0) ? 1 : 0;
  }
  else if (game_active == 0){
    digitalWrite(redledpin, LOW);
    digitalWrite(greenledpin, LOW);
    digitalWrite(buzzer, LOW); // Turn the buzzer off
  } 

}




