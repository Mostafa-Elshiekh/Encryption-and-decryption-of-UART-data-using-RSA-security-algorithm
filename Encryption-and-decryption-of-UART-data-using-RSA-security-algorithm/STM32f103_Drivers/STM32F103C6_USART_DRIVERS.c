/*
 * STM32F103C6_USART_DRIVERS.c
 *
 *  Created on: Oct 20, 2021
 *      Author: musta
 */


#include "STM32F103C6_USART_DRIVERS.h"


/*==========================================================*/
/*Generic Variables*/
/*==========================================================*/


USART_Config Global_UART_Config[3] ;


/*==========================================================*/
/*Generic Functions*/
/*==========================================================*/







/* ==============================================================
 *              APIs Supported by "MCAL USART DRIVER"
 * ===============================================================*/




/**=================================================================
 * @Fn -                    -MCAL_UART_INIT
 * @brief -                 -Initialize the USARTx according specified parameters in USART_Config
 * @param [in] -            -USARTx : where x can be (1,2,3 depending on device used)
 * @param [in] -            -UART_Config pointer to a UART_Config structure that contains
 * @retval -                -none
 * note -                   -none
 *
 */
/**================================================================= */
void MCAL_UART_INIT(USART_TypeDef* USARTx,USART_Config * UART_Config)
{

	uint32_t pclk ,BRR;


	//Enable Clock For Given USART Peripheral
	if(USARTx == USART1)
	{
		RCC_USART1_CLOCK_EN();
		Global_UART_Config[0] = *UART_Config;
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_CLOCK_EN();
		Global_UART_Config[1] = *UART_Config;
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_CLOCK_EN();
		Global_UART_Config[2] = *UART_Config;
	}

	//Enable UART Module Bit 13 UE: USART enable
	USARTx->CR1 |=(1<<13);

	//Enable TX RX according to the USART_MODE configuration item
	USARTx->CR1 |= UART_Config->USART_MODE;

	//PayLoad Length
	USARTx->CR1 |=UART_Config->PayLoad_Length;

	//Baud Rate
	USARTx->CR1 |=UART_Config->BaudRate;

	//Parity
	USARTx->CR1 |=UART_Config->Parity;

	//StopBits
	USARTx->CR1 |=UART_Config->StopBits;

	//HW_FlowCtrl
	USARTx->CR1 |=UART_Config->HW_FlowCtrl;

	//IRQ_Enable
	USARTx->CR1 |=UART_Config->IRQ_Enable;

	/*Configuration of BRR(BaudRate Register)*/
	//PCLK1 for USART2,3
	//PCLK2 for USART1
	if(USARTx == USART1)
	{
		pclk=MCAL_RCC_Get_PCLK2_Freq();
	}
	else
	{
		pclk=MCAL_RCC_Get_PCLK1_Freq();
	}

	BRR = USART_BRR_REGISTER(pclk,UART_Config->BaudRate);
	USARTx->BRR = BRR;

	/*Enable/Disable interrupt*/
	//USART_CR1
	if( UART_Config->IRQ_Enable != USART_IRQ_Enable_NONE ) //this mean user enable interrupt
	{
		USARTx->CR1 |= UART_Config->IRQ_Enable;

		//Enable interrupt for NVIC for USARTx IRQ
		if(USARTx == USART1)
		{
			NVIC_IRQ37_USART1_ENABLE();
		}
		else if(USARTx == USART2)
		{
			NVIC_IRQ38_USART2_ENABLE();
		}
		else if(USARTx == USART3)
		{
			NVIC_IRQ39_USART3_ENABLE();
		}

	}

}


/**=================================================================
 * @Fn -                    -MCAL_UART_DeINIT
 * @brief -                 -Reset All USART Registers
 * @param [in] -            -USARTx : where x can be (1,2,3)
 * @retval -                -none
 * note -                   -none
 */
/**================================================================= */
void MCAL_UART_DeINIT(USART_TypeDef* USARTx,USART_Config * UART_Config)
{

	if(USARTx == USART1)
	{
		RCC_USART1_RESET();
		NVIC_IRQ37_USART1_DISABLE();
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_RESET();
		NVIC_IRQ38_USART2_DISABLE();
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_RESET();
		NVIC_IRQ39_USART3_DISABLE();
	}
}

/*
 * This functions is used by uart driver to get the index of the global array for the used instance
 * */
static uint8_t Which_UART(USART_TypeDef* USARTx){
	if(USARTx == USART1)
	{
		return 0;
	}
	else if(USARTx == USART2)
	{
		return 1;
	}
	else if(USARTx == USART3)
	{
		return 3;
	}
	return 4;		//will cause error for user when he uses wrong address for USARTx
}
void MCAL_UART_SEND_DATA(USART_TypeDef* USARTx,uint16_t* pTXBuffer,enum PoLLing_Mechnism PollengEn)
{

	//Wait until TXE flag is set in SR
	if(PollengEn == enable)
	{
		while(! (USARTx->SR & (1<<7)) );
	}

	uint8_t Gindex=Which_UART(USARTx);
	//check the USART_PayLoad_Length (9B or 8B)

	/*When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	because it is replaced by the parity.
	When receiving with the parity enabled, the value read in the MSB bit is the received parity
	bit.*/


	if( Global_UART_Config[Gindex].PayLoad_Length ==  USART_PayLoad_Length_9B)
	{
		USARTx->DR = (*pTXBuffer & (uint16_t)0x01FF);
	}
	else
	{
		//If 8Bit
		USARTx->DR = (*pTXBuffer & (uint8_t)0xFF);
	}



}


void MCAL_UART_RECEIVE_DATA(USART_TypeDef* USARTx,uint16_t* pTXBuffer,enum PoLLing_Mechnism PollengEn)
{

	if(PollengEn == enable)
	{
		//wait till RXNE flag is set in the SR
		while(! (USARTx->SR & (1<<5)) );
	}

	//check the USART_PayLoad_Length (9B or 8B)
	uint8_t Gindex=Which_UART(USARTx);
	if(Global_UART_Config[Gindex].PayLoad_Length == USART_PayLoad_Length_9B)
	{
		if(Global_UART_Config[Gindex].Parity == USART_Parity_NONE)
		{
			//no parity so all 9bit consider as data
			*((uint16_t*) pTXBuffer) = USARTx->DR;
		}
		else
		{
			//9Bit (8data + 1 parity)
			*((uint16_t*)pTXBuffer) = (USARTx->DR & (uint8_t)0xFF);
		}

	}
	else //8Bit
	{
		//8Bit & no parity
		if(Global_UART_Config[Gindex].Parity == USART_Parity_NONE)
		{
			//no parity so all 8bit consider as data
			*((uint16_t*) pTXBuffer) = (USARTx->DR & (uint8_t)0xFF) ;
		}
		else
		{
			//8Bit (7data + 1 parity)
			*((uint16_t*)pTXBuffer) = (USARTx->DR & (uint8_t)0x7F);
		}
	}


}

void MCAL_UART_GPIO_Set_Pins(USART_TypeDef* USARTx)
{
	GPIO_Pin_Configure_t PinCfg;
	if( USARTx == USART1 )
	{
		/* PA9  ->TX
		 * PA10 ->RX
		 * PA11 ->CTS
		 * PA12 ->RTS
		 */

		//TX
		PinCfg.GPIO_Pin_Number=GPIO_PIN_9;
		PinCfg.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_OUTPUT_SPEED=GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		//RX
		PinCfg.GPIO_Pin_Number=GPIO_PIN_10;
		PinCfg.GPIO_MODE=GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		if (Global_UART_Config[0].HW_FlowCtrl == USART_HW_FlowCtrl_CTS 				||
				Global_UART_Config[0].HW_FlowCtrl == USART_HW_FlowCtrl_CTS_AND_RTS 		)
		{
			PinCfg.GPIO_Pin_Number=GPIO_PIN_11;
			PinCfg.GPIO_MODE=GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

		if (Global_UART_Config[0].HW_FlowCtrl == USART_HW_FlowCtrl_RTS 				||
				Global_UART_Config[0].HW_FlowCtrl == USART_HW_FlowCtrl_CTS_AND_RTS 		)
		{
			PinCfg.GPIO_Pin_Number=GPIO_PIN_12;
			PinCfg.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

	}
	if( USARTx == USART2 )
	{
		/* PA2  ->TX
		 * PA3 ->RX
		 * PA0 ->CTS
		 * PA1 ->RTS
		 */

		//TX
		PinCfg.GPIO_Pin_Number=GPIO_PIN_2;
		PinCfg.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_OUTPUT_SPEED=GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		//RX
		PinCfg.GPIO_Pin_Number=GPIO_PIN_3;
		PinCfg.GPIO_MODE=GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		if (Global_UART_Config[1].HW_FlowCtrl == USART_HW_FlowCtrl_CTS 					||
				Global_UART_Config[1].HW_FlowCtrl == USART_HW_FlowCtrl_CTS_AND_RTS 			)
		{
			PinCfg.GPIO_Pin_Number=GPIO_PIN_0;
			PinCfg.GPIO_MODE=GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

		if (Global_UART_Config[1].HW_FlowCtrl == USART_HW_FlowCtrl_RTS 					||
				Global_UART_Config[1].HW_FlowCtrl == USART_HW_FlowCtrl_CTS_AND_RTS 		)
		{
			PinCfg.GPIO_Pin_Number=GPIO_PIN_1;
			PinCfg.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}

	}
	if( USARTx == USART3 )
	{
		/* PB10 ->TX
		 * PB11 ->RX
		 * PB13 ->CTS
		 * PB14 ->RTS
		 */

		//TX
		PinCfg.GPIO_Pin_Number=GPIO_PIN_10;
		PinCfg.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_OUTPUT_SPEED=GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		//RX
		PinCfg.GPIO_Pin_Number=GPIO_PIN_11;
		PinCfg.GPIO_MODE=GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOB, &PinCfg);


		if (Global_UART_Config[2].HW_FlowCtrl == USART_HW_FlowCtrl_CTS 					||
				Global_UART_Config[2].HW_FlowCtrl == USART_HW_FlowCtrl_CTS_AND_RTS 		)
		{
			PinCfg.GPIO_Pin_Number=GPIO_PIN_13;
			PinCfg.GPIO_MODE =GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}

		if (Global_UART_Config[2].HW_FlowCtrl == USART_HW_FlowCtrl_RTS 					||
				Global_UART_Config[2].HW_FlowCtrl == USART_HW_FlowCtrl_CTS_AND_RTS 			)
		{
			PinCfg.GPIO_Pin_Number=GPIO_PIN_14;
			PinCfg.GPIO_MODE=GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED=GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}

	}
}


void MCAL_UART_WAIT_TC(USART_TypeDef* USARTx)
{
	//wait till TC flag is set in the SR
	while(! (USARTx->SR & (1<<6)) );

}








//ISR
void USART1_IRQHandler(void)
{
	Global_UART_Config[0].P_IRQ_Call_Back ();

}

void USART2_IRQHandler(void)
{
	Global_UART_Config[1].P_IRQ_Call_Back ();

}

void USART3_IRQHandler(void)
{
	Global_UART_Config[2].P_IRQ_Call_Back ();

}





