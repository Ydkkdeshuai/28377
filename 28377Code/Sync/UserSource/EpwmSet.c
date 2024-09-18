/*
 * EpwmSet.c
 *
 *  Created on: 2024年7月15日
 *      Author: Mengfanbin
 */
//#include "F28x_Project.h"

#include"EpwmSet.h"

void EpwmSet(void)
{
    CpuSysRegs.PCLKCR2.bit.EPWM1=1;
    CpuSysRegs.PCLKCR2.bit.EPWM2=1;
    CpuSysRegs.PCLKCR2.bit.EPWM3=1;
    CpuSysRegs.PCLKCR2.bit.EPWM4=1;
    CpuSysRegs.PCLKCR2.bit.EPWM5=1;
    CpuSysRegs.PCLKCR2.bit.EPWM6=1;
    CpuSysRegs.PCLKCR2.bit.EPWM7=1;
    CpuSysRegs.PCLKCR2.bit.EPWM8=1;
    CpuSysRegs.PCLKCR2.bit.EPWM9=1;
    CpuSysRegs.PCLKCR2.bit.EPWM10=1;
    CpuSysRegs.PCLKCR2.bit.EPWM11=1;
    CpuSysRegs.PCLKCR2.bit.EPWM12=1;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC =0;
    EDIS;
    //Epwm1和2为逆变器3的驱动
    Epwm1Set();
    Epwm2Set();
    //Epwm3和4为逆变器2的驱动
    Epwm3Set();
    Epwm4Set();
    //Epwm6和7为逆变器1的驱动
    Epwm6Set();
    Epwm7Set();

    //Epwm8A为1P
    Epwm8Set();
    //Epwm9A为1Q
    Epwm9Set();
    //Epwm10A为3P
    Epwm10Set();
    //Epwm11A为5P
    Epwm11Set();
//    Epwm5A为7P
    Epwm5Set();
    //Epwm12A为9P，Epwm12B为风扇调速接口
    Epwm12Set();

    //EPWM同步配置
    EALLOW;
    SyncSocRegs.SYNCSELECT.bit.EPWM4SYNCIN = 0;     //EPWM1输出同步EPWM4
    SyncSocRegs.SYNCSELECT.bit.EPWM7SYNCIN = 0;     // EPWM1 同步EPWM7
    SyncSocRegs.SYNCSELECT.bit.EPWM10SYNCIN = 0;     // EPWM1 同步EPWM10
    EPwm1Regs.TBCTL.bit.SYNCOSEL   = TB_CTR_ZERO;
    EDIS;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC =1;
    EDIS;

}

