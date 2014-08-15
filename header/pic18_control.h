/* 
 * File:   pic18_control.h
 * Author: holemanj
 *
 * Created on August 14, 2014, 12:30 PM
 */

#ifndef PIC18_CONTROL_H
#define	PIC18_CONTROL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

    void setPWM_RC1(uint_fast16_t newDutyCycle);
    void setPWM_RC2(uint_fast16_t newDutyCycle);
    void setPWM_RC1_dir_RC0(uint_fast16_t newDutyCycle, bool forward);
    void setPWM_RC2_dir_RC5(uint_fast16_t newDutyCycle, bool forward);

    /* adjust functions return true if modification successful*/

    bool adjustPWM_RC1(int_fast8_t change);
    bool adjustPWM_RC2(int_fast8_t change);


#ifdef	__cplusplus
}
#endif

#endif	/* PIC18_CONTROL_H */

