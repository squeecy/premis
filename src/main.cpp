#include "accel.h"

void setup() {
  Serial.begin(9600);
  configure();
  //mpu_setup();
}
void loop() {

  mpu_loop(mpu_x);




  delay(500);
}
