/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* Define system operating frequency */
#define SYS_FREQ        8000000L
#define _XTAL_FREQ      8000000L

/* Microcontroller MIPs (FCY) */
#define FCY             SYS_FREQ/4

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureOscillator(void); /* Handles clock switching/osc initialization */
