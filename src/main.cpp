#include "imu/accel.h"

#include "Wire.h" // This library allows you to communicate with I2C devices.

void setup() {
  Serial.begin(9600);
  mpu_setup();
}
void loop() {
  mpu_data_loop();
  raw_2_accel(accelerometer_x);
  mpu_data_print();

  delay(500);
}
