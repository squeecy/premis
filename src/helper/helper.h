#include "Arduino.h"
#define EARTH_GRAVITY 9.80665
#define RAD2DEG(x) ((x) * (180/M_PI)) /*radian to degree*/
#define DEG2RAD(x) ((x) * (M_PI/180)) /*degree to radian*/

/*
 * Length and velocity conversions
 */

#define FEET2MET(x) ((x) * 0.3048) /*feet to meter*/
#define IN2MM(x) ((x) * 25.4) /*inch to mm */
#define IN2MET(x) ((x) / 39.37) /*inch to meter*/
#define MET2FEET(x) ((x) * 3.2808398950131) /*meters to feet*/

/*
 * environment conversions and constants
 */

#define FAH2C(f)        (((f) - 32) * 0.555555) /*fahrenheit to celcius*/
#define C2FAH(c)        (((c) * 1.8) + 32) /*celcius to fahrenheit*/
#define FAH2KELVIN(f)   (((f) + 459.67) * 0.5555555555) /*fahrenheit to kelvin*/
#define KELVIN2FAH(k)   (((k) * 1.8) - 459.67) /*kelvin to fahrenheit*/
#define KELVIN2C(k)     (((k) - 273.15) /*kelvin to celcius*/
#define MOLAR_MASS 0.0289644

char tmp_str[7]; // temporary variable used in convert function
char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

float int32tofloat(int32_t x, float place_v)
{
        return (float)x / place_v;
}
