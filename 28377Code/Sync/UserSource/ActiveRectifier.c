/*
 * ActiveRectifier.c
 *
 *  Created on: 2024年7月17日
 *      Author: Mengfanbin
 */

#include "ActiveRectifier.h"
#include "math.h"


float DRV_DELAY_PHASE = 0;
int32 CompTemp ;

float VdsRef = 700; // Vds reference  700

//------Control variable ------
PI VdsPI;                           // Vds PS PI controller
PI VdsDpsPI;                        // Vds DPS PI controller
PI IoPI;                            // Io PI controller

//------Electrical variable ------
float sita = 0;                     // Phase of ILrs calculated by PQ modulation
float sitaRef = 0;//                // Reference instruction of phase (ILrs to Us)-180;
float PhaseComp = 0;                // Phase compensation considering frequency difference of primary and secondary
Uint16 CompMode = 0;                // Phase compensation mode -- 1: considering 3rd and 5th harmonics  0: no harmonics considered
float Bs = 180;//120.3;         // Secondary side phase shift angle (range: 0~180 degree)
float delt = 0;// 0 110;//137.3;        // Phase shift angle that secondary side lagging to primary side (range: -180~180 degree)

PI DLL_PI;      // PI controller of DLL
PI PLL_PI;      // PI controller of PLL

float SoftStartVdsRef = 0;          // Vds reference during soft start
float SoftStartsitaRef = 0;         // sita reference during soft switch

