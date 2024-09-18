/*
 * ADC_Sample.c
 *
 *  Created on: 2024年7月16日
 *      Author: Mengfanbin
 */
//#include "F28x_Project.h"
#include "ADCSample.h"

INV_ANA_REGS InvAna = {0};
INV_ANA_REGS InvAnaGain = {0};
INV_ANA_REGS InvAnaBase = {0};

void ADCanalog_init()
{
    //运放增益
     InvAnaGain.f32VDS_EV_AD=0.2571;//3/4096/(20/7020); 800V对应2.28V
     InvAnaGain.f32VDS_EV_AD_R1=0.2571;//3/4096/(20/7020);
     InvAnaGain.f32VDS_EV_AD_R2=0.2571;//3/4096/(20/7020);

     InvAnaGain.f32VDS_INV_AD=0.2571;//3/4096/(20/7020);
     InvAnaGain.f32VDS_INV_AD_R1=0.2571;//3/4096/(20/7020);
     InvAnaGain.f32VDS_INV_AD_R2=0.2571;//3/4096/(20/7020);

     InvAnaGain.f32ILRS_PK=0.03052;//3/4096/0.024;//0.012*2 120A对应+2.88V
     InvAnaGain.f32ILRS_PK_R1=0.03052;//3/4096/0.024;//0.012*2 120A对应+2.88V
     InvAnaGain.f32ILRS_PK_R2=0.03052;//3/4096/0.024;//0.012*2 120A对应+2.88V
     InvAnaGain.f32ILRS_AC_AD=0.06104;//3/4096/0.012;//120A对应+2.94V，-120A对应0.06V

     InvAnaGain.f32IO_AD=0.03662;//3/4096/(0.02*2/2);//70A对应+2.9V  -70A对应0.1V
     InvAnaGain.f32IO_AD_R1=0.03662;//3/4096/(0.02*2/2);//70A对应+2.9V  -70A对应0.1V
     InvAnaGain.f32IO_AD_R2=0.03662;//3/4096/(0.02*2/2);//70A对应+2.9V  -70A对应0.1V

     InvAnaGain.f32TEMP_AD=0;

     InvAnaGain.f32PHASE_P=0.09587;//3/4096/(0.012*2/2*2/3.1415926)
     InvAnaGain.f32PHASE_Q=0.09587;//3/4096/(0.012*2/2*2/3.1415926)
     InvAnaGain.f32PHASE_3P=0.09587;//3/4096/(0.012*2/2*2/3.1415926)
     InvAnaGain.f32PHASE_5P=0.09587;//3/4096/(0.012*2/2*2/3.1415926)
     InvAnaGain.f32PHASE_7P=0.09587;//3/4096/(0.012*2/2*2/3.1415926)
     InvAnaGain.f32PHASE_9P=0.09587;//3/4096/(0.012*2/2*2/3.1415926)

    InvAnaBase.f32VDS_EV_AD=0;
    InvAnaBase.f32VDS_EV_AD_R1=0;
    InvAnaBase.f32VDS_EV_AD_R2=0;

    InvAnaBase.f32VDS_INV_AD=0;
    InvAnaBase.f32VDS_INV_AD_R1=0;
    InvAnaBase.f32VDS_INV_AD_R2=0;

    InvAnaBase.f32ILRS_PK=0;
    InvAnaBase.f32ILRS_PK_R1=0;
    InvAnaBase.f32ILRS_PK_R2=0;
    InvAnaBase.f32ILRS_AC_AD=0;

    InvAnaBase.f32IO_AD=0;
    InvAnaBase.f32IO_AD_R1=0;
    InvAnaBase.f32ILRS_PK_R2=0;

    InvAnaBase.f32TEMP_AD=0;

    InvAnaBase.f32PHASE_P=0;
    InvAnaBase.f32PHASE_Q=0;
    InvAnaBase.f32PHASE_3P=0;
    InvAnaBase.f32PHASE_5P=0;
    InvAnaBase.f32PHASE_7P=0;
    InvAnaBase.f32PHASE_9P=0;
}
#pragma CODE_SECTION(INVADCRead,".TI.ramfunc");

