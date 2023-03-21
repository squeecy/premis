#include <pid.h>

/*
 * Initialize PIDController struct
 * 
 * @param *pid PIDController struct
 */

void pidInit(PIDController *pid)
{
	pid->proportional = 0.0f;
	pid->integral = 0.0f;
	pid->error = 0.0f;
	pid->prevError = 0.0f;
	pid->result = 0.0f;

	pid->FREQ = 0.30f;

	pid->Kp = 2.0f;
	pid->Ki = 0.75f;

	pid->maxInteg = 7.0f;
	pid->minInteg = -7.0f;

	//16 degrees of servo rotation
	pid->maxResult = 16.0f; 
	pid->minResult = -16.0f; 

}

/*
 * Update and run PID Controller
 *
 * @param *pid calls PIDController struct
 * @param input takes system input
 * @param setPoint the point you wish the PID to stay at
 * @return required devation
 */
float pidUpdate(PIDController *pid, float input,  float setPoint)
{

	float maxInteg_l,minInteg_l;

	pid->error = setPoint - input;

	pid->proportional = pid->Kp * pid->error;

	pid->integral += (((pid->Ki * pid->FREQ) / 2.0f) * (pid->error + pid->prevError));

	//clamping integrator (anti windup)
	if(pid->maxInteg > pid->proportional)
		maxInteg_l = pid->maxInteg - pid->proportional;
	else
		maxInteg_l = 0.0f;
	if(pid->minInteg < pid->proportional)
		minInteg_l = pid->minInteg - pid->proportional;
	else
		minInteg_l = 0.0f;

	pid->result = pid->proportional + pid->integral;

	//limit PID values to our hardware limits
	if(pid->result > pid->maxResult)
		pid->result = pid->maxResult;
	else if(pid->result < pid->minResult)
		pid->result = pid->minResult;


	//update variables
	pid->prevError = pid->error;
	pid->prevInput = input;  

	return pid->result;
}
