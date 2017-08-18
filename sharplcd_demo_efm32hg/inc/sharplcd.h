/*
 * sharplcd.h
 *
 *  Created on: 17 рту. 2017 у.
 *      Author: User
 */

#ifndef INC_SHARPLCD_H_
#define INC_SHARPLCD_H_

/* -------------------DEFINE Section ----------------- */

/* Commands */
#define SHARPLCD_WRITE_CMD		(0x80)
#define SHARPLCD_CLEAR_CMD		(0x20)
#define SHARPLCD_NOP_CMD		(0x00)
/* VCOM defines */
#define SHARPLCD_VCOM_HI_CMD	(0x40)
#define SHARPLCD_VCOM_LO_CMD	(0x00)

#define SHARPLCD_NULL_BYTE		(0x00)
/* --------------------------------------------------- */

/* -------------------Types  Section ----------------- */

/* Types section */
typedef struct {
	/* Parametric values */
	uint16_t xRes;
	uint16_t yRes;

	/* Calculated values */
	uint16_t bytesPerLine;
	uint16_t bufferSize;

	/* Last vaules */

	/* Pointers to functions */
	void (*Write)(uint8_t * pData, uint16_t * len);
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

/* --------------------------------------------------- */

/* -------------------Prototypes Section-------------- */

void SHARPLCD_Init(sharplcd_t * sharplcd);
void SHARPLCD_Clear(sharplcd_t * sharplcd);
void SHARPLCD_SendWriteCommand(sharplcd_t * sharplcd);
void SHARPLCD_SendTrailer(sharplcd_t * sharplcd);
void SHARPLCD_WriteLine(sharplcd_t *sharplcd, uint8_t lineNo, uint8_t * lineArray);
void SHARPLCD_ShowFrame(sharplcd_t *sharplcd, uint8_t frame);
/* --------------------------------------------------- */

#endif /* INC_SHARPLCD_H_ */
