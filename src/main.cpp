#include "imu/accel.h"

void setup() {
  Serial.begin(9600);
  mpu_setup();
}
void loop() {
  MPU_t mpu_60;
  Euler_Angles_t euler_ang;

  MPU_t *mpuptr = &mpu_60;
  Euler_Angles_t *eulptr = &euler_ang;

  mpu_data_print(eulptr);




  delay(500);
}
