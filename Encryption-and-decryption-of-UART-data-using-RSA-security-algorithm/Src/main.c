/******************************************************************************
 * @file           : main.c
 * @author         : Eng : Mostafa Elshiekh -- Learn In Depth
 * @brief          :Context Switching In RTOS -APP(Master/Slave)communications with UART Session 3
 ******************************************************************************/
#include "STM32_F103C6.h"
#include "STM32F103C6_GPIO_DRIVERS.h"
#include "STM32F103C6_USART_DRIVERS.h"
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "semphr.h"
#include "string.h"
#include "RSA_Algorithm.h"





#define UART_1       1
#define UART_2       2



/*Global Variables*/

/*=== RSA Algorithm global Variables ==*/
double euler= 0;
double n=0;
double e=0;
double d = 0;
int Encryption_Message=0;
double Decryption_Message=0;
/*=====================================*/




/*================TASKS HANDELS=================*/
TaskHandle_t xOriginal_massage_Task1_Handle = NULL;
TaskHandle_t xEncryptionTask2_Handle = NULL;
TaskHandle_t xDesplay_EncryptedTask3_Handle = NULL;
/*==============================================*/


/*================Semaphores HANDELS===============*/
SemaphoreHandle_t xSmphor_Dsply_Encrpted_Mess = NULL;
SemaphoreHandle_t xSmphor_Start_Encryption = NULL;
SemaphoreHandle_t xSmphor_Desply_Orig_Mass = NULL;
/*==================================================*/




/*============Tasks Prototype===========*/
void Original_massage_task1(void* params);
void EncryptionTask2(void* params);
void Desplay_EncryptedTask3(void* params);
/*=====================================*/



QueueHandle_t xQueueHandel = NULL;


volatile int USART2_Rcv_Original_Message = 0;
volatile int Temp_Rcv_Ogn_Msg = 0;
char Rec_Data_UART2;
char Buf_Print_Trsm_Org_Msg[50];
char buffer_Encryption[50];
char bufferToSendToUART1[10];
volatile char Flg_Syn_InISR = 0;
char Buff_NewLine[2] = "\n";



void USART2_callBack(void)
{
	MCAL_UART_RECEIVE_DATA(USART2, &Rec_Data_UART2, disable);
	MCAL_UART_SEND_DATA(USART2, &Rec_Data_UART2, disable);
	if(Flg_Syn_InISR == 0)
	{
		// Convert the received string to a decimal value
		Temp_Rcv_Ogn_Msg = atoi(&Rec_Data_UART2) * 10;
		Flg_Syn_InISR = 1;
	}
	else
	{
		// Convert the received string to a decimal value
		USART2_Rcv_Original_Message = Temp_Rcv_Ogn_Msg + atoi(&Rec_Data_UART2);
		xSemaphoreGive(xSmphor_Desply_Orig_Mass);
		xSemaphoreGive(xSmphor_Start_Encryption);
		Flg_Syn_InISR = 0;
	}
}

/*===========Functions Prototype========*/
void Fun_UART_Init(char UARTx);
void RSA_Calc_Init(void);
/*=====================================*/

int main(void)
{
	RCC_GPIOC_CLOCK_EN();
	RCC_GPIOA_CLOCK_EN();
	RCC_AFIO_CLOCK_EN();
	Fun_UART_Init(UART_1);
	Fun_UART_Init(UART_2);

	RSA_Calc_Init();

	strcpy(Buf_Print_Trsm_Org_Msg ,"Transmit The Original Msg: ");
	for (int i = 0; i < strlen(Buf_Print_Trsm_Org_Msg); ++i)
	{
		MCAL_UART_SEND_DATA(USART2,&Buf_Print_Trsm_Org_Msg[i], disable);
	}


	//Semaphores Creation
	xSmphor_Dsply_Encrpted_Mess = xSemaphoreCreateBinary();
	xSmphor_Start_Encryption = xSemaphoreCreateBinary();
	xSmphor_Desply_Orig_Mass = xSemaphoreCreateBinary();


	/*===============Tasks Creation===============*/
	xTaskCreate(Original_massage_task1, "Original_massage_task1", 128, NULL, 1, xOriginal_massage_Task1_Handle);
	xTaskCreate(EncryptionTask2, "EncryptionTask2", 128, NULL, 2, xEncryptionTask2_Handle);
	xTaskCreate(Desplay_EncryptedTask3, "EncryptionTask2", 128, NULL, 2, xDesplay_EncryptedTask3_Handle);


	//Scheduler Start
	vTaskStartScheduler();

	while(1)
	{
	}

	return 0;
}


