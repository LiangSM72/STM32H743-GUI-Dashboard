/**
 * @file sdram_init.h
 * @brief SDRAM (256MB) initialization header
 */

#ifndef __SDRAM_INIT_H
#define __SDRAM_INIT_H

#include "stm32h7xx_hal.h"

#define SDRAM_BANK_ADDR  0xC0000000  /* SDRAM bank address */
#define SDRAM_SIZE       (256 * 1024 * 1024)  /* 256MB */

void SDRAM_Init(void);
void SDRAM_Test(void);

#endif /* __SDRAM_INIT_H */
