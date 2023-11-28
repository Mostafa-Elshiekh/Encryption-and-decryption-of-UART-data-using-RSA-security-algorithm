/*
 * STM32_F103C6_GPIO_DRIVERS.c
 *
 *  Created on: Jul 4, 2021
 *      Author: Mostafa Elshiekh
 */


#include "STM32F103C6_GPIO_DRIVERS.h"


uint8_t Get_CRLH_Postion(uint16_t PinNumber)
{
	switch (PinNumber)
	{
	case GPIO_PIN_0:
		return 0;
		break;

	case GPIO_PIN_1:
		return 4;
		break;

	case GPIO_PIN_2:
		return 8;
		break;

	case GPIO_PIN_3:
		return 12;
		break;

	case GPIO_PIN_4:
		return 16;
		break;

	case GPIO_PIN_5:
		return 20;
		break;

	case GPIO_PIN_6:
		return 24;
		break;

	case GPIO_PIN_7:
		return 28;
		break;

	case GPIO_PIN_8:
		return 0;
		break;

	case GPIO_PIN_9:
		return 4;
		break;

	case GPIO_PIN_10:
		return 8;
		break;

	case GPIO_PIN_11:
		return 12;
		break;

	case GPIO_PIN_12:
		return 16;
		break;

	case GPIO_PIN_13:
		return 20;
		break;

	case GPIO_PIN_14:
		return 24;
		break;

	case GPIO_PIN_15:
		return 28;
		break;
	default:
		return 0;
		break;

	}
}

/**=================================================================
 * @Fn -                    -MCAL_GPIO_INIT
 * @brief -                 -Initialize the GPIOx PINy according specified parameters in PinConfig
 * @param [in] -            -GPIOx : where x can be (A..E depending on device used)
 * @param [in] -            -PinConfig pointer to a GPIO_PinConfig_t structure that contains
 * @retval -                -none
 * note -                   -stmf103c6 MCU has GPIO A,B,C,D,E Modules
 *                           but LQFP48 Package has only GPIO A,B, Part of C/D exported external pins
 */
/**================================================================= */
void MCAL_GPIO_Init( GPIO_TypeDef *GPIOx , GPIO_Pin_Configure_t *Pin_Config )
{

	//To Init Any Pins Must Write On Port configuration register low (GPIOx_CRL) 0>>>7
	//Or register low (GPIOx_CRH) 8>>>15
	//We Determine The Position Should Write On It In  configuration register By Determine First Position Pin

	volatile uint32_t *ConfigureRegister = NULL;
	uint8_t   ConfigurePin=0;     //In This Variable We Store The Configure Pin

	ConfigureRegister = (Pin_Config->GPIO_Pin_Number < GPIO_PIN_8)? &GPIOx->CRL : &GPIOx->CRH ;
	//Clear CNF & MODE
	*(ConfigureRegister) &=~(0xf<<Get_CRLH_Postion(Pin_Config->GPIO_Pin_Number));

	if (Pin_Config->GPIO_MODE == GPIO_MODE_OUTPUT_AF_OD || Pin_Config->GPIO_MODE ==GPIO_MODE_OUTPUT_AF_PP || Pin_Config->GPIO_MODE ==GPIO_MODE_OUTPUT_OD || Pin_Config->GPIO_MODE ==GPIO_MODE_OUTPUT_PP)
	{

		//I sure The User Want Make The Pin As Output & in Case Output Should Configure Mode(Speed) & CNF(State)
		ConfigurePin = ((( (Pin_Config->GPIO_MODE - 4)<<2) |(Pin_Config->GPIO_OUTPUT_SPEED)) & 0x0f); //Shift 2 to Set The CNF Bits

	}

	else  //I sure The User Want Make The Pin As Input & in Case input Should Configure Mode(Speed)=00 & CNF(State)
	{
		if(Pin_Config->GPIO_MODE == GPIO_MODE_INPUT_FLO || GPIO_MODE_Analog)
		{
			ConfigurePin = (( ( (Pin_Config->GPIO_MODE) <<2) | 0x0) & 0x0F);      //Shift 2 to Set The CNF Bits
		}

		else if(Pin_Config->GPIO_MODE == GPIO_MODE_AF_INPUT)
		{
			ConfigurePin = (( ( (GPIO_MODE_INPUT_FLO) <<2) | 0x0) & 0x0f);      //Shift 2 to Set The CNF Bits
		}
		else  //PullUp Or PullDown
		{
			ConfigurePin = ( (((GPIO_MODE_INPUT_PU)<<2  ) |  0x0) & 0x0f);
			// 20. Port bit configuration table
			/*In Case GPIO_MODE_INPUT_PU OR GPIO_MODE_INPUT_PD We Put The Same Value 10 In CNF
			And Go To ODR IF GPIO_MODE_INPUT_PU Put 1 And If GPIO_MODE_INPUT_PD Put In ODR 0 Shifting By Bin Number*/
			if(Pin_Config->GPIO_MODE == GPIO_MODE_INPUT_PU)
			{
				GPIOx->ODR |=(Pin_Config->GPIO_Pin_Number); //Not Making Shifting because The Pin Number Already Shifted in Header
			}
			else //GPIO_MODE_INPUT_PD
			{
				GPIOx->ODR &=~(Pin_Config->GPIO_Pin_Number);//Not Making Shifting because The Pin Number Already Shifted in Header
			}
		}
	}
	//Write On CRH Or CLH
	*(ConfigureRegister) |=( ConfigurePin << Get_CRLH_Postion(Pin_Config->GPIO_Pin_Number) );
}