void DLLSync(void)
{

    if( CompMode == 1)
        InvAna.f32PHASE_Q = InvAna.f32PHASE_Q - InvAna.f32PHASE_3P * 0.333333 - InvAna.f32PHASE_5P * 0.2;     // Q = Q - 3rd/3 - 5th/5
    else if( CompMode == 2)
        InvAna.f32PHASE_Q = InvAna.f32PHASE_Q - InvAna.f32PHASE_3P * 0.333333;       // Q = Q - 3rd/3 - 5th/5
    else if( CompMode == 3)
    {
#define XS  ( 2.0*3.141592653*85000*12.4/1000000 )  // Xs
#define VDS_        100.0 //200.0
#define COMP_FACTOR     12.2397  //24.4793 //(float)( 8.0*VDS_/(3.141592653^2*XS) )

        float Comp3, Comp5, Comp7, Comp9, Comp11;
        float Comp;
        Comp3 = 0.0417*__sin(1.5*Bs*0.0174533)*COMP_FACTOR;           // 0.0417=1/(3*(3^2-1))  0.0174533 degree to radius
        Comp5 = 0.0083*__sin(2.5*Bs*0.0174533)*COMP_FACTOR;           // 0.0083=1/(5*(5^2-1))
        Comp7 = 0.003*__sin(3.5*Bs*0.0174533)*COMP_FACTOR;            // 0.0030=1/(7*(7^2-1))
        Comp9 = 0.0014*__sin(4.5*Bs*0.0174533)*COMP_FACTOR;           // 0.0014=1/(9*(9^2-1))
        Comp11 = 0.00075758*__sin(5.5*Bs*0.0174533)*COMP_FACTOR;      // 0.00075758=1/(11*(11^2-1))
        Comp = Comp3+Comp5+Comp7+Comp9+Comp11;

        CompTemp = Comp * 100;

        InvAna.f32PHASE_Q = InvAna.f32PHASE_Q + Comp;
    }
    else
        InvAna.f32PHASE_Q = InvAna.f32PHASE_Q;

    float temp32;
    temp32=__divf32(-InvAna.f32PHASE_Q , InvAna.f32PHASE_P);

    if( (InvAna.f32PHASE_P >= 0) && (InvAna.f32PHASE_Q >= 0))
    {
        sita = __atan(temp32) * 57.2957795;//sita = atan(InvAna.f32PHASE_Q/InvAna.f32PHASE_P) * 57.2957795;     // sita = atan(Q/P)/pi*180 (ps: 1/pi*180=57.2957795)
    }
    else if( (InvAna.f32PHASE_P >= 0) && (InvAna.f32PHASE_Q < 0))
    {
        sita = __atan(temp32) * 57.2957795;//sita = atan(InvAna.f32PHASE_Q/InvAna.f32PHASE_P) * 57.2957795;
    }
    else if( (InvAna.f32PHASE_P < 0) && (InvAna.f32PHASE_Q > 0))
    {
        sita = -180 + __atan(temp32) * 57.2957795;//sita = 180 + atan(InvAna.f32PHASE_Q/InvAna.f32PHASE_P) * 57.2957795;
    }
    else
    {
        sita = 180 + __atan(temp32) * 57.2957795;//sita = -180 + atan(InvAna.f32PHASE_Q/InvAna.f32PHASE_P) * 57.2957795;
    }
    // sita calc run time 5.5us


    DLL_PI.Fbk = sita;                                      // Feedback is phase of Ilrs
    //DLL_PI.Ref = 0;                                       // Reference is phase between Us and Ilrs
    DLL_PI.Ref = sitaRef+PhaseComp;                         // Reference is phase between Us and Ilrs
    DLL_PI.calc( &DLL_PI );                                 // DLL control
    delt = -DLL_PI.Out;

    //delt = sitaRef;
    PhaseComp = PhaseComp*0.98 + WRAP_N180_P180(DLL_PI.Ref-DLL_PI.Fbk)*0.02;    //Err很大时，WRAP会使数字滤波出错，可以考虑改进算法，写出适应数字滤波的WRAP函数  20190116
    PhaseComp = LIMIT(PhaseComp,180,-180);

    //LegsPhaseUpdate();        // Update phase of legs
    // PI and leg phase updade run time 18.7us
}
// Initialize variable for DLL
void DLLInit(void)
{
    //-----pi(s) = kp + ki/s     --(z-tran)-->  Kp = kp ; Ki = ki * Ts ---------//
    //                pi(s) = kp + ki/s = 0 + 3000/s
    //          --->  Kp = 0   Ki = 3000 * (1/20000) = 0.15
    DLL_PI.Kp = 0;                                  // Kp = 0
    //DLL_PI.Ki = 0.12;//0.15;                      // Ki = 0.12 (10kHz)
    //DLL_PI.Ki = 0.15;//0.15;                              // Ki = 0.15 (20kHz)
    //DLL_PI.Ki = 0.015;//0.15;                             // Ki = 0.15 (20kHz)  //20190906
    //DLL_PI.Ki = 0.004;      //20230209
    DLL_PI.Ki = 0.01;
    DLL_PI.Umax = 360;                          // No limitation
    DLL_PI.Umin = -360;                         // No limitation
    DLL_PI.calc = (void(*)(void*))I_calc;           // Link to PI calculation function (must be I_calc)
    DLL_PI.Ref = 0;                                 // Ref = 0
    DLL_PI.Fbk = 0;                                 // Clear feedback
    DLL_PI.Out = 0;                                 // Clear output
    DLL_PI.i1 = 0;                                  // Clear calculation variable
    DLL_PI.ui = 0;                                  // Clear calculation variable
    DLL_PI.up = 0;                                  // Clear calculation variable
    DLL_PI.v1 = 0;                                  // Clear calculation variable
}


