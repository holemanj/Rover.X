/*
 * File:   pic18_init.c
 * Author: holemanj
 *
 * Created on August 13, 2014, 3:12 PM
 * This holds code for hardware-level (PIC18F45k20) initialization routines
 */

#include "pic18_init.h"

/* Define system operating frequency */
#define SYS_FREQ        16000000L
#define _XTAL_FREQ      16000000L

/* Microcontroller MIPs (FCY) */
#define FCY             SYS_FREQ/4


void initPic18Hardware()
{
  /* First configure oscillator; make sure this configuration is */
  /* consistent with the macros defined above */
  OSCCON = 0b01110000;    //16MHz on main clock - 4MHz instruction clock

  /* TODO Initialize User Ports/Peripherals/Project here */

  /* Setup analog functionality and port direction */

  //Port A not used for now - set as digital inputs
  TRISA = 0xFF;

  //Port B is all digital inputs - motor speed pulses
  TRISB = 0xFF;

  //Port C RC1 and RC2 are PWM outputs. Intialize at outputs - they will be changed later
  //      RC0 and RC5 are direction outputs
  //      Rest are currently unused - set as inputs
  TRISC = 0b11011110;

  //Port D not used for now - set as digital inputs

  TRISD = 0x00;
  //Port E not used for now - set as digital inputs
  TRISE = 0x00;

  /* Initialize peripherals */
  //CCP1 and CCP2 set upfor PWM

  PR2 = 0xFF;     //For 10 bit resolution on the PWM - maybe change later for higher frequency

  CCP1CON = 0b00111100;   //Note - LSb for duty cycle is 11 for 1st 100% experiment
  CCP2CON = 0b00111100;   //Note - LSb for duty cycle is 11 for 1st 100% experiment
                          //After experiments, initialize to zero

  CCPR1L = 0x00;          //Initialize to zero speed
  CCPR2L = 0xA0;

  PIR1bits.TMR2IF = 0;
  T2CONbits.TMR2ON = 1;



  while(PIR1bits.TMR2IF==0);  //Wait for first PWM cycle

  TRISC = 0b11011000; //Enable outputs

  PIR1bits.TMR1IF = 0;

  /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */
  RCONbits.IPEN = 1;

  /* Enable interrupts */

}