void Epwm1Set(void)
{
    // Setup TBCLK
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to EPWMCLK : /1    默认的epwm时钟为 100MHz
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;               // Clock ratio to EPWMCLK : /1

    EPwm1Regs.TBPRD = TBPRD_Up;                       // Set timer period 85kHz
    EPwm1Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm1Regs.TBCTR = 0x0000;                     // Clear counter

    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;   // Load registers every ZERO
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_PRD;

    // Setup compare
    EPwm1Regs.CMPA.bit.CMPA = EPwm1Regs.TBPRD*0; //Duty = 0.5
    EPwm1Regs.CMPB.bit.CMPB = EPwm1Regs.TBPRD*0.5; //Duty = 0.5
    // Set actions
    EPwm1Regs.AQCSFRC.bit.CSFA = 1;                 // AQ submodule output PWMA forced to low
    EPwm1Regs.AQCSFRC.bit.CSFB = 1;                 // AQ submodule output PWMB forced to low
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;              // CMPA up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;
    EPwm1Regs.AQCTLA.bit.CBU = AQ_CLEAR;            // CMPB up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;

//         Active Low PWMs - Setup Deadband
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;  //RED 和 FED均有效
    EPwm1Regs.DBCTL.bit.POLSEL =DB_ACTV_HIC ;
    EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm1Regs.DBRED.bit.DBRED = 35; //一个时钟周期为5ns
    EPwm1Regs.DBFED.bit.DBFED = 35;

//         Interrupt where we will change the Deadband
    EPwm1Regs.ETSEL.bit.INTSEL = ET_DISABLE;    // Select INT on Zero event 选择0匹配事件中断
    EPwm1Regs.ETSEL.bit.INTEN = 0;               // Enable INT
    EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;          // Generate INT on 3rd event 三次中断请求

}
void Epwm2Set(void)
{
    // Setup TBCLK
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to EPWMCLK : /1    默认的epwm时钟为 100MHz
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;               // Clock ratio to EPWMCLK : /1

    EPwm2Regs.TBPRD = TBPRD_Up;                       // Set timer period 85kHz
    EPwm2Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm2Regs.TBCTR = 0x0000;                     // Clear counter

    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;   // Load registers every ZERO
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_PRD;

    // Setup compare
    EPwm2Regs.CMPA.bit.CMPA = EPwm2Regs.TBPRD*0; //Duty = 0.5
    EPwm2Regs.CMPB.bit.CMPB = EPwm2Regs.TBPRD*0.5; //Duty = 0.5
    // Set actions
    EPwm2Regs.AQCSFRC.bit.CSFA = 1;                 // AQ submodule output PWMA forced to low
    EPwm2Regs.AQCSFRC.bit.CSFB = 1;                 // AQ submodule output PWMB forced to low
    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;              // CMPA up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;
    EPwm2Regs.AQCTLA.bit.CBU = AQ_CLEAR;            // CMPB up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;

//         Active Low PWMs - Setup Deadband
    EPwm2Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;  //RED 和 FED均有效
    EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm2Regs.DBRED.bit.DBRED = 35; //一个时钟周期为5ns
    EPwm2Regs.DBFED.bit.DBFED = 35;

//         Interrupt where we will change the Deadband
    EPwm2Regs.ETSEL.bit.INTSEL = ET_DISABLE;    // Select INT on Zero event 选择0匹配事件中断
    EPwm2Regs.ETSEL.bit.INTEN = 0;               // Enable INT
    EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;          // Generate INT on 3rd event 三次中断请求

}


