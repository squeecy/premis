#include "accel.h"

void setup() {
  configure();
  //mpu_setup();
}
void loop() {

  mpu_T MPU;

  mpu_loop();




  delay(100);
}
