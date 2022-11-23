#ifndef ACCEL_H
#define ACCEL_H
#include "lowpass.h"
#include "kalman.h"
#include "quaternion.h"
#include "Wire.h"


typedef struct 
{
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  int16_t tmp;
}mpu_T;

const int mpu_serial_addr = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.


static float d_t = 0;
static unsigned long print_ms = 200;
static float temperature; // variables for temperature data

void configure();
void mpu_raw_data(mpu_T *mpu_s);
void mpu_loop();
void calculate_IMU_error();


#endif