void Epwm3Set(void)
{
    // Setup TBCLK
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to EPWMCLK : /1    默认的epwm时钟为 100MHz
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;               // Clock ratio to EPWMCLK : /1

    EPwm3Regs.TBPRD = TBPRD_Up;                       // Set timer period 85kHz
    EPwm3Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm3Regs.TBCTR = 0x0000;                     // Clear counter

    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;   // Load registers every ZERO
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_PRD;

    // Setup compare
    EPwm3Regs.CMPA.bit.CMPA = EPwm3Regs.TBPRD*0; //Duty = 0.5
    EPwm3Regs.CMPB.bit.CMPB = EPwm3Regs.TBPRD*0.5; //Duty = 0.5
    // Set actions
    EPwm3Regs.AQCSFRC.bit.CSFA = 1;                 // AQ submodule output PWMA forced to low
    EPwm3Regs.AQCSFRC.bit.CSFB = 1;                 // AQ submodule output PWMB forced to low
    EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;              // CMPA up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;
    EPwm3Regs.AQCTLA.bit.CBU = AQ_CLEAR;            // CMPB up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;

//         Active Low PWMs - Setup Deadband
    EPwm3Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;  //RED 和 FED均有效
    EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm3Regs.DBRED.bit.DBRED = 35; //一个时钟周期为5ns
    EPwm3Regs.DBFED.bit.DBFED = 35;

//         Interrupt where we will change the Deadband
    EPwm3Regs.ETSEL.bit.INTSEL = ET_DISABLE;    // Select INT on Zero event 选择0匹配事件中断
    EPwm3Regs.ETSEL.bit.INTEN = 0;               // Enable INT
    EPwm3Regs.ETPS.bit.INTPRD = ET_1ST;          // Generate INT on 3rd event 三次中断请求

}
void Epwm4Set(void)
{
    // Setup TBCLK
    EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to EPWMCLK : /1    默认的epwm时钟为 100MHz
    EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;               // Clock ratio to EPWMCLK : /1

    EPwm4Regs.TBPRD = TBPRD_Up;                       // Set timer period 85kHz
    EPwm4Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm4Regs.TBCTR = 0x0000;                     // Clear counter

    EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;   // Load registers every ZERO
    EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
    EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_PRD;

    // Setup compare
    EPwm4Regs.CMPA.bit.CMPA = EPwm4Regs.TBPRD*0; //Duty = 0.5
    EPwm4Regs.CMPB.bit.CMPB = EPwm4Regs.TBPRD*0.5; //Duty = 0.5
    // Set actions
    EPwm4Regs.AQCSFRC.bit.CSFA = 1;                 // AQ submodule output PWMA forced to low
    EPwm4Regs.AQCSFRC.bit.CSFB = 1;                 // AQ submodule output PWMB forced to low
    EPwm4Regs.AQCTLA.bit.CAU = AQ_SET;              // CMPA up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;
    EPwm4Regs.AQCTLA.bit.CBU = AQ_CLEAR;            // CMPB up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;

//         Active Low PWMs - Setup Deadband
    EPwm4Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;  //RED 和 FED均有效
    EPwm4Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm4Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm4Regs.DBRED.bit.DBRED = 35; //一个时钟周期为5ns
    EPwm4Regs.DBFED.bit.DBFED = 35;

//         Interrupt where we will change the Deadband
    EPwm4Regs.ETSEL.bit.INTSEL = ET_DISABLE;    // Select INT on Zero event 选择0匹配事件中断
    EPwm4Regs.ETSEL.bit.INTEN = 0;               // Enable INT
    EPwm4Regs.ETPS.bit.INTPRD = ET_1ST;          // Generate INT on 3rd event 三次中断请求

}

void Epwm6Set(void)
{
    // Setup TBCLK
    EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    EPwm6Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
    EPwm6Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to EPWMCLK : /1    默认的epwm时钟为 100MHz
    EPwm6Regs.TBCTL.bit.CLKDIV = TB_DIV1;               // Clock ratio to EPWMCLK : /1

    EPwm6Regs.TBPRD = TBPRD_Up;                       // Set timer period 85kHz
    EPwm6Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm6Regs.TBCTR = 0x0000;                     // Clear counter

    EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;   // Load registers every ZERO
    EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
    EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_PRD;

    // Setup compare
    EPwm6Regs.CMPA.bit.CMPA = EPwm6Regs.TBPRD*0; //Duty = 0.5
    EPwm6Regs.CMPB.bit.CMPB = EPwm6Regs.TBPRD*0.5; //Duty = 0.5
    // Set actions
//    EPwm6Regs.AQCSFRC.bit.CSFA = 1;                 // AQ submodule output PWMA forced to low
//    EPwm6Regs.AQCSFRC.bit.CSFB = 1;                 // AQ submodule output PWMB forced to low
    EPwm6Regs.AQCTLA.bit.CAU = AQ_SET;              // CMPA up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;
    EPwm6Regs.AQCTLA.bit.CBU = AQ_CLEAR;            // CMPB up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;

//         Active Low PWMs - Setup Deadband
    EPwm6Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;  //RED 和 FED均有效
    EPwm6Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm6Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm6Regs.DBRED.bit.DBRED = 35; //一个时钟周期为5ns
    EPwm6Regs.DBFED.bit.DBFED = 35;

//         Interrupt where we will change the Deadband
    EPwm6Regs.ETSEL.bit.INTSEL = ET_DISABLE;    // Select INT on Zero event 选择0匹配事件中断
    EPwm6Regs.ETSEL.bit.INTEN = 0;               // Enable INT
    EPwm6Regs.ETPS.bit.INTPRD = ET_1ST;          // Generate INT on 3rd event 三次中断请求

}


