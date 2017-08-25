#include <stdbool.h>
#include <stdint.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_usart.h"
#include "InitDevice.h"
#include "sharpLCD.h"
#include "bsp.h"

sharplcd_t sharplcd;
/* =====Counts 1ms timeTicks===== */
volatile uint32_t msTicks = 0;

/* =====Interrupt Handlers Section===== */
void SysTick_Handler(void)
{
	msTicks++;
}

/* =====================Main Section===================== */
int main(void)
{
	// Chip errata
	CHIP_Init();
	enter_DefaultMode_from_RESET();

	SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000);

	// Init Display
	SHARPLCD_Init();

	//Set Display ON
	DISPLAY_SetDISP();

	while (1)
	{
		//Straight line
		uint8_t line_1[12] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

		//LEDs
		GPIO_PinOutToggle(LED0_PORT, LED0_PIN);
		GPIO_PinOutToggle(LED1_PORT, LED1_PIN);

		//Lines

		// ========== Not working for now
		DISPLAY_WriteLine(line_1, 12, 2, 0x40);
		Delay(500);

		DISPLAY_WriteLine(line_1, 12, 4, 0x00);
		Delay(500);

		DISPLAY_WriteLine(line_1, 12, 6, 0x40);
		Delay(500);

		DISPLAY_WriteLine(line_1, 12, 8, 0x00);
		Delay(500);

		DISPLAY_WriteLine(line_1, 12, 10, 0x40);
		Delay(500);

		//Clear display
		DISPLAY_Clear(0x00);

		Delay(500);
	}
}
/* ============================================================ */
