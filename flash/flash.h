#ifndef __FLASH_H__
#define __FLASH_H__

#include <stdint.h>

#include "flash_driver.h"

/**
 * @file
 *
 * @defgroup flash Module for writing flash using linear addressing
 * @ingroup flash
 * @{
 *
 * @brief Module lets user request blocking write to flash in linear addressing mode.
*/

/**
 * @brief Initialize flash module. Function works in blocking way.
 */
void FlashInit();

/**
 * @brief Write to flash region using linear addressing mode. This function
 * takes care of splitting the data and writing it to flash pages using flash
 * driver.
 *
 * @note This function is blocking. It will return only when driver has
 * finished operation.
 *
 * @param address Start address in flash where data should be written.
 * @param data Pointer to data to be copied.
 * @param data_len Length of data that will be written to flash.
 */
ErrorCode_t FlashWrite(uint32_t address, uint8_t *data, uint32_t data_len);

#endif /* __FLASH_H__ */
/** @} */
