#ifndef __FLASH_H__
#define __FLASH_H__

#include <stdint.h>

#include "flash_driver.h"

/*
 *
 */
void FlashInit();

/*
 *
 * @brief Write to flash region using linear addressing mode. This function
 * takes care of splitting the data and writing it to flash pages using flash
 * driver.
 *
 * @param address Start address in flash where data should be written.
 * @param data Pointer to data to be copied.
 * @param data_len Length of data that will be written to flash.
 */
ErrorCode_t FlashWrite(uint32_t address, uint8_t *data, uint32_t data_len);

#endif /* __FLASH_H__ */
