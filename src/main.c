/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif

#include "user.h"          /* User funct/params, such as InitApp */
#include "motorControl_basic.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Function Prototypes                                                        */
/******************************************************************************/

void setMotorSpeedAndTurnRate(uint_fast16_t speed, float turnRate);
//  "Primary" control function.
//  Sets motor state for desired wheel speed, including differential speed
//  speed: tenths of a percent of duty cycle for PWM; negative it backward
//  turnRate: rad/sec; positive = CCW, negative = CW

// "User-friendly" motor control functions:
void moveForward(uint_fast16_t speed);
//  speed: PWM duty cycle, tenths of percent
//  equivalent to setMotorSpeedAndTurnRate(speed, 0.0)

void moveBackward(uint_fast16_t speed);
//  speed: PWM duty cycle, tenths of percent
//  equivalent to setMotorSpeedAndTurnRate(-speed, 0.0)

void turnRight(float turnRate);
//  turnRate: rad/Sec (assume positive, if negative, left turn)
//  equivalent to setMotorSpeedAndTurnRate(0, -turnRate)

void turnLeft(float turnRate);
//  turnRate: rad/Sec (assume positive, if negative, right turn)
//  equivalent to setMotorSpeedAndTurnRate(0, turnRate)

void stop();
// equivalent to setMotorSpeedAndTurnRate(0, 0.0)


/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    int i, j;
    float angle = -3.14;

    /* Initialize I/O and Peripherals for application */
    InitApp();

    /* TODO <INSERT USER APPLICATION CODE HERE> */

    while(1)
    {
        for(i=0; i<256; i++)
        {
            angle = (float)(i-128) * 0.0078125;
            setMotorSpeedAndTurnRate(700,angle);

            __delay_ms(40);
        }

        for(i=256;i>0; i--)
        {
            angle = (float)(i-128) * 0.0078125;
            setMotorSpeedAndTurnRate(700,angle);

            __delay_ms(40);
        }
    }
}

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