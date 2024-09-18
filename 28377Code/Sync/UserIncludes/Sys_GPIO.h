/*
 * Sys_GPIO.h
 *
 *  Created on: 2024年9月6日
 *      Author: Mengfanbin
 */

#ifndef USERINCLUDES_SYS_GPIO_H_
#define USERINCLUDES_SYS_GPIO_H_

#include "F28x_Project.h"

//====================== LED ================================================
    /*
     * LED0-------->GPIO34
     * LED1-------->GPIO33
     * LED2-------->GPIO41
     * LED3-------->GPIO48
     * LED4-------->GPIO50
     */

#define LED0_OFF  GPIO_WritePin(34,0)
#define LED1_OFF  GPIO_WritePin(33,0)
#define LED2_OFF  GPIO_WritePin(41,0)
#define LED3_OFF  GPIO_WritePin(48,0)
#define LED4_OFF  GPIO_WritePin(50,0)

#define LED0_ON  GPIO_WritePin(34,1)
#define LED1_ON  GPIO_WritePin(33,1)
#define LED2_ON  GPIO_WritePin(41,1)
#define LED3_ON  GPIO_WritePin(48,1)
#define LED4_ON  GPIO_WritePin(50,1)

#define LED0_TOGGLE   GPIO_WritePin(34,2)
#define LED1_TOGGLE   GPIO_WritePin(33,2)
#define LED2_TOGGLE   GPIO_WritePin(41,2)
#define LED3_TOGGLE   GPIO_WritePin(48,2)
#define LED4_TOGGLE   GPIO_WritePin(50,2)

//====================== HARDPROTECTION ================================================
    /*
     * ILRS_OCP----------------->GPIO99
     * ILRS_OCP_R1------------->GPIO26
     * ILRS_OCP_R2------------->GPIO27
     *
     * VDS_EV_OCP------------->GPIO29
     * VDS_EV_OCP_R1--------->GPIO25
     * VDS_EV_OCP_R2--------->GPIO93
     *
     * VDS_INV_OCP------------>GPIO30
     * VDS_INV_OCP_R1-------->GPIO24
     * VDS_INV_OCP_R2-------->GPIO94
     *
     * MOS_OTP----------------->GPIO88
     * MOS_OTP_R1------------->GPIO90
     * MOS_OTP_R2------------->GPIO87
     *
     * IO_OTP------------------->GPIO92
     * IO_OTP_R1--------------->GPIO91
     * IO_OTP_R2--------------->GPIO89
     *
     * INV_DRV_FAULT--------->GPIO83
     * INV_DRV_FAULT_R1----->GPIO86
     * INV_DRV_FAULT_R2----->GPIO85
     *
     */
#define ILRS_OCP  GPIO_ReadPin(99)==0
#define ILRS_OCP_R1  GPIO_ReadPin(26)==0
#define ILRS_OCP_R2  GPIO_ReadPin(27)==0

#define VDS_EV_OCP  GPIO_ReadPin(29)==0
#define VDS_EV_OCP_R1  GPIO_ReadPin(25)==0
#define VDS_EV_OCP_R2  GPIO_ReadPin(93)==0

#define VDS_INV_OCP  GPIO_ReadPin(30)==0
#define VDS_INV_OCP_R1  GPIO_ReadPin(24)==0
#define VDS_INV_OCP_R2  GPIO_ReadPin(94)==0

#define MOS_OTP  GPIO_ReadPin(88)==0
#define MOS_OTP_R1  GPIO_ReadPin(90)==0
#define MOS_OTP_R2  GPIO_ReadPin(87)==0

#define IO_OTP  GPIO_ReadPin(92)==0
#define IO_OTP_R1  GPIO_ReadPin(94)==0
#define IO_OTP_R2  GPIO_ReadPin(89)==0

#define INV_DRV_FAULT  GPIO_ReadPin(83)==0
#define INV_DRV_FAULT_R1  GPIO_ReadPin(86)==0
#define INV_DRV_FAULT_R2  GPIO_ReadPin(85)==0

//====================== RELAY ================================================
#define RELAY_H_ON_Vol 600
#define RELAY_R1_H_ON_Vol 600
#define RELAY_R2_H_ON_Vol 600

    /*
     * RELAY_H_DRIVER-------->GPIO74
     * RELAY_L_DRIVER-------->GPIO70
     * SOFT_RELAY_DRIVER-------->GPIO76
     *
     * RELAY_H_DRIVER_R1-------->GPIO80
     * RELAY_L_DRIVER_R1-------->GPIO78
     * SOFT_RELAY_DRIVER_R1-------->GPIO82
     *
     * RELAY_H_DRIVER_R2-------->GPIO75
     * RELAY_L_DRIVER_R2-------->GPIO73
     * SOFT_RELAY_DRIVER_R2-------->GPIO77
     */

#define RELAY_H_DRIVER_OFF                  GPIO_WritePin(74,0)
#define RELAY_L_DRIVER_OFF                   GPIO_WritePin(70,0)
#define SOFT_RELAY_DRIVER_OFF            GPIO_WritePin(76,0)

#define RELAY_H_DRIVER_R1_OFF            GPIO_WritePin(80,0)
#define RELAY_L_DRIVER_R1_OFF             GPIO_WritePin(78,0)
#define SOFT_RELAY_DRIVER_R1_OFF      GPIO_WritePin(82,0)

#define RELAY_H_DRIVER_R2_OFF            GPIO_WritePin(75,0)
#define RELAY_L_DRIVER_R2_OFF             GPIO_WritePin(73,0)
#define SOFT_RELAY_DRIVER_R2_OFF      GPIO_WritePin(77,0)


