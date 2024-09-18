/*
 * EpwmSet.h
 *
 *  Created on: 2024Äê7ÔÂ15ÈÕ
 *      Author: Mengfanbin
 */

#ifndef USERINCLUDES_EPWMSET_H_
#define USERINCLUDES_EPWMSET_H_
#include "F28x_Project.h"

#define TBPRD_Up 1176 //100MHz Up TBPRD=1176 85kHz
#define TBPRD_Up_3rd 392 //100MHz Up TBPRD=392 255kHz
#define TBPRD_Up_5rd 235 //100MHz Up TBPRD=235 425kHz
#define TBPRD_Up_7rd 168 //100MHz Up TBPRD=168 425kHz
#define TBPRD_Up_9rd 130 //100MHz Up TBPRD=130 425kHz

#define TBPRD_UpDown 588 //100MHz UpDown TBPRD=588 85kHz
#define TBPRD_UpDown_3rd 196 //100MHz UpDown TBPRD=255 85kHz
#define TBPRD_UpDown_5rd 117 //100MHz UpDown TBPRD=425 85kHz

void EpwmSet(void);
void Epwm1Set(void);
void Epwm2Set(void);
void Epwm3Set(void);
void Epwm4Set(void);
void Epwm5Set(void);
void Epwm6Set(void);
void Epwm7Set(void);
void Epwm8Set(void);
void Epwm9Set(void);
void Epwm10Set(void);
void Epwm11Set(void);
void Epwm12Set(void);

#endif /* USERINCLUDES_EPWMSET_H_ */