void INVADCRead()
{
    AdcaRegs.ADCSOCFRC1.all = 0xffff; //SOC0 and SOC1
    AdcbRegs.ADCSOCFRC1.all = 0xffff; //SOC0 and SOC1
    AdccRegs.ADCSOCFRC1.all = 0xffff; //SOC0 and SOC1
    AdcdRegs.ADCSOCFRC1.all = 0xffff; //SOC0 and SOC1

    while(AdcaRegs.ADCINTFLG.bit.ADCINT1 == 0);
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    //wait for ADCB to complete, then acknowledge flag
    while(AdcbRegs.ADCINTFLG.bit.ADCINT1 == 0);
    AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    while(AdccRegs.ADCINTFLG.bit.ADCINT1 == 0);
    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    //wait for ADCB to complete, then acknowledge flag
    while(AdcdRegs.ADCINTFLG.bit.ADCINT1 == 0);
    AdcdRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    //电压采样
    int  i16tmp;
    i16tmp = VDS_EV_AD - InvAnaBase.f32VDS_EV_AD;
    InvAna.f32VDS_EV_AD = InvAnaGain.f32VDS_EV_AD * i16tmp;
    i16tmp = VDS_EV_AD_R1 - InvAnaBase.f32VDS_EV_AD_R1;
    InvAna.f32VDS_EV_AD_R1 = InvAnaGain.f32VDS_EV_AD_R1 * i16tmp;
    i16tmp = VDS_EV_AD_R2 - InvAnaBase.f32VDS_EV_AD_R2;
    InvAna.f32VDS_EV_AD_R2 = InvAnaGain.f32VDS_EV_AD_R2 * i16tmp;

    i16tmp = VDS_INV_AD - InvAnaBase.f32VDS_INV_AD;
    InvAna.f32VDS_INV_AD = InvAnaGain.f32VDS_INV_AD * i16tmp;
    i16tmp = VDS_INV_AD_R1 - InvAnaBase.f32VDS_INV_AD_R1;
    InvAna.f32VDS_INV_AD_R1 = InvAnaGain.f32VDS_INV_AD_R1 * i16tmp;
    i16tmp = VDS_INV_AD_R2 - InvAnaBase.f32VDS_INV_AD_R2;
    InvAna.f32VDS_INV_AD_R2 = InvAnaGain.f32VDS_INV_AD_R2 * i16tmp;

    //直流电流采样
    i16tmp = IO_AD - InvAnaBase.f32IO_AD;
    InvAna.f32IO_AD = InvAnaGain.f32IO_AD * i16tmp;
    i16tmp = IO_AD_R1 - InvAnaBase.f32IO_AD_R1;
    InvAna.f32IO_AD_R1 = InvAnaGain.f32IO_AD_R1 * i16tmp;
    i16tmp = IO_AD_R2 - InvAnaBase.f32IO_AD_R2;
    InvAna.f32IO_AD_R2 = InvAnaGain.f32IO_AD_R2 * i16tmp;

    //谐振电流采样
    i16tmp = ILRS_PK - InvAnaBase.f32ILRS_PK;
    InvAna.f32ILRS_PK = InvAnaGain.f32ILRS_PK * i16tmp;
    i16tmp = ILRS_PK_R1 - InvAnaBase.f32ILRS_PK_R1;
    InvAna.f32ILRS_PK_R1 = InvAnaGain.f32ILRS_PK_R1 * i16tmp;
    i16tmp = ILRS_PK_R2 - InvAnaBase.f32ILRS_PK_R2;
    InvAna.f32ILRS_PK_R2 = InvAnaGain.f32ILRS_PK_R2 * i16tmp;

    i16tmp = ILRS_AC_AD - InvAnaBase.f32ILRS_AC_AD;
    InvAna.f32ILRS_AC_AD = InvAnaGain.f32ILRS_AC_AD * i16tmp;

    //调制波
    i16tmp = PHASE_P - InvAnaBase.f32PHASE_P;
    InvAna.f32PHASE_P = InvAnaGain.f32PHASE_P * i16tmp;
    i16tmp = PHASE_Q - InvAnaBase.f32PHASE_Q;
    InvAna.f32PHASE_Q = InvAnaGain.f32PHASE_Q * i16tmp;
    i16tmp = PHASE_3P - InvAnaBase.f32PHASE_3P;
    InvAna.f32PHASE_3P = InvAnaGain.f32PHASE_3P * i16tmp;
    i16tmp = PHASE_5P - InvAnaBase.f32PHASE_5P;
    InvAna.f32PHASE_5P = InvAnaGain.f32PHASE_5P * i16tmp;
    i16tmp = PHASE_7P - InvAnaBase.f32PHASE_7P;
    InvAna.f32PHASE_7P = InvAnaGain.f32PHASE_7P * i16tmp;
    i16tmp = PHASE_9P - InvAnaBase.f32PHASE_9P;
    InvAna.f32PHASE_9P = InvAnaGain.f32PHASE_9P * i16tmp;

    //温度
    i16tmp = TEMP_AD - InvAnaBase.f32TEMP_AD;
    InvAna.f32TEMP_AD = InvAnaGain.f32TEMP_AD * i16tmp;

    if(1 == AdcaRegs.ADCINTOVF.bit.ADCINT1)
    {
        AdcaRegs.ADCINTOVFCLR.bit.ADCINT1 = 1; //clear INT1 overflow flag
        AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    }

    if(1 == AdcbRegs.ADCINTOVF.bit.ADCINT1)
    {
        AdcbRegs.ADCINTOVFCLR.bit.ADCINT1 = 1; //clear INT1 overflow flag
        AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    }

    if(1 == AdccRegs.ADCINTOVF.bit.ADCINT1)
    {
        AdccRegs.ADCINTOVFCLR.bit.ADCINT1 = 1; //clear INT1 overflow flag
        AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    }

    if(1 == AdcdRegs.ADCINTOVF.bit.ADCINT1)
    {
        AdcdRegs.ADCINTOVFCLR.bit.ADCINT1 = 1; //clear INT1 overflow flag
        AdcdRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    }
}

