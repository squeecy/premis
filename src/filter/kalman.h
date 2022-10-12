#ifndef KALMAN_H
#define KALMAN_H

#include "global/global.h"
#include "math.h"
#include "BasicLinearAlgebra.h"
#define CONFIG_FILE_FILTER "src/filter/filter.txt"

static unsigned long currentTime = 0, prevTime = 0;
static float dt = 0.0f;


static BLA::Matrix<3,1> X = {0,
                      0,
                      0};

static BLA::Matrix<3,3> F;


static BLA::Matrix<3,3> I = {1,0,0,
                      0,1,0,
                      0,0,1};

static BLA::Matrix<3,3> P = {10, 0,0, 
                      0, 1, 0,
                      0, 0, 100};

static BLA::Matrix<3,3> Q = {0.1, 0, 0,
                      0, 0.1, 0,
                      0, 0, 10};

static BLA::Matrix<1,1> Z_Baro;
static BLA::Matrix<1,1> Z_Accel;
static BLA::Matrix<3,1> K_Baro;
static BLA::Matrix<3,1> K_Accel;
static BLA::Matrix<1,1> R_Baro = {10};
static BLA::Matrix<1,1> R_Accel = {10};

static BLA::Matrix<1,3> H_Baro;
static BLA::Matrix<1,3> H_Accel;


static 
void variableUpdate();

static 
void kalmanInit();

static
void predict();

static 
void baroUpdate(float altitude);

static 
void acelUpdate(float accel);

#endif
