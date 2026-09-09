/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 * 2017-10-20     ZYH          emmm...setup for HAL Libraries
 */

// <<< Use Configuration Wizard in Context Menu >>>
#ifndef __BOARD_H__
#define __BOARD_H__

#include "ch32h417.h"

#define CH32H416RDU6_CHIP   1
#define CH32H415REU6_CHIP   2
#define CH32H417QEU6_CHIP   3
#define CH32H417MEU6_CHIP   4
#define CH32H417WEU6_CHIP   5


#define CH32H4xx_CHIP     CH32H417QEU6_CHIP
/* board configuration */
#define SRAM_SIZE  255
#define SRAM_END (0x200C0000+512+256 + SRAM_SIZE * 1024)

extern int _ebss;
#define HEAP_BEGIN  ((void *)&_ebss)
#define HEAP_END    (SRAM_END-__stack_size)


void rt_hw_board_init(void);

#endif /* __BOARD_H__ */
