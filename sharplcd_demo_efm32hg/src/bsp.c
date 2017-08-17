/*
 * bsp.c
 *
 *  Created on: 17 рту. 2017 у.
 *      Author: Danil Borchevkin
 */

#include <stdint.h>
#include "em_usart.h"
#include "em_gpio.h"
#include "InitDevice.h"
#include "bsp.h"

extern uint32_t systime;

void _ErrorHandler(void)
{
	DEBUG_BREAK;
}

void DelayTicks(uint32_t delayTicks)
{
	uint32_t currentTicks;

	currentTicks = systime;
	while ((systime - currentTicks) < delayTicks);
}

void SPI0_SendPacket(uint8_t * pkt, uint16_t len)
{
	for (uint8_t i = 0; i < len; i++)
	{
		USART_SpiTransfer(USART0, *pkt);
		pkt++;
	}
}

void SPI0_SetLSBFirst(void)
{
	//TODO
	//Check docs and appnote
	USART0->CTRL &= ~USART_CTRL_MSBF;
}

void SPI0_SetMSBFirst(void)
{
	//TODO
	//Check docs and appnote
	USART0->CTRL |= USART_CTRL_MSBF;
}

void DISPLAY_SetCS(void)
{
	GPIO_PinOutSet(SHARPLCD_CS_PORT, SHARPLCD_CS_PIN);
}

void DISPLAY_ClearCS(void)
{
	GPIO_PinOutClear(SHARPLCD_CS_PORT, SHARPLCD_CS_PIN);
}

void DISPLAY_SetVCOM(void)
{
	GPIO_PinOutSet(SHARPLCD_VCOM_PORT, SHARPLCD_VCOM_PIN);
}

void DISPLAY_ClearVCOM(void)
{
	GPIO_PinOutClear(SHARPLCD_VCOM_PORT, SHARPLCD_VCOM_PIN);
}

uint8_t DISPLAY_GetVCOM(void)
{
	//TODO
	uint8_t result = 0;

	return result;
}

void DISPLAY_SetDISP(void)
{
	GPIO_PinOutSet(SHARPLCD_DISP_PORT, SHARPLCD_VCOM_PIN);
}

void DISPLAY_ClearDISP(void)
{
	GPIO_PinOutClear(SHARPLCD_DISP_PORT, SHARPLCD_VCOM_PIN);
}
