/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */
/* Define system operating frequency */
#define SYS_FREQ        16000000L
#define _XTAL_FREQ      16000000L

/* Microcontroller MIPs (FCY) */
#define FCY             SYS_FREQ/4

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */
