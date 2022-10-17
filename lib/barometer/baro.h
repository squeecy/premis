#include <math.h>
#include <vector>
#include "imu/accel.h"
std::vector<double> store_altitude;

/*
 * estimated altitude from pressure
 * P0 - Pressure at sea level (pa)
 * P - Pressure at altitude (m)
 * T - Temperature
 */

double altitude(double P0, double P, double T)
{
       return ((pow((P0/P),(1/5.257)) - 1) * (T + 273.15)) / 0.0065;
}

double apogee_detect(double alt)
{

}

