#ifndef SERIALREAD__H
#define SERIALREAD__H
#include "serialclass.h"
#include <sstream>

typedef struct
{
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
}serialData_T;

void serialRead(serialData_T *data);
void serialDisconnect();

#endif
