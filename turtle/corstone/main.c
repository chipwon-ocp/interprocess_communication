/**
 * @file main.c
 * @brief An example is demostrated over CMSIS-RTOS2 framework.
 * @copyright Copyright (c) 2023-2025 ChipWon Technology. All rights reserved.
 */

#include "RTE_Components.h"
#include CMSIS_device_header

#include <stdio.h>
#include <time.h>

int
main(void)
{
    printf("[SEML] Build information: %s - %s\n", __DATE__, __TIME__);
    printf("[SEML] Hello, World!!!\n");
    for (;;)
    {
    }
    return 0;
}
