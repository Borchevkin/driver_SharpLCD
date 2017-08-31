/*
 * bsp.h
 *
 *  Created on: 23 рту. 2017 у.
 *      Author: user
 */

#ifndef INC_BSP_H_
#define INC_BSP_H_

#define OK					(0x00)
#define NG					(-0x01)
#define DEBUG_BREAK			__asm__("BKPT #0")

void _ErrorHandler(void);

void Delay(uint32_t dlyTicks);

void SPI1_SendPacket(uint8_t * pkt, uint16_t len);
void SPI1_SetLSBFirst(void);
void SPI1_SetMSBFirst(void);

void DISPLAY_SetCS(void);
void DISPLAY_ClearCS(void);
void DISPLAY_SetVCOM(void);
void DISPLAY_ClearVCOM(void);
uint8_t DISPLAY_GetVCOM(void);
void DISPLAY_SetDISP(void);
void DISPLAY_ClearDISP(void);

#endif /* INC_BSP_H_ */
