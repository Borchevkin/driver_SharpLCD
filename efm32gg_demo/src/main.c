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
#include "testFrame.h"

sharplcd_t sharplcd;

// ========================== TEST

char heartRate[10];
int hr_curr_1 = 6;
int hr_curr_2 = 0;

char text_buffer[6];
int min_1 = 0;
int sec_1 = 0;
int min_2 = 0;
int sec_2 = 0;

// ===============================

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

	//Clear Display
	SHARPLCD_Clear(&sharplcd);

	//Show Heart
	SHARPLCD_Bitmap(&sharplcd, heart, 96, 96, 0, 1);

	while (1)
	{
		//LEDs
		GPIO_PinOutToggle(LED0_PORT, LED0_PIN);
		GPIO_PinOutToggle(LED1_PORT, LED1_PIN);

		//Display
		Delay(500);
		SHARPLCD_Bitmap(&sharplcd, battery_0, 16, 8, 0, 1);
		Delay(500);
		SHARPLCD_Bitmap(&sharplcd, battery_20, 16, 8, 0, 1);
		Delay(500);
		SHARPLCD_Bitmap(&sharplcd, battery_40, 16, 8, 0, 1);
		Delay(500);
		SHARPLCD_Bitmap(&sharplcd, battery_60, 16, 8, 0, 1);
		Delay(500);
		SHARPLCD_Bitmap(&sharplcd, battery_80, 16, 8, 0, 1);
		Delay(500);
		SHARPLCD_Bitmap(&sharplcd, battery_100, 16, 8, 0, 1);
		Delay(500);

		if (sec_2 > 9)
		{
			sec_2 = 0;
			sec_1++;
		}
		if (sec_1 == 6 && sec_2 == 0)
		{
			sec_1 = 0;
			sec_2 = 0;
			min_2++;
		}

		if (min_2 > 9)
		{
			min_2 = 0;
			min_1++;
		}

		text_buffer[0] = min_1 + '0';
		text_buffer[1] = min_2 + '0';
		text_buffer[2] = ':';
		text_buffer[3] = sec_1 + '0';
		text_buffer[4] = sec_2 + '0';
		text_buffer[5] = 0;

		SHARPLCD_Print(&sharplcd, text_buffer, 9, 0);

		sec_2++;


		if (hr_curr_2 > 9)
		{
			hr_curr_2 = 0;
			hr_curr_1++;
		}

		if (hr_curr_1 == 8 && hr_curr_2 == 0)
		{
			hr_curr_1 = 6;
			hr_curr_2 = 0;
		}

		heartRate[0] = ' ';
		heartRate[1] = ' ';
		heartRate[2] = ' ';
		heartRate[3] = ' ';
		heartRate[4] = 'H';
		heartRate[5] = 'R';
		heartRate[6] = ':';
		heartRate[7] = hr_curr_1 + '0';
		heartRate[8] = hr_curr_2 + '0';
		heartRate[9] = 0;

		SHARPLCD_Print(&sharplcd, heartRate, 80, 0);

		hr_curr_2++;
	}
}
