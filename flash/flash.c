#include <stdint.h>

#include "flash.h"

/* In API there is no pointer to flash module instance, so it only has
 * one instance in the program.
 */
static Flash_t flash;

void FlashDriver_Init(FlashDriverCallback callback)
{
    if (callback)
    {
        flash.callback = callback;
    }
}

/**
 * @brief Write data to flash.
 * @param page_number Page number You write to.
 * @param data Data to be written
 * @param callback Called on operation finish
 */
ErrorCode_t FlashDriver_Write(uint32_t page_number, S_Array_t data, FlashDriverCallback callback)
{
    if (flash.pending)
    {
       return PENDING;
    }

    flash.pending = true;

    // write data

    flash.callback(SUCCESS);
    flash.pending = false;

    return SUCCESS;
}