void PhaseShiftUpdate( volatile struct EPWM_REGS* pEPwmRegs , float Phase )
{
    int16 CMPA, CMPB, TBPRD_HALF, CMPA_DELT, CMPB_DELT;

    //Phase = LIMIT( Phase , 360 , 0 );

    TBPRD_HALF = pEPwmRegs->TBPRD >> 1;                                 // Half of TBPRD :TBPRD/2

    CMPA = pEPwmRegs->TBPRD * Phase * 0.0027777777;                     // Calculating new CMPA (should be in [0,TBPRD-1])     phase/360 转换成弧度

    CMPB = TBPRD_HALF + pEPwmRegs->TBPRD * Phase * 0.0027777777;        // Calculating new CMPB (should be in [0,TBPRD-1])
    CMPB = WRAP( CMPB , 0 , (int16)pEPwmRegs->TBPRD );

    CMPA_DELT = ABS( CMPA - (int16)pEPwmRegs->CMPA.bit.CMPA );          // Change of last and new CMPA
    CMPB_DELT = ABS( CMPB - (int16)pEPwmRegs->CMPB.bit.CMPB );                              // Change of last and new CMPB


    if( ( CMPA_DELT >= TBPRD_HALF ) && ( CMPA >= TBPRD_HALF ) )         // Change of CMPA larger than half of TBPRD and CMPA in [TBPRD_HALF,TBPRD], mean a negtive cross
    {
        //Action when counter equals zero.
        pEPwmRegs->AQCTLA.bit.ZRO = AQ_SET;                                         //force EPWMxA output high.
        //Action when the counter equals the period.
        pEPwmRegs->AQCTLA.bit.PRD = AQ_SET;                                         //force EPWMxA output high.
        //Action when the counter equals the active CMPA register and the counter is incrementing.
        pEPwmRegs->AQCTLA.bit.CAU = AQ_NO_ACTION;                           // May only change of ZRO, no CAU and CBU, including conditions of below (need verified)
        //Action when the counter equals the active CMPB register and the counter is incrementing.
        pEPwmRegs->AQCTLA.bit.CBU = AQ_CLEAR;
    }
    else if( ( CMPB_DELT >= TBPRD_HALF ) && ( CMPB >= TBPRD_HALF ) )    // Change of CMPB larger than half of TBPRD and CMPB in [TBPRD_HALF,TBPRD], mean a negtive cross
    {
        pEPwmRegs->AQCTLA.bit.ZRO = AQ_CLEAR;
        pEPwmRegs->AQCTLA.bit.PRD = AQ_CLEAR;
        pEPwmRegs->AQCTLA.bit.CAU = AQ_SET;
        pEPwmRegs->AQCTLA.bit.CBU = AQ_NO_ACTION;
    }
    else                                                                // No cross or postive cross
    {
        pEPwmRegs->AQCTLA.bit.CAU = AQ_SET;
        pEPwmRegs->AQCTLA.bit.CBU = AQ_CLEAR;
        pEPwmRegs->AQCTLA.bit.ZRO = AQ_NO_ACTION;
        pEPwmRegs->AQCTLA.bit.PRD = AQ_NO_ACTION;
    }

    pEPwmRegs->CMPA.bit.CMPA = CMPA;                                    // New CPMA loaded
    pEPwmRegs->CMPB.bit.CMPB = CMPB;                                                        // New CMPB loaded
}