/*===========Functions Definition========*/
void Fun_UART_Init(char UARTx)
{
	if(UARTx == 1)
	{
		USART_Config uart1CFG;
		uart1CFG.BaudRate = USART_BaudRate_115200;
		uart1CFG.HW_FlowCtrl = USART_HW_FlowCtrl_NONE;
		uart1CFG.IRQ_Enable = USART_IRQ_Enable_RXNE;
		//uart1CFG.P_IRQ_Call_Back = USART1_callBack;
		uart1CFG.Parity = USART_Parity_NONE;
		uart1CFG.PayLoad_Length = USART_PayLoad_Length_8B;
		uart1CFG.StopBits = USART_StopBits_1;
		uart1CFG.USART_MODE = USART_MODE_RX_AND_TX;
		MCAL_UART_INIT(USART1, &uart1CFG);
		MCAL_UART_GPIO_Set_Pins(USART1);
	}
	else if (UARTx == 2)
	{
		USART_Config uartCFG;
		uartCFG.BaudRate = USART_BaudRate_115200;
		uartCFG.HW_FlowCtrl = USART_HW_FlowCtrl_NONE;
		uartCFG.IRQ_Enable = USART_IRQ_Enable_RXNE;
		uartCFG.P_IRQ_Call_Back = USART2_callBack;
		uartCFG.Parity = USART_Parity_NONE;
		uartCFG.PayLoad_Length = USART_PayLoad_Length_8B;
		uartCFG.StopBits = USART_StopBits_1;
		uartCFG.USART_MODE = USART_MODE_RX_AND_TX;
		MCAL_UART_INIT(USART2, &uartCFG);
		MCAL_UART_GPIO_Set_Pins(USART2);
	}
}
void RSA_Calc_Init(void)
{
	euler=RSA_Calc_Euler(p,q);
	n=RSA_Calc_N(p,q);
	e=RSA_Generate_e(euler);
	d =RSA_Decryption_Calc_d(euler,e);
}
/*=====================================*/




/*==============System Tasks==========*/
void Original_massage_task1(void* params)
{
	// Buffer to store the string representation of the decimal value
	char buffer[50] ="\nTransmit The Original Msg: ";
	while(1)
	{

		if(xSemaphoreTake(xSmphor_Desply_Orig_Mass , (TickType_t)5)==pdTRUE)
		{
			for (int i = 0; i < strlen(buffer); ++i)
			{
				MCAL_UART_SEND_DATA(USART2,&buffer[i], disable);
			}

		}
		vTaskDelay(100);
	}
}


void EncryptionTask2(void* params)
{
	while(1)
	{
		//Try to take the xSmphor_Start_Encryption
		if(xSemaphoreTake(xSmphor_Start_Encryption , (TickType_t)5)==pdTRUE)
		{
			Encryption_Message = (int)RSA_Encryption(USART2_Rcv_Original_Message, n, e);
			//Give the semaphore when the button state is changed
			xSemaphoreGive(xSmphor_Dsply_Encrpted_Mess);
		}
		vTaskDelay(15);
	}
}



void Desplay_EncryptedTask3(void* params)
{
	while(1)
	{
		//Try to take the xSmphor_Dsply_Encrpted_Mess
		if(xSemaphoreTake(xSmphor_Dsply_Encrpted_Mess , (TickType_t)5)==pdTRUE)
		{
			// Buffer to store the string representation of the decimal value
			strcpy(buffer_Encryption ,"Encrypted massage is : ");
			for (int i = 0; i < strlen(buffer_Encryption); ++i)
			{
				MCAL_UART_SEND_DATA(USART1,&buffer_Encryption[i], disable);
			}

			// Convert decimal value to string
			itoa(Encryption_Message, bufferToSendToUART1, 10);
			for (int i = 0; i < strlen(bufferToSendToUART1); ++i)
			{
				MCAL_UART_SEND_DATA(USART1,&bufferToSendToUART1[i], disable);
			}
			//print new line
			for (int i = 0; i < strlen(Buff_NewLine); ++i)
			{
				MCAL_UART_SEND_DATA(USART1,&Buff_NewLine[i], disable);
			}

		}
		vTaskDelay(30);
	}
}

