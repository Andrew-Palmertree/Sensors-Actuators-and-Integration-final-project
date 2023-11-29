#include <Arduino.h>
#include <Stepper.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Stepper stepper(2048, 8, 9 ,10, 11);//create stepper motor
Adafruit_MPU6050 mpu;//createIMU
long pi = 3.14159;

void setup() {
  Serial.begin(9600);
  stepper.setSpeed(12);

  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  //initalize IMU
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("");
  delay(100);

}

void loop() {

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);//read data from IMU

  long tilt = (180/pi) * atan2(a.acceleration.x, a.acceleration.z);//calculate tilt measurement from IMU
  Serial.println(tilt);

  if(tilt > 45){//move CW when tilt > 45 deg
    stepper.step(tilt);
  }
  else if(tilt < - 45){//move CCW when tilt < -45 deg
    stepper.step(tilt);
  }
  
  
}
