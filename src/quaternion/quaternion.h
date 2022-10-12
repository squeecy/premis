#ifndef QUATERNION_H
#define QUATERNION_H
#include <cmath>

typedef struct Quaternion_s Quaternion_t;
typedef struct Euler_Angles_s Euler_Angles_t;

Euler_Angles_t Mahony_update(float,float,float,float,float,float,float); 
Quaternion_t Euler_2_Quaternion(double,double,double);
Euler_Angles_t Quaternion_2_Euler(Quaternion_t *q);

#endif