/**=================================================================
 * @Fn -                    -MCAL_GPIO_DeINIT
 * @brief -                 -Reset All GPIO Registers
 * @param [in] -            -GPIOx : where x can be (A..E depending on device used)
 * @retval -                -none
 * note -                   -none
 */
/**================================================================= */
void MCAL_GPIO_DeInit( GPIO_TypeDef *GPIOx )
{

	/*If MicroController Not Include Reset Controller You Should Make Reset Any Peripheral Manual By Way
	Go To All Registers In This Peripheral And Put On Reset Value*/
	/*GPIOx->CRL  |= 0x44444444;
	GPIOx->CRH  |= 0x44444444;
    //GPIOx->IDR = (Read Only);
	GPIOx->ODR  |= 0x00000000;
	GPIOx->BRR  |= 0x00000000;
	GPIOx->LCKR |= 0x00000000;
	GPIOx->BSRR |= 0x00000000;*/

	/*If MicroController Include Reset Controller We Reset Any Peripheral By It*/

	if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR |=(1<<2);
		RCC->APB2RSTR &=~(1<<2);
	}
	else if(GPIOx == GPIOB)
	{
		RCC->APB2RSTR |=(1<<3);
		RCC->APB2RSTR &=~(1<<3);
	}
	else if(GPIOx == GPIOC)
	{
		RCC->APB2RSTR |=(1<<4);
		RCC->APB2RSTR &=~(1<<4);
	}
	else if(GPIOx == GPIOD)
	{
		RCC->APB2RSTR |=(1<<5);
		RCC->APB2RSTR &=~(1<<5);
	}
	else if(GPIOx == GPIOE)
	{
		RCC->APB2RSTR |=(1<<5);
		RCC->APB2RSTR &=~(1<<5);
	}
}




/**=================================================================
 * @Fn -                    - MCAL_GPIO_ReadPin
 * @brief -                 -Read Specific PIN
 * @param [in] -            -GPIOx : where x can be (A..E depending on device used)
 * @param [in] -            -PinNumber :
 * @retval -                -the input pin value (tow values based on @ref GPIO_PIN_State)
 * note -                   -none
 */
/**================================================================= */
uint8_t MCAL_GPIO_Read_Pin( GPIO_TypeDef *GPIOx , uint16_t Pin_Number )
{

	uint8_t PinState =0;
	if( (GPIOx->IDR & Pin_Number) != (uint32_t)GPIO_PIN_FALSE )
	{
		PinState = GPIO_PIN_TRUE;
	}
	else
	{
		PinState = GPIO_PIN_FALSE;
	}
	return PinState;

}



/**=================================================================
 * @Fn -                    - MCAL_GPIO_ReadPort
 * @brief -                 -Read the input port value
 * @param [in] -            -GPIOx : where x can be (A..E depending on device used)
 * @param [in] -            -PinNumber :
 * @retval -                -the input pin value (tow values based on @ref GPIO_PIN_State)
 * note -                   -none
 */
