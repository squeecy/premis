#ifndef PID_H
#define PID_H

typedef struct
{
	float proportional;
	float integral;

	float error;
	float prevError;

	float prevInput;

	float FREQ;

	float Kp;
	float Ki;

	float maxInteg;
	float minInteg;

	float maxResult;
	float minResult;

	float result;

}PIDController;


void pidInit(PIDController *pid);
float pidUpdate(PIDController *pid, float input, float setPoint);

#endif
