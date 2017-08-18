/*
 * sharplcd.c
 *
 *  Created on: 17 рту. 2017 у.
 *      Author: User
 */

#include <stdint.h>
#include <stdbool.h>

void SHARPLCD_Init(sharplcd_t * sharplcd)
{
	//Calculate values for struct

	//Set CS to inactive

	//Set DISP to inactive
}

void SHARPLCD_Clear(sharplcd_t * sharplcd)
{

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
	//1. Pullup CS line for select display
	sharplcd->SetCS();

	//2. Send number of line. Warning! Number of line starts from 1!
	sharplcd->Write(lineNo + 1, 1);

	//2. Set proper byte order - MSB for data
	sharplcd->SetMSBFirst();

	//3. Write line data
	sharplcd->Write(lineArray, sharplcd->bytesPerLine);

	//4. Clear CS
	sharplcd->ClearCS();

	//4. Set LSB byte order again
	sharplcd->SetLSBFirst();
}
