/*
 * SysStsFlt.c
 *
 *  Created on: 2024年7月22日
 *      Author: Mengfanbin
 */

#include "SysStsFlt.h"
#include "Sys_GPIO.h"
union SYS_STS SysSts;       // System states

/************************************************************************************************************************
    Function     : void SysFltInit(void)
    Introduction : Initialize system fault states
    Inputs       : None
    Outputs      : None
    Comments     : None

*************************************************************************************************************************/

void SysStsFltInit(void)
{
    SysSts.bit.SYS_WORK_STS = SYS_WORK_STS_IDLE;                    // System is idle
    SysSts.bit.WIFI_STS = WIFI_STS_DISCONNECTED;                    // Wifi is disconnected
    SysSts.bit.ILRS_FLT_STS = ILRS_FLT_STS_NORMAL;                  // ILrs no overcurrent
    SysSts.bit.VDS_INV_FLT_STS = VDS_INV_FLT_STS_NORMAL;                    // ILs no overcurrent
    SysSts.bit.VDS_EV_FLT_STS = VDS_EV_FLT_STS_NORMAL;
    SysSts.bit.GA_STS = GA_STS_IDLE;                                // GA is idle
}

void WptPrimaryFullBridgePWMEnable(void)
{
    EPwm6Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;   // OUT_MODE set to 3 : Dead-band is fully enabled
    EPwm7Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm6Regs.AQCSFRC.bit.CSFA = 0;     // Software force for output is closed
    EPwm6Regs.AQCSFRC.bit.CSFB = 0;
    EPwm7Regs.AQCSFRC.bit.CSFA = 0;
    EPwm7Regs.AQCSFRC.bit.CSFB = 0;
}

void WptPrimaryFullBridgePWMDisable(void)
{
    EPwm6Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;   //OUT_MODE set to 0 : Dead-band closed
    EPwm7Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    EPwm6Regs.AQCSFRC.bit.CSFA = 1;     // Software force the output to 0
    EPwm6Regs.AQCSFRC.bit.CSFB = 1;
    EPwm7Regs.AQCSFRC.bit.CSFA = 1;
    EPwm7Regs.AQCSFRC.bit.CSFB = 1;
}

void WptPrimaryFullBridgeShotCut(void)
{
    EPwm6Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;   //OUT_MODE set to 0 : Dead-band closed
    EPwm7Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    EPwm6Regs.AQCSFRC.bit.CSFA = 2;     // Software force the output to 1
    EPwm6Regs.AQCSFRC.bit.CSFB = 1;
    EPwm7Regs.AQCSFRC.bit.CSFA = 2;
    EPwm7Regs.AQCSFRC.bit.CSFB = 1;
}

void WptPQSyncPWMEnable(void)
{
    EPwm8Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;   // OUT_MODE set to 3 : Dead-band is fully enabled
    EPwm9Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm10Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm11Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm8Regs.AQCSFRC.bit.CSFA = 0;     // Software force for output is closed
    EPwm8Regs.AQCSFRC.bit.CSFB = 0;
    EPwm9Regs.AQCSFRC.bit.CSFA = 0;
    EPwm9Regs.AQCSFRC.bit.CSFB = 0;
    EPwm10Regs.AQCSFRC.bit.CSFA = 0;
    EPwm10Regs.AQCSFRC.bit.CSFB = 0;
    EPwm11Regs.AQCSFRC.bit.CSFA = 0;
    EPwm11Regs.AQCSFRC.bit.CSFB = 0;
}


void WptPQSyncPWMDisable(void)
{
    EPwm8Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;   //OUT_MODE set to 0 : Dead-band closed
    EPwm9Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    EPwm10Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    EPwm11Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;
    EPwm8Regs.AQCSFRC.bit.CSFA = 1;     // Software force the output to 0
    EPwm8Regs.AQCSFRC.bit.CSFB = 1;
    EPwm9Regs.AQCSFRC.bit.CSFA = 1;
    EPwm9Regs.AQCSFRC.bit.CSFB = 1;
    EPwm10Regs.AQCSFRC.bit.CSFA = 1;
    EPwm10Regs.AQCSFRC.bit.CSFB = 1;
    EPwm11Regs.AQCSFRC.bit.CSFA = 1;
    EPwm11Regs.AQCSFRC.bit.CSFB = 1;
}

//软件保护
void SysFaultCheck(void)
{
    if((InvAna.f32ILRS_PK >= ILRS_OC_VALUE)|| (InvAna.f32VDS_INV_AD >= VDS_INV_OC_VALUE)||(ABS(InvAna.f32IO_AD)>= IO_OC_VALUE)|| (InvAna.f32VDS_EV_AD  >= VDS_EV_OC_VALUE) )
    {
        WptPrimaryFullBridgeShotCut();                  //短路保护
    }

    //-------------------------------ILrs overcurrent protection-------------------------------
    if( InvAna.f32ILRS_PK >= ILRS_OC_VALUE )
    {
        SysSts.bit.ILRS_FLT_STS = ILRS_FLT_STS_OC;          // Update ILRS_FLT_STS
        SysSts.bit.SYS_WORK_STS = SYS_WORK_STS_FLTSTOP;     // Update SYS_WORK_STS

    }
    //-------------------------------ILs overcurrent protection-------------------------------
    if( InvAna.f32VDS_INV_AD >= VDS_INV_OC_VALUE )
    {
        SysSts.bit.VDS_INV_FLT_STS = VDS_INV_FLT_STS_OC;          // Update ILRS_FLT_STS
        SysSts.bit.SYS_WORK_STS = SYS_WORK_STS_FLTSTOP;     // Update SYS_WORK_STS
    }

    //-------------------------------Io overcurrent protection-------------------------------
        if( (InvAna.f32IO_AD >= IO_OC_VALUE) || (InvAna.f32IO_AD <= -IO_OC_VALUE) )
        {
            SysSts.bit.IO_FLT_STS = IO_FLT_STS_OC;          // Update ILRS_FLT_STS
            SysSts.bit.SYS_WORK_STS = SYS_WORK_STS_FLTSTOP;     // Update SYS_WORK_STS
        }
        if( InvAna.f32VDS_EV_AD  >= VDS_EV_OC_VALUE )
        {
            SysSts.bit. VDS_EV_FLT_STS = VDS_EV_FLT_STS_OC;          // Update ILRS_FLT_STS
            SysSts.bit.SYS_WORK_STS = SYS_WORK_STS_FLTSTOP;     // Update SYS_WORK_STS
        }
}