void Epwm7Set(void)
{
    // Setup TBCLK
    EPwm7Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    EPwm7Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
    EPwm7Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to EPWMCLK : /1    默认的epwm时钟为 100MHz
    EPwm7Regs.TBCTL.bit.CLKDIV = TB_DIV1;               // Clock ratio to EPWMCLK : /1

    EPwm7Regs.TBPRD = TBPRD_Up;                       // Set timer period 85kHz
    EPwm7Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm7Regs.TBCTR = 0x0000;                     // Clear counter

    EPwm7Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;   // Load registers every ZERO
    EPwm7Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm7Regs.CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
    EPwm7Regs.CMPCTL.bit.LOADBMODE = CC_CTR_PRD;

    // Setup compare
    EPwm7Regs.CMPA.bit.CMPA = EPwm7Regs.TBPRD*0; //Duty = 0.5
    EPwm7Regs.CMPB.bit.CMPB = EPwm7Regs.TBPRD*0.5; //Duty = 0.5
    // Set actions
//    EPwm7Regs.AQCSFRC.bit.CSFA = 1;                 // AQ submodule output PWMA forced to low
//    EPwm7Regs.AQCSFRC.bit.CSFB = 1;                 // AQ submodule output PWMB forced to low
    EPwm7Regs.AQCTLA.bit.CAU = AQ_CLEAR;              // CMPA up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;
    EPwm7Regs.AQCTLA.bit.CBU = AQ_SET;            // CMPB up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;

//         Active Low PWMs - Setup Deadband
    EPwm7Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;  //RED 和 FED均有效
    EPwm7Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm7Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm7Regs.DBRED.bit.DBRED = 35; //一个时钟周期为5ns
    EPwm7Regs.DBFED.bit.DBFED = 35;

//         Interrupt where we will change the Deadband
    EPwm7Regs.ETSEL.bit.INTSEL = ET_DISABLE;    // Select INT on Zero event 选择0匹配事件中断
    EPwm7Regs.ETSEL.bit.INTEN = 0;               // Enable INT
    EPwm7Regs.ETPS.bit.INTPRD = ET_1ST;          // Generate INT on 3rd event 三次中断请求

}

//1P
void Epwm8Set(void)
{
    // Setup TBCLK
    EPwm8Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    EPwm8Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
    EPwm8Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to EPWMCLK : /1    默认的epwm时钟为 100MHz
    EPwm8Regs.TBCTL.bit.CLKDIV = TB_DIV1;               // Clock ratio to EPWMCLK : /1

    EPwm8Regs.TBPRD = TBPRD_Up;                       // Set timer period 85kHz
    EPwm8Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm8Regs.TBCTR = 0x0000;                     // Clear counter

    EPwm8Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;   // Load registers every ZERO
    EPwm8Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm8Regs.CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
    EPwm8Regs.CMPCTL.bit.LOADBMODE = CC_CTR_PRD;

    // Setup compare
    EPwm8Regs.CMPA.bit.CMPA = EPwm8Regs.TBPRD*0; //Duty = 0.5
    EPwm8Regs.CMPB.bit.CMPB = EPwm8Regs.TBPRD*0.5; //Duty = 0.5
    // Set actions
    EPwm8Regs.AQCSFRC.bit.CSFA = 1;                 // AQ submodule output PWMA forced to low
    EPwm8Regs.AQCSFRC.bit.CSFB = 1;                 // AQ submodule output PWMB forced to low
    EPwm8Regs.AQCTLA.bit.CAU = AQ_SET;              // CMPA up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;
    EPwm8Regs.AQCTLA.bit.CBU = AQ_CLEAR;            // CMPB up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;

//         Active Low PWMs - Setup Deadband
    EPwm8Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;  //RED 和 FED均有效
    EPwm8Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm8Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm8Regs.DBRED.bit.DBRED = 0; //一个时钟周期为5ns
    EPwm8Regs.DBFED.bit.DBFED = 0;

//         Interrupt where we will change the Deadband
    EPwm8Regs.ETSEL.bit.INTSEL = ET_DISABLE;    // Select INT on Zero event 选择0匹配事件中断
    EPwm8Regs.ETSEL.bit.INTEN = 0;               // Enable INT
    EPwm8Regs.ETPS.bit.INTPRD = ET_1ST;          // Generate INT on 3rd event 三次中断请求

}