#define RELAY_H_DRIVER_ON                   GPIO_WritePin(74,1)
#define RELAY_L_DRIVER_ON                    GPIO_WritePin(70,1)
#define SOFT_RELAY_DRIVER_ON             GPIO_WritePin(76,1)

#define RELAY_H_DRIVER_R1_ON             GPIO_WritePin(80,1)
#define RELAY_L_DRIVER_R1_ON              GPIO_WritePin(78,1)
#define SOFT_RELAY_DRIVER_R1_ON       GPIO_WritePin(82,1)

#define RELAY_H_DRIVER_R2_ON             GPIO_WritePin(75,1)
#define RELAY_L_DRIVER_R2_ON              GPIO_WritePin(73,1)
#define SOFT_RELAY_DRIVER_R2_ON       GPIO_WritePin(77,1)


//====================== 干节点 ================================================

#define DO_1_ON                   GPIO_WritePin(47,1)
#define DO_2_ON                   GPIO_WritePin(68,1)

#define DO_1_OFF                   GPIO_WritePin(47,0)
#define DO_2_OFF                   GPIO_WritePin(68,0)

#define DI_1_ON                   GPIO_ReadPin(67)==1
#define DI_2_ON                   GPIO_ReadPin(67)==1

#define DI_1_OFF                   GPIO_ReadPin(69)==0
#define DI_2_OFF                   GPIO_ReadPin(69)==0

#define RX485_ON                   GPIO_WritePin(46,1)
#define TX485_ON                   GPIO_WritePin(46,0)

#define WIFI_POWEREN          GPIO_WritePin(45,0)
#define WIFI_POWEROFF        GPIO_WritePin(45,1)
#define WIFI_NLINK             GPIO_ReadPin(133)==1//WIFI_NLINK
#define WIFI_LINK                GPIO_ReadPin(133)==0//WIFI_LINK
#define WIFI_NReload         GPIO_WritePin(44,1)//WIFI不恢复出厂
#define WIFI_Reload            GPIO_WritePin(44,0)//WIFI恢复出厂

#define WIFI_Reset            GPIO_WritePin(66,0)//WIFI复位
#define WIFI_NReset            GPIO_WritePin(66,1)//WIFI不复位

#define INV_DRV_FAULT_RESET_ON         GPIO_WritePin(79,1)
#define INV_DRV_FAULT_RESET_R1_ON      GPIO_WritePin(71,1)
#define INV_DRV_FAULT_RESET_R2_ON      GPIO_WritePin(81,1)
#define INV_DRV_FAULT_RESET_OFF         GPIO_WritePin(79,0)
#define INV_DRV_FAULT_RESET_R1_OFF      GPIO_WritePin(71,0)
#define INV_DRV_FAULT_RESET_R2_OFF      GPIO_WritePin(81,0)


#define INV_DRV_FAULT_RESET_R1_ON      GPIO_WritePin(71,1)
#define INV_DRV_FAULT_RESET_R2_ON      GPIO_WritePin(81,1)
#define INV_DRV_FAULT_RESET_OFF         GPIO_WritePin(79,0)
#define INV_DRV_FAULT_RESET_R1_OFF      GPIO_WritePin(71,0)
#define INV_DRV_FAULT_RESET_R2_OFF      GPIO_WritePin(81,0)

    /*
     * SEL_AD1-------->GPIO28
     * SEL_AD2-------->GPIO32
     * SEL_AD3-------->GPIO31
     */
#define SEL000 do{\
    GPIO_WritePin(28,0);\
    GPIO_WritePin(32,0);\
    GPIO_WritePin(31,0);\
}while(0) //通道0

#define SEL001 do{\
    GPIO_WritePin(28,1);\
    GPIO_WritePin(32,0);\
    GPIO_WritePin(31,0);\
}while(0)  //通道1

#define SEL010 do{\
    GPIO_WritePin(28,0);\
    GPIO_WritePin(32,1);\
    GPIO_WritePin(31,0);\
}while(0)  //通道2

#define SEL011 do{\
    GPIO_WritePin(28,1);\
    GPIO_WritePin(32,1);\
    GPIO_WritePin(31,0);\
}while(0)  //通道3

#define SEL100 do{\
    GPIO_WritePin(28,0);\
    GPIO_WritePin(32,0);\
    GPIO_WritePin(31,1);\
}while(0)  //通道4

#define SEL101 do{\
    GPIO_WritePin(28,1);\
    GPIO_WritePin(32,0);\
    GPIO_WritePin(31,1);\
}while(0)  //通道5

#define SEL110 do{\
    GPIO_WritePin(28,0);\
    GPIO_WritePin(32,1);\
    GPIO_WritePin(31,1);\
}while(0)  //通道6

#define SEL111 do{\
    GPIO_WritePin(28,1);\
    GPIO_WritePin(32,1);\
    GPIO_WritePin(31,1);\
}while(0)  //通道7



/**************************************************************************************************************/
/***********************************************FUNCTIONS******************************************************/
/**************************************************************************************************************/

// Initialize the GPIO used for LED
void LED_GPIOInit(void);
void HardProtection_GPIOInit(void);

void RELAY_GPIOInit(void);
void RELAY_ON(void);
void RELAY_R1_ON(void);
void RELAY_R2_ON(void);
void RELAY_OFF(void);
void RELAY_R1_OFF(void);
void RELAY_R2_OFF(void);

void DODI_GPIOInit(void);
void RS485_EN_GPIOInit(void);
void WIFI_EN_GPIOInit(void);

void INV_DRV_FAULT_RESET_GPIOInit(void);
void SEL_AD_GPIOInit(void);
void SYS_GPIOInit(void);
#endif /* USERINCLUDES_SYS_GPIO_H_ */
