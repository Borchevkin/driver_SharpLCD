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

#include "font.h"

sharplcd_t sharplcd;

// ========================== TEST

void SHARPLCD_AddLineToBuff(uint8_t x1, uint8_t x2, uint8_t y);
void SHARPLCD_AddRectToBuff(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2);
void SHARPLCD_AddTextToBuff(const char* text, uint8_t lineNo, uint8_t options);
uint8_t m_buffer[12];

void ClearFrameBuffer(void);

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
		SHARPLCD_RectangleFilled(&sharplcd, 0, 4, 18, 22);
		Delay(500);
		SHARPLCD_Bitmap(&sharplcd, battery_20, 16, 8, 0, 1);
		SHARPLCD_RectangleFilled(&sharplcd, 4, 8, 18, 22);
		Delay(500);
		SHARPLCD_Bitmap(&sharplcd, battery_40, 16, 8, 0, 1);
		SHARPLCD_RectangleFilled(&sharplcd, 8, 12, 18, 22);
		Delay(500);
		SHARPLCD_Bitmap(&sharplcd, battery_60, 16, 8, 0, 1);
		SHARPLCD_RectangleFilled(&sharplcd, 12, 16, 18, 22);
		Delay(500);
		SHARPLCD_Bitmap(&sharplcd, battery_80, 16, 8, 0, 1);
		SHARPLCD_RectangleFilled(&sharplcd, 16, 20, 18, 22);
		Delay(500);
		SHARPLCD_Bitmap(&sharplcd, battery_100, 16, 8, 0, 1);
		SHARPLCD_RectangleFilled(&sharplcd, 20, 24, 18, 22);


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


		Delay(500);
		SHARPLCD_Bitmap(&sharplcd, frameBuffer, 96, 96, 0, 1);
		Delay(500);

		SHARPLCD_AddLineToBuff(20,80,40);
		SHARPLCD_Bitmap(&sharplcd, frameBuffer, 96, 96, 0, 1);
		Delay(500);

		SHARPLCD_AddLineToBuff(40,60,40);
		SHARPLCD_Bitmap(&sharplcd, frameBuffer, 96, 96, 0, 1);
		Delay(500);

		SHARPLCD_AddRectToBuff(30,60,20,50);
		SHARPLCD_Bitmap(&sharplcd, frameBuffer, 96, 96, 0, 1);
		Delay(500);

		SHARPLCD_AddRectToBuff(45,75,10,40);
		SHARPLCD_Bitmap(&sharplcd, frameBuffer, 96, 96, 0, 1);
		Delay(500);

		SHARPLCD_AddTextToBuff("    TEXT   ",30,1);
		SHARPLCD_Bitmap(&sharplcd, frameBuffer, 96, 96, 0, 1);
		Delay(500);

		ClearFrameBuffer();
		SHARPLCD_Bitmap(&sharplcd, frameBuffer, 96, 96, 0, 1);
	}
}


// ============================ TEST FIELD

void ClearFrameBuffer()
{
	int z = 0;
	int w = 0;
	while(z < 95)
	{
		frameBuffer[z][w] = 0xff;
		w++;
		if (w > 11)
		{
			w = 0;
			z++;
		}
	}
}

void SHARPLCD_AddLineToBuff(uint8_t x1, uint8_t x2, uint8_t y)
{
	uint16_t LineBuffer[12] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	uint16_t xi = 0;


	int x_index_min = x1 >> 3;
	int x_index_max = x2 >> 3;
	int ucfirst_x_byte, uclast_x_byte;

	ucfirst_x_byte = (0xFF >> (x1 & 0x7));
	uclast_x_byte = (0xFF << (7 - (x2 & 0x7)));


	if(x_index_min != x_index_max)
	{
	LineBuffer[x_index_min] = ~ucfirst_x_byte;
	xi = x_index_min + 1;

	//write middle bytes
	for(; xi < x_index_max - 1; xi++)
	{
		LineBuffer[xi] = 0x00;
	}
	LineBuffer[xi] = 0x00;

	//write last byte
	LineBuffer[x_index_max] = ~uclast_x_byte;
	}
	else
	{
		ucfirst_x_byte &= uclast_x_byte;
		LineBuffer[x_index_min] = ~ucfirst_x_byte;
	}

	while (x_index_min < x_index_max)
	{
		frameBuffer[y][x_index_min] &= LineBuffer [x_index_min];
		x_index_min++;
	}
	frameBuffer[y][x_index_min] &= LineBuffer [x_index_min];
}

void SHARPLCD_AddRectToBuff(uint8_t x1, uint8_t x2, uint8_t y1, uint8_t y2)
{
	while (y1 < y2)
	{
		SHARPLCD_AddLineToBuff(x1, x2, y1);
		y1++;
	}
	SHARPLCD_AddLineToBuff(x1, x2, y2);
}

void SHARPLCD_AddTextToBuff(const char* text, uint8_t lineNo, uint8_t options)
{
	unsigned char c, b, i, j, k, z, w;
	z = 0;
	w = 12;

	k = 0;
	while (k < 8 && lineNo < SHARPLCD_YRES) { // loop for 8 character lines while within display
		i = 0;
		j = 0;
		while (j < (SHARPLCD_XRES/8) && (c = text[i]) != 0) {     // while we did not reach end of line or string
			if (c < ' ' || c > 'Z') {                        // invalid characters are replace with SPACE
				c = ' ';
			}

			c = c - 32;                                      // convert character to index in font table
			b = font8x8[(c*8)+k];                            // retrieve byte defining one line of character

			if (!(options & SHARPLCD_DISP_INVERT)) {                  // invert bits if DISP_INVERT is _NOT_ selected
				b = ~b;// pixels are LOW active
			}

			if (!((options & 2) && (c != 0))) {           // double width rendering if DISP_WIDE and character is not SPACE
				m_buffer[j] = b;                // store pixels in line buffer
				j++;                                      // we've written two bytes to buffer
			}

			i++;                                             // next character
		}

		while (j < (SHARPLCD_XRES/8)) {                           // pad line for empty characters
			m_buffer[j] = 0xff;
			j++;
		}


		while (z < w)
		{
			frameBuffer[lineNo][z] |= m_buffer[z];
			z++;
		}

		z = 0;
		lineNo++;
		k++;                                                 // next pixel line
		}
}

// =======================================
