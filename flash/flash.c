#include <stdint.h>

#include "flash.h"

/* In API there is no pointer to flash module instance, so it only has
 * one instance in the program.
 */
static Flash_t flash;

void FlashDriver_Init(FlashDriverCallback callback)
{
    flash.callback = callback;
}

/**
 * @brief Write data to flash.
 * @param page_number Page number You write to.
 * @param data Data to be written
 * @param callback Called on operation finish
 */
ErrorCode_t FlashDriver_Write(uint32_t page_number, S_Array_t data, FlashDriverCallback callback)
{
    flash.callback(SUCCESS);
}
