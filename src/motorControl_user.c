/*
 * File:   motorControl_user.c
 * Author: holemanj
 *
 * Created on August 15, 2014, 11:28 AM
 */
#include "motorControl_basic.h"
#include "motorControl_user.h"

void setMotorSpeedAndTurnRate(uint_fast16_t speed, float turnRate)
{
    int leftMotor, rightMotor;
    char leftDir, rightDir;

    if(turnRate < 0.0)  //right turn; right motor is "inside"
    {
        turnRate=-turnRate;

        rightMotor  = (int)(speed/(turnRate+1.0)) - (int)(351*turnRate);
        leftMotor   = (int)(speed/(turnRate+1.0)) + (int)(351*turnRate);
    }
    else //left turn
    {
        rightMotor  = (int)(speed/(turnRate+1.0)) + (int)(351*turnRate);
        leftMotor   = (int)(speed/(turnRate+1.0)) - (int)(351*turnRate);
    }

    if(leftMotor<0) //motor is going backward
    {
        leftDir=0;
        leftMotor=-leftMotor;
    }
    else leftDir = 1;

    if(rightMotor<0) //motor is going backward
    {
        rightDir=0;
        rightMotor=-rightMotor;
    }
    else rightDir = 1;

    setMotorState(leftMotor, leftDir, rightMotor, rightDir);
}

// "User-friendly" motor control functions:
void moveForward(uint_fast16_t speed)
{
    setMotorSpeedAndTurnRate(speed, 0.0);
}

void moveBackward(uint_fast16_t speed)
{
    setMotorSpeedAndTurnRate(-speed, 0.0);
}

void turnRight(float turnRate)
{
    setMotorSpeedAndTurnRate(0, -turnRate);
}
void turnLeft(float turnRate)
{
    setMotorSpeedAndTurnRate(0, turnRate);
}

void stop()
{
    setMotorSpeedAndTurnRate(0, 0.0);
}