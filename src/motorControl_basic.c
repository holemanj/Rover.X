/*
 * File:   motorControl_basic.c
 * Author: holemanj
 *
 * Created on August 15, 2014, 8:19 AM
 */

#include "motorControl_basic.h"

void inline setMotorState(uint_fast16_t leftMotorSpeed, bool leftMotorForward,
    uint_fast16_t rightMotorSpeed, bool rightMotorForward)
{
  setPWM_RC1_dir_RC0(leftMotorSpeed, leftMotorForward);
  setPWM_RC2_dir_RC5(rightMotorSpeed, rightMotorForward);
}

