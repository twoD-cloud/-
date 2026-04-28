#include "tb6612.h"
#include "board.h"

#define CCR 1000 
/*MOTOR_STOP:使得电机停止运动*/

void MOTOR_STOP(void)
{
    DL_GPIO_setPins(MOTOR_PORT,MOTOR_AIN_1_PIN);
    DL_GPIO_setPins(MOTOR_PORT, MOTOR_AIN_2_PIN);
}

/*MOTOR_Control:控制电机转动方向以及PWM占空比*/
void MOTOR_Control(bool dir, uint32_t speed)
{
    if (speed>CCR-1)
    {
        lc_printf("\nspeed >CCR!error!\r\n");
        return;
    }
    if (dir)//正转
    {
        DL_GPIO_clearPins(MOTOR_PORT, MOTOR_AIN_2_PIN);
        DL_GPIO_setPins(MOTOR_PORT,MOTOR_AIN_1_PIN);
    }
    else//反转
    {
        DL_GPIO_clearPins(MOTOR_PORT, MOTOR_AIN_1_PIN);
        DL_GPIO_setPins(MOTOR_PORT, MOTOR_AIN_2_PIN);
    }
    DL_TimerG_setCaptureCompareValue(PWM_MOTOR_INST, speed, GPIO_PWM_MOTOR_C0_IDX);
}