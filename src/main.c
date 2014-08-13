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

#include "../header/system.h"        /* System funct/params, like osc/peripheral config */
#include "../header/user.h"          /* User funct/params, such as InitApp */

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/******************************************************************************/
/* Function Prototypes                                                        */
/******************************************************************************/

void inline setMotorDutyCycles(int leftMotor, char leftMotorForward,
        int rightMotor, char rightMotorForward);

//  When the PWM duty cycle, and motor direction have been computed, use
//  this function to set the appropriate registers
//  "inline" used to avoid extra function call

void setMotorSpeedAndTurnRate(int speed, float turnRate);
//  "Primary" control function.
//  Sets motor state for desired wheel speed, including differential speed
//  speed: tenths of a percent of duty cycle for PWM; negative it backward
//  turnRate: rad/sec; positive = CCW, negative = CW

// "User-friendly" motor control functions:
void moveForward(int speed);
//  speed: PWM duty cycle, tenths of percent
//  equivalent to setMotorSpeedAndTurnRate(speed, 0.0)

void moveBackward(int speed);
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
    /* Configure the oscillator for the device */
    ConfigureOscillator();

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

void inline setMotorDutyCycles(int leftMotor, char leftMotorForward,
    int rightMotor, char rightMotorForward)
{
    //Enforce PWM value limits
    if(leftMotor>0b1111111111) leftMotor = 0b1111111111;
    if(leftMotor<0) leftMotor = 0;

    if(rightMotor>0b1111111111) rightMotor = 0b1111111111;
    if(rightMotor<0) rightMotor = 0;

    //Set low PWM bits
    CCP1CONbits.DC1B = leftMotor % 4;
    CCP2CONbits.DC2B = rightMotor % 4;

    //Set high PWM bits
    CCPR1L = leftMotor >> 2;
    CCPR2L = rightMotor >> 2;

    //Set motor directions
    LATCbits.LATC0 = leftMotorForward; //Set direction for RC0
    LATCbits.LATC5 = rightMotorForward; //Set direction for RC5
}

void setMotorSpeedAndTurnRate(int speed, float turnRate)
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

    setMotorDutyCycles(leftMotor, leftDir, rightMotor, rightDir);
}

// "User-friendly" motor control functions:
void moveForward(int speed)
{
    setMotorSpeedAndTurnRate(speed, 0.0);
}

void moveBackward(int speed)
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