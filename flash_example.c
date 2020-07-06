#include <stdio.h>
#include <stdint.h>

#include "flash_driver/flash_driver.h"

void user_callback(ErrorCode_t code)
{
    printf("callback: error %d\n", code);
}

int main(void)
{
    // printf only used for demo/testing purpose, on microcontroller disable stdio.h and use dedicated logging
    printf("Flash example start\n");

    uint32_t page_number = 12;
    S_Array_t data_to_write = {0};

    FlashDriver_Init(user_callback);
    ErrorCode_t err = FlashDriver_Write(page_number, data_to_write, user_callback);
    if (err != SUCCESS)
    {
        printf("Flash write failed with code %d\n", err);
    }

    return 0;
}

