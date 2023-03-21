#include <Wire.h>
#include "SPI.h"
#include "baro.h"
//#include <Adafruit_Sensor.h>


void baro_Init() 
{
	bmp.begin(); 
	//Serial.begin(9600);
}

void set_Baro(barometer_t *baro)
{

	baro->pressure = bmp.readPressure();
	baro->temperature = bmp.readTemperature();
	baro->altitude= bmp.readAltitude(1019.6416);

	//Serial.println(baro->pressure);
}



//static
//void altitude(barometer_t *pressure, barometer_t *altitude, barometer_t *temperature)
//{
	
//}

static
double apogee_detect(double alt)
{
	return max(alt,alt);
}
