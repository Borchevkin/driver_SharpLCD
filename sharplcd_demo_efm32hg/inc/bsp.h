/*
 * bsp.h
 *
 *
 *      Author: Danil Borchevkin
 */

#ifndef INC_BSP_H_
#define INC_BSP_H_

#define OK					(0x00)
#define NG					(-0x01)
#define DEBUG_BREAK			__asm__("BKPT #0")

void _ErrorHandler(void);

void DelayTicks(uint32_t delayTicks);

void SPI0_SendPacket(uint8_t * pkt, uint16_t len);
void SPI0_SetLSBFirst(void);
void SPI0_SetMSBFirst(void);

void DISPLAY_SetCS(void);
void DISPLAY_ClearCS(void);
void DISPLAY_SetVCOM(void);
void DISPLAY_ClearVCOM(void);
uint8_t DISPLAY_GetVCOM(void);
void DISPLAY_SetDISP(void);
void DISPLAY_ClearDISP(void);

#endif /* INC_BSP_H_ */
