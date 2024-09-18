/*
 * ADC_Sample.h
 *
 *  Created on: 2024Äê7ÔÂ16ÈÕ
 *      Author: Mengfanbin
 */

#ifndef USERINCLUDES_ADCSAMPLE_H_
#define USERINCLUDES_ADCSAMPLE_H_

#include "F28x_Project.h"

//AD¼Ä´æÆ÷
#define     PHASE_P        AdcaResultRegs.ADCRESULT0
#define     PHASE_Q        AdcaResultRegs.ADCRESULT1
#define     ILRS_PK             AdcaResultRegs.ADCRESULT2
#define     IO_AD                  AdcaResultRegs.ADCRESULT3
#define     VDS_INV_AD                  AdcaResultRegs.ADCRESULT4
#define     VDS_EV_AD                  AdcaResultRegs.ADCRESULT5

#define     PHASE_5P        AdcbResultRegs.ADCRESULT0
#define     PHASE_3P        AdcbResultRegs.ADCRESULT1
#define     IO_AD_R2            AdcbResultRegs.ADCRESULT2
#define     ILRS_PK_R2                   AdcbResultRegs.ADCRESULT3

#define     TEMP_AD                               AdccResultRegs.ADCRESULT0
#define     ILRS_AC_AD                AdccResultRegs.ADCRESULT1
#define     VDS_INV_AD_R2                            AdccResultRegs.ADCRESULT2
#define     VDS_EV_AD_R2                  AdccResultRegs.ADCRESULT3
#define     PHASE_7P                               AdccResultRegs.ADCRESULT4

#define     VDS_EV_AD_R1        AdcdResultRegs.ADCRESULT0
#define     VDS_INV_AD_R1        AdcdResultRegs.ADCRESULT1
#define     IO_AD_R1               AdcdResultRegs.ADCRESULT2
#define     ILRS_PK_R1                    AdcdResultRegs.ADCRESULT3
#define     PHASE_9P                            AdcdResultRegs.ADCRESULT4

#define     VOLT_AD_ZERO       2048
#define     CURRENT_AD_ZERO     2048

typedef struct
{
    float f32VDS_EV_AD;
    float f32VDS_EV_AD_R1;
    float f32VDS_EV_AD_R2;

    float f32VDS_INV_AD;
    float f32VDS_INV_AD_R1;
    float f32VDS_INV_AD_R2;

    float f32ILRS_PK;
    float f32ILRS_PK_R1;
    float f32ILRS_PK_R2;

    float f32IO_AD;
    float f32IO_AD_R1;
    float f32IO_AD_R2;

    float   f32PHASE_P;
    float   f32PHASE_Q;
    float   f32PHASE_3P;
    float   f32PHASE_5P;
    float   f32PHASE_7P;
    float   f32PHASE_9P;

    float   f32ILRS_AC_AD;
    float   f32TEMP_AD;
    /* data */
}INV_ANA_REGS;

extern INV_ANA_REGS InvAna;
extern INV_ANA_REGS InvAnaGain;
extern INV_ANA_REGS InvAnaBase;

void ConfigureADC(void);
void SetupADC(void);
void ADCBaseGet(void);
void INVADCRead(void);
void ADCanalog_init(void);
#endif /* USERINCLUDES_ADCSAMPLE_H_ */
