/* 
 * File:   motorControl_basic.h
 * Author: holemanj
 *
 * Created on August 15, 2014, 8:19 AM
 */

#ifndef MOTORCONTROL_BASIC_H
#define	MOTORCONTROL_BASIC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
/* Motor speed is tenths of a percent from 0 to 1000  */

void inline setMotorState(uint_fast16_t leftMotorSpeed, bool leftMotorForward,
    uint_fast16_t rightMotorSpeed, bool rightMotorForward);



#ifdef	__cplusplus
}
#endif

#endif	/* MOTORCONTROL_BASIC_H */

