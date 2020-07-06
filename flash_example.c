#include <stdio.h>
#include <stdint.h>

#include "flash/flash.h"

#define TEST_DATA_LEN 6000
#define TEST_DATA_LEN_TOO_BIG 32000

int main(void)
{
    // printf only used for demo/testing purpose, on microcontroller disable stdio.h and use dedicated logging
    printf("Flash example start\n");

    FlashInit();

    // Generate data
    uint8_t data[TEST_DATA_LEN];
    for (int i = 0; i < TEST_DATA_LEN; i++)
    {
        data[i] = i % 0xFF;
    }

    ErrorCode_t err = FlashWrite(1000, data, TEST_DATA_LEN);
    if (err != SUCCESS)
    {
        goto error;
    }

    // Too much data, write should fail.
    uint8_t empty_data[TEST_DATA_LEN_TOO_BIG];
    err = FlashWrite(2048, empty_data, TEST_DATA_LEN_TOO_BIG);
    if (err != SUCCESS)
    {
        goto error;
    }

    return 0;

error:
    printf("Flash operation failed with error %d\n", err);
}

