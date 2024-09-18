/*
 * Led.c
 *
 *  Created on: 2024年7月22日
 *      Author: Mengfanbin
 */

#include "Sys_GPIO.h"
#include "ADCSample.h"

void LED_GPIOInit(void)
{
    /*
     * LED0-------->GPIO34
     * LED1-------->GPIO33
     * LED2-------->GPIO41
     * LED3-------->GPIO48
     * LED4-------->GPIO50

     */
    /* configurating the mode of GPIO as the output;setting the initial value is 0 */

    GPIO_SetupPinMux(34, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(34, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(33, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(33, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(41, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(41, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(48, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(48, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(50, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(50, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式


    LED0_OFF;                               // Default state : LED off
    LED1_OFF;                               // Default state : LED off
    LED2_OFF;                               // Default state : LED off
    LED3_OFF;                               // Default state : LED off
    LED4_OFF;                               // Default state : LED off

}

void HardProtection_GPIOInit(void)
{
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
    GPIO_SetupPinMux(99, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(99, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(26, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(26, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(27, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(27, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(29, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(29, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(25, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(25, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(93, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(93, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(30, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(30, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(24, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(24, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(94, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(94, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(88, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(88, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(90, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(90, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(87, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(87, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(92, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(92, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(91, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(91, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(85, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(85, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(83, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(83, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(86, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(86, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(99, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(99, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式
}

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
void RELAY_GPIOInit(void)
{
    GPIO_SetupPinMux(74, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(74, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(70, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(70, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(76, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(76, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(80, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(80, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(78, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(78, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(78, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(78, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(82, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(82, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(75, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(75, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(73, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(78, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(77, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(77, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    RELAY_H_DRIVER_OFF;
    RELAY_L_DRIVER_OFF;
    SOFT_RELAY_DRIVER_OFF;

    RELAY_H_DRIVER_R1_OFF;
    RELAY_L_DRIVER_R1_OFF;
    SOFT_RELAY_DRIVER_R1_OFF;

    RELAY_H_DRIVER_R2_OFF;
    RELAY_L_DRIVER_R2_OFF;
    SOFT_RELAY_DRIVER_R2_OFF;
}

void RELAY_ON(void)
{
    RELAY_L_DRIVER_ON;
    SOFT_RELAY_DRIVER_ON;
//检测电压是否达到阈值
    if(InvAna.f32VDS_INV_AD>=RELAY_H_ON_Vol)
    {
        RELAY_H_DRIVER_ON;
    }
    if(InvAna.f32VDS_EV_AD-InvAna.f32VDS_INV_AD<=10)
    {
        SOFT_RELAY_DRIVER_OFF;
    }
}

void RELAY_R1_ON(void)
{
    RELAY_L_DRIVER_R1_ON;
    SOFT_RELAY_DRIVER_R1_ON;
    //检测电压是否达到阈值
    if(InvAna.f32VDS_INV_AD>=RELAY_R1_H_ON_Vol)
    {
        RELAY_H_DRIVER_R1_ON;
    }
    if(InvAna.f32VDS_EV_AD-InvAna.f32VDS_INV_AD<=10)
    {
        SOFT_RELAY_DRIVER_R1_OFF;
    }
}

void RELAY_R2_ON(void)
{
    RELAY_L_DRIVER_R2_ON;
    SOFT_RELAY_DRIVER_R2_ON;
    //检测电压是否达到阈值
    if(InvAna.f32VDS_INV_AD>=RELAY_R2_H_ON_Vol)
    {
        RELAY_H_DRIVER_R2_ON;
    }
    if(InvAna.f32VDS_EV_AD-InvAna.f32VDS_INV_AD<=10)
    {
        SOFT_RELAY_DRIVER_R2_OFF;
    }
}

void RELAY_OFF(void)
{
    RELAY_H_DRIVER_OFF;
    RELAY_L_DRIVER_OFF;
}

void RELAY_R1_OFF(void)
{
    RELAY_H_DRIVER_R1_OFF;
    RELAY_L_DRIVER_R1_OFF;
}

void RELAY_R2_OFF(void)
{
    RELAY_H_DRIVER_R2_OFF;
    RELAY_L_DRIVER_R2_OFF;
}


void DODI_GPIOInit(void)
{
    /*
     * DI-1-------->GPIO67
     * DI-2-------->GPIO69
     * DO-1-------->GPIO47
     * DO-2-------->GPIO68
     */
    GPIO_SetupPinMux(47, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(47, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(68, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(68, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(67, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(67, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(69, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(69, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    DO_1_OFF;
    DO_2_OFF;
}

void RS485_EN_GPIOInit(void)
{
    /*
     * 485R_EN-------->GPIO46
     */
    GPIO_SetupPinMux(46, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(46, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式
    RX485_ON;//默认接收
}

void WIFI_EN_GPIOInit(void)
{
    /*
     * WIFI_POWERCON-------->GPIO45
     * WIFI_RESET-------->GPIO66
     * WIFI_NLINK-------->GPIO133
     * WIFI_NRELOAD-------->GPIO44
     */
    GPIO_SetupPinMux(45, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(45, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(44, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(44, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(133, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(133, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(66, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(66, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    WIFI_POWEREN;
    WIFI_NReload;
    WIFI_NReset;
}

void INV_DRV_FAULT_RESET_GPIOInit(void)
{
    /*
     * RESET_3V3-------->GPIO79
     * RESET_R1_3V3-------->GPIO71
     * RESET_R2_3V3-------->GPIO81
     */
    GPIO_SetupPinMux(79, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(79, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(71, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(71, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(81, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(81, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    INV_DRV_FAULT_RESET_OFF;
    INV_DRV_FAULT_RESET_R1_OFF;
    INV_DRV_FAULT_RESET_R2_OFF;
}
void SEL_AD_GPIOInit(void)
{
    /*
     * SEL_AD1-------->GPIO28
     * SEL_AD2-------->GPIO32
     * SEL_AD3-------->GPIO31
     */
    GPIO_SetupPinMux(28, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(28, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(32, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(32, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    GPIO_SetupPinMux(31, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(31, GPIO_OUTPUT, GPIO_PUSHPULL);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

}


void SYS_GPIOInit(void)
{
    LED_GPIOInit();
    HardProtection_GPIOInit();
    RELAY_GPIOInit();
    DODI_GPIOInit();
    RS485_EN_GPIOInit();
    WIFI_EN_GPIOInit();
    INV_DRV_FAULT_RESET_GPIOInit();
    SEL_AD_GPIOInit();



}