void LegsPhaseUpdate(void)
{
    float AngleTemp = 0;

//#define DRV_DELAY_PHASE       6//3//5//8.26  //6.5            // Driver signals has a delay of 120ns, meanning a delay of 3.7 degree, phase shift the PQ modulation signal to cancel the error
                                        // When PWM1A change from 1 to 0, from scope can see it takes about 270ns(8.26 degree) for MOSFET to turn off(not yet consider dead time effection)   // 20190904
    AngleTemp = delt;                                                       // Leading leg phase calculate
    //AngleTemp>360,则AngleTemp-360；AngleTemp<0,则AngleTemp+360；
    PhaseShiftUpdate( &EPwm6Regs , WRAP( AngleTemp , 0.0 , 360.0 ) );       // Leading leg phase updated        1.43us 副边第一个桥臂

    AngleTemp = delt - Bs;                                                                                  // Lagging leg phase calculate                  副边第二个桥臂
    PhaseShiftUpdate( &EPwm7Regs , WRAP( AngleTemp , 0.0 , 360.0 ) );       // Lagging leg phase updated

    AngleTemp = delt - 0.5 * Bs + 90 + DRV_DELAY_PHASE;                         // InvAna.f32PHASE_P leg phase calculate  S_rd 滞后副边桥臂（0.5*Bs-90）
    PhaseShiftUpdate( &EPwm8Regs , WRAP( AngleTemp , 0.0 , 360.0 ) );       // InvAna.f32PHASE_P leg phase updated

    AngleTemp = delt - 0.5 * Bs + DRV_DELAY_PHASE;                                  // InvAna.f32PHASE_Q leg phase calculate S_rq 超前S_rd 90
    PhaseShiftUpdate( &EPwm9Regs , WRAP( AngleTemp , 0.0 , 360.0 ) );       // InvAna.f32PHASE_Q leg phase updated

    AngleTemp = ( delt - 0.5 * Bs + DRV_DELAY_PHASE ) * 3;                      // Phase_3rd leg phase calculate

    AngleTemp = WRAP( AngleTemp , 0.0 , 360.0 );
    AngleTemp = WRAP( AngleTemp , 0.0 , 360.0 );
    AngleTemp = WRAP( AngleTemp , 0.0 , 360.0 );
    AngleTemp = WRAP( AngleTemp , 0.0 , 360.0 );
    AngleTemp = WRAP( AngleTemp , 0.0 , 360.0 );

    PhaseShiftUpdate( &EPwm10Regs , WRAP( AngleTemp , 0.0 , 360.0 ) );       // Phase_3rd leg phase updated

    AngleTemp = ( delt - 0.5 * Bs + DRV_DELAY_PHASE ) * 5;                  // Phase_5th leg phase calculate

    AngleTemp = WRAP( AngleTemp , 0.0 , 360.0 );
    AngleTemp = WRAP( AngleTemp , 0.0 , 360.0 );
    AngleTemp = WRAP( AngleTemp , 0.0 , 360.0 );
    AngleTemp = WRAP( AngleTemp , 0.0 , 360.0 );
    AngleTemp = WRAP( AngleTemp , 0.0 , 360.0 );

    PhaseShiftUpdate( &EPwm11Regs , WRAP( AngleTemp , 0.0 , 360.0 ) );       // Phase_5th leg phase updated
}

void PQPwmUpdate(void)
{
    float AngleTemp = 0;

//#define DRV_DELAY_PHASE       6//3//5//8.26  //6.5            // Driver signals has a delay of 120ns, meanning a delay of 3.7 degree, phase shift the PQ modulation signal to cancel the error
                                        // When PWM1A change from 1 to 0, from scope can see it takes about 270ns(8.26 degree) for MOSFET to turn off(not yet consider dead time effection)   // 20190904
    AngleTemp = delt - 0.5 * Bs + 90 + DRV_DELAY_PHASE;                     // InvAna.f32PHASE_P leg phase calculate
    PhaseShiftUpdate( &EPwm8Regs , WRAP( AngleTemp , 0.0 , 360.0 ) );       // InvAna.f32PHASE_P leg phase updated

    AngleTemp = delt - 0.5 * Bs + DRV_DELAY_PHASE;                          // InvAna.f32PHASE_Q leg phase calculate
    PhaseShiftUpdate( &EPwm9Regs , WRAP( AngleTemp , 0.0 , 360.0 ) );       // InvAna.f32PHASE_Q leg phase updated

    AngleTemp = ( delt - 0.5 * Bs + DRV_DELAY_PHASE ) * 3;                  // Phase_3rd leg phase calculate

    AngleTemp = WRAP( AngleTemp , 0.0 , 360.0 );
    AngleTemp = WRAP( AngleTemp , 0.0 , 360.0 );
    AngleTemp = WRAP( AngleTemp , 0.0 , 360.0 );
    AngleTemp = WRAP( AngleTemp , 0.0 , 360.0 );
    AngleTemp = WRAP( AngleTemp , 0.0 , 360.0 );

    PhaseShiftUpdate( &EPwm10Regs , WRAP( AngleTemp , 0.0 , 360.0 ) );       // Phase_3rd leg phase updated

    AngleTemp = ( delt - 0.5 * Bs + DRV_DELAY_PHASE ) * 5;                  // Phase_5th leg phase calculate

    AngleTemp = WRAP( AngleTemp , 0.0 , 360.0 );
    AngleTemp = WRAP( AngleTemp , 0.0 , 360.0 );
    AngleTemp = WRAP( AngleTemp , 0.0 , 360.0 );
    AngleTemp = WRAP( AngleTemp , 0.0 , 360.0 );
    AngleTemp = WRAP( AngleTemp , 0.0 , 360.0 );

    PhaseShiftUpdate( &EPwm11Regs , WRAP( AngleTemp , 0.0 , 360.0 ) );       // Phase_5th leg phase updated
}


