#include "helper/helper.h"
#include "Wire.h"
#include "math.h"

const int mpu_serial_addr = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

long accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
float gyro_x, gyro_y, gyro_z; // variables for gyro raw data
float temperature; // variables for temperature data

void mpu_setup()
{
  Wire1.setSCL(16);
  Wire1.setSDA(17);
  Wire1.begin();
  Wire1.beginTransmission(mpu_serial_addr); 
  Wire1.write(0x6B); // PWR_MGMT_1 register
  Wire1.write(0); // set to zero (wakes up the MPU-6050)
  Wire1.endTransmission(true);
}


void mpu_data_loop()
{
  Wire1.beginTransmission(mpu_serial_addr);
  Wire1.write(0x3B); 
  Wire1.endTransmission(false); 
  Wire1.requestFrom(mpu_serial_addr, 7*2, true); 

  accelerometer_x = Wire1.read()<<8 | Wire1.read(); 
  accelerometer_y = Wire1.read()<<8 | Wire1.read(); 
  accelerometer_z = (Wire1.read()<<8 | Wire1.read()); 
  temperature = Wire1.read()<<8 | Wire1.read(); 
  gyro_x = Wire1.read()<<8 | Wire1.read(); 
  gyro_y = Wire1.read()<<8 | Wire1.read(); 
  gyro_z = Wire1.read()<<8 | Wire1.read(); 
}

/*
 * Converts raw mpu data to gravitational acceleration
 */

float raw_2_accel(long accel)
{
        return (accel/(16400.0)); 

}

/*
 * Theta angle = -tan(ax/az)
 * converts acceleration to the x angle
 */
float theta_ang(long raw_x, long raw_z)
{
        return RAD2DEG(-atan2(raw_x,raw_z));
}

/*
 * Phi angle = -tan(ay/az)
 * converts acceleration to the y angle
 */
float phi_ang(long raw_y, long raw_z)
{
        return RAD2DEG(-atan2(raw_y,raw_z));
}

/*
 * detect a change in acceleration 
 * within the y direction
 */
void launch_detect()
{
        
}

void mpu_data_print()
{
  // print out data
  float x = accelerometer_z / 16384.0;
  Serial.print("aX = "); Serial.print(theta_ang(accelerometer_x,accelerometer_z));
  Serial.print(" | aY = "); Serial.print(phi_ang(accelerometer_y,accelerometer_z));
  Serial.print(" | aZ = "); Serial.print(raw_2_accel(accelerometer_z));

  Serial.print(" | tmp = "); Serial.print(temperature/340.00+36.53);

  Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
  Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
  Serial.print(" | gZ = "); Serial.print(convert_int16_to_str(gyro_z));
  Serial.println();

}
