/**
 * @file tty.c
 * @brief An application for LED blink.
 * debugger..
 * @copyright Copyright (c) 2023-2025 ChipWon Technology. All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "RTE_Components.h"
#include CMSIS_device_header

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "blinky.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Driver_GPIO.h"
#include "pinconf.h"

/*******************************************************************************
 * Private macros, defines, enumerations, structures(with typedefs)
 ******************************************************************************/

/*******************************************************************************
 * Private typedefs
 ******************************************************************************/
/* LED1 gpio pins */
#define GPIO6_PORT                      6   /*< Use LED1_R,LED1_B,LED1_R GPIO port >*/
#define PIN2                            2   /*< LED1_R gpio pin >*/
#define PIN5                            5   /*< LED1_G gpio pin >*/
#define PIN6                            6   /*< LED1_B gpio pin >*/

/* GPIO port used for LED1_R, LED1_B & LED1_G */
extern  ARM_DRIVER_GPIO ARM_Driver_GPIO_(GPIO6_PORT);
ARM_DRIVER_GPIO *gpioDrv6 = &ARM_Driver_GPIO_(GPIO6_PORT);

/*******************************************************************************
 * Global variables
 ******************************************************************************/

/*******************************************************************************
 * Static variables
 ******************************************************************************/
static volatile bool sb_exit     = false;
static volatile bool sb_rt_error = false;

/*******************************************************************************
 * Static function prototypes
 ******************************************************************************/

/*******************************************************************************
 * Global functions
 ******************************************************************************/
/**
 * @brief The initialization function for this thread creation.
 * @details The initialization sequence at thread lunched
 */
void
blinky_main(void *p_argument)
{
    (void)p_argument;

    int32_t ret1 = 0;
    int32_t ret2 = 0;
    int32_t ret3 = 0;
    uint8_t LED1_R = PIN2;
    uint8_t LED1_G = PIN5;
    uint8_t LED1_B = PIN6;
    const TickType_t tick_delay = (1000 / portTICK_PERIOD_MS);

    vTaskDelay(20 / portTICK_PERIOD_MS);

    printf("[M55HP] Blinky running!\n");
    /* pinmux configurations for all GPIOs */
    pinconf_set(GPIO6_PORT, LED1_R, PINMUX_ALTERNATE_FUNCTION_0, 0);
    pinconf_set(GPIO6_PORT, LED1_G, PINMUX_ALTERNATE_FUNCTION_0, 0);
    pinconf_set(GPIO6_PORT, LED1_B, PINMUX_ALTERNATE_FUNCTION_0, 0);

    ret1 = gpioDrv6->Initialize(LED1_R, NULL);
    ret2 = gpioDrv6->Initialize(LED1_G, NULL);
    ret3 = gpioDrv6->Initialize(LED1_B, NULL);
    if ((ret1 != ARM_DRIVER_OK) || (ret2 != ARM_DRIVER_OK) || (ret3 != ARM_DRIVER_OK)) {
        printf("[M55HP] ERROR: Failed to initialize!\n");
        sb_exit = true;
    }

    if (false == sb_exit) {
        ret1 = gpioDrv6->PowerControl(LED1_R, ARM_POWER_FULL);
        ret2 = gpioDrv6->PowerControl(LED1_G, ARM_POWER_FULL);
        ret3 = gpioDrv6->PowerControl(LED1_B, ARM_POWER_FULL);
        if ((ret1 != ARM_DRIVER_OK) || (ret2 != ARM_DRIVER_OK) || (ret3 != ARM_DRIVER_OK)) {
            printf("[M55HP] ERROR: Failed to powered full!\n");
            sb_exit = true;
        }
    }

    if (false == sb_exit) {
        ret1 = gpioDrv6->SetDirection(LED1_R, GPIO_PIN_DIRECTION_OUTPUT);
        ret2 = gpioDrv6->SetDirection(LED1_G, GPIO_PIN_DIRECTION_OUTPUT);
        ret3 = gpioDrv6->SetDirection(LED1_B, GPIO_PIN_DIRECTION_OUTPUT);
        if ((ret1 != ARM_DRIVER_OK) || (ret2 != ARM_DRIVER_OK) || (ret3 != ARM_DRIVER_OK)) {
            printf("[M55HP] ERROR: Failed to configure!\n");
            sb_exit = true;
            sb_rt_error = true;
        }
    }

    for (; (false == sb_exit) && (false == sb_rt_error);) {
        /* Toggle LED */
        ret1 = gpioDrv6->SetValue(LED1_R, GPIO_PIN_OUTPUT_STATE_TOGGLE);
        ret2 = gpioDrv6->SetValue(LED1_G, GPIO_PIN_OUTPUT_STATE_TOGGLE);
        ret3 = gpioDrv6->SetValue(LED1_B, GPIO_PIN_OUTPUT_STATE_LOW);
        if ((ret1 != ARM_DRIVER_OK) || (ret2 != ARM_DRIVER_OK) || (ret3 != ARM_DRIVER_OK)) {
            printf("[M55HP] ERROR: Failed to toggle LEDs!\n");
            sb_exit = true;
            sb_rt_error = true;
            break;
        }

        /* delay for 1 Sec */
        vTaskDelay(tick_delay);
    }

    if (true == sb_rt_error) {
        ret1 = gpioDrv6->PowerControl(LED1_R, ARM_POWER_OFF);
        ret2 = gpioDrv6->PowerControl(LED1_G, ARM_POWER_OFF);
        ret3 = gpioDrv6->PowerControl(LED1_B, ARM_POWER_OFF);
        if ((ret1 != ARM_DRIVER_OK) || (ret2 != ARM_DRIVER_OK) || (ret3 != ARM_DRIVER_OK)) {
            printf("[M55H] ERROR: Failed to power off!\n");
        } else {
            printf("[M55HP] LEDs power off.\n");
        }
    }

    if (true == sb_exit) {
        ret1 = gpioDrv6->Uninitialize(LED1_R);
        ret2 = gpioDrv6->Uninitialize(LED1_G);
        ret3 = gpioDrv6->Uninitialize(LED1_B);
        if ((ret1 != ARM_DRIVER_OK) || (ret2 != ARM_DRIVER_OK) || (ret2 != ARM_DRIVER_OK)) {
            printf("[M55HP] ERROR: Failed to un-initialize!\n");
        } else {
            printf("[M55HP] Successfully un-initialized.\n");
        }
    }

    printf("[M55HP] Blinky leaving!\n");
}

/*******************************************************************************
 * Static functions
 ******************************************************************************/

/*** end of file ***/
