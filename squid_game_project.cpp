#include <Arduino.h>

int greenledpin=9; //initialize pin 9
int redledpin=11;// initialize pin 11


// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  pinMode(greenledpin, OUTPUT);// set green LED pin as "output"
  pinMode(redledpin,OUTPUT);// set red LED pin as “output”

  int result = myFunction(2, 3); //hi
}

void loop() {
  // I made changes
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}
