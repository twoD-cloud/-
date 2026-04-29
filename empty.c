/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ti_msp_dl_config.h"
#include "board.h"
#include "stdio.h"
#include "lcd_init.h"
#include "lcd.h"
#include "pic.h"
#include "tb6612.h"
#include "mid_button.h"
#include "app_key_task.h"
#include "hw_key.h"
#include "LCD_1315/driver_ssd1315.h"
#include "LCD_1315/driver_ssd1315_advance.h"
#include "LCD_UNI_DRIVER/lcd_uni.h"

# define CIRCLE_DIG 407
# define SLOW_PERCENTAGE 20.409 //电机减速比
# define ENCODER 13
volatile bool ADC_flag=false;
volatile uint16_t digital_voltage;
volatile float analog_voltage;
volatile uint16_t get_digital;//对数字信号
volatile float angle;
volatile uint16_t pulse;
bool motor_direction = false;
bool motor_flag=true;
float n_speed;//电机转速
uint8_t key1_num=0;
uint8_t key2_num=0;
uint8_t key3_num=0;
uint8_t key4_num=0;
uint32_t sys_time=0;

int main(void)
{
    SYSCFG_DL_init();

    // 枚举LCD_TYPE_SSD1315或LCD_TYPE_ST7735
    lcd_uni_set_type(LCD_TYPE_SSD1315);
    if (lcd_uni_init() != 0)
    {
        while(1);// lcd not ready
    }

    lcd_uni_clear(0);
    lcd_uni_show_string(0, 0, "ceshiabc123!", 1, 16);
    lcd_uni_fill_rect(10, 40, 118, 60, 1);

    while(1)
    {

    }


//     /* 开启中断配置 */
// //    NVIC_EnableIRQ(ADC_voltage_INST_INT_IRQN);
//     NVIC_EnableIRQ(MOTOR_STOP_INT_IRQN);
//     NVIC_EnableIRQ(QEI_0_INST_INT_IRQN);
//     NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
//     NVIC_EnableIRQ(Button_INST_INT_IRQN);

//     /* 打开定时器 */
//     DL_TimerG_startCounter(PWM_MOTOR_INST);
//     DL_TimerA_startCounter(TIMER_0_INST);
//     DL_TimerG_startCounter(QEI_0_INST);
//     DL_TimerA_startCounter(Button_INST);




//     while (1) {
//         ADC_flag = false;
// //        DL_ADC12_startConversion(ADC_voltage_INST);

//         if (motor_flag)
//         {
//           //  MOTOR_Control(1,500);
//         }
//         else {
//             MOTOR_STOP();
//         }

//         // while (!ADC_flag)
//         // {
//         //     //等待信号
//         // }
//         /*ADC采集*/
//         DL_ADC12_enableConversions(ADC_voltage_INST);
//         digital_voltage = DL_ADC12_getMemResult(ADC_voltage_INST,ADC_voltage_ADCMEM_0);
//         analog_voltage = 3.3*(double_t)digital_voltage/(double_t)4095;

//         get_digital = digital_voltage%CIRCLE_DIG;
//         angle = (float)get_digital*360/(float)CIRCLE_DIG;
//         n_speed = (float)(pulse*50)/(260);
  

//         /*显示*/
//         // LCD_ShowString(0,20,(const u8 *)"DIG_V:",BLACK,background_color,12,0);
//         // LCD_ShowIntNum(48,20,digital_voltage,4,BLACK,background_color,12);
//         // LCD_ShowString(0,40,(const u8 *)"ANA_V:",BLACK,background_color,12,0);
//         // LCD_ShowFloatNum1(48,40,analog_voltage,4,BLACK,background_color,12);
//         // LCD_ShowString(0,60,(const u8 *)"ANGLE:",BLACK,background_color,12,0);
//         // LCD_ShowFloatNum1(37, 60, angle, 5, BLACK, background_color, 12);
//         LCD_ShowIntNum(0, 0, key1_num, 3, BLACK, background_color, 12);
//         LCD_ShowIntNum(0, 20, key2_num, 3, BLACK, background_color, 12);        
//         LCD_ShowIntNum(0, 40, key3_num, 3, BLACK, background_color, 12);
//         LCD_ShowIntNum(0, 60, key4_num, 3, BLACK, background_color, 12);
//         if (motor_direction)
//         {
//             LCD_ShowString(0, 80, "right", BLACK, background_color, 12, 0);
//         }
//         else {
//             LCD_ShowString(0, 80, "left", BLACK, background_color, 12, 0);
//         }
//         LCD_ShowString(0, 100, "n:", BLACK, background_color, 12, 0);
//         LCD_ShowFloatNum1(13, 100, n_speed, 3, BLACK, background_color, 12);
        
//     }
    
}
void ADC_voltage_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC_voltage_INST)) {
        case DL_ADC12_IIDX_MEM0_RESULT_LOADED:
            ADC_flag = true;
            break;
        default:
            break;
    }    
}
void GROUP1_IRQHandler(void)//Group1的中断服务函数，全局中断
{
    switch( DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1) )
    {
        //检查是否是KEY的GPIOB端口中断，注意是INT_IIDX，不是PIN_22_IIDX
        case MOTOR_STOP_INT_IIDX:
           // motor_flag = !motor_flag;
        break;
    }
}

void QEI_0_INST_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(QEI_0_INST)) {
        case DL_TIMER_IIDX_DIR_CHANGE:
            if (DL_TimerG_getQEIDirection(QEI_0_INST) == DL_TIMER_QEI_DIR_DOWN)
                motor_direction = true;
            else
                motor_direction = false;
        default:
            break;
    }
}
void TIMER_0_INST_IRQHandler(void)
{
    switch(DL_TimerA_getPendingInterrupt(TIMER_0_INST)){
        case DL_TIMER_IIDX_LOAD:
            // pulse = DL_TimerG_getTimerCount(QEI_0_INST);
            // DL_TimerG_setTimerCount(QEI_0_INST,0);//得到脉冲数之后清零
            motor_flag = !motor_flag;


        default:
            break;
    }
}
void Button_INST_IRQHandler(void)
{
    switch (DL_TimerA_getPendingInterrupt(Button_INST)) {
        case DL_TIMER_IIDX_LOAD:
            flex_button_scan();
        
        default:
            break;
    
    }
}