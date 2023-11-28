/*
 * STM32_F103C6_RCC_DRIVERS.c
 *
 *  Created on: Jul 17, 2021
 *      Author: Mostafa Elshiekh
 */



#include "STM32F103C6_GPIO_DRIVERS.h"
#include "STM32F103C6_RCC_DRIVERS.h"


/*Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
	Set and cleared by software to control the division factor of the APB low-speed clock
	(PCLK1).
	Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
	0xx: HCLK not divided
	100: HCLK divided by 2
	101: HCLK divided by 4
	110: HCLK divided by 8
	111: HCLK divided by 16*/
const uint8_t APBPrescTable[8] = {0,0,0,0,1,2,3,4}; //shift right 1 = Div on 2


/*Bits 7:4 HPRE: AHB prescaler
	Set and cleared by software to control the division factor of the AHB clock.
	0xxx: SYSCLK not divided
	1000: SYSCLK divided by 2
	1001: SYSCLK divided by 4
	1010: SYSCLK divided by 8
	1011: SYSCLK divided by 16
	1100: SYSCLK divided by 64
	1101: SYSCLK divided by 128
	1110: SYSCLK divided by 256
	1111: SYSCLK divided by 512*/
const uint8_t AHBPrescTable[16] = {0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8};


uint32_t MCAL_RCC_Get_SYS_CLKFreq(void)
{
	/*Bits 1:0 SW: System clock switch
	Set and cleared by software to select SYSCLK source.
	Set by hardware to force HSI selection when leaving Stop and Standby mode or in case of
	failure of the HSE oscillator used directly or indirectly as system clock (if the Clock Security
	System is enabled).
	00: HSI selected as system clock
	01: HSE selected as system clock
	10: PLL selected as system clock
	11: not allowed*/

	switch( (RCC->CFGR >>2) & 0b11 )
	{

	case 00:
		return HSI_RC_CLK;
		break;

	case 01:
		//to do calc it HSE user should specify it
		//return HSE_CLK;
		break;

	case 10:
		//to do calc it HSE PLLCLK & PLLMULL & PLL source Mux
		return 16000000;
		break;

	default:
		return 0;
		break;

	}
	return 0;
}


uint32_t MCAL_RCC_Get_HCLK_Freq(void)
{

	/*Bits 7:4 HPRE: AHB prescaler
	Set and cleared by software to control the division factor of the AHB clock.
	0xxx: SYSCLK not divided
	1000: SYSCLK divided by 2
	1001: SYSCLK divided by 4
	1010: SYSCLK divided by 8
	1011: SYSCLK divided by 16
	1100: SYSCLK divided by 64
	1101: SYSCLK divided by 128
	1110: SYSCLK divided by 256
	1111: SYSCLK divided by 512*/
	return MCAL_RCC_Get_SYS_CLKFreq() >> AHBPrescTable[( (RCC->CFGR >> 7) & 0b1111) ];/*(( RCC->CFGR >>8) & 0b1111) This Is
	                                                      Read Value of AHB  prescaler To Determine index On 2d Upper Array */


}



uint32_t MCAL_RCC_Get_PCLK1_Freq(void)
{

	/*Bits 10:8 PPRE1: APB low-speed prescaler (APB1)
	Set and cleared by software to control the division factor of the APB low-speed clock
	(PCLK1).
	Warning: the software has to set correctly these bits to not exceed 36 MHz on this domain.
	0xx: HCLK not divided
	100: HCLK divided by 2
	101: HCLK divided by 4
	110: HCLK divided by 8
	111: HCLK divided by 16*/

	return ( MCAL_RCC_Get_HCLK_Freq() >> APBPrescTable[ (( RCC->CFGR >>8) & 0b111) ] ); /*(( RCC->CFGR >>8) & 0b111) This Is
	                                                      Read Value of  PPRE1 prescaler To Determine index On Upper Array */

}


uint32_t MCAL_RCC_Get_PCLK2_Freq(void)
{

	/*Bits 13:11 PPRE2: APB high-speed prescaler (APB2)
	Set and cleared by software to control the division factor of the APB high-speed clock
	(PCLK2).
	0xx: HCLK not divided
	100: HCLK divided by 2
	101: HCLK divided by 4
	110: HCLK divided by 8
	111: HCLK divided by 16*/

	return (MCAL_RCC_Get_HCLK_Freq() >> (APBPrescTable[( (RCC->CFGR >>11) & 0b111 )])); /*(( RCC->CFGR >>11) & 0b111) This Is
	                                                      Read Value of  PPRE2 prescaler To Determine index On Upper Array */

}
