/*
 * bsp.c
 *
 *  Created on: 23 рту. 2017 у.
 *      Author: user
 */

#include <stdint.h>
#include "em_usart.h"
#include "em_gpio.h"
#include "InitDevice.h"
#include "bsp.h"
#include "sharpLCD.h"

extern uint32_t msTicks;

void _ErrorHandler(void)
{
	DEBUG_BREAK;
}

void Delay(uint32_t dlyTicks)
{
	uint32_t curTicks;

	curTicks = msTicks;
	while ((msTicks - curTicks) < dlyTicks) ;
}

void SPI1_SendPacket(uint8_t * pkt, uint16_t len)
{
	for(uint8_t i = 0; i < len; i++)
	{
		USART_SpiTransfer(USART1, *pkt);
		pkt++;
	}
}

void SPI1_SetMSBFirst()
{
	USART1->CTRL |= USART_CTRL_MSBF;
}

void SPI1_SetLSBFirst()
{
	USART1->CTRL &= ~USART_CTRL_MSBF;
}

void DISPLAY_SetCS(void)
{
	GPIO_PinOutSet(LCDCS_PORT, LCDCS_PIN);
}

void DISPLAY_ClearCS(void)
{
	GPIO_PinOutClear(LCDCS_PORT, LCDCS_PIN);
}

void DISPLAY_SetVCOM(void)
{
	GPIO_PinOutSet(VCOM_PORT, VCOM_PIN);
}

void DISPLAY_ClearVCOM(void)
{
	GPIO_PinOutClear(VCOM_PORT, VCOM_PIN);
}

uint8_t DISPLAY_GetVCOM(void)
{
	//TODO
	uint8_t result = 0;

	return result;
}

void DISPLAY_SetDISP(void)
{
	GPIO_PinOutSet(DISP_PORT, DISP_PIN);
}

void DISPLAY_ClearDISP(void)
{
	GPIO_PinOutClear(DISP_PORT, DISP_PIN);
}
