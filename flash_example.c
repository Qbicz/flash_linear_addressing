#include <stdio.h>
#include <stdint.h>

#include "flash/flash.h"

#define TEST_DATA_LEN 4000

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

    FlashWrite(1000, data, TEST_DATA_LEN);

    return 0;
}

