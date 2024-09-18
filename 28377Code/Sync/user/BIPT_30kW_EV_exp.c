//
// Included Files
//
#include "BIPT_30kW_EV_exp.h"
#include "F28x_Project.h"
//
// Function Prototypes
//
__interrupt void cpu_timer0_isr(void);

//
// System variable
//

void main(void)
{
    InitSysCtrl();
    InitGpio();

    InitEPwmGpio();
//    RELAY_GPIOInit();//�̵���GPIO

    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.TIMER0_INT = &cpu_timer0_isr;
    EDIS;    // This is needed to disable write to EALLOW protected registers



//  ��ʼ��ADC
    ConfigureADC();
   //����ADC����ͨ��
    SetupADC();
     //��ʼ��ADCģ����
    ADCanalog_init();
     //AD������׼ֵ��ȡ
    ADCBaseGet();
    //��ʼEPWMģ��
    EpwmSet();


    InitCpuTimers();   // For this example, only initialize the Cpu Timers
    ConfigCpuTimer(&CpuTimer0, 200, 50);
    CpuTimer0Regs.TCR.all = 0x4000;

    IER |= M_INT1;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

//
// Step 6. IDLE loop. Just sit and loop forever (optional):
//
    while(1)
    {

    }
}

//
// cpu_timer0_isr - CPU Timer0 ISR with interrupt counter
//
__interrupt void cpu_timer0_isr(void)
{


   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
   GPIO_WritePin(34, 0);//GPIO 0 д1
   INVADCRead();//����ʱ��Լ5us
   GPIO_WritePin(34, 1);//GPIO 0 д1

}

//
// End of file
//
