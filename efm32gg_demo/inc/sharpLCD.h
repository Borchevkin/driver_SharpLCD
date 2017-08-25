/*
 * sharpLCD.h
 *
 *  Created on: 16 ���. 2017 �.
 *      Author: user
 */

#ifndef INC_SHARPLCD_H_
#define INC_SHARPLCD_H_

#include <stdint.h>

/* ==========DEFINE========== */

//Commands
#define SHARPLCD_WRITE_CMD 	 	0x80	//write line command
#define SHARPLCD_CLEAR_CMD	 	0x20	//clear memory command
#define SHARPLCD_NOP_CMD	 	0x00	//NOP command (used to switch VCOM)
#define SHARPLCD_NULL_BYTE		0x00	//Trailer after command and data

//Resolution
#define SHARPLCD_XRES 			(96)									//pixels per horizontal line
#define SHARPLCD_YRES			(96)									//pixels per vertical line
#define SHARPLCD_BYTES_LINE 	(SHARPLCD_XRES / 8)						//number of bytes in a line
#define SHARPLCD_BUF_SIZE   	(SHARPLCD_YRES * SHARPLCD_BYTES_LINE)

//VCOM defines
#define SHARPLCD_VCOM_HI_CMD 		0x40
#define SHARPLCD_VCOM_LO_CMD 		0x00
#define SHARPLCD_VCOM_TOGGLE_CMD 	0x40

/* ========================== */

/* ==========TYPES========== */

typedef struct {
	/* Parametric values */
	uint16_t xRes;
	uint16_t yRes;

	/* Calculated values */
	uint16_t bytesPerLine;
	uint16_t bufferSize;
	uint8_t currentVcom;

	/* Last values */

	/* Pointers to functions */
	void (*Write)(uint8_t * pData, uint16_t len);
	void (*SetCS)(void);
	void (*ClearCS)(void);
	void (*SetVCOM)(void);
	void (*ClearVCOM)(void);
	_Bool (*GetVCOM)(void);
	void (*SetDISP)(void);
	void (*ClearDISP)(void);
	void (*SetLSBFirst)(void);
	void (*SetMSBFirst)(void);
	void (*DelayMs)(uint32_t delayMs);
} sharplcd_t;

/* ========================= */

/* ==========PROTOTYPES========== */

void SHARPLCD_ToggleVCOM(sharplcd_t * sharplcd);
void SHARPLCD_Init(sharplcd_t * sharplcd);
void SHARPLCD_Clear(sharplcd_t * sharplcd);
void SHARPLCD_SendWriteCommand(sharplcd_t * sharplcd);
void SHARPLCD_SendTrailer(sharplcd_t * sharplcd);
void SHARPLCD_WriteLine(sharplcd_t *sharplcd, uint8_t lineNo, uint8_t * lineArray);
void SHARPLCD_ShowFrame(sharplcd_t *sharplcd, uint8_t frame);
/* ============================== */

#endif /* INC_SHARPLCD_H_ */
