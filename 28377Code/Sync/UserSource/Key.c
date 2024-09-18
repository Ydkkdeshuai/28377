/*
 * Key.c
 *
 *  Created on: 2024年7月22日
 *      Author: Mengfanbin
 */
#include "Key.h"
Uint32 KeyDownCount0;       // S0 Key down counter
Uint32 KeyDownCount1;       // S1 Key down counter
Uint32 KeyDownCount2;       // S2 Key down counter
Uint32 KeyDownCount3;       // S3 Key down counter

/**************************************************************************************************************
    Function     : void KeyBoardGpioInit(void)
    Introduction : Initialize the GPIO used for keyboard
    Inputs       : none
    Outputs      : none
    Comments     : none

***************************************************************************************************************/
void KeyBoardGpioInit(void)
{
    /*****************************************************
    *           GPIO49--S0,  keydown-->low level
    *           GPIO52--S1,  keydown-->low level
    *           GPIO51--S2,  keydown-->low level
    *           GPIO53--S3,  keydown-->low level
    *****************************************************/
    EALLOW;

    /********GPIO49--S0, GPIO input, no pill-up**************/
    GPIO_SetupPinMux(49, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(49, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    /********GPIO52--S1, GPIO input, no pill-up**************/
    GPIO_SetupPinMux(52, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(52, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式


    /********GPIO51--S2, GPIO input, no pill-up**************/
    GPIO_SetupPinMux(51, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(51, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式


    /********GPIO53--S3, GPIO input, no pill-up**************/
    GPIO_SetupPinMux(53, GPIO_MUX_CPU1, 0);                                  //第一位是GPIO，第二位是CPU，第三位是设置GPIO的功能
    GPIO_SetupPinOptions(53, GPIO_INPUT, GPIO_QUAL6);    //第一位是GPIO，第二位是 GPIO输入输出，第三位是设置GPIO的输入输出模式

    EDIS;
}

/**************************************************************************************************************
    Function     : void KeyBoardInit(void)
    Introduction : Initialize keyboard
    Inputs       : none
    Outputs      : none
    Comments     : none

***************************************************************************************************************/
void KeyBoardInit(void)
{
    KeyBoardGpioInit();     // Initialize the GPIO used for keyboard

    KeyDownCount0 = 0;      // Clear keydown counter
    KeyDownCount1 = 0;      // Clear keydown counter
    KeyDownCount2 = 0;      // Clear keydown counter
    KeyDownCount3 = 0;      // Clear keydown counter
}

/**************************************************************************************************************
    Function     : Uint32 S0KeyDown(void)
    Introduction : Scan S0 to see if it's down
    Inputs       : none
    Outputs      : 0: no keydown
                   1: keydown
    Comments     : none

***************************************************************************************************************/
Uint32 S0KeyDown(void)
{
    if(S0_KEYDOWN)                                          // S0 keydown
    {
        KeyDownCount0 ++;

        if(KeyDownCount0 >= KEY_SEC(3000))                      // Count up limit to 3000s
        {
            KeyDownCount0 = KEY_SEC(3000);
        }

        if(KeyDownCount0 == KEY_SEC(0.02))      // If keydown continue 20ms, return a keydown signal
        {
            return 1;   // Return 1, keydown
        }
        else if((KeyDownCount0 >= KEY_SEC(0.5)) && (KeyDownCount0 < KEY_SEC(3)))    // If keydown continue 0.5s~3s, return keydown signals every 0.1s
        {
            if((KeyDownCount0 % KEY_SEC(0.1)) == 0)
            {
                return 1;   // Return 1, keydown
            }
            else
            {
                return 0;   // Return 0, no keydown
            }
        }
        else if(KeyDownCount0 >= KEY_SEC(3))    // If keydown continue more than 3s, return keydown signals every 0.05s
        {
            if((KeyDownCount0 % KEY_SEC(0.05)) == 0)
            {
                return 1;   // Return 1, keydown
            }
            else
            {
                return 0;   // Return 0, no keydown
            }
        }
        else                                    // No keydown signals return
        {
            return 0;   // Return 0, no keydown
        }
    }
    else                                                    // S0 keyup
    {
        KeyDownCount0 = 0;  // Clear counter

        return 0;   // Return 0, no keydown
    }

}

/**************************************************************************************************************
    Function     : Uint32 S1KeyDown(void)
    Introduction : Scan S1 to see if it's down
    Inputs       : none
    Outputs      : 0: no keydown
                   1: keydown
    Comments     : none

***************************************************************************************************************/
Uint32 S1KeyDown(void)
{
    if(S1_KEYDOWN)                                          // S1 keydown
    {
        KeyDownCount1 ++;

        if(KeyDownCount1 >= KEY_SEC(3000))                      // Count up limit to 3000s
        {
            KeyDownCount1 = KEY_SEC(3000);
        }

        if(KeyDownCount1 == KEY_SEC(0.02))      // If keydown continue 20ms, return a keydown signal
        {
            return 1;   // Return 1, keydown
        }
        else if((KeyDownCount1 >= KEY_SEC(0.5)) && (KeyDownCount1 < KEY_SEC(3)))    // If keydown continue 0.5s~3s, return keydown signals every 0.1s
        {
            if((KeyDownCount1 % KEY_SEC(0.1)) == 0)
            {
                return 1;   // Return 1, keydown
            }
            else
            {
                return 0;   // Return 0, no keydown
            }
        }
        else if(KeyDownCount1 >= KEY_SEC(3))    // If keydown continue more than 3s, return keydown signals every 0.05s
        {
            if((KeyDownCount1 % KEY_SEC(0.05)) == 0)
            {
                return 1;   // Return 1, keydown
            }
            else
            {
                return 0;   // Return 0, no keydown
            }
        }
        else                                    // No keydown signals return
        {
            return 0;   // Return 0, no keydown
        }
    }
    else                                                    // S1 keyup
    {
        KeyDownCount1 = 0;  // Clear counter

        return 0;   // Return 0, no keydown
    }

}

/**************************************************************************************************************
    Function     : Uint32 S2KeyDown(void)
    Introduction : Scan S2 to see if it's down
    Inputs       : none
    Outputs      : 0: no keydown
                   1: keydown
    Comments     : none

***************************************************************************************************************/
Uint32 S2KeyDown(void)
{
    if(S2_KEYDOWN)                                          // S2 keydown
    {
        KeyDownCount2 ++;

        if(KeyDownCount2 >= KEY_SEC(3000))                      // Count up limit to 3000s
        {
            KeyDownCount2 = KEY_SEC(3000);
        }

        if(KeyDownCount2 == KEY_SEC(0.02))      // If keydown continue 20ms, return a keydown signal
        {
            return 1;   // Return 1, keydown
        }
        else if((KeyDownCount2 >= KEY_SEC(0.5)) && (KeyDownCount2 < KEY_SEC(3)))    // If keydown continue 0.5s~3s, return keydown signals every 0.1s
        {
            if((KeyDownCount2 % KEY_SEC(0.1)) == 0)
            {
                return 1;   // Return 1, keydown
            }
            else
            {
                return 0;   // Return 0, no keydown
            }
        }
        else if(KeyDownCount2 >= KEY_SEC(3))    // If keydown continue more than 3s, return keydown signals every 0.05s
        {
            if((KeyDownCount2 % KEY_SEC(0.05)) == 0)
            {
                return 1;   // Return 1, keydown
            }
            else
            {
                return 0;   // Return 0, no keydown
            }
        }
        else                                    // No keydown signals return
        {
            return 0;   // Return 0, no keydown
        }
    }
    else                                                    // S2 keyup
    {
        KeyDownCount2 = 0;  // Clear counter

        return 0;   // Return 0, no keydown
    }

}

/**************************************************************************************************************
    Function     : Uint32 S3KeyDown(void)
    Introduction : Scan S3 to see if it's down
    Inputs       : none
    Outputs      : 0: no keydown
                   1: keydown
    Comments     : none

***************************************************************************************************************/
Uint32 S3KeyDown(void)
{
    if(S3_KEYDOWN)                                          // S3 keydown
    {
        KeyDownCount3 ++;

        if(KeyDownCount3 >= KEY_SEC(3000))                      // Count up limit to 3000s
        {
            KeyDownCount3 = KEY_SEC(3000);
        }

        if(KeyDownCount3 == KEY_SEC(0.02))      // If keydown continue 20ms, return a keydown signal
        {
            return 1;   // Return 1, keydown
        }
        else if((KeyDownCount3 >= KEY_SEC(0.5)) && (KeyDownCount3 < KEY_SEC(3)))    // If keydown continue 0.5s~3s, return keydown signals every 0.1s
        {
            if((KeyDownCount3 % KEY_SEC(0.1)) == 0)
            {
                return 1;   // Return 1, keydown
            }
            else
            {
                return 0;   // Return 0, no keydown
            }
        }
        else if(KeyDownCount3 >= KEY_SEC(3))    // If keydown continue more than 3s, return keydown signals every 0.05s
        {
            if((KeyDownCount3 % KEY_SEC(0.05)) == 0)
            {
                return 1;   // Return 1, keydown
            }
            else
            {
                return 0;   // Return 0, no keydown
            }
        }
        else                                    // No keydown signals return
        {
            return 0;   // Return 0, no keydown
        }
    }
    else                                                    // S3 keyup
    {
        KeyDownCount3 = 0;  // Clear counter

        return 0;   // Return 0, no keydown
    }

}


