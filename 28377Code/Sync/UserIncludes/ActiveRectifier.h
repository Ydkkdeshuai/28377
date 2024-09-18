/*
 * ActiveRectifier.h
 *
 *  Created on: 2024Äê7ÔÂ17ÈÕ
 *      Author: Mengfanbin
 */

#ifndef USERINCLUDES_ACTIVERECTIFIER_H_
#define USERINCLUDES_ACTIVERECTIFIER_H_

#include "F28x_Project.h"
#include "CommonModle.h"
#include "ADCSample.h"

extern int32 CompTemp ;

extern float VdsRef; // Vds reference  700

//------Control variable ------
extern PI VdsPI;                           // Vds PS PI controller
extern PI VdsDpsPI;                        // Vds DPS PI controller
extern PI IoPI;                            // Io PI controller

//------Electrical variable ------

extern INV_ANA_REGS InvAna;

extern float sita;                     // Phase of ILrs calculated by PQ modulation
extern float sitaRef;//                // Reference instruction of phase (ILrs to Us)-180;
extern float PhaseComp;                // Phase compensation considering frequency difference of primary and secondary
extern Uint16 CompMode;                // Phase compensation mode -- 1: considering 3rd and 5th harmonics  0: no harmonics considered
extern float Bs;//120.3;         // Secondary side phase shift angle (range: 0~180 degree)
extern float delt;// 0 110;//137.3;        // Phase shift angle that secondary side lagging to primary side (range: -180~180 degree)

extern PI DLL_PI;      // PI controller of DLL
extern PI PLL_PI;      // PI controller of PLL

extern float SoftStartVdsRef;          // Vds reference during soft start
extern float SoftStartsitaRef;         // sita reference during soft switch


#define PWM_TBPRD(fpwm) (Uint16)(150000000.0/fpwm)
#define PWM_DUTY 0.5
#define PWM_CMP(fpwm) (Uint16)(PWM_TBPRD(fpwm)*0.5)

#define ARU_CTL_FREQUENCY           20000.0                     // Control frequency of active rectifier
#define ARU_CTL_PERIOD              (1.0/ARU_CTL_FREQUENCY)     // Control period of active rectifier
#define ARU_SOFT_START_FINISH       0x00                        // Soft start of active rectifier is finshed
#define ARU_SOFT_START_UNDERWAY     0x01                        // Soft start of active rectifier is underway

#define SOFT_START_TIME             1.0                                         // Soft start time of VA full bridge, unit: s
#define SOFT_START_DELT_FACTOR      ( 1.0/SOFT_START_TIME*ARU_CTL_PERIOD )      // Soft start delta increasement factor

#define PD_SOFT_SWITCH_FINISH       0x00                        // Soft swicth of power direction is finshed
#define PD_SOFT_SWITCH_UNDERWAY     0x01                        // Soft swicth of power direction is underway
#define SOFT_SWITCH_TIME                5.0                                         // Soft switch time of power direction, unit: ms
#define DELT_SITA       ( 180.0/(SOFT_SWITCH_TIME/1000/ARU_CTL_PERIOD) )        // Soft start delta increasement factor



// Update phase of full bridge legs
void PhaseShiftUpdate( volatile struct EPWM_REGS* pEPwmRegs , float Phase );
// Calculate phase of full bridge legs and update
void LegsPhaseUpdate(void);
// Calculate phase of Square_P and Square_Q and update the cooresponding PWM signal
void PQPwmUpdate(void);
// Synchronize and lock phase of primary and secondary by DLL
void DLLSync(void);

// Initialize variable for DLL
void DLLInit(void);

// Initialize VdsPI controller
void VdsPIInit(void);
// Initialize IoPI controller
void IoPIInit(void);
// Initialize VdsDpsPI controller
void VdsDpsPIInit(void);
// Vds control with PS
void VdsPsCtl(float VdsRef);
// Vds control with DPS
void VdsDpsCtl(float VdsRef);
// Active Rectifier soft start
Uint8 ARUSoftStart(float VdsRef);
// Initialize variables related to active rectifier
void ARUVarsInit(void);
// Power direction soft switch
Uint8 PowerDirectionSoftSwitch(Uint32 Direction);
#endif /* USERINCLUDES_ACTIVERECTIFIER_H_ */