//1Q
void Epwm9Set(void)
{
    // Setup TBCLK
    EPwm9Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    EPwm9Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
    EPwm9Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to EPWMCLK : /1    默认的epwm时钟为 100MHz
    EPwm9Regs.TBCTL.bit.CLKDIV = TB_DIV1;               // Clock ratio to EPWMCLK : /1

    EPwm9Regs.TBPRD = TBPRD_Up;                       // Set timer period 85kHz
    EPwm9Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm9Regs.TBCTR = 0x0000;                     // Clear counter

    EPwm9Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;   // Load registers every ZERO
    EPwm9Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm9Regs.CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
    EPwm9Regs.CMPCTL.bit.LOADBMODE = CC_CTR_PRD;

    // Setup compare
    EPwm9Regs.CMPA.bit.CMPA = EPwm9Regs.TBPRD*0; //Duty = 0.5
    EPwm9Regs.CMPB.bit.CMPB = EPwm9Regs.TBPRD*0.5; //Duty = 0.5
    // Set actions
    EPwm9Regs.AQCSFRC.bit.CSFA = 1;                 // AQ submodule output PWMA forced to low
    EPwm9Regs.AQCSFRC.bit.CSFB = 1;                 // AQ submodule output PWMB forced to low
    EPwm9Regs.AQCTLA.bit.CAU = AQ_SET;              // CMPA up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;
    EPwm9Regs.AQCTLA.bit.CBU = AQ_CLEAR;            // CMPB up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;

//         Active Low PWMs - Setup Deadband
    EPwm9Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;  //RED 和 FED均有效
    EPwm9Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm9Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm9Regs.DBRED.bit.DBRED = 0; //一个时钟周期为5ns
    EPwm9Regs.DBFED.bit.DBFED = 0;

//         Interrupt where we will change the Deadband
    EPwm9Regs.ETSEL.bit.INTSEL = ET_DISABLE;    // Select INT on Zero event 选择0匹配事件中断
    EPwm9Regs.ETSEL.bit.INTEN = 0;               // Enable INT
    EPwm9Regs.ETPS.bit.INTPRD = ET_1ST;          // Generate INT on 3rd event 三次中断请求

}

