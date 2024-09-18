/*
 * SysStsFlt.h
 *
 *  Created on: 2024年7月22日
 *      Author: Mengfanbin
 */

#ifndef USERINCLUDES_SYSSTSFLT_H_
#define USERINCLUDES_SYSSTSFLT_H_


#include "F28x_Project.h"
#include "ADCSample.h"
#include "CommonModle.h"
extern INV_ANA_REGS InvAna;
#define ILRS_OC_VALUE                   85.0
#define IO_OC_VALUE                       50
#define VDS_INV_OC_VALUE           800
#define VDS_EV_OC_VALUE             800

//=====================System state defination================================================
struct SYS_STS_BITS
{
    Uint16  SYS_WORK_STS:3;                 // system state:    SYS_WORK_STS_IDLE       System is idle  \
                                                                SYS_WORK_STS_RUNNING    System is running   \
                                                                SYS_WORK_STS_FLTSTOP    System is fault and stoped
    Uint16  WIFI_STS:2;                     // Wifi State:      WIFI_STS_CONNECTED      Wifi connected  \
                                                                WIFI_STS_DISCONNECTED   Wifi disconnected
    Uint16 ILRS_FLT_STS:1;                  // ILrs overcurrent
    Uint16 VDS_INV_FLT_STS:1;                   // ILs overcurrent
    Uint16 IO_FLT_STS:1;                // Io overcurrent
    Uint16 VDS_EV_FLT_STS:1;           // VDS overcurrent
    Uint16 GA_STS:3;                        // GA system state:
    Uint16 SYS_Direction_STS:1;
    Uint16 rsvd:3;                          //
};

#define SYS_WORK_STS_IDLE           0x00    // System is in idle mode
#define SYS_WORK_STS_SOFT_START     0x01    // System is in soft start mode
#define SYS_WORK_STS_CHARGING       0x02    // System is in charging mode
#define SYS_WORK_STS_FLTSTOP        0x03    // System is fault and in stop mode

#define SYS_Direction_STS_FORWARD_DIRECTION 0x00//系统正向工作
#define SYS_Direction_STS_BACKWARD_DIRECTION 0x01//系统反向工作

#define WIFI_STS_CONNECTED          0x00    // Wifi connected
#define WIFI_STS_DISCONNECTED       0x01    // Wifi disconnected

#define ILRS_FLT_STS_NORMAL         0x00    // No overcurrent
#define ILRS_FLT_STS_OC             0x01    // Overcurrent

#define VDS_INV_FLT_STS_NORMAL          0x00    // No overcurrent
#define VDS_INV_FLT_STS_OC              0x01    // Overcurrent

#define IO_FLT_STS_NORMAL          0x00    // No overcurrent
#define IO_FLT_STS_OC              0x01    // Overcurrent

#define VDS_EV_FLT_STS_NORMAL          0x00    // No overcurrent
#define VDS_EV_FLT_STS_OC              0x01    // Overcurrent

#define GA_STS_IDLE                 0x00    // GA is in idle mode
#define GA_STS_CHARGING             0x01    // GA is in charging mode
#define GA_STS_FLTSTOP              0x02    // GA is fault and in stop mode

union SYS_STS
{
    Uint16  all;
    struct  SYS_STS_BITS  bit;
};

extern union SYS_STS SysSts;                // System state

// Initialize system fault states
void SysStsFltInit(void);

// Enable PWM output of WPT primary full bridge
void WptPrimaryFullBridgePWMEnable(void);

// Disable PWM output of WPT primary full bridge
void WptPrimaryFullBridgePWMDisable(void);
void WptPrimaryFullBridgeShotCut(void);
// Enable PWM output of WPT PQ modulation based synchronization
void WptPQSyncPWMEnable(void);

// Disable PWM output of WPT PQ modulation based synchronization
void WptPQSyncPWMDisable(void);

// System fault check and protection
void SysFaultCheck(void);


#endif /* USERINCLUDES_SYSSTSFLT_H_ */
