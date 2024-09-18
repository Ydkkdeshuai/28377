/*
 * CommonModle.c
 *
 *  Created on: 2024Äê7ÔÂ17ÈÕ
 *      Author: Mengfanbin
 */
#include "CommonModle.h"
/*********************************************************************
    Function :  void PI_calc(PI_handle v)
    Purpose  :  PI calaculation
    Inputs   :  PI_handle v
    Outputs  :  PI_handle v
    Equation :
             pi(s) = kp(1 + ki/s)    --(z-tran)-->  Kp = kp ; Ki = ki * Ts ;
*********************************************************************/
void PI_calc(PI_handle v)
{
    /* proportional term */
    v->up = v->Ref - v->Fbk;

    /* integral term */
    if(     ((ABS(v->Out - v->Umin) < 0.0000001) && (v->up < 0))    ||
            ((ABS(v->Out - v->Umax) < 0.0000001) && (v->up > 0))        )       // to avoid the PI can't get out of saturation in some case,change the condition of calculating I  //20160424
    {
        v->ui = v->i1;
    }
    else
    {
        v->ui = (v->Ki * v->up) + v->i1;
    }
    v->i1 = v->ui;

    /* control output */
    v->v1 = (v->Kp * (v->up + v->ui));
    v->Out = MAX(MIN(v->v1 , v->Umax) , v->Umin);
}

/*********************************************************************
    Function :  void PI_calc1(PI_handle v)
    Purpose  :  PI calaculation
    Inputs   :  PI_handle v
    Outputs  :  PI_handle v
    Equation :
             pi(s) = kp + ki/s   --(z-tran)-->  Kp = kp ; Ki = ki * Ts ;
*********************************************************************/
void PI_calc1(PI_handle v)
{
    /* proportional term */
    v->up = v->Ref - v->Fbk;

    /* integral term */
    v->ui = (ABS(v->Out - v->v1) < 0.0000001) ? ((v->Ki * v->up) + v->i1) : v->i1;
    v->i1 = v->ui;

    /* control output */
    v->v1 = v->Kp * v->up + v->ui;
    v->Out = MAX(MIN(v->v1 , v->Umax) , v->Umin);
}

/*********************************************************************
    Function :  void I_calc(PI_handle v)
    Purpose  :  PI calaculation with only integral and wrap the input error and output from -180 to 180
    Inputs   :  PI_handle v
    Outputs  :  PI_handle v
    Equation :
             pi(s) = ki/s    --(z-tran)-->  Ki = ki * Ts ;
*********************************************************************/
void I_calc(PI_handle v)
{
    /* proportional term */
    v->up = v->Ref - v->Fbk;
    v->up = WRAP_N180_P180(v->up);

    /* integral term */
    v->ui = (v->Ki * v->up) + v->i1;
    v->i1 = WRAP_N180_P180(v->ui);

    /* control output */
    v->Out = v->i1;
}


