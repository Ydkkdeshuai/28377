/*
 * CommonModle.h
 *
 *  Created on: 2024Äê7ÔÂ17ÈÕ
 *      Author: Mengfanbin
 */

#ifndef USERINCLUDES_COMMONMODLE_H_
#define USERINCLUDES_COMMONMODLE_H_

#include "F28x_Project.h"

//Definition of PI struct
typedef struct {
                  void  (*calc) (void*);    // Function pointer: point to PI calculation
                  float  Ref;               // Input: reference set-point
                  float  Fbk;               // Input: feedback
                  float  Out;               // Output: controller output
                  float  Kp;                // Parameter: proportional loop gain
                  float  Ki;                // Parameter: integral gain
                  float  Umax;              // Parameter: upper saturation limit
                  float  Umin;              // Parameter: lower saturation limit
                  float  up;                // Data: proportional term
                  float  ui;                // Data: integral term
                  float  v1;                // Data: pre-saturated controller output
                  float  i1;                // Data: integrator storage: ui(k-1)
                } PI;

//Definition of point to PI struct
typedef PI* PI_handle;

//Definition of a initialized PI struct
#define PI_DEFAULTS {       \
    (void(*)(void*))PI_calc,        \
    0,              \
    0,              \
    0,              \
    0,              \
    0,              \
    0,              \
    0,              \
    0,              \
    0,              \
    0,              \
    0,              \
}


//PI calaculation function
void PI_calc(PI_handle v);      // Kp(1+Ki/s)
void PI_calc1(PI_handle v);     // Kp+Ki/s
void I_calc(PI_handle v);       // Ki/s


#define MAX(a,b)    ((a) > (b) ? (a) : (b))             // Return maximum
#define MIN(a,b)    ((a) < (b) ? (a) : (b))             // Return Minimum
#define ABS(x)  ((x)<0 ? -(x) : (x))                    // Return absolute value
#define LIMIT(x,up,low) (MIN(MAX((x),(low)),(up)))      // Limited between lower(low) and upper(up)
#define WRAP_N180_P180(x)   ( ((x)>180) ? ((x)-360) : ( ((x)<-180) ? ((x)+360) : (x) ) )    // Wrap from -180 to 180
#define WRAP(x,low,up) ( ((x)>=(up)) ? ((x)-((up)-(low))) : ( ((x)>=(low)) ? (x) : ((x)+((up)-(low))) ) )   // Wrap x between [low,high), input x should be in [ high+(high-low) , low-(high-low) )


#endif /* USERINCLUDES_COMMONMODLE_H_ */
