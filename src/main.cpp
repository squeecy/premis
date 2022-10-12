#include "imu/accel.h"

void setup() {
  Serial.begin(9600);
  mpu_setup();
}
void loop() {
  mpu_data_print();




  delay(500);
}
