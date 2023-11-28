/*
 * STM32F103C6_GPIO_DRIVERS.h
 *
 *  Created on: Jul 5, 2021
 *      Author: musta
 */

#ifndef INC_STM32F103C6_GPIO_DRIVERS_H_
#define INC_STM32F103C6_GPIO_DRIVERS_H_

/*
 * Stmf103c6_GPIO_Driver.h
 *
 *  Created on: Jun 26, 2021
 *      Author: musta
 */


//includes
#include "STM32_F103C6.h"


//config structure
typedef struct
{
	uint16_t GPIO_Pin_Number; // Specifies the GPIO pins to be configured.
	//This parameter must be set based on @ref GPIO_PINS_define

	uint8_t GPIO_MODE ;      // Specifies the operation mode for the selected pins
	//this parameter must be set based on @ref GPIO_MODE_define

	uint8_t GPIO_OUTPUT_SPEED; // Specifies speed for the selected pins.
	//This parameter can be set based on @ref GPIO_SPEED_define

}GPIO_Pin_Configure_t;


//===========================
//Macros Configuration References
//===========================

//@ref GPIO_PINS_define
#define GPIO_PIN_0               ((uint16_t )0x0001)//Pin 0 Selected
#define GPIO_PIN_1               ((uint16_t )0x0002)//Pin 1 Selected
#define GPIO_PIN_2               ((uint16_t )0x0004)//Pin 2 Selected
#define GPIO_PIN_3               ((uint16_t )0x0008)//Pin 3 Selected
#define GPIO_PIN_4               ((uint16_t )0x0010)//Pin 4 Selected
#define GPIO_PIN_5               ((uint16_t )0x0020)//Pin 5 Selected
#define GPIO_PIN_6               ((uint16_t )0x0040)//Pin 6 Selected
#define GPIO_PIN_7               ((uint16_t )0x0080)//Pin 7 Selected
#define GPIO_PIN_8               ((uint16_t )0x0100)//Pin 8 Selected
#define GPIO_PIN_9               ((uint16_t )0x0200)//Pin 9 Selected
#define GPIO_PIN_10              ((uint16_t )0x0400)//Pin 10 Selected
#define GPIO_PIN_11              ((uint16_t )0x0800)//Pin 11 Selected
#define GPIO_PIN_12              ((uint16_t )0x1000)//Pin 12 Selected
#define GPIO_PIN_13              ((uint16_t)0x2000)
#define GPIO_PIN_14              ((uint16_t )0x4000)//Pin 14 Selected
#define GPIO_PIN_15              ((uint16_t )0x8000)//Pin 15 Selected
#define GPIO_PIN_ALL             ((uint16_t)0xFFFF) //ALL Pins |Selected
#define GPIO_PIN_MASK            0x0000FFFFu


//@ref GPIO_MODE_define
/*
 * 0: Analog mode
1: Floating input (reset state)
2: Input with pull-up
3: pull-down
4: General purpose output push-pull
5: General purpose output Open-drain
6: Alternate function output Push-pull
7: Alternate function output Open-drain
8: Alternate function input*/
#define GPIO_MODE_Analog           0x00000000u  //Analog mode
#define GPIO_MODE_INPUT_FLO        0x00000001u  //Floating input
#define GPIO_MODE_INPUT_PU         0x00000002u  //Input with pull-up
#define GPIO_MODE_INPUT_PD         0x00000003u  //pull-down
#define GPIO_MODE_OUTPUT_PP        0x00000004u  //General purpose output push-pull
#define GPIO_MODE_OUTPUT_OD        0x00000005u  //General purpose output Open-drain
#define GPIO_MODE_OUTPUT_AF_PP     0x00000006u  //Alternate function output Push-pull
#define GPIO_MODE_OUTPUT_AF_OD     0x00000007u  //Alternate function output Open-drain
#define GPIO_MODE_AF_INPUT         0x00000008u  //Alternate function input



//@ref GPIO_SPEED_define
/*00: Input mode (reset state)
1: Output mode, max speed 10 MHz.
2: Output mode, max speed 2 MHz.
3: Output mode, max speed 50 MHz.*/
#define GPIO_SPEED_10M              0x00000001 //Output mode, max speed 10 MHz.
#define GPIO_SPEED_2M               0x00000002 //Output mode, max speed 2 MHz.
#define GPIO_SPEED_50M              0x00000003 //Output mode, max speed 50 MHz.

//@ref GPIO_PIN_State
#define GPIO_PIN_TRUE                1
#define GPIO_PIN_FALSE               0


//@ref GPIO_RETURN_LOCK
#define GPIO_RETURN_LOCK_DONE        1
#define GPIO_RETURN_LOCK_ERROR       0

/*
 * ========================================================================================
 *                         APIs Supported by "MCAL GPIO DRIVER"
 * ========================================================================================
 *
 */
void MCAL_GPIO_Init(GPIO_TypeDef * GPIOx, GPIO_Pin_Configure_t* PinConfig);
void MCAL_GPIO_Deinit(GPIO_TypeDef * GPIOx);
uint8_t MCAL_GPIO_Read_Pin(GPIO_TypeDef * GPIOx,uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef * GPIOx);
void MCAL_GPIO_WritePin(GPIO_TypeDef * GPIOx,uint16_t PinNumber,uint8_t Vlaue);
void MCAL_GPIO_WritePort(GPIO_TypeDef * GPIOx,uint16_t Vlaue);
void MCAL_GPIO_Toggle_pin(GPIO_TypeDef *GPIOx , uint16_t PinNumber);
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef * GPIOx,uint16_t PinNumber);
void MCAL_GPIO_WriteGroup(GPIO_TypeDef * GPIOx,uint16_t Value,uint16_t Mask);



#endif /* INC_STMF103C6_GPIO_DRIVER_H_ */


