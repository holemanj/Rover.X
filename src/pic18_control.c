/*
 * File:   pic18_control.c
 * Author: holemanj
 *
 * Created on August 13, 2014, 3:12 PM
 * This holds code for hardware-level (PIC18F45k20) initialization routines
 */

#include "pic18_control.h"

void setPWM_RC1(uint_fast16_t newDutyCycle)
{
  //Enforce PWM 10-bit value limits
  if(newDutyCycle>0b1111111111) newDutyCycle = 0b1111111111;
  if(newDutyCycle<0) newDutyCycle = 0;

  //Set low PWM bits
  CCP1CONbits.DC1B = newDutyCycle % 4;

  //Set high PWM bits
  CCPR1L = newDutyCycle >> 2;
}

void setPWM_RC1_dir_RC0(uint_fast16_t newDutyCycle, bool forward)
{
  setPWM_RC1(newDutyCycle);

  /* set direction output */
  LATCbits.LATC0 = forward? 1: 0;
}

void setPWM_RC2(uint_fast16_t newDutyCycle)
{
  //Enforce PWM 10-bit value limits
  if(newDutyCycle>0b1111111111) newDutyCycle = 0b1111111111;
  if(newDutyCycle<0) newDutyCycle = 0;

  //Set low PWM bits
  CCP2CONbits.DC2B = newDutyCycle % 4;

  //Set high PWM bits
  CCPR2L = newDutyCycle >> 2;
}
void setPWM_RC2_dir_RC5(uint_fast16_t newDutyCycle, bool forward)
{
  setPWM_RC2(newDutyCycle);
  /* set direction output */
  LATCbits.LATC5 = forward? 1: 0;
}


bool adjustPWM_RC1(int_fast8_t change)
{
  bool success = true;

  uint_fast16_t PWM =
          (CCPR1L << 2)
          + (0b00000011 & CCP1CONbits.DC1B)
          +change;

  if(PWM > 0b1111111111)
  {
    PWM = 0b1111111111;
    success = false;
  }

  setPWM_RC1(PWM);

  return success;
}

bool adjustPWM_RC2(int_fast8_t change)
{
  bool success = true;

  uint_fast16_t PWM =
          (CCPR2L << 2)
          + (0b00000011 & CCP2CONbits.DC2B)
          +change;

  if(PWM > 0b1111111111)
  {
    PWM = 0b1111111111;
    success = false;
  }

  setPWM_RC2(PWM);

  return success;
}
