/* 
 * File:   motorControl_user.h
 * Author: holemanj
 *
 * Created on August 15, 2014, 11:28 AM
 */

#ifndef MOTORCONTROL_USER_H
#define	MOTORCONTROL_USER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

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



#ifdef	__cplusplus
}
#endif

#endif	/* MOTORCONTROL_USER_H */