// Initialize VdsPI controller
void VdsPIInit(void)
{
    //----- pi(s) = kp(1 + ki/s)     --(z-tran)-->  Kp = kp ; Ki = ki * Ts  ---------//
    //                pi(s) = kp(1 + ki/s) = 0.4*(1 + 3125/s)
    //          --->  Kp = 0.4   Ki = 3125 * (1/20000) = 1.5625
    VdsPI.Kp = 0.4;                                 // Kp = 0
    VdsPI.Ki = 1.5625;                              // Ki = 0.15
    VdsPI.Umax = 180;                               // Upper limitation
    VdsPI.Umin = 0;                                 // Lowwer limitation
    VdsPI.calc = (void(*)(void*))PI_calc;           // Link to PI calculation function
    VdsPI.Ref = 0;                                  // Ref = 0
    VdsPI.Fbk = 0;                                  // Clear feedback
    VdsPI.Out = 0;                                  // Clear output
    VdsPI.i1 = 0;                                   // Clear calculation variable
    VdsPI.ui = 0;                                   // Clear calculation variable
    VdsPI.up = 0;                                   // Clear calculation variable
    VdsPI.v1 = 0;                                   // Clear calculation variable
}
void IoPIInit(void)
{
    //----- pi(s) = kp(1 + ki/s)     --(z-tran)-->  Kp = kp ; Ki = ki * Ts  ---------//
    //                pi(s) = kp(1 + ki/s) = 100*(1 + 3000/s)
    //          --->  Kp = 0   Ki = 3000 * (1/20000) = 0.15
    IoPI.Kp = 1;                                    // Kp = 0
    IoPI.Ki = 0.15;                                 // Ki = 0.15
    IoPI.Umax = 180;                                // Upper limitation
    IoPI.Umin = 0;                                  // Lowwer limitation
    IoPI.calc = (void(*)(void*))PI_calc;            // Link to PI calculation function
    IoPI.Ref = 0;                                   // Ref = 0
    IoPI.Fbk = 0;                                   // Clear feedback
    IoPI.Out = 0;                                   // Clear output
    IoPI.i1 = 0;                                    // Clear calculation variable
    IoPI.ui = 0;                                    // Clear calculation variable
    IoPI.up = 0;                                    // Clear calculation variable
    IoPI.v1 = 0;                                    // Clear calculation variable
}
// Initialize VdsDpsPI controller
void VdsDpsPIInit(void)
{
    //----- pi(s) = kp(1 + ki/s)     --(z-tran)-->  Kp = kp ; Ki = ki * Ts  ---------//
    //                pi(s) = kp(1 + ki/s) = 0.004*(1 + 3125/s)
    //          --->  Kp = 0.004   Ki = 3125 * (1/20000) = 1.5625
    VdsDpsPI.Kp = 0.004/10/10;                              // Kp = 0.004
    VdsDpsPI.Ki = 1.5625;                               // Ki = 1.5625
    VdsDpsPI.Umax = 1;                                  // Upper limitation
    VdsDpsPI.Umin = -1;                                 // Lowwer limitation
    VdsDpsPI.calc = (void(*)(void*))PI_calc;            // Link to PI calculation function
    VdsDpsPI.Ref = 0;                                   // Ref = 0
    VdsDpsPI.Fbk = 0;                                   // Clear feedback
    VdsDpsPI.Out = 0;                                   // Clear output
    VdsDpsPI.i1 = 0;                                    // Clear calculation variable
    VdsDpsPI.ui = 0;                                    // Clear calculation variable
    VdsDpsPI.up = 0;                                    // Clear calculation variable
    VdsDpsPI.v1 = 0;                                    // Clear calculation variable
}

// Vds control with PS
void VdsPsCtl(float VdsRef)
{
    VdsPI.Ref = VdsRef;
    VdsPI.Fbk = InvAna.f32VDS_INV_AD;
    VdsPI.calc(&VdsPI);
    Bs = VdsPI.Out;
}

