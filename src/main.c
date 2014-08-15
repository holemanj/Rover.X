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
#include "motorControl_user.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

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

