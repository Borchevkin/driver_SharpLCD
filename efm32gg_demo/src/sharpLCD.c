/*
 * sharpLCD.c
 *
 *  Created on: 23 ���. 2017 �.
 *      Author: user
 */

#include <stdint.h>
#include <stdbool.h>
#include "sharpLCD.h"
#include "font.h"

void SHARPLCD_Init(sharplcd_t * sharplcd)
{
	//Calculate values for struct
	sharplcd->xRes = SHARPLCD_XRES;
	sharplcd->yRes = SHARPLCD_YRES;
	sharplcd->bytesPerLine = SHARPLCD_BYTES_LINE;
	sharplcd->bufferSize = SHARPLCD_BUF_SIZE;
	sharplcd->currentVcom = 0;

	//Set CS to inactive

	//Set DISP to inactive

}

void SHARPLCD_ToggleVCOM(sharplcd_t * sharplcd)
{
	sharplcd->currentVcom ^= SHARPLCD_VCOM_TOGGLE_CMD;
}

void SHARPLCD_Clear(sharplcd_t * sharplcd)
{
	uint8_t buffer[1];

	//1. Set MSB byte order for command
	sharplcd->SetMSBFirst();

	//2. Pullup CS line for select display
	sharplcd->SetCS();

	//3. Write command
	buffer[0] = SHARPLCD_CLEAR_CMD | sharplcd->currentVcom;
	SHARPLCD_ToggleVCOM(sharplcd);
	sharplcd->Write(buffer, 1);

	//4. Set proper byte order - LSB for line number and data
	sharplcd->SetLSBFirst();

	//5. Write trailer
	buffer[0] = SHARPLCD_NULL_BYTE;
	sharplcd->Write(buffer, 1);

	//6. Clear CS
	sharplcd->ClearCS();

	//7. Set MSB byte order again
	sharplcd->SetMSBFirst();
}

void SHARPLCD_ShowFrame(sharplcd_t *sharplcd, uint8_t frame)
{

}

void SHARPLCD_SendWriteCommand(sharplcd_t * sharplcd)
{

}

void SHARPLCD_SendTrailer(sharplcd_t * sharplcd)
{

}

void SHARPLCD_WriteLine(sharplcd_t *sharplcd, uint8_t lineNo, uint8_t * lineArray)
{
	uint8_t buffer[1];

	//1. Set MSB byte order for command
	sharplcd->SetMSBFirst();

	//2. Pullup CS line for select display
	sharplcd->SetCS();

	//3. Write command
	buffer[0] = SHARPLCD_WRITE_CMD | sharplcd->currentVcom;
	SHARPLCD_ToggleVCOM(sharplcd);
	sharplcd->Write(buffer, 1);

	//4. Set proper byte order - LSB for line number and data
	sharplcd->SetLSBFirst();

	//5. Send number of line. Warning! Number of line starts from 1!
	buffer[0] = lineNo + 1;
	sharplcd->Write(buffer, 1);

	//6. Set back MSB
	sharplcd->SetMSBFirst();

	//7. Write line data
	sharplcd->Write(lineArray, sharplcd->bytesPerLine);

	//8. Trailer
	buffer[0] = SHARPLCD_NULL_BYTE;
	sharplcd->Write(buffer, 1);
	sharplcd->Write(buffer, 1);

	//9. Clear CS
	sharplcd->ClearCS();
}

void SHARPLCD_WriteBuffer(sharplcd_t *sharplcd, uint8_t lineNo)
{
	if (lineNo > SHARPLCD_YRES) return;

	uint8_t buffer[1];

	//1. Set MSB byte order for command
	sharplcd->SetMSBFirst();

	//2. Pullup CS line for select display
	sharplcd->SetCS();

	//3. Write command
	buffer[0] = SHARPLCD_WRITE_CMD | sharplcd->currentVcom;
	SHARPLCD_ToggleVCOM(sharplcd);
	sharplcd->Write(buffer, 1);

	//4. Set proper byte order - LSB for line number and data
	sharplcd->SetLSBFirst();

	//5. Send number of line. Warning! Number of line starts from 1!
	buffer[0] = lineNo + 1;
	sharplcd->Write(buffer, 1);

	//6. Set back MSB
	sharplcd->SetMSBFirst();

	//7. Write line data
	uint8_t j = 0;
	while (j < (SHARPLCD_XRES/8)) {           // write pixels / 8 bytes
		buffer[0] = sharplcd->m_buffer[j];
		sharplcd->Write(buffer, 1);
		j++;
	}

	//8. Trailer
	buffer[0] = SHARPLCD_NULL_BYTE;
	sharplcd->Write(buffer, 1);
	sharplcd->Write(buffer, 1);

	//9. Clear CS
	sharplcd->ClearCS();
}

void SHARPLCD_Bitmap(sharplcd_t *sharplcd, const unsigned char* bitmap, uint8_t width, uint8_t height, uint8_t lineNo, uint8_t options)
{
	//1. Set MSB byte order for command
	sharplcd->SetMSBFirst();

	if (!bitmap) return;

	uint16_t b;
	uint16_t i = 0;
	uint16_t p = 0;
	uint16_t x = width/8;

	while (height > 0 && lineNo < SHARPLCD_YRES) {
		while (i < SHARPLCD_XRES/8 && i < x) {
			b = bitmap[p+i];
			if (!(options & SHARPLCD_DISP_INVERT)) {         // invert bits if DISP_INVERT is _NOT_ selected
				b = ~b;// pixels are LOW active
			}
			sharplcd->m_buffer[i] = b;
			i++;
		}
		SHARPLCD_WriteBuffer(sharplcd, lineNo);
		p += x;
		i = 0;
		height--;
		lineNo++;
	}
}

void SHARPLCD_Print(sharplcd_t *sharplcd, const char* text, uint8_t lineNo, uint8_t options)
{
	//1. Set MSB byte order for command
	sharplcd->SetMSBFirst();

	// c = char
	// b = bitmap
	// i = text index
	// j = line buffer index
	// k = char line
	unsigned char c, b, i, j, k;

	// rendering happens line-by-line because this display can only be written by line
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
				sharplcd->m_buffer[j] = b;                // store pixels in line buffer
				j++;                                      // we've written two bytes to buffer
			}

			i++;                                             // next character
		}

		while (j < (SHARPLCD_XRES/8)) {                           // pad line for empty characters
			sharplcd->m_buffer[j] = 0xff;
			j++;
		}

		SHARPLCD_WriteBuffer(sharplcd, lineNo++);                                 // write line buffer to display

		if ((options & SHARPLCD_DISP_HIGH)&& lineNo < SHARPLCD_YRES) {        // repeat line if DISP_HIGH is selected
			SHARPLCD_WriteBuffer(sharplcd, lineNo++);
		}

		k++;                                                 // next pixel line
	}
}

