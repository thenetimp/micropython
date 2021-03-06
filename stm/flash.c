#include <stdio.h>
#include <stm32f4xx.h>
#include <stm32f4xx_flash.h>
#include "flash.h"

/* Base address of the Flash sectors */
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

static const uint32_t flash_info_table[26] = {
    ADDR_FLASH_SECTOR_0, FLASH_Sector_0,
    ADDR_FLASH_SECTOR_1, FLASH_Sector_1,
    ADDR_FLASH_SECTOR_2, FLASH_Sector_2,
    ADDR_FLASH_SECTOR_3, FLASH_Sector_3,
    ADDR_FLASH_SECTOR_4, FLASH_Sector_4,
    ADDR_FLASH_SECTOR_5, FLASH_Sector_5,
    ADDR_FLASH_SECTOR_6, FLASH_Sector_6,
    ADDR_FLASH_SECTOR_7, FLASH_Sector_7,
    ADDR_FLASH_SECTOR_8, FLASH_Sector_8,
    ADDR_FLASH_SECTOR_9, FLASH_Sector_9,
    ADDR_FLASH_SECTOR_10, FLASH_Sector_10,
    ADDR_FLASH_SECTOR_11, FLASH_Sector_11,
    ADDR_FLASH_SECTOR_11 + 0x20000, 0,
};

uint32_t flash_get_sector_info(uint32_t addr, uint32_t *start_addr, uint32_t *size) {
    if (addr >= flash_info_table[0]) {
        for (int i = 0; i < 24; i += 2) {
            if (addr < flash_info_table[i + 2]) {
                if (start_addr != NULL) {
                    *start_addr = flash_info_table[i];
                }
                if (size != NULL) {
                    *size = flash_info_table[i + 2] - flash_info_table[i];
                }
                return flash_info_table[i + 1];
            }
        }
    }
    return 0;
}

#if 0
/**
  * @brief  Gets the sector of a given address
  * @param  None
  * @retval The sector of a given address
  */
uint32_t flash_get_sector(uint32_t addr) {
    if ((addr < ADDR_FLASH_SECTOR_1) && (addr >= ADDR_FLASH_SECTOR_0)) {
        return FLASH_Sector_0;
    } else if ((addr < ADDR_FLASH_SECTOR_2) && (addr >= ADDR_FLASH_SECTOR_1)) {
        return FLASH_Sector_1;
    } else if ((addr < ADDR_FLASH_SECTOR_3) && (addr >= ADDR_FLASH_SECTOR_2)) {
        return FLASH_Sector_2;
    } else if ((addr < ADDR_FLASH_SECTOR_4) && (addr >= ADDR_FLASH_SECTOR_3)) {
        return FLASH_Sector_3;
    } else if ((addr < ADDR_FLASH_SECTOR_5) && (addr >= ADDR_FLASH_SECTOR_4)) {
        return FLASH_Sector_4;
    } else if ((addr < ADDR_FLASH_SECTOR_6) && (addr >= ADDR_FLASH_SECTOR_5)) {
        return FLASH_Sector_5;
    } else if ((addr < ADDR_FLASH_SECTOR_7) && (addr >= ADDR_FLASH_SECTOR_6)) {
        return FLASH_Sector_6;
    } else if ((addr < ADDR_FLASH_SECTOR_8) && (addr >= ADDR_FLASH_SECTOR_7)) {
        return FLASH_Sector_7;
    } else if ((addr < ADDR_FLASH_SECTOR_9) && (addr >= ADDR_FLASH_SECTOR_8)) {
        return FLASH_Sector_8;
    } else if ((addr < ADDR_FLASH_SECTOR_10) && (addr >= ADDR_FLASH_SECTOR_9)) {
        return FLASH_Sector_9;
    } else if ((addr < ADDR_FLASH_SECTOR_11) && (addr >= ADDR_FLASH_SECTOR_10)) {
        return FLASH_Sector_10;
    } else {
        return FLASH_Sector_11;
    }
}
#endif

void flash_write(uint32_t flash_dest, const uint32_t *src, uint32_t num_word32) {
    // unlock
    FLASH_Unlock();

    // Clear pending flags (if any)
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
                    FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);

    // Device voltage range supposed to be [2.7V to 3.6V], the operation will be done by word
    if (FLASH_EraseSector(flash_get_sector_info(flash_dest, NULL, NULL), VoltageRange_3) != FLASH_COMPLETE) {
        /* Error occurred while sector erase.
         User can add here some code to deal with this error  */
        return;
    }

    /* Program the user Flash area word by word ********************************/

    for (int i = 0; i < num_word32; i++) {
        if (FLASH_ProgramWord(flash_dest, *src) == FLASH_COMPLETE)
        {
            flash_dest += 4;
            src += 1;
        }
        else
        {
            /* Error occurred while writing data in Flash memory.
               User can add here some code to deal with this error */
            return;
        }
    }

    // lock
    FLASH_Lock();
}
