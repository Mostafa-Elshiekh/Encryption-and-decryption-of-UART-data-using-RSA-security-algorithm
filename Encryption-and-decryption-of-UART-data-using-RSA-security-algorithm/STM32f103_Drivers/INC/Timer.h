/*
 * Timer.h
 *
 *  Created on: Oct 10, 2021
 *      Author: Mostafa Elshiekh
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "STM32_F103C6.h"
#include "STM32F103C6_GPIO_DRIVERS.h"

#define RCC_APB1ENR                           *( volatile uint32_t *)(RCC_BASE+0x1C)
#define RCC_APB2ENR                           *( volatile uint32_t *)(RCC_BASE+0x18)
#define PWM_TIM_0                            0
#define PWM_TIM_10                           0xFFFF/10
#define PWM_TIM_20                           0xFFFF/5
#define PWM_TIM_25                           0xFFFF/4
#define PWM_TIM_30                           0xFFFF/3.33
#define PWM_TIM_40                           0xFFFF/2.5
#define PWM_TIM_50                           0xFFFF/2
#define PWM_TIM_60                           0xFFFF/1.666
#define PWM_TIM_75                           0xFFFF/1.333
#define PWM_TIM_80                           0xFFFF/1.25
#define PWM_TIM_90                           0xFFFF/1.111
#define PWM_TIM_100                          0xFFFF/1

//TIMER1
#define TIM1_BASE                              0x40012C00
#define TIM1_CNT                              *( volatile uint32_t *)(TIM1_BASE+0x24)
#define TIM1_CR1                              *( volatile uint32_t *)(TIM1_BASE+0x00)
#define TIM1_PSC                              *( volatile uint32_t *)(TIM1_BASE+0x28)
#define TIM1_SR                               *( volatile uint32_t *)(TIM1_BASE+0x10)
#define TIM1_DIER                             *( volatile uint32_t *)(TIM1_BASE+0x0c)
#define TIM1_ARR                              *( volatile uint32_t *)(TIM1_BASE+0x2c)
#define TIM1_CCR1                             *( volatile uint32_t *)(TIM1_BASE+0x34)
#define TIM1_CCMR1                            *( volatile uint32_t *)(TIM1_BASE+0x18)
#define TIM1_CCER                             *( volatile uint32_t *)(TIM1_BASE+0x20)
#define TIM1_BDTR                             *( volatile uint32_t *)(TIM1_BASE+0x44)
#define TIM1_CCR4                             *( volatile uint32_t *)(TIM1_BASE+0x40)
#define TIM1_CCMR2                            *( volatile uint32_t *)(TIM1_BASE+0x1c)




//TIMER2
#define TIM2_timer_Base                        0x40000000
#define TIM2_CNT                              *( volatile uint32_t *)(TIM2_timer_Base+0x24)
#define TIM2_CR1                              *( volatile uint32_t *)(TIM2_timer_Base+0x00)
#define TIM2_PSC                              *( volatile uint32_t *)(TIM2_timer_Base+0x28)
#define TIM2_SR                               *( volatile uint32_t *)(TIM2_timer_Base+0x10)
#define TIM2_DIER                             *( volatile uint32_t *)(TIM2_timer_Base+0x0c)
#define TIM2_ARR                              *( volatile uint32_t *)(TIM2_timer_Base+0x2c)

//TIMER3
#define TIM3_BASE                              0x40000400
#define TIM3_CNT                              *( volatile uint32_t *)(TIM3_BASE+0x24)
#define TIM3_CR1                              *( volatile uint32_t *)(TIM3_BASE+0x00)
#define TIM3_PSC                              *( volatile uint32_t *)(TIM3_BASE+0x28)
#define TIM3_SR                               *( volatile uint32_t *)(TIM3_BASE+0x10)
#define TIM3_DIER                             *( volatile uint32_t *)(TIM3_BASE+0x0c)
#define TIM3_ARR                              *( volatile uint32_t *)(TIM3_BASE+0x2c)


int MyTicks ;
float Count_Start_Vlaue;
float Count_End_Vlaue;
float Puls_width;



/*=================Timer2======================*/
void Timer2_init(void);
void dus(int us);
void dms(int ms);
/*=================Timer3======================*/
void Timer3_init(void);
void Start_Timer3(void);
void Stop_Timer3(void);

/*=================Timer1======================*/
void Timer1_Init_PWM(void);
void Timer1_PWM1_Set_Value(int PWM1);
void Timer1_PWM2_Set_Value(int PWM2);

#endif /* INC_TIMER_H_ */
