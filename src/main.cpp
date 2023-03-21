#include "accel.h"
#include "baro.h"
#include "pid.h"
#include <chrono>

//chrono accelTimer;
unsigned long start_time, end_time;
void setup() {
  configure();
  baro_Init();
  //mpu_setup();
}


void loop() {
  start_time = millis();
  barometer_t BARO;
  float deltaT = start_time - end_time;

  mpu_loop();
  set_Baro(&BARO);
  //end_time = millis();
  end_time = start_time;


  //delay(((1.0/30.0) * 1000) - (end_time - start_time));


}
