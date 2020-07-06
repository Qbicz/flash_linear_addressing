#include <stdio.h>
#include <stdint.h>
#include <stdatomic.h>

#include "flash.h"

_Atomic(bool) driver_busy = ATOMIC_VAR_INIT(false);

void UserCallback(ErrorCode_t code)
{
    printf("callback: error code %d\n", code);

    // Driver operation finished
    atomic_flag_clear(&driver_busy);
}

void FlashInit()
{
    atomic_flag_test_and_set(&driver_busy);
    FlashDriver_Init(UserCallback);

    // wait for callback
    while (driver_busy) {;}

    printf("Flash initialized\n");
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

        atomic_flag_test_and_set(&driver_busy);

        printf("Writing page %d, len %d, data @ %p, write_ptr %p\n",
                page, data_to_write.size, data_to_write.data, write_ptr);
        err = FlashDriver_Write(page, data_to_write, UserCallback);
        if (err != SUCCESS)
        {
            printf("Flash write failed with code %d\n", err);
            // Not needed to wait for callback, it's only scheduled when API returns SUCCESS)
            return err;
        }

        // Wait for callback indicating that driver is ready
        while (driver_busy) {;}

        write_ptr += data_to_write.size;
    }

    return err;
}

