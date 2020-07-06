#include <stdio.h>

#include "flash.h"

void user_callback(ErrorCode_t code)
{
    // Note: Called from separate context.

    printf("callback: error %d\n", code);

    // set a flag to indicate operation done
}

void FlashInit()
{
    FlashDriver_Init(user_callback);
}

ErrorCode_t FlashWrite(uint32_t address, uint8_t *data, uint32_t data_len)
{
    printf("addr: %d, len: %d\n", address, data_len);

    // Check if address is within bounds
    if (address > FLASH_REGION_END)
    {
        return INVALID_ARGS;
    }

    // Check if data fits flash region
    if (data_len > FLASH_REGION_END - FLASH_REGION_BEGIN)
    {
        return INVALID_ARGS;
    }

    // Check which pages need to be written
    uint32_t first_page = address / PAGE_SIZE;
    uint32_t last_page = (address + data_len) / PAGE_SIZE;
    printf("first page: %d, last page: %d\n", first_page, last_page);

    ErrorCode_t err = SUCCESS;
    uint8_t *write_ptr = data;

    for (uint32_t page = first_page; page <= last_page; page++)
    {
        if (write_ptr > data + data_len)
        {
            break;
        }

        S_Array_t data_to_write = {0};
        if (page == first_page && page == last_page)
        {
            data_to_write.size = data_len;
        }
        else if (page == first_page)
        {
            data_to_write.size = (page + 1) * PAGE_SIZE - address;
        }
        else if (page == last_page)
        {
            data_to_write.size = (address + data_len - page * PAGE_SIZE);
        }
        else
        {
            data_to_write.size = PAGE_SIZE;
        }

        data_to_write.data = write_ptr;

        // check if operation pending

        printf("Writing page %d, len %d, data @ %p, write_ptr %p\n", page, data_to_write.size, data_to_write.data, write_ptr);
        err = FlashDriver_Write(page, data_to_write, user_callback);
        if (err != SUCCESS)
        {
            printf("Flash write failed with code %d\n", err);
            // Not needed to wait for callback, it's only scheduled when API returns SUCCESS)
            return err;
        }

        // wait for callback, blocking
        // callback should use semaphore to signal that flash is ready. Then we return

        write_ptr += data_to_write.size;
    }

    return err;
}

