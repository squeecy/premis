#ifndef ACCEL_H
#define ACCEL_H

#include "helper/helper.h"

struct
{
        float thetaM;
        float phiM;
        float thetaFold = 0;
        float thetaFnew;
        float phyFold = 0;
        float phyFnew;
}filter;
float low_filter(float old, float new_v,float input, float old_trust, float new_trust)
{
        return (old_trust * old) + new_trust;
}

#endif