/**================================================================= */
uint16_t MCAL_GPIO_ReadPort( GPIO_TypeDef *GPIOx )
{

	uint16_t PortState =0;
	PortState = (uint16_t)GPIOx->IDR;
	return PortState;

}



/**=================================================================
 * @Fn -                    - MCAL_GPIO_WritePin
 * @brief -                 -Write on specific input pin
 * @param [in] -            -GPIOx : where x can be (A..E depending on device used)
 * @param [in] -            -PinNumber :
 * @param [in] -            -Vlaue to write on this bit
 * @retval -                -the input pin value (tow values based on @ref GPIO_PIN_State)
 * note -                   -none
 */
/**================================================================= */
void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx , uint16_t Pin_Number , uint8_t Value)
{
	if(Value != GPIO_PIN_FALSE )
	{
		GPIOx->ODR |=(uint32_t) (Pin_Number);
	}
	else
	{
		GPIOx->ODR &=~(uint32_t)(Pin_Number);
	}
}



/**=================================================================
 * @Fn -                    - MCAL_GPIO_WritePort
 * @brief -                 -Write on specific port
 * @param [in] -            -GPIOx : where x can be (A..E depending on device used)
 * @param [in] -            -Vlaue to write on this port
 * @retval -                -none
 * note -                   -none
 */
/**================================================================= */
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx , uint16_t Value)
{

	GPIOx->ODR = (uint32_t)Value;
}



/**=================================================================
 * @Fn -                    - MCAL_GPIO_TogglePin
 * @brief -                 -toggle specific pin
 * @param [in] -            -GPIOx : where x can be (A..E depending on device used)
 * @param [in] -            -PinNumber :
 * @retval -                -none
 * note -                   -none
 */
/**================================================================= */
void MCAL_GPIO_Toggle_pin(GPIO_TypeDef *GPIOx , uint16_t PinNumber)
{
	GPIOx->ODR ^= (PinNumber);
}



/**=================================================================
 * @Fn -                    - MCAL_GPIO_LockPin
 * @brief -                 -Lock specific pin to be frozen the configuration of this pin
 * @param [in] -            -GPIOx : where x can be (A..E depending on device used)
 * @param [in] -            -PinNumber :
 * @retval -                -Ok if pin config is locked or Error if pin not locked
 *                           (ok & Error are defined @ref GPIO_RETURN_LOCK)
 * note -                   -none
 */
/**================================================================= */
uint8_t MCAL_GPIO_Lock_pin(GPIO_TypeDef *GPIOx , uint8_t PinNumber)
{
	/*This register is used to lock the configuration of the port bits when a correct write sequence
	is applied to bit 16 (LCKK). The value of bits [15:0] is used to lock the configuration of the
	GPIO. During the write sequence, the value of LCKR[15:0] must not change. When the
	LOCK sequence has been applied on a port bit it is no longer possible to modify the value of
	the port bit until the next reset.
	Each lock bit freezes the corresponding 4 bits of the control register (CRL, CRH). */
	GPIOx->LCKR |=(PinNumber);

	/*Bit 16 LCKK[16]: Lock key
	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	0: Port configuration lock key not active
	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	LOCK key writing sequence:
	Write 1
	Write 0
	Write 1
	Read 0
	Read 1 (this read is optional but confirms that the lock is active)
	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	Any error in the lock sequence will abort the lock.*/

	/*LOCK key writing sequence:*/
	//Write 1
	GPIOx->LCKR |=(1<<16);
	//Write 0
	GPIOx->LCKR &=~(1<<16);
	//Write 1
	GPIOx->LCKR |=(1<<16);
   //Read 0
    if((uint16_t)(GPIOx->LCKR & 1<<16 ))
    {
    	return GPIO_RETURN_LOCK_DONE;
    }
    else
    {
    	return GPIO_RETURN_LOCK_ERROR;
    }

}

/**================================================================= */
void MCAL_GPIO_WriteGroup(GPIO_TypeDef * GPIOx,uint16_t Value,uint16_t Mask)
{
	GPIOx->ODR &= ~(Mask);				// clear the group
	GPIOx->ODR |= (Value & Mask);		// put the new value
}


