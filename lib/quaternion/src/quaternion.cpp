#include "Arduino.h"
#include "math.h"
#include "quaternion.h"



float Kp = 30.0;
float Ki = 0.0;

//From https://forum.arduino.cc/t/getting-quaternion-values-from-mpu6050/668823/2

Euler_Angles_t *  Mahony_update(float ax, float ay, float az, float gx, float gy, float gz, 
                float deltat) 
{
  Euler_Angles_t *eul_ang = calloc(sizeof (*eul_ang), 1);

  float recipNorm;
  float vx, vy, vz;
  float ex, ey, ez;  //error terms
  float qa, qb, qc;
  static float ix = 0.0, iy = 0.0, iz = 0.0;  //integral feedback terms
  float tmp;

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
    vx = eul_ang->q[1] * eul_ang->q[3] - eul_ang->q[0] * eul_ang->q[2];
    vy = eul_ang->q[0] * eul_ang->q[1] + eul_ang->q[2] * eul_ang->q[3];
    vz = eul_ang->q[0] * eul_ang->q[0] - 0.5f + eul_ang->q[3] * eul_ang->q[3];
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
  qa = eul_ang->q[0];
  qb = eul_ang->q[1];
  qc = eul_ang->q[2];
  eul_ang->q[0] += (-qb * gx - qc * gy - eul_ang->q[3] * gz);
  eul_ang->q[1] += (qa * gx + qc * gz - eul_ang->q[3] * gy);
  eul_ang->q[2] += (qa * gy - qb * gz + eul_ang->q[3] * gx);
  eul_ang->q[3] += (qa * gz + qb * gy - qc * gx);

  // renormalise quaternion
  recipNorm = 1.0 / sqrt(eul_ang->q[0] * eul_ang->q[0] + eul_ang->q[1] * eul_ang->q[1] + eul_ang->q[2] * eul_ang->q[2] + eul_ang->q[3] * eul_ang->q[3]);
  eul_ang->q[0] = eul_ang->q[0] * recipNorm;
  eul_ang->q[1] = eul_ang->q[1] * recipNorm;
  eul_ang->q[2] = eul_ang->q[2] * recipNorm;
  eul_ang->q[3] = eul_ang->q[3] * recipNorm;

  return eul_ang;
}

Quaternion_t *Euler_2_Quaternion(double yaw, double pitch, double roll)
{

		//Euler_Angles_t *eul_ang = calloc(sizeof (*eul_ang), 1);
        Quaternion_t *q = calloc(sizeof (*q), 1);
        double cy,sy,cp,sp,cr,sr;

        cy = cos(yaw/2.0);
        sy = sin(yaw/2.0);
        cp = cos(pitch/2.0);
        sp = sin(pitch/2.0);
        cr = cos(roll/2.0);
        sr = sin(roll/2.0);

        q->w = cr * cp * cy + sr * sp * sy;
        q->x = sr * cp * cy - cr * sp * sy;
        q->y = cr * sp * cy + sr * cp * sy;
        q->z = cr * cp * sy - sr * sp * cy;

        return q;
}



/*
 * q0 -> qw
 * q1 -> qx
 * q2 -> qy
 * q3 -> qz
 */
extern Euler_Angles_t *  Quaternion_2_Euler(Euler_Angles_t *angle)
{

        //yaw
        double sin_yaw = 2.0 * (angle->q[0] * angle->q[1] + angle->q[2] * angle->q[3]);
        double cos_yaw = 1.0 - 2.0 * (pow(angle->q[1], 2) + pow(angle->q[2], 2));
        angle->yaw = -atan2(sin_yaw, cos_yaw);
        
        //pitch
        double sinp = 2.0 * (angle->q[0] * angle->q[2] - angle->q[3] * angle->q[1]);
        //protect against over rotation
        if(abs(sinp) >= 1)
                angle->pitch = copysign(M_PI/2.0, sinp);
        else
                angle->pitch = asin(sinp);

        //roll
        double sinr = 2.0 * (angle->q[0]* angle->q[1] + angle->q[2] * angle->q[3]);
        double cosr = 1.0 - 2.0 * (pow(angle->q[1] , 2) + pow(angle->q[2], 2));
        angle->roll = atan2(sinr,cosr);

        return angle;
}
