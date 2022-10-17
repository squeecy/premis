#ifndef QUATERNION_H
#define QUATERNION_H
#include <cmath>


typedef struct 
{
        float w, x, y, z;
}Quaternion_t;

typedef struct 
{
        float q[4] = {1.0, 0.0, 0.0, 0.0};
        float yaw, pitch, roll;
}Euler_Angles_t;

//Euler_Angles_t  *euler_ang = &Euler_Angles_t;

Euler_Angles_t *Mahony_update(float,float,float,float,float,float,float); 
extern Quaternion_t *Euler_2_Quaternion(double,double,double);
Euler_Angles_t Quaternion_2_Euler(Quaternion_t *q);

#endif