//3P
void Epwm10Set(void)
{
    // Setup TBCLK
    EPwm10Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    EPwm10Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
    EPwm10Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to EPWMCLK : /1    默认的epwm时钟为 100MHz
    EPwm10Regs.TBCTL.bit.CLKDIV = TB_DIV1;               // Clock ratio to EPWMCLK : /1

    EPwm10Regs.TBPRD = TBPRD_Up_3rd;                       // Set timer period 85kHz
    EPwm10Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm10Regs.TBCTR = 0x0000;                     // Clear counter

    EPwm10Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;   // Load registers every ZERO
    EPwm10Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm10Regs.CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
    EPwm10Regs.CMPCTL.bit.LOADBMODE = CC_CTR_PRD;

    // Setup compare
    EPwm10Regs.CMPA.bit.CMPA = EPwm10Regs.TBPRD*0; //Duty = 0.5
    EPwm10Regs.CMPB.bit.CMPB = EPwm10Regs.TBPRD*0.5; //Duty = 0.5
    // Set actions
    EPwm10Regs.AQCSFRC.bit.CSFA = 1;                 // AQ submodule output PWMA forced to low
    EPwm10Regs.AQCSFRC.bit.CSFB = 1;                 // AQ submodule output PWMB forced to low
    EPwm10Regs.AQCTLA.bit.CAU = AQ_SET;              // CMPA up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;
    EPwm10Regs.AQCTLA.bit.CBU = AQ_CLEAR;            // CMPB up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;

//         Active Low PWMs - Setup Deadband
    EPwm10Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;  //RED 和 FED均有效
    EPwm10Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm10Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm10Regs.DBRED.bit.DBRED = 0; //一个时钟周期为5ns
    EPwm10Regs.DBFED.bit.DBFED = 0;

//         Interrupt where we will change the Deadband
    EPwm10Regs.ETSEL.bit.INTSEL = ET_DISABLE;    // Select INT on Zero event 选择0匹配事件中断
    EPwm10Regs.ETSEL.bit.INTEN = 0;               // Enable INT
    EPwm10Regs.ETPS.bit.INTPRD = ET_1ST;          // Generate INT on 3rd event 三次中断请求

}
//5P
void Epwm11Set(void)
{
    // Setup TBCLK
    EPwm11Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    EPwm11Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
    EPwm11Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to EPWMCLK : /1    默认的epwm时钟为 100MHz
    EPwm11Regs.TBCTL.bit.CLKDIV = TB_DIV1;               // Clock ratio to EPWMCLK : /1

    EPwm11Regs.TBPRD = TBPRD_Up_5rd;                       // Set timer period 85kHz
    EPwm11Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm11Regs.TBCTR = 0x0000;                     // Clear counter

    EPwm11Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;   // Load registers every ZERO
    EPwm11Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm11Regs.CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
    EPwm11Regs.CMPCTL.bit.LOADBMODE = CC_CTR_PRD;

    // Setup compare
    EPwm11Regs.CMPA.bit.CMPA = EPwm11Regs.TBPRD*0; //Duty = 0.5
    EPwm11Regs.CMPB.bit.CMPB = EPwm11Regs.TBPRD*0.5; //Duty = 0.5
    // Set actions
    EPwm11Regs.AQCSFRC.bit.CSFA = 1;                 // AQ submodule output PWMA forced to low
    EPwm11Regs.AQCSFRC.bit.CSFB = 1;                 // AQ submodule output PWMB forced to low
    EPwm11Regs.AQCTLA.bit.CAU = AQ_SET;              // CMPA up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;
    EPwm11Regs.AQCTLA.bit.CBU = AQ_CLEAR;            // CMPB up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;

//         Active Low PWMs - Setup Deadband
    EPwm11Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;  //RED 和 FED均有效
    EPwm11Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm11Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm11Regs.DBRED.bit.DBRED = 0; //一个时钟周期为5ns
    EPwm11Regs.DBFED.bit.DBFED = 0;

//         Interrupt where we will change the Deadband
    EPwm11Regs.ETSEL.bit.INTSEL = ET_DISABLE;    // Select INT on Zero event 选择0匹配事件中断
    EPwm11Regs.ETSEL.bit.INTEN = 0;               // Enable INT
    EPwm11Regs.ETPS.bit.INTPRD = ET_1ST;          // Generate INT on 3rd event 三次中断请求

}
//7P,做控制可不用，暂时配置成85kHz
void Epwm5Set(void)
{
    // Setup TBCLK
    EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    EPwm5Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
    EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to EPWMCLK : /1    默认的epwm时钟为 100MHz
    EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV1;               // Clock ratio to EPWMCLK : /1

    EPwm5Regs.TBPRD = TBPRD_Up;                       // Set timer period 85kHz
    EPwm5Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm5Regs.TBCTR = 0x0000;                     // Clear counter

    EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;   // Load registers every ZERO
    EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
    EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_PRD;

    // Setup compare
    EPwm5Regs.CMPA.bit.CMPA = EPwm5Regs.TBPRD*0; //Duty = 0.5
    EPwm5Regs.CMPB.bit.CMPB = EPwm5Regs.TBPRD*0.5; //Duty = 0.5
    // Set actions
    EPwm5Regs.AQCSFRC.bit.CSFA = 1;                 // AQ submodule output PWMA forced to low
    EPwm5Regs.AQCSFRC.bit.CSFB = 1;                 // AQ submodule output PWMB forced to low
    EPwm5Regs.AQCTLA.bit.CAU = AQ_SET;              // CMPA up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;
    EPwm5Regs.AQCTLA.bit.CBU = AQ_CLEAR;            // CMPB up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;

//         Active Low PWMs - Setup Deadband
    EPwm5Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;  //RED 和 FED均有效
    EPwm5Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm5Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm5Regs.DBRED.bit.DBRED = 0; //一个时钟周期为5ns
    EPwm5Regs.DBFED.bit.DBFED = 0;

//         Interrupt where we will change the Deadband
    EPwm5Regs.ETSEL.bit.INTSEL = ET_DISABLE;    // Select INT on Zero event 选择0匹配事件中断
    EPwm5Regs.ETSEL.bit.INTEN = 0;               // Enable INT
    EPwm5Regs.ETPS.bit.INTPRD = ET_1ST;          // Generate INT on 3rd event 三次中断请求

}
//9rd做控制可不用，暂时配置成85kHz
void Epwm12Set(void)
{
    // Setup TBCLK
    EPwm12Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    EPwm12Regs.TBCTL.bit.PHSEN = TB_ENABLE;        // Disable phase loading
    EPwm12Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to EPWMCLK : /1    默认的epwm时钟为 100MHz
    EPwm12Regs.TBCTL.bit.CLKDIV = TB_DIV1;               // Clock ratio to EPWMCLK : /1

    EPwm12Regs.TBPRD = TBPRD_Up;                       // Set timer period 85kHz
    EPwm12Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm12Regs.TBCTR = 0x0000;                     // Clear counter

    EPwm12Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;   // Load registers every ZERO
    EPwm12Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm12Regs.CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
    EPwm12Regs.CMPCTL.bit.LOADBMODE = CC_CTR_PRD;

    // Setup compare
    EPwm12Regs.CMPA.bit.CMPA = EPwm12Regs.TBPRD*0; //Duty = 0.5
    EPwm12Regs.CMPB.bit.CMPB = EPwm12Regs.TBPRD*0.5; //Duty = 0.5
    // Set actions
    EPwm12Regs.AQCSFRC.bit.CSFA = 1;                 // AQ submodule output PWMA forced to low
    EPwm12Regs.AQCSFRC.bit.CSFB = 1;                 // AQ submodule output PWMB forced to low
    EPwm12Regs.AQCTLA.bit.CAU = AQ_SET;              // CMPA up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;
    EPwm12Regs.AQCTLA.bit.CBU = AQ_CLEAR;            // CMPB up compare action:0x00 no action ; 0x01 low ; 0x10 high ; 0x11 toggle;

//         Active Low PWMs - Setup Deadband
    EPwm12Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;  //RED 和 FED均有效
    EPwm12Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm12Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm12Regs.DBRED.bit.DBRED = 0; //一个时钟周期为5ns
    EPwm12Regs.DBFED.bit.DBFED = 0;

//         Interrupt where we will change the Deadband
    EPwm12Regs.ETSEL.bit.INTSEL = ET_DISABLE;    // Select INT on Zero event 选择0匹配事件中断
    EPwm12Regs.ETSEL.bit.INTEN = 0;               // Enable INT
    EPwm12Regs.ETPS.bit.INTPRD = ET_1ST;          // Generate INT on 3rd event 三次中断请求

}
