/**
 * @file main.c
 * @brief An example is demostrated over CMSIS-RTOS2 framework.
 * @copyright Copyright (c) 2023-2025 ChipWon Technology. All rights reserved.
 */

#include "RTE_Components.h"
#include CMSIS_device_header

#include <stdio.h>
#include <time.h>
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "Driver_GPIO.h"
#include "pinconf.h"
#if defined(RTE_CMSIS_Compiler_STDOUT)
#include "retarget_stdout.h"
#else
#if 0 /* comment this out to enable semi-hosting printf. Update the alif.csolution.yaml as well.*/
    #undef printf
    #define printf(...)
#endif 
#endif  /* RTE_CMSIS_Compiler_STDOUT */
#include "board.h"
#include "blinky.h"
#include "tty.h"
#include "msg_comm.h"

TaskHandle_t task_handle_blinky;
TaskHandle_t task_handle_tty;
TaskHandle_t task_handle_msg_comm;

int
main(void)
{
    #if defined(RTE_CMSIS_Compiler_STDOUT_Custom)
    int32_t ret;
    ret = stdout_init();
    if(ret != ARM_DRIVER_OK)
    {
        while(1)
        {
        }
    }
    #endif /* RTE_CMSIS_Compiler_STDOUT_Custom */
    /* System Initialization */
    SystemCoreClockUpdate();
    printf("[M55HP] Build information: %s - %s\n", __DATE__, __TIME__);
    printf("[M55HP] CPU name: %s\n", CPU_NAME);
    printf("[M55HP] System clock: %d Hz\n", SystemCoreClock);
    printf("[M55HP] Enter main!!!\n");
    /* Create application main thread */
    BaseType_t xReturned = xTaskCreate(blinky_main, "rabbit\\blinky", 96, NULL, configMAX_PRIORITIES-1, &task_handle_blinky);
    if (xReturned != pdPASS)
    {
        vTaskDelete(task_handle_blinky);
        printf("[M55HP] Abort main!!!\n");
        return -1;
    }
    xReturned = xTaskCreate(tty_main, "rabbit\\tty", 160, NULL, configMAX_PRIORITIES-1, &task_handle_tty);
    if (xReturned != pdPASS)
    {
        vTaskDelete(task_handle_tty);
        printf("[M55HP] Abort main!!!\n");
        return -1;
    }
    xReturned = xTaskCreate(msg_comm_main, "rabbit\\msg_comm", 256, NULL, 1, &task_handle_msg_comm);
    if (xReturned != pdPASS)
    {
        vTaskDelete(task_handle_msg_comm);
        printf("[M55HP] Abort main!!!\n");
        return -1;
    }
    /* Start thread execution */
    vTaskStartScheduler();
    printf("[M55HP] Exit main!!!\n");
    return 0;
}