// Vds control with DPS
void VdsDpsCtl(float VdsRef)
{
    float Bs0;
    VdsDpsPI.Ref = VdsRef;
    VdsDpsPI.Fbk = InvAna.f32VDS_INV_AD;
    VdsDpsPI.calc(&VdsDpsPI);
    Bs0 = asin(VdsDpsPI.Out) * 114.591559;      // 2/pi*180=114.591559
    Bs = LIMIT( ABS(Bs0), 180, 0 );
    sitaRef = -(Bs0+180) * 0.5;
}
// Power direction soft switch
Uint8 PowerDirectionSoftSwitch(Uint32 Direction)
{
    if( Direction == 1 )
    {
        SoftStartsitaRef = SoftStartsitaRef + DELT_SITA;
    }
    else
    {
        SoftStartsitaRef = SoftStartsitaRef - DELT_SITA;
    }
    if(SoftStartsitaRef >= 0)                               // If Vds reference reach the predefined Vdsref, soft start finish
    {
        SoftStartsitaRef = 0;
        sitaRef = SoftStartsitaRef;

        return PD_SOFT_SWITCH_FINISH;                           // return ARU_SOFT_START_FINISH
    }
    else if(SoftStartsitaRef <= -180)                               // If Vds reference reach the predefined Vdsref, soft start finish
    {
        SoftStartsitaRef = -180;
        sitaRef = SoftStartsitaRef;

        return PD_SOFT_SWITCH_FINISH;                           // return ARU_SOFT_START_FINISH
    }
    else// Soft switch
    {
        sitaRef = SoftStartsitaRef;

        return PD_SOFT_SWITCH_UNDERWAY;                         // return ARU_SOFT_START_UNDERWAY
    }
}
// Active Rectifier soft start
Uint8 ARUSoftStart(float VdsRef)
{
    float DeltVds;

    DeltVds = VdsRef*SOFT_START_DELT_FACTOR;                    // Calculate delta increasment of Vds referencee        1.57us
    SoftStartVdsRef += DeltVds;                                 // Increase Vds reference

    if(SoftStartVdsRef >= VdsRef)                               // If Vds reference reach the predefined Vdsref, soft start finish
    {
        SoftStartVdsRef = VdsRef;                               // Clamp the Vds reference to VdsRef
        VdsDpsCtl(SoftStartVdsRef);                             // Vds control with DPS
        DLLSync();                                              // Synchronization
        LegsPhaseUpdate();                                      // Update phase of legs

        return ARU_SOFT_START_FINISH;                           // return ARU_SOFT_START_FINISH
    }
    else                                                        // Soft start
    {
        VdsDpsCtl(SoftStartVdsRef);                             // Vds control with DPS     3.9us
        DLLSync();                                              // Synchronization          5.52us
        LegsPhaseUpdate();                                      // Update phase of legs     10.3us

        return ARU_SOFT_START_UNDERWAY;                         // return ARU_SOFT_START_UNDERWAY
    }
}
// Initialize variables related to active rectifier
void ARUVarsInit(void)
{
    VdsRef = 700;                    // Vds reference

    //------Control variable -----
    DLLInit();                  // Initialize variable for DLL
    VdsPIInit();                // Initialize VdsPI
    IoPIInit();                 // Initialize VdsPI
    VdsDpsPIInit();             // Initialize VdsDpsPI

    sita = 0;                       // Phase of ILrs calculated by PQ modulation
    sitaRef = 190;                  // Reference instruction of phase (ILrs to Us)//-180;
    PhaseComp = 0;              // Phase compensation considering frequency difference of primary and secondary
    CompMode = 0x01;//0x01              // Phase compensation mode -- 1: considering 3rd and 5th harmonics  0: no harmonics considered
    Bs = 180;//120.3;           // Secondary side phase shift angle (range: 0~180 degree)
    delt = 0;//110;//137.3;     // Phase shift angle that secondary side lagging to primary side (range: -180~180 degree)
    SoftStartVdsRef = 700;            // Vds reference during soft start

}

