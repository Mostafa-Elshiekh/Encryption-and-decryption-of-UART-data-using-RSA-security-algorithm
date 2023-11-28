/*
 * STM32F103C6_RCC_DRIVERS.h
 *
 *  Created on: Jul 17, 2021
 *      Author: musta
 */

#ifndef INC_STM32F103C6_RCC_DRIVERS_H_
#define INC_STM32F103C6_RCC_DRIVERS_H_


//includes
#include "STM32_F103C6.h"
#include "STM32F103C6_GPIO_DRIVERS.h"

#define HSI_RC_CLK 8000000


uint32_t MCAL_RCC_Get_SYS_CLKFreq(void);
uint32_t MCAL_RCC_Get_HCLK_Freq(void);
uint32_t MCAL_RCC_Get_PCLK1_Freq(void);
uint32_t MCAL_RCC_Get_PCLK2_Freq(void);

#endif /* INC_STMF103C6_RCC_DRIVER_H_ */


