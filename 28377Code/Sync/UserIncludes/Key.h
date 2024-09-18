/*
 * Key.h
 *
 *  Created on: 2024Äê7ÔÂ22ÈÕ
 *      Author: Mengfanbin
 */

#ifndef USERINCLUDES_KEY_H_
#define USERINCLUDES_KEY_H_

#include "F28x_Project.h"

/*----------------------------------------MACRO DEFINE-----------------------------------------------*/
#define KEY_SCAN_FREQ   ((Uint32)10000)                         // The frequency of key scanning
#define KEY_SEC(x)  (Uint32)((float)(x)*KEY_SCAN_FREQ)          // Second x define for time of keydown

#define S0_KEYDOWN GPIO_ReadPin(49)==0        // S0 keydown GPIO read define
#define S1_KEYDOWN GPIO_ReadPin(52)==0        // S1 keydown GPIO read define
#define S2_KEYDOWN GPIO_ReadPin(51)==0        // S2 keydown GPIO read define
#define S3_KEYDOWN GPIO_ReadPin(53)==0        // S3 keydown GPIO read define

extern Uint32 KeyDownCount0;        // S0 Keydown counter
extern Uint32 KeyDownCount1;        // S1 Keydown counter
extern Uint32 KeyDownCount2;        // S2 Keydown counter
extern Uint32 KeyDownCount3;        // S3 Keydown counter

/**************************************************************************************************************/
/***********************************************FUNCTIONS******************************************************/
/**************************************************************************************************************/

// Initialize the GPIO used for keyboard
void KeyBoardGpioInit(void);
// Initialize keyboard
void KeyBoardInit(void);
// Scan S0 to see if it's down
Uint32 S0KeyDown(void);
// Scan S1 to see if it's down
Uint32 S1KeyDown(void);
// Scan S2 to see if it's down
Uint32 S2KeyDown(void);
// Scan S3 to see if it's down
Uint32 S3KeyDown(void);



#endif /* USERINCLUDES_KEY_H_ */
