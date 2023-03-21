#ifndef QUATERNION_H
#define QUATERNION_H
#include <cmath>

typedef struct
{
    float w, x, y, z;
    float q[4] = {1.0, 0.0, 0.0, 0.0};
}Quaternion_t;

typedef struct 
{
		float yaw;
		float pitch;
		float roll;
}Euler_Angles_t;


void Mahony_update(float,float,float,float,float,float,float, Quaternion_t *qua); 
void Euler_2_Quaternion(Euler_Angles_t *eul_ang, Quaternion_t *quat);
void Quaternion_2_Euler(Euler_Angles_t *eul_ang, Quaternion_t *quat);

#endif
