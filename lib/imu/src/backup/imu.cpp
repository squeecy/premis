/*
#include "accel.h"
#include "quaternion.h"
#include "quaternion.cpp"

double accelX;

void mpu_setup()
{
  Wire1.setSCL(19);
  Wire1.setSDA(18);
  Wire1.begin();
  Wire1.beginTransmission(mpu_serial_addr); 
  Wire1.write(0x6B); // PWR_MGMT_1 register
  Wire1.write(0); // set to zero (wakes up the MPU-6050)
  Wire1.endTransmission(true);
}

void mpu_data_raw(struct MPU_t mpu_l)
{


	
  //MPU_t mpu;
  //MPU_t *mpu_60 = &mpu;
  

  Wire1.beginTransmission(mpu_serial_addr);
  Wire1.write(0x3B); 
  Wire1.endTransmission(false); 
  Wire1.requestFrom(mpu_serial_addr, 7*2, true); 

  accelX = Wire1.read()<<8 | Wire1.read(); 
  mpu_l.ay = Wire1.read()<<8 | Wire1.read(); 
  mpu_l.az = Wire1.read()<<8 | Wire1.read(); 

  //mpu.accel_ang_x = RAD2DEG(-atan2((float)mpu.accel_x/16384.0, (float)mpu.accel_z/16384.0));
  //mpu.accel_ang_y = RAD2DEG(-atan2((float)mpu.accel_y/16384.0, (float)mpu.accel_z/16384.0));

  temperature = Wire1.read()<<8 | Wire1.read(); 
  mpu_l.gx = Wire1.read()<<8 | Wire1.read(); 
  mpu_l.gy = Wire1.read()<<8 | Wire1.read(); 
  mpu_l.gz = Wire1.read()<<8 | Wire1.read(); 

}


void mpu_data_loop()
{

  MPU_t mpu_66;
  mpu_data_raw(mpu_x);

  Quaternion_t *q;
  MPU_t mpu_h;
  MPU_t *mpu_60 = &mpu_h;

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

  Quaternion_2_Euler();
}

//
 //detect a change in acceleration 
 // within the y direction
 //

void mpu_data_print()
{

  Euler_Angles_t eul;
  Euler_Angles_t *euler_ang = &eul;

	
  mpu_data_raw(mpu_x);
  mpu_data_loop();

  static unsigned long now = 0, last = 0;
  now_ms = millis();


  //Serial.print("aX = "); Serial.print(mpu.accel_ang_x);
  //Serial.print("ang_aX = "); Serial.print(x);
  //Serial.print(" | ang_aY = "); Serial.print(y);
  //Serial.print(" | aZ = "); Serial.print(((float)z / 16384.0));

  //Serial.print(" | tmp = "); Serial.print(temperature/340.00+36.53);

  //Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
  //Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
  //Serial.print(" | gZ = "); Serial.print(convert_int16_to_str(gyro_z));
  

        if(now_ms - last_ms >= print_ms)
        {
				int test = 5;

                last_ms = now_ms;
                Serial.print(accelX, 0);
                Serial.print(", ");
                Serial.print(euler_ang->pitch, 0);
                Serial.print(", ");
                Serial.println(euler_ang->roll, 0);
        }
}

*/
