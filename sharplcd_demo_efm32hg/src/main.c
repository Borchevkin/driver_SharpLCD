#include <stdbool.h>
#include <stdint.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_usart.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "InitDevice.h"
#include "bsp.h"

/* Global vars */
volatile uint32_t systime = 0;

/* Prototypes section */
void TEST_SpiConnection();
void TEST_DisplayLine();
void TEST_DisplayRect();
void TEST_DisplayText(char * text, uint8_t len);

/* Main Section */
int main(void)
{
	/* Chip errata */
	CHIP_Init();

	/* Apply Configurator routines */
	enter_DefaultMode_from_RESET();

	/*---------------------- Init section-------------------------- */
	/* Init Systick with interrupt every 1 ms*/
	if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000))
	{
		_ErrorHandler();
	}

	/* ------------------------------------------------------------ */

	/* Infinite loop */
	while (1)
	{
		// Toggle LED
		GPIO_PinOutToggle(LED0_PORT, LED0_PIN);
		DelayTicks(100);

		TEST_SpiConnection();
	}
}

/* Interrupt Handlers Section */
void SysTick_Handler(void)
{
      /*Increment systime */
      systime++;
}

/* Test Sections */
void TEST_SpiConnection()
{
	uint8_t testPacket[4] = {0x11, 0x22, 0x33, 0x44};
	SPI0_SendPacket((uint8_t *)testPacket, 4);
}

void TEST_DisplayLine()
{

}

void TEST_DisplayRect()
{

}

void TEST_DisplayText(char * text, uint8_t len)
{

}
