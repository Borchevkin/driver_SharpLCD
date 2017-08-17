/*
 * bsp.h
 *
 *  Created on: 17 рту. 2017 у.
 *      Author: User
 */

#ifndef INC_BSP_H_
#define INC_BSP_H_

#define OK					(uint8_t(0x00))
#define NG					(uint8_t(-0x01))
#define DEBUG_BREAK			__asm__("BKPT #0")

void _ErrorHandler(void);

void DelayTicks(uint32_t delayTicks);

int8_t SPI1_SendPacket(uint8_t pkt, uint8_t len);

#endif /* INC_BSP_H_ */
