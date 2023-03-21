#include "Arduino.h"
#include "math.h"
#include "quaternion.h"
#define RAD_TO_DEG 57.295779513082320876798154814105  // 180/PI


/*
 * credit https://forum.arduino.cc/t/getting-quaternion-values-from-mpu6050/668823/2
 *
 * Converts raw IMU data to Quanternion data
 *
 * respected accelerometer
 * @param ax
 * @param ay
 * @param az
 *
 * respected gyroscope
 * @param gx
 * @param gy
 * @param gz
 * @param dt change in time
 * @param *qua Quaternion_t struct
 *
 * @note returns to Quaternion_t struct
 */
void Mahony_update(float ax, float ay, float az, float gx, float gy, float gz, 
                float deltat, Quaternion_t *qua) 
{

  float recipNorm;
  float vx, vy, vz;
  float ex, ey, ez;  //error termyaws
  float qa, qb, qc;
  static float ix = 0.0, iy = 0.0, iz = 0.0;  //integral feedback terms
  float tmp;
  float Kp = 30.0;
  float Ki = 0.0;

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
 * Converts Euler Angle to Quaternion
 *
 * @param *eul_ang Euler_Angles_t struct
 * @param *quat Quaternion_t struct
 * 
 * @note returns to Quaternion_t struct
 */
void Euler_2_Quaternion(Euler_Angles_t *eul_ang, Quaternion_t *quat)
{

        double cy,sy,cp,sp,cr,sr;

        cy = cos(eul_ang->yaw/2.0);
        sy = sin(eul_ang->yaw/2.0);
        cp = cos(eul_ang->pitch/2.0);
        sp = sin(eul_ang->pitch/2.0);
        cr = cos(eul_ang->roll/2.0);
        sr = sin(eul_ang->roll/2.0);

        quat->q[0] = cr * cp * cy + sr * sp * sy;
        quat->q[1] = sr * cp * cy - cr * sp * sy;
        quat->q[2] = cr * sp * cy + sr * cp * sy;
        quat->q[3] = cr * cp * sy - sr * sp * cy;

}

/*
 * Converts Quaternion to Euler Angle (Yaw Pitch Roll)
 *
 * @param *eul_ang Euler_Angles_t struct
 * @param *quat Quaternion_t struct
 *
 * @note returns to eul_ang struct
 */
void Quaternion_2_Euler(Euler_Angles_t *eul_ang, Quaternion_t *quat)
{
		/*
		q.w = q[0] 
		q.x = q[1]
		q.y = q[2]
		q.z = q[3]
		*/

        //yaw
        double sin_yaw = 2.0 * (quat->q[0] * quat->q[3] + quat->q[1] * quat->q[2]);
        double cos_yaw = 1.0 - 2.0 * (pow(quat->q[2], 2) + pow(quat->q[3], 2));
        eul_ang->yaw = atan2(sin_yaw, cos_yaw) * RAD_TO_DEG;
        
        //pitch
        double sinp = 2.0 * (quat->q[0] * quat->q[2] - quat->q[3] * quat->q[1]);
        //protect against over rotation
        if(abs(sinp) >= 1)
                eul_ang->pitch = 90.0;
        else if(abs(sinp) <= -1.0)
                eul_ang->pitch = -90.0;
		else
			eul_ang->pitch = asin(sinp) * RAD_TO_DEG;

        //roll
        double sinr = 2.0 * (quat->q[0]* quat->q[1] + quat->q[2] * quat->q[3]);
        double cosr = 1.0 - 2.0 * (pow(quat->q[1] , 2) + pow(quat->q[2], 2));
        eul_ang->roll = atan2(sinr,cosr) * RAD_TO_DEG;



}
