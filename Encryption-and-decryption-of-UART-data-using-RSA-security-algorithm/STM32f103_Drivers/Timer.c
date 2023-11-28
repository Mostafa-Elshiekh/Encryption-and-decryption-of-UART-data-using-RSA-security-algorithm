/*
 * Timer.c
 *
 *  Created on: Oct 10, 2021
 *      Author: Mostafa Elshiekh
 */

#include "Timer.h"


/*======================Global Variables===========================*/
int MyTicks=0 ;
float Count_Start_Vlaue=0;
float Count_End_Vlaue=0;
float Puls_width=0;


//we need move the delay function from timer2 to timer1 to relase timer2 for RTOS
/*==============================APIs================================*/

/*========================Timer2 For Delay========================*/
void Timer2_init(void)//for delay
{
	RCC_APB1ENR |=(1<<0);     //Enable Rcc for tim2
	TIM2_PSC = 7;             //Clk_input=(8M/(7+1))=1MHZ
	TIM2_ARR = 0xFFFF;        //to make interrupt after 50000 tike(50000*10^-6)=0.05-->20*0.05=1
	TIM2_CR1 |=(1<<0);
	while(!(TIM2_SR)&(1<<0));
}

void dus(int us)
{
	TIM2_CNT=0;
	while(TIM2_CNT<us);
}

void dms(int ms)
{
	int i=0;
	for(i=0;i<ms;i++)
	{
		dus(1000);
	}
}
/*==================================================================*/


/*==================================================================*/
void Timer3_init(void) //ulter
{
	RCC_APB1ENR |=(1<<1);    //Enable Rcc for tim1
	TIM3_PSC = 7;            //Clk_input=(8M/(7+1))=1MHZ
	TIM3_ARR = 0xFFFF;        //to make interrupt after 50000 tike(50000*10^-6)=0.05-->20*0.05=1
	TIM3_CR1 |=(1<<0);
}


/*==================================================================*/

/*void Start_Timer3(void)
{
	TIM3_CR1 |=(1<<0);
}

void Stop_Timer3(void)
{
	TIM3_CR1 &=~(1<<0);
}*/



/*===================PWM=============================*/
//Table 46. TIM1 alternate function remapping

/* The reference PWM signal OCxREF is high as long as TIMx_CNT < TIMx_CCRx else it becomes low*/
void Timer1_Init_PWM(void)
{
	/*GPIO Configuration */
	//TIM1_CH1 PA8
	GPIO_Pin_Configure_t PinCfg;
	//PA8 CH1 PWM1
	PinCfg.GPIO_Pin_Number=GPIO_PIN_8;
	PinCfg.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
	PinCfg.GPIO_OUTPUT_SPEED=GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &PinCfg);

	//A11 CH4 PWM2
	PinCfg.GPIO_Pin_Number=GPIO_PIN_11;
	PinCfg.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
	PinCfg.GPIO_OUTPUT_SPEED=GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &PinCfg);


	/*Timer1 Configuration*/
	//Bit 11 TIM1EN: TIM1 timer clock enable
	RCC_APB2ENR |=(1<<11);

	//Bit 7 ARPE: Auto-reload preload enable
	TIM1_CR1 |=(1<<7);

	//Upcounting is active when the DIR bit in the TIMx_CR1 register is low
	//Bit 4 DIR: Direction
	TIM1_CR1 &=~(1<<4);

	TIM1_PSC=3;

	//allows generating a signal with a frequency determined by the value of the TIMx_ARR register
	TIM1_ARR = 0xC350;


	/*=========================Channel 1 ==============================*/
	//Bits 6:4 OC1M: Output Compare 1 mode
	//110: PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1
	TIM1_CCMR1 |=(0b110<<4);

	/*The corresponding preload register must be enabled by setting the
    OCxPE bit in the TIMx_CCMRx register*/
	//Bit 3 OC1PE: Output Compare 1 preload enable
	TIM1_CCMR1 |=(1<<3);


	//Bit 1 CC1P: Capture/Compare 1 output polarity
	//1: OC1 active low
	//TIM1_CCER |=(1<<1);


	//Bit 0 CC1E: Capture/Compare 1 output enable
	TIM1_CCER |=(1<<0);

	//Bits 12:14 OC1M: Output Compare 1 mode
	//110: PWM mode 1 - In upcounting, channel 4 is active as long as TIM1_CNT<TIM1_CCR4
	TIM1_CCMR2 |=(0b110<<12);

	/*=========================Channel 4 ==============================*/
	//Bit 11 OC4PE: Output compare 4 preload enable
	TIM1_CCMR2 |=(1<<11);

	//Bit 12 CC4E: Capture/Compare 4 output enable
	TIM1_CCER |=(1<<12);

	//Bit 13 CC14P: Capture/Compare 4 output polarity
	//1: OC1 active low
	//TIM1_CCER |=(1<<13);


	//Bit 15 MOE: Main output enable
	TIM1_BDTR |=(1<<15);

	//Bit 0 CEN: Counter enable
	//TIM1_CR1 |=(1<<0);



}



void Timer1_PWM1_Set_Value(int PWM1)
{
	//duty cycle determined by the value of the TIMx_CCRx register.
	TIM1_CCR1 = PWM1;
	//Bit 0 CEN: Counter enable
	TIM1_CR1 |=(1<<0);
}


void Timer1_PWM2_Set_Value(int PWM2)
{
	//duty cycle determined by the value of the TIMx_CCRx register.
	TIM1_CCR4 = PWM2;
	//Bit 0 CEN: Counter enable
	TIM1_CR1 |=(1<<0);
}










/*====================ISR============================*/
/*void TIM3_IRQHandler(void)
{
	TIM3_CNT=0;
	TIM3_SR &=~(1<<0);
}*/