void ADCBaseGet()
{
    int i;
    for( i=0 ; i<1000 ; i++ )
    {
    AdcaRegs.ADCSOCFRC1.all = 0xffff; //SOC0 and SOC1
    AdcbRegs.ADCSOCFRC1.all = 0xffff; //SOC0 and SOC1
    AdccRegs.ADCSOCFRC1.all = 0xffff; //SOC0 and SOC1
    AdcdRegs.ADCSOCFRC1.all = 0xffff; //SOC0 and SOC1

    while(AdcaRegs.ADCINTFLG.bit.ADCINT1 == 0);
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    //wait for ADCB to complete, then acknowledge flag
    while(AdcbRegs.ADCINTFLG.bit.ADCINT1 == 0);
    AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    while(AdccRegs.ADCINTFLG.bit.ADCINT1 == 0);
    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    //wait for ADCB to complete, then acknowledge flag
    while(AdcdRegs.ADCINTFLG.bit.ADCINT1 == 0);
    AdcdRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    //电压采样
    InvAnaBase.f32VDS_EV_AD += VDS_EV_AD;
    InvAnaBase.f32VDS_EV_AD_R1 += VDS_EV_AD_R1;
    InvAnaBase.f32VDS_EV_AD_R2 += VDS_EV_AD_R2;

    InvAnaBase.f32VDS_INV_AD += VDS_INV_AD;
    InvAnaBase.f32VDS_INV_AD_R1 += VDS_INV_AD_R1;
    InvAnaBase.f32VDS_INV_AD_R2 += VDS_INV_AD_R2;

    //直流电流采样
    InvAnaBase.f32IO_AD += IO_AD;
    InvAnaBase.f32IO_AD_R1 += IO_AD_R1;
    InvAnaBase.f32IO_AD_R2 += IO_AD_R2;

    //谐振电流采样

    InvAnaBase.f32ILRS_PK += ILRS_PK;
    InvAnaBase.f32ILRS_PK_R1 += ILRS_PK_R1;
    InvAnaBase.f32ILRS_PK_R2 += ILRS_PK_R2;
    InvAnaBase.f32ILRS_AC_AD += ILRS_AC_AD;

    //调制波
    InvAnaBase.f32PHASE_P += PHASE_P;
    InvAnaBase.f32PHASE_Q += PHASE_Q;
    InvAnaBase.f32PHASE_3P += PHASE_3P;
    InvAnaBase.f32PHASE_5P += PHASE_5P;
    InvAnaBase.f32PHASE_7P += PHASE_7P;
    InvAnaBase.f32PHASE_9P += PHASE_9P;
    //温度
    InvAnaBase.f32TEMP_AD += TEMP_AD;
    }


    InvAnaBase.f32VDS_EV_AD = __divf32(InvAnaBase.f32VDS_EV_AD , 1000);
    InvAnaBase.f32VDS_EV_AD_R1 = __divf32(InvAnaBase.f32VDS_EV_AD_R1 , 1000);
    InvAnaBase.f32VDS_EV_AD_R2 =__divf32(InvAnaBase.f32VDS_EV_AD_R2 , 1000) ;

    InvAnaBase.f32VDS_INV_AD = __divf32(InvAnaBase.f32VDS_INV_AD , 1000);
    InvAnaBase.f32VDS_INV_AD_R1 = __divf32(InvAnaBase.f32VDS_INV_AD_R1 , 1000);
    InvAnaBase.f32VDS_INV_AD_R2 = __divf32(InvAnaBase.f32VDS_INV_AD_R2 , 1000);

    //直流电流采样
    InvAnaBase.f32IO_AD =  __divf32(InvAnaBase.f32IO_AD , 1000);
    InvAnaBase.f32IO_AD_R1 = __divf32(InvAnaBase.f32IO_AD_R1 , 1000);
    InvAnaBase.f32IO_AD_R2 =  __divf32(InvAnaBase.f32IO_AD_R2 , 1000);

    //谐振电流采样

    InvAnaBase.f32ILRS_PK = __divf32(InvAnaBase.f32ILRS_PK , 1000);
    InvAnaBase.f32ILRS_PK_R1 = __divf32(InvAnaBase.f32ILRS_PK_R1 , 1000);
    InvAnaBase.f32ILRS_PK_R2 = __divf32(InvAnaBase.f32ILRS_PK_R2 , 1000);
    InvAnaBase.f32ILRS_AC_AD = __divf32(InvAnaBase.f32ILRS_AC_AD , 1000);

    //调制波
    InvAnaBase.f32PHASE_P = __divf32(InvAnaBase.f32PHASE_P , 1000);
    InvAnaBase.f32PHASE_Q = __divf32(InvAnaBase.f32PHASE_Q , 1000);
    InvAnaBase.f32PHASE_3P = __divf32(InvAnaBase.f32PHASE_3P , 1000);
    InvAnaBase.f32PHASE_5P = __divf32(InvAnaBase.f32PHASE_5P , 1000);
    InvAnaBase.f32PHASE_7P = __divf32(InvAnaBase.f32PHASE_7P , 1000);
    InvAnaBase.f32PHASE_9P = __divf32(InvAnaBase.f32PHASE_9P , 1000);
    //温度
    InvAnaBase.f32TEMP_AD = __divf32(InvAnaBase.f32TEMP_AD , 1000);

    if(1 == AdcaRegs.ADCINTOVF.bit.ADCINT1)
    {
        AdcaRegs.ADCINTOVFCLR.bit.ADCINT1 = 1; //clear INT1 overflow flag
        AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    }

    if(1 == AdcbRegs.ADCINTOVF.bit.ADCINT1)
    {
        AdcbRegs.ADCINTOVFCLR.bit.ADCINT1 = 1; //clear INT1 overflow flag
        AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    }

    if(1 == AdccRegs.ADCINTOVF.bit.ADCINT1)
    {
        AdccRegs.ADCINTOVFCLR.bit.ADCINT1 = 1; //clear INT1 overflow flag
        AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    }

    if(1 == AdcdRegs.ADCINTOVF.bit.ADCINT1)
    {
        AdcdRegs.ADCINTOVFCLR.bit.ADCINT1 = 1; //clear INT1 overflow flag
        AdcdRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    }
}

