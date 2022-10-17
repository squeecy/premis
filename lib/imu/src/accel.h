#ifndef ACCEL_H
#define ACCEL_H
#include "lowpass.h"
#include "kalman.h"
#include "quaternion.h"
//#include "helper/helper.h"
#include "Wire.h"


typedef struct 
{
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  int16_t tmp;
}MPU_t;

static MPU_t mpu;
const int mpu_serial_addr = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.


static float deltat = 0;
static long now_ms, last_ms = 0;
static unsigned long print_ms = 200;

static float temperature; // variables for temperature data

static float A_cal[6] = {265.0, -80.0, -700.0, 0.994, 1.000, 1.014};
static float G_off[3] = {-499.5, -17.7, -82.0};
#define gscale ((250./32768.0) * (M_PI/180.0)


typedef struct MPU_s mpu_t;
void mpu_setup();
void mpu_data_raw();
void mpu_data_loop(Euler_Angles_t *eul_ang);
void mpu_data_print(Euler_Angles_t *euler_ang);

#endif