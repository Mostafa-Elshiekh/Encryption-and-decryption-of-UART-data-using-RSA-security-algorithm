/*
 * STM32F103C6_USART_DRIVERS.h
 *
 *  Created on: Oct 20, 2021
 *      Author: musta
 */

#ifndef INC_STM32F103C6_USART_DRIVERS_H_
#define INC_STM32F103C6_USART_DRIVERS_H_

/*==========================================================*/
//includes
/*==========================================================*/
#include "STM32_F103C6.h"
#include "STM32F103C6_GPIO_DRIVERS.h"
#include "STM32F103C6_RCC_DRIVERS.h"


//configuration structure
typedef struct
{
	uint8_t           USART_MODE ;   //Specifies TX/RX Enable/Disable
	                                 //This parameter must be set based on @Ref USART_MODE_define

	uint32_t          BaudRate;       //Specifies communication Baud Rate
	                                  //This parameter must be set based on @Ref USART_BaudRate_define

	uint8_t          PayLoad_Length; //Specifies number of data bits transmitted or received in a frame
		                             //This parameter must be set based on @Ref USART_PayLoad_Length_define

	uint8_t          Parity;         //Specifies the Parity mode
		                             //This parameter must be set based on @Ref USART_Parity_define

	uint8_t          StopBits;      //Specifies the StopBits
			                        //This parameter must be set based on @Ref USART_StopBits_define

	uint8_t          HW_FlowCtrl;      //Specifies the HW_FlowCtrl
				                       //This parameter must be set based on @Ref USART_HW_FlowCtrl_define

	uint8_t          IRQ_Enable;      //Specifies the IRQ_Enable
					                  //This parameter must be set based on @Ref USART_IRQ_Enable_define

	void (* P_IRQ_Call_Back)(void);  //Set C Function() Which You Need Call it When IRQ is happened


}USART_Config;

//===========================
//Macros Configuration References
//===========================

/*@Ref USART_MODE_define */
#define USART_MODE_RX                 (uint32_t)(1<<2)   //Bit 2 RE: Receiver enable
#define USART_MODE_TX                 (uint32_t)(1<<3)   //Bit 3 TE: Transmitter enable
#define USART_MODE_RX_AND_TX          (uint32_t)(1<<2 | 1<<3) //Bit 2 RE: Receiver enable & Bit 3 TE: Transmitter enable



/*@Ref USART_BaudRate_define*/
#define USART_BaudRate_2400            2400
#define USART_BaudRate_9600            9600
#define USART_BaudRate_19200           19200
#define USART_BaudRate_57600           57600
#define USART_BaudRate_115200          115200
#define USART_BaudRate_230400          230400
#define USART_BaudRate_460800          460800
#define USART_BaudRate_921600          921600
#define USART_BaudRate_2250000         2250000
#define USART_BaudRate_4500000         4500000


/*@Ref USART_PayLoad_Length_define*/
#define USART_PayLoad_Length_8B        (uint32_t)(0<<12)
#define USART_PayLoad_Length_9B        (uint32_t)(1<<12)



/*@Ref USART_Parity_define*/
#define USART_Parity_NONE             (uint32_t)(0<<10)
#define USART_Parity_EVEN             (uint32_t)(0<<9 | 1<<10)
#define USART_Parity_ODD              (uint32_t)(1<<9 | 1<<10)



/*@Ref USART_StopBits_define*/
#define USART_StopBits_1             (uint32_t)(0b00<<12)
#define USART_StopBits_hafe           (uint32_t)(0b01<<12)
#define USART_StopBits_2             (uint32_t)(0b10<<12)
#define USART_StopBits_1_hafe           (uint32_t)(0b11<<12)



/*@Ref USART_HW_FlowCtrl_define*/
#define USART_HW_FlowCtrl_NONE              (uint8_t)(0<<8 | 0<<9)
#define USART_HW_FlowCtrl_CTS               (uint8_t)(0<<8 | 1<<9)
#define USART_HW_FlowCtrl_RTS               (uint8_t)(1<<8 | 0<<9)
#define USART_HW_FlowCtrl_CTS_AND_RTS       (uint8_t)(1<<8 | 1<<9)



/*@Ref USART_IRQ_Enable_define*/
#define USART_IRQ_Enable_NONE               (uint32_t)(0)
#define USART_IRQ_Enable_TXE                (uint32_t)(1<<7)  //Transmitter enable (Data Register Empty)
#define USART_IRQ_Enable_TC                 (uint32_t)(1<<6)  //Transmission complete interrupt enable
#define USART_IRQ_Enable_RXNE               (uint32_t)(1<<5)  //Transmitter Complete
#define USART_IRQ_Enable_PE                 (uint32_t)(1<<8)  //Parity Error





/*
 * ========================================================================================
 *                         APIs Supported by "MCAL USART DRIVER"
 * ========================================================================================
 *
 */
#define USART_DIV(PCLK,BaudRate)                (uint32_t)( PCLK/(BaudRate*16) )
#define USART_DIV_MULL_100(PCLK,BaudRate)       (uint32_t)( (25*PCLK/(4*BaudRate)))
#define USART_MANTISSA_MULL_100(PCLK,BaudRate)  (uint32_t)(USART_DIV(PCLK,BaudRate)*100)
#define USART_MANTISSA(PCLK,BaudRate)           (uint32_t)(USART_DIV(PCLK,BaudRate))
#define USART_FRACTION(PCLK,BaudRate)           (uint32_t)(( (USART_DIV_MULL_100(PCLK,BaudRate) - USART_MANTISSA_MULL_100(PCLK,BaudRate)) *16)/100)
#define USART_BRR_REGISTER(PCLK,BaudRate)       ( ((USART_MANTISSA(PCLK,BaudRate))<<4) | (  USART_FRACTION(PCLK,BaudRate)) & 0XF )

enum PoLLing_Mechnism
{
	enable,
	disable
};

void MCAL_UART_INIT(USART_TypeDef* USARTx,USART_Config * UART_Config);
void MCAL_UART_DeINIT(USART_TypeDef* USARTx,USART_Config * UART_Config);
void MCAL_UART_GPIO_Set_Pins(USART_TypeDef* USARTx);
void MCAL_UART_SEND_DATA(USART_TypeDef* USARTx,uint16_t* pTXBuffer,enum PoLLing_Mechnism PollengEn);
void MCAL_UART_RECEIVE_DATA(USART_TypeDef* USARTx,uint16_t* pTXBuffer,enum PoLLing_Mechnism PollengEn);
void MCAL_UART_WAIT_TC(USART_TypeDef* USARTx);

//To Do
//MCAL_USART_LIN_INIT();
//MCAL_USART_INIT();
//MCAL_USART_DMA_INIT();


#endif /* INC_STM32F103C6_USART_DRIVERS_H_ */
