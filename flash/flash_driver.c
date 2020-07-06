#include <stdint.h>

#include "flash_driver.h"

/* In API there is no pointer to flash module instance, so it only has
 * one instance in the program.
 */

typedef struct FlashControlBlock_type
{
    FlashDriverCallback callback; ///< Function called after flash operation has finished
    bool pending;                 ///< Flag indicating if operation is pending in driver
} Flash_t;

static Flash_t flash;

void FlashDriver_Init(FlashDriverCallback callback)
{
    if (callback)
    {
        flash.callback = callback;
    }

    flash.callback(SUCCESS);
}

ErrorCode_t FlashDriver_Write(uint32_t page_number, S_Array_t data, FlashDriverCallback callback)
{
    if (flash.pending)
    {
       return PENDING;
    }

    flash.pending = true;

    // Check if page is available
    if (page_number > (FLASH_REGION_END / PAGE_SIZE))
    {
        return INVALID_ARGS;
    }

    // Check if data fits page size
    if (data.size > PAGE_SIZE)
    {
        return INVALID_ARGS;
    }

    // Write flash

    flash.callback(SUCCESS);
    flash.pending = false;

    return SUCCESS;
}
