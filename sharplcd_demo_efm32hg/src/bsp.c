/*
 * bsp.c
 *
 *  Created on: 17 ���. 2017 �.
 *      Author: Danil Borchevkin
 */

#include <stdint.h>
#include <bsp.h>

extern uint32_t systime;

void _ErrorHandler(void)
{
	DEBUG_BREAK;
}

void DelayTicks(uint32_t delayTicks)
{
      uint32_t currentTicks;

      currentTicks = systime;
      while ((systime - currentTicks) < delayTicks) ;
}
