#ifndef ACCEL_H
#define ACCEL_H
#include "lowpass.h"
#include "kalman.h"
#include "quaternion.h"
//#include "helper/helper.h"
#include "Wire.h"


static struct MPU_t
{
  double ax = 0.0, ay = 0.0, az = 0.0;
  double gx = 0.0, gy = 0.0, gz = 0.0;
  double tmp = 0.0;
}mpu_x;

//static MPU_t mpu;
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
void mpu_data_raw(struct MPU_t mpu_l);
void mpu_data_loop();
void mpu_data_print();

void configure();

void mpu_raw_data(double& ax, double& ay, double& az);
void mpu_loop(struct MPU_t mpu_l);
void calculate_IMU_error();

#endif

