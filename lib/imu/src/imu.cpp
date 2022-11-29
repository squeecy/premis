#include <Wire.h>
#include <accel.h>
#include <quaternion.h>

#define gscale ((250./32768.0) * (M_PI/180.0))
float A_cal[6] = {265.0, -80.0, -700.0, 0.994, 1.000, 1.014};
float G_off[3] = {-499.5, -17.7, -82.0};

const int MPU_ADR = 0x68; // MPU6050 I2C address

float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
float AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;

unsigned long now_ms, last_ms = 0;
float oldTime = 0;
int c = 0;

float Axyz[3];
float Gxyz[3];

//initialize MPU6050
void configure() {

  Wire.begin(); //Initialize comunication
  Serial.begin(9600); //Serial information printing to 9600 
  Wire.beginTransmission(MPU_ADR); // Start communication with MPU6050 // MPU=0x68
  Wire.write(0x6B); // Talk to the register 6B
  Wire.write(0); // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true); //end the transmission
}


//capture MPU6050 raw values
//@Param1 struct MPU_T
void mpu_raw_data(mpu_T *mpu_s)
{
  //initialize for reading data
  Wire.beginTransmission(MPU_ADR);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADR, 14, true); // Read 6 registers total, each axis value is stored in 2 registers

  //read raw MPU
  int t = Wire.read() << 8;
  mpu_s->ax = t | Wire.read(); // X-axis value
  t = Wire.read() << 8;
  mpu_s->ay = t | Wire.read(); // Y-axis value
  t = Wire.read() << 8;
  mpu_s->az = t | Wire.read(); // Z-axis value
  t = Wire.read() << 8;

  mpu_s->gx = t | Wire.read(); // For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
  t = Wire.read() << 8;
  mpu_s->gy = t | Wire.read();
  t = Wire.read() << 8;
  mpu_s->gz = t | Wire.read();
  
  
  //set raw mpu data to array 
  //[0] == x | [1] == y | [2] == z

  //The MPU6050 will be positioned vertically, so we change the orientation of 
  //the raw data. y = inverse(Z) , Z = Y
  Axyz[0] = (float) mpu_s->ax;
  Axyz[1] = (float) -mpu_s->az; 
  Axyz[2] = (float) mpu_s->ay;

  //apply offests and scale factors from Magneto
  for (int i = 0; i < 3; i++)
  {
	  Axyz[i] = (Axyz[i] - A_cal[i]) * A_cal[i + 3];
  }

  Gxyz[0] = ((float) mpu_s->gx - G_off[0]) * gscale;
  Gxyz[1] = ((float) mpu_s->gy - G_off[1]) * gscale;
  Gxyz[2] = ((float) mpu_s->gz - G_off[2]) * gscale;
}

//Converts MPU data
void mpu_loop() 
{

  static float deltat = 0;
  static unsigned long now = 0, last = 0;

  Quaternion_t quat;
  mpu_T mpu_s;
  Euler_Angles_t eul;


  mpu_raw_data(&mpu_s);


  now = micros();
  d_t = (now - last) * 1.0e-6; //change in time
  last = now;

  Mahony_update(Axyz[0], Axyz[1], Axyz[2], Gxyz[0], Gxyz[1], Gxyz[2], d_t,
		  &quat); //Convert raw values to Quanternion values

  Quaternion_2_Euler(&eul, &quat); //Convert Quanternion values to yaw, pitch roll

  
  //print serial data
  Serial.println(eul.yaw);
  Serial.println(eul.pitch);
  Serial.println(eul.roll);
 
}

void calculate_IMU_error() {
  // We can call this funtion in the setup section to calculate the accelerometer and gyro data error. From here we will get the error values used in the above equations printed on the Serial Monitor.
  // Note that we should place the IMU flat in order to get the proper values, so that we then can the correct values
  // Read accelerometer values 200 times
  while (c < 200) {
    Wire.beginTransmission(MPU_ADR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADR, 6, true);
    AccX = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    AccY = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0 ;
    // Sum all readings
    AccErrorX = AccErrorX + ((atan((AccY) / sqrt(pow((AccX), 2) + pow((AccZ), 2))) * 180 / PI));
    AccErrorY = AccErrorY + ((atan(-1 * (AccX) / sqrt(pow((AccY), 2) + pow((AccZ), 2))) * 180 / PI));
    c++;
  }
  //Divide the sum by 200 to get the error value
  AccErrorX = AccErrorX / 200;
  AccErrorY = AccErrorY / 200;
  c = 0;
  // Read gyro values 200 times
  while (c < 200) {
    Wire.beginTransmission(MPU_ADR);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADR, 6, true);
    GyroX = Wire.read() << 8 | Wire.read();
    GyroY = Wire.read() << 8 | Wire.read();
    GyroZ = Wire.read() << 8 | Wire.read();
    // Sum all readings
    GyroErrorX = GyroErrorX + (GyroX / 131.0);
    GyroErrorY = GyroErrorY + (GyroY / 131.0);
    GyroErrorZ = GyroErrorZ + (GyroZ / 131.0);
    c++;
  }
  //Divide the sum by 200 to get the error value
  GyroErrorX = GyroErrorX / 200;
  GyroErrorY = GyroErrorY / 200;
  GyroErrorZ = GyroErrorZ / 200;
  // Print the error values on the Serial Monitor
  Serial.print("AccErrorX: ");
  Serial.println(AccErrorX);
  Serial.print("AccErrorY: ");
  Serial.println(AccErrorY);
  Serial.print("GyroErrorX: ");
  Serial.println(GyroErrorX);
  Serial.print("GyroErrorY: ");
  Serial.println(GyroErrorY);
  Serial.print("GyroErrorZ: ");
  Serial.println(GyroErrorZ);
}
