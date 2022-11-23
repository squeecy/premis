#include "Arduino.h"
#include "math.h"
#include "quaternion.h"



float Kp = 30.0;
float Ki = 0.0;

//From https://forum.arduino.cc/t/getting-quaternion-values-from-mpu6050/668823/2

void Mahony_update(float ax, float ay, float az, float gx, float gy, float gz, 
                float deltat, Quaternion_t *qua) 
{
  //eul_ang = (struct Euler_Angles_t*)
	  //malloc(sizeof(struct Euler_Angles_t));

  //Euler_Angles_t *eul_ang = calloc(sizeof (*eul_ang), 1);
  //Euler_Angles_t eul;

  //Euler_Angles_t *eul_ang = &eul;

  float recipNorm;
  float vx, vy, vz;
  float ex, ey, ez;  //error termyaws
  float qa, qb, qc;
  static float ix = 0.0, iy = 0.0, iz = 0.0;  //integral feedback terms
  float tmp;

  //Serial.println(deltat);
  // Compute feedback only if accelerometer measurement valid (avoids NaN in accelerometer normalisation)
  tmp = ax * ax + ay * ay + az * az;
  if (tmp > 0.0)
  {

    // Normalise accelerometer (assumed to measure the direction of gravity in body frame)
    recipNorm = 1.0 / sqrt(tmp);
    ax *= recipNorm;
    ay *= recipNorm;
    az *= recipNorm;

    // Estimated direction of gravity in the body frame (factor of two divided out)
    vx = qua->q[1] * qua->q[3] - qua->q[0] * qua->q[2];
    vy = qua->q[0] * qua->q[1] + qua->q[2] * qua->q[3];
    vz = qua->q[0] * qua->q[0] - 0.5f + qua->q[3] * qua->q[3];
// Error is cross product between estimated and measured direction of gravity in body frame
    // (half the actual magnitude)
    ex = (ay * vz - az * vy);
    ey = (az * vx - ax * vz);
    ez = (ax * vy - ay * vx);

    // Compute and apply to gyro term the integral feedback, if enabled
    if (Ki > 0.0f) {
      ix += Ki * ex * deltat;  // integral error scaled by Ki
      iy += Ki * ey * deltat;
      iz += Ki * ez * deltat;
      gx += ix;  // apply integral feedback
      gy += iy;
      gz += iz;
    }

    // Apply proportional feedback to gyro term
    gx += Kp * ex;
    gy += Kp * ey;
    gz += Kp * ez;
  }

  // Integrate rate of change of quaternion, q cross gyro term
  deltat = 0.5 * deltat;
  gx *= deltat;   // pre-multiply common factors
  gy *= deltat;
  gz *= deltat;
  qa = qua->q[0];
  qb = qua->q[1];
  qc = qua->q[2];
  qua->q[0] += (-qb * gx - qc * gy - qua->q[3] * gz);
  qua->q[1] += (qa * gx + qc * gz - qua->q[3] * gy);
  qua->q[2] += (qa * gy - qb * gz + qua->q[3] * gx);
  qua->q[3] += (qa * gz + qb * gy - qc * gx);

  // renormalise quaternion
  recipNorm = 1.0 / sqrt(qua->q[0] * qua->q[0] + qua->q[1] * qua->q[1] + qua->q[2] * qua->q[2] + qua->q[3] * qua->q[3]);
  qua->q[0] = qua->q[0] * recipNorm;
  qua->q[1] = qua->q[1] * recipNorm;
  qua->q[2] = qua->q[2] * recipNorm;
  qua->q[3] = qua->q[3] * recipNorm;


}

/*
void Euler_2_Quaternion(double yaw, double pitch, double roll, double &Q1,
		double &Q2, double &Q3, double &Q4)
{

        double cy,sy,cp,sp,cr,sr;

        cy = cos(yaw/2.0);
        sy = sin(yaw/2.0);
        cp = cos(pitch/2.0);
        sp = sin(pitch/2.0);
        cr = cos(roll/2.0);
        sr = sin(roll/2.0);

        Q1 = cr * cp * cy + sr * sp * sy;
        Q2 = sr * cp * cy - cr * sp * sy;
        Q3 = cr * sp * cy + sr * cp * sy;
        Q4 = cr * cp * sy - sr * sp * cy;

}
*/



/*
 * q0 -> qw
 * q1 -> qx
 * q2 -> qy
 * q3 -> qz
 */
/*
void Quaternion_2_Euler(Euler_Angles_t *eul_ang, Quaternion_t *quat)
{

		//Quaternion_t *quat;

		//quat = malloc(sizeof(Quaternion_t));

		//Quaternion_t quats;

		
	//	Euler_Angles_t eul;
	//	Euler_Angles_t *angle = &eul;

        //yaw
        double sin_yaw = 2.0 * (quat->q[0] * quat->q[1] + quat->q[2] * quat->q[3]);
        double cos_yaw = 1.0 - 2.0 * (pow(quat->q[1], 2) + pow(quat->q[2], 2));
        eul_ang->yaw = -atan2(sin_yaw, cos_yaw);
        
		//Serial.print("/");
        //pitch
        double sinp = 2.0 * (quat->q[0] * quat->q[2] - quat->q[3] * quat->q[1]);
        //protect against over rotation
        if(abs(sinp) >= 1)
                eul_ang->pitch = copysign(M_PI/2.0, sinp);
        else
                eul_ang->pitch = asin(sinp);

        //roll
        double sinr = 2.0 * (quat->q[0]* quat->q[1] + quat->q[2] * quat->q[3]);
        double cosr = 1.0 - 2.0 * (pow(quat->q[1] , 2) + pow(quat->q[2], 2));
        eul_ang->roll = atan2(sinr,cosr);
		//Serial.println(quat->q[2]);
		//Serial.println(eul_ang->roll);
}
*/



void Quaternion_2_Euler(Euler_Angles_t *eul_ang, Quaternion_t *quat)
{

		//Quaternion_t *quat;

		//quat = malloc(sizeof(Quaternion_t));

		//Quaternion_t quats;

		
	//	Euler_Angles_t eul;
	//	Euler_Angles_t *angle = &eul;

        //yaw
        eul_ang->yaw = -atan2((quat->q[1] * quat->q[2] + quat->q[0] * quat->q[3]), 
				0.5 - (pow(quat->q[2],2) + pow(quat->q[3], 2)));
		eul_ang->yaw *= 180.0 / M_PI;
		if(eul_ang->yaw < 0)
			eul_ang->yaw += 360.0;
        
        //pitch
        eul_ang->pitch = asin(2.0 * (quat->q[0] * quat->q[2] - quat->q[1] * quat->q[3]));
		eul_ang->pitch *= 180.0 / M_PI;

        //roll
        eul_ang->roll = atan2((quat->q[0] * quat->q[1] + quat->q[2] * quat->q[3]),
			0.5 - (pow(quat->q[1],2) + pow(quat->q[2],2)));
		eul_ang->roll *= 180.0 / M_PI;
}
