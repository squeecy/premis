#ifndef ACCEL_H
#define ACCEL_H
#include "lowpass.h"
#include "kalman.h"
#include "quaternion.h"
#include "Wire.h"

const unsigned long FREQ = 20;
// freq = 20


typedef struct 
{
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  int16_t tmp;
}mpu_t;

const int mpu_serial_addr = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.


static float Axyz_t[3]; //testing for noise
static float Axyz[3];
static float Gxyz[3];

static float d_t = 0;
static unsigned long nsync_ms, lsync_ms = 0;
static float temperature; // variables for temperature data

void configure();
void mpu_raw_data(mpu_t *mpu);
void mpu_loop();
void calculate_IMU_error();


#endif

