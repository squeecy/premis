#include "imu/accel.h"
#include "quaternion/quaternion.h"


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

void mpu_data_raw()
{

  MPU_t *mpu_60 = &mpu;
  

  Wire1.beginTransmission(mpu_serial_addr);
  Wire1.write(0x3B); 
  Wire1.endTransmission(false); 
  Wire1.requestFrom(mpu_serial_addr, 7*2, true); 

  mpu_60->ax = Wire1.read()<<8 | Wire1.read(); 
  mpu_60->ay = Wire1.read()<<8 | Wire1.read(); 
  mpu_60->az = Wire1.read()<<8 | Wire1.read(); 

  //mpu.accel_ang_x = RAD2DEG(-atan2((float)mpu.accel_x/16384.0, (float)mpu.accel_z/16384.0));
  //mpu.accel_ang_y = RAD2DEG(-atan2((float)mpu.accel_y/16384.0, (float)mpu.accel_z/16384.0));

  temperature = Wire1.read()<<8 | Wire1.read(); 
  mpu_60->gx = Wire1.read()<<8 | Wire1.read(); 
  mpu_60->gy = Wire1.read()<<8 | Wire1.read(); 
  mpu_60->gz = Wire1.read()<<8 | Wire1.read(); 

}


void mpu_data_loop(Euler_Angles_t *eul_ang)
{
  Quaternion_t *q;
  MPU_t *mpu_60 = &mpu;

  static unsigned long now = 0, last = 0;

  float Axyz[3];
  float Gxyz[3];


  Axyz[0] = (float) mpu_60->ax;
  Axyz[1] = (float) mpu_60->ay;
  Axyz[2] = (float) mpu_60->az; 

  for(int i = 0; i < 3; i++) 
  {
          Axyz[i] = (Axyz[i] - A_cal[i]) * A_cal[i + 3];
  }

  
  Gxyz[0] = ((float)mpu_60->gx - G_off[0]) * gscale);
  Gxyz[1] = ((float)mpu_60->gx - G_off[1]) * gscale);
  Gxyz[2] = ((float)mpu_60->gx - G_off[2]) * gscale);
  

  now = micros();
  deltat = (now - last) * 1.0e-6;
  last = now;

  Mahony_update(Axyz[0], Axyz[1], Axyz[2], Gxyz[0], Gxyz[1], Gxyz[2], deltat);

  Quaternion_2_Euler(q);
}

/*
 * detect a change in acceleration 
 * within the y direction
 */

void mpu_data_print(Euler_Angles_t *euler_ang)
{

	
  mpu_data_loop(euler_ang);

  static unsigned long now = 0, last = 0;
  now_ms = millis();


  /*Serial.print("aX = "); Serial.print(mpu.accel_ang_x);
  Serial.print("ang_aX = "); Serial.print(x);
  Serial.print(" | ang_aY = "); Serial.print(y);
  Serial.print(" | aZ = "); Serial.print(((float)z / 16384.0));

  Serial.print(" | tmp = "); Serial.print(temperature/340.00+36.53);

  Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
  Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
  Serial.print(" | gZ = "); Serial.print(convert_int16_to_str(gyro_z));
  */

        if(now_ms - last_ms >= print_ms)
        {
                last_ms = now_ms;
                Serial.print(euler_ang->yaw, 0);
                Serial.print(", ");
                Serial.print(euler_ang->pitch, 0);
                Serial.print(", ");
                Serial.println(euler_ang->roll, 0);
        }
}

