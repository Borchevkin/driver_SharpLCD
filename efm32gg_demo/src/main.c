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
	sharplcd.Write = SPI1_SendPacket;
	sharplcd.SetCS = DISPLAY_SetCS;
	sharplcd.ClearCS = DISPLAY_ClearCS;
	sharplcd.SetVCOM = DISPLAY_SetVCOM;
	sharplcd.ClearVCOM = DISPLAY_ClearVCOM;
	//sharplcd.GetVCOM = DISPLAY_GetVCOM;
	sharplcd.SetDISP = DISPLAY_SetDISP;
	sharplcd.ClearDISP = DISPLAY_ClearDISP;
	sharplcd.SetLSBFirst = SPI1_SetLSBFirst;
	sharplcd.SetMSBFirst = SPI1_SetMSBFirst;
	sharplcd.DelayMs = Delay;
	SHARPLCD_Init(&sharplcd);

	//Set Display ON
	DISPLAY_SetDISP();

	while (1)
	{
		//Straight line
		uint8_t line_1[12] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

		//LEDs
		GPIO_PinOutToggle(LED0_PORT, LED0_PIN);
		GPIO_PinOutToggle(LED1_PORT, LED1_PIN);

		// ========== Test Field

		SHARPLCD_WriteLine(&sharplcd, 2, line_1);
		Delay(500);
		SHARPLCD_WriteLine(&sharplcd, 4, line_1);
		Delay(500);
		SHARPLCD_WriteLine(&sharplcd, 3, line_1);
		Delay(500);
		SHARPLCD_Clear(&sharplcd);
		Delay(500);
	}
}
/* ============================================================ */
