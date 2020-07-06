#include <stdint.h>

#include "flash.h"

/* In API there is no pointer to flash module instance, so it only has
 * one instance in the program.
 */

typedef struct FlashControlBlock_type
{
    FlashDriverCallback callback; ///< Function called after flash operation has finished
    bool pending;
} Flash_t;

static Flash_t flash;

void FlashDriver_Init(FlashDriverCallback callback)
{
    if (callback)
    {
        flash.callback = callback;
    }
}

ErrorCode_t FlashDriver_Write(uint32_t page_number, S_Array_t data, FlashDriverCallback callback)
{
    if (flash.pending)
    {
       return PENDING;
    }

    flash.pending = true;

    // Check if data fits page size
    if (data.size > PAGE_SIZE)
    {
        return INVALID_ARGS;
    }

    // Write flash
    // (done by 3rd party)

    flash.callback(SUCCESS);
    flash.pending = false;

    return SUCCESS;
}
