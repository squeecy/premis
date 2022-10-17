#include "kalman.h"

static 
void variableUpdate()
{
        global._pos = X(0, 0);
        global._vel = X(1,0);
        global._acc = X(2,0);
}

static 
void kalmanInit()
{
        X = {
            0,
            0,
            0,
            };

        P = {0.001, 0, 0,
             0, 0.001, 0,
             0, 0, 0.001};
}

static
void predict()
{
        currentTime = micros();
        dt = (currentTime - prevTime) / 1000000.0f;
        prevTime = currentTime;

       F = {1, dt, (pow(dt,2) * 0.5), 
            0, 1, dt,
            0, 0, 1};
       X = F * X; 
}

static 
void baroUpdate(float altitude)
{
        //Insert raw data into array
        Z_Baro = {altitude}; 
        
        K_Baro = P * ~H_Baro * (H_Baro * P * ~H_Baro + R_Baro).Inverse();

        X = X + K_Baro * (Z_Baro - H_Baro * X);

        P = (I - K_Baro * H_Baro) * P * (~(I - K_Baro * H_Baro)) + K_Baro * R_Baro * ~K_Baro;

        variableUpdate();

}

static 
void acelUpdate(float accel)
{
    Z_Accel = {accel}; 
        
    K_Accel = P * ~H_Accel * (H_Accel * P * ~H_Accel + R_Accel).Inverse();

    X = X + K_Accel * (Z_Accel - H_Accel * X);

    P = (I - K_Accel * H_Accel) * P * (~(I - K_Accel * H_Accel)) + K_Accel * R_Accel* ~K_Accel;

    variableUpdate();

}

