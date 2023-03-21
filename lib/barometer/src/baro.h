#include <Adafruit_BMP280.h>
#include <math.h>
#include <vector>
//#include "imu/accel.h"

static Adafruit_BMP280 bmp;

static std::vector<double> store_altitude;

typedef struct
{
	float pressure;
	float temperature;
	float altitude;
}barometer_t;

void baro_Init();


void set_Baro(barometer_t *baro);



/*
 * estimated altitude from pressure
 * P0 - Pressure at sea level (pa)
 * P - Pressure at altitude (m)
 * T - Temperature
 */
//static
//void altitude(barometer_t *pressure, barometer_t *altitude, barometer_t *temperature);

static double apogee_detect(double alt);