void ConfigureADC()
{
    EALLOW;
    //
    //write configurations
    //
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    //
    //Set pulse positions to late
    //
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    //
    //power up the ADC
    //
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    //
    //delay for 1ms to allow ADC time to power up
    //
    DELAY_US(1000);
    //
    //write configurations
    //
    AdcbRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    //
    //Set pulse positions to late
    //
    AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    //
    //power up the ADC
    //
    AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    //
    //delay for 1ms to allow ADC time to power up
    //
    DELAY_US(1000);
    //
    //write configurations
    //
    AdccRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCC, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    //
    //Set pulse positions to late
    //
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    //
    //power up the ADC
    //
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    //
    //delay for 1ms to allow ADC time to power up
    //
    DELAY_US(1000);
    //
    //write configurations
    //
    AdcdRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCD, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    //
    //Set pulse positions to late
    //
    AdcdRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    //
    //power up the ADC
    //
    AdcdRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    //
    //delay for 1ms to allow ADC time to power up
    //
    DELAY_US(1000);

    EDIS;
}

void SetupADC()
{
    Uint16 acqps;
    Uint16 trigsel;

    //
    // Determine minimum acquisition window (in SYSCLKS) based on resolution
    //
    if(ADC_RESOLUTION_12BIT == AdcaRegs.ADCCTL2.bit.RESOLUTION)
    {
        acqps = 14; //75ns
    }
    else //resolution is 16-bit
    {
        acqps = 63; //320ns
    }
    trigsel = 0;
    //
    //Select the channels to convert and end of conversion flag
    //
    EALLOW;

    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0;  //A0
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = trigsel; //trigger on ePWM SOC

    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 1;  //A1
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = trigsel; //trigger on ePWM SOC

    AdcaRegs.ADCSOC2CTL.bit.CHSEL = 2;  //A2
    AdcaRegs.ADCSOC2CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = trigsel; //trigger on ePWM SOC

    AdcaRegs.ADCSOC3CTL.bit.CHSEL = 3;  //A3
    AdcaRegs.ADCSOC3CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC3CTL.bit.TRIGSEL = trigsel; //trigger on ePWM SOC

    AdcaRegs.ADCSOC4CTL.bit.CHSEL = 4;  //A4
    AdcaRegs.ADCSOC4CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC4CTL.bit.TRIGSEL = trigsel; //trigger on ePWM SOC

    AdcaRegs.ADCSOC5CTL.bit.CHSEL = 5;  //A5
    AdcaRegs.ADCSOC5CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC5CTL.bit.TRIGSEL = trigsel; //trigger on ePWM SOC

    // ADCb通道配置

    AdcbRegs.ADCSOC0CTL.bit.CHSEL = 0;  //B0
    AdcbRegs.ADCSOC0CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = trigsel; //trigger on ePWM SOC

    AdcbRegs.ADCSOC1CTL.bit.CHSEL = 1;  //B1
    AdcbRegs.ADCSOC1CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC1CTL.bit.TRIGSEL = trigsel; //trigger on ePWM SOC

    AdcbRegs.ADCSOC2CTL.bit.CHSEL = 2;  //B2
    AdcbRegs.ADCSOC2CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC2CTL.bit.TRIGSEL = trigsel; //trigger on ePWM SOC

    AdcbRegs.ADCSOC3CTL.bit.CHSEL = 3;  //B3
    AdcbRegs.ADCSOC3CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcbRegs.ADCSOC3CTL.bit.TRIGSEL = trigsel; //trigger on ePWM SOC

    // ADCC通道配置

    AdccRegs.ADCSOC0CTL.bit.CHSEL = 14;  //14
    AdccRegs.ADCSOC0CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdccRegs.ADCSOC0CTL.bit.TRIGSEL = trigsel; //trigger on ePWM SOC

    AdccRegs.ADCSOC1CTL.bit.CHSEL = 15;  //15
    AdccRegs.ADCSOC1CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdccRegs.ADCSOC1CTL.bit.TRIGSEL = trigsel; //trigger on ePWM SOC

    AdccRegs.ADCSOC2CTL.bit.CHSEL = 2;  //C2
    AdccRegs.ADCSOC2CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdccRegs.ADCSOC2CTL.bit.TRIGSEL = trigsel; //trigger on ePWM SOC

    AdccRegs.ADCSOC3CTL.bit.CHSEL = 3;  //C3
    AdccRegs.ADCSOC3CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdccRegs.ADCSOC3CTL.bit.TRIGSEL = trigsel; //trigger on ePWM SOC

    AdccRegs.ADCSOC3CTL.bit.CHSEL =4;  //C4
    AdccRegs.ADCSOC3CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdccRegs.ADCSOC3CTL.bit.TRIGSEL = trigsel; //trigger on ePWM SOC
    // ADCD通道配置

    AdcdRegs.ADCSOC0CTL.bit.CHSEL = 0;  //D0
    AdcdRegs.ADCSOC0CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC0CTL.bit.TRIGSEL = trigsel; //trigger on ePWM SOC

    AdcdRegs.ADCSOC1CTL.bit.CHSEL = 1;  //D1
    AdcdRegs.ADCSOC1CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC1CTL.bit.TRIGSEL = trigsel; //trigger on ePWM SOC

    AdcdRegs.ADCSOC2CTL.bit.CHSEL = 2;  //D2
    AdcdRegs.ADCSOC2CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC2CTL.bit.TRIGSEL = trigsel; //trigger on ePWM SOC

    AdcdRegs.ADCSOC3CTL.bit.CHSEL = 3;  //D3
    AdcdRegs.ADCSOC3CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC3CTL.bit.TRIGSEL = trigsel; //trigger on ePWM SOC

    AdcdRegs.ADCSOC3CTL.bit.CHSEL = 4;  //D4
    AdcdRegs.ADCSOC3CTL.bit.ACQPS = acqps; //sample window is 100 SYSCLK cycles
    AdcdRegs.ADCSOC3CTL.bit.TRIGSEL = trigsel; //trigger on ePWM SOC

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 5; //end of SOC0 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;   //enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared

    AdcbRegs.ADCINTSEL1N2.bit.INT1SEL = 3; //end of SOC3 will set INT1 flag
    AdcbRegs.ADCINTSEL1N2.bit.INT1E = 1;   //enable INT1 flag
    AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared

    AdccRegs.ADCINTSEL1N2.bit.INT1SEL = 4; //end of SOC4 will set INT1 flag
    AdccRegs.ADCINTSEL1N2.bit.INT1E = 1;   //enable INT1 flag
    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared

    AdcdRegs.ADCINTSEL1N2.bit.INT1SEL = 4; //end of SOC4 will set INT1 flag
    AdcdRegs.ADCINTSEL1N2.bit.INT1E = 1;   //enable INT1 flag
    AdcdRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared

    EDIS;
}
