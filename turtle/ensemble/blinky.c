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
/* LED0 gpio pins */
#define GPIO12_PORT                     12  /*< Use LED0_R,LED0_B GPIO port >*/
#define GPIO7_PORT                      7   /*< Use LED0_G GPIO port >*/
#define PIN3                            3   /*< LED0_R gpio pin >*/
#define PIN4                            4   /*< LED0_G gpio pin >*/
#define PIN0                            0   /*< LED0_B gpio pin >*/

/* GPIO port used for LED0_R & LED0_B */
extern  ARM_DRIVER_GPIO ARM_Driver_GPIO_(GPIO12_PORT);
ARM_DRIVER_GPIO *gpioDrv12 = &ARM_Driver_GPIO_(GPIO12_PORT);

/* GPIO port used for LED0_G */
extern  ARM_DRIVER_GPIO ARM_Driver_GPIO_(GPIO7_PORT);
ARM_DRIVER_GPIO *gpioDrv7 = &ARM_Driver_GPIO_(GPIO7_PORT);

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
    uint8_t LED0_R = PIN3;
    uint8_t LED0_G = PIN4;
    uint8_t LED0_B = PIN0;
    const TickType_t tick_delay = (1000 / portTICK_PERIOD_MS);

    vTaskDelay(20 / portTICK_PERIOD_MS);

    printf("[M55HE] Blinky running!\n");
    /* pinmux configurations for all GPIOs */
    pinconf_set(GPIO12_PORT, LED0_R, PINMUX_ALTERNATE_FUNCTION_0, 0);
    pinconf_set(GPIO7_PORT, LED0_G, PINMUX_ALTERNATE_FUNCTION_0, 0);
    pinconf_set(GPIO12_PORT, LED0_B, PINMUX_ALTERNATE_FUNCTION_0, 0);

    ret1 = gpioDrv12->Initialize(LED0_R, NULL);
    ret2 = gpioDrv7->Initialize(LED0_G, NULL);
    ret3 = gpioDrv12->Initialize(LED0_B, NULL);
    if ((ret1 != ARM_DRIVER_OK) || (ret2 != ARM_DRIVER_OK) || (ret3 != ARM_DRIVER_OK)) {
        printf("[M55HE] ERROR: Failed to initialize!\n");
        sb_exit = true;
    }

    if (false == sb_exit) {
        ret1 = gpioDrv12->PowerControl(LED0_R, ARM_POWER_FULL);
        ret2 = gpioDrv7->PowerControl(LED0_G, ARM_POWER_FULL);
        ret3 = gpioDrv12->PowerControl(LED0_B, ARM_POWER_FULL);
        if ((ret1 != ARM_DRIVER_OK) || (ret2 != ARM_DRIVER_OK) || (ret3 != ARM_DRIVER_OK)) {
            printf("[M55HE] ERROR: Failed to powered full!\n");
            sb_exit = true;
        }
    }

    if (false == sb_exit) {
        ret1 = gpioDrv12->SetDirection(LED0_R, GPIO_PIN_DIRECTION_OUTPUT);
        ret2 = gpioDrv7->SetDirection(LED0_G, GPIO_PIN_DIRECTION_OUTPUT);
        ret3 = gpioDrv12->SetDirection(LED0_B, GPIO_PIN_DIRECTION_OUTPUT);
        if ((ret1 != ARM_DRIVER_OK) || (ret2 != ARM_DRIVER_OK) || (ret3 != ARM_DRIVER_OK)) {
            printf("[M55HE] ERROR: Failed to configure!\n");
            sb_exit = true;
            sb_rt_error = true;
        }
    }

    for (; (false == sb_exit) && (false == sb_rt_error);) {
        /* Toggle LED */
        ret1 = gpioDrv12->SetValue(LED0_R, GPIO_PIN_OUTPUT_STATE_LOW);
        ret2 = gpioDrv7->SetValue(LED0_G, GPIO_PIN_OUTPUT_STATE_TOGGLE);
        ret3 = gpioDrv12->SetValue(LED0_B, GPIO_PIN_OUTPUT_STATE_LOW);
        if ((ret1 != ARM_DRIVER_OK) || (ret2 != ARM_DRIVER_OK) || (ret3 != ARM_DRIVER_OK)) {
            printf("[M55HE] ERROR: Failed to toggle LEDs!\n");
            sb_exit = true;
            sb_rt_error = true;
            break;
        }

        /* delay for 1 Sec */
        vTaskDelay(tick_delay);
    }

    if (true == sb_rt_error) {
        ret1 = gpioDrv12->PowerControl(LED0_R, ARM_POWER_OFF);
        ret2 = gpioDrv7->PowerControl(LED0_G, ARM_POWER_OFF);
        ret3 = gpioDrv12->PowerControl(LED0_B, ARM_POWER_OFF);
        if ((ret1 != ARM_DRIVER_OK) || (ret2 != ARM_DRIVER_OK) || (ret3 != ARM_DRIVER_OK)) {
            printf("[M55HE] ERROR: Failed to power off!\n");
        } else {
            printf("[M55HE] LEDs power off.\n");
        }
    }

    if (true == sb_exit) {
        ret1 = gpioDrv12->Uninitialize(LED0_R);
        ret2 = gpioDrv7->Uninitialize(LED0_G);
        ret3 = gpioDrv12->Uninitialize(LED0_B);
        if ((ret1 != ARM_DRIVER_OK) || (ret2 != ARM_DRIVER_OK) || (ret2 != ARM_DRIVER_OK)) {
            printf("[M55HE] ERROR: Failed to un-initialize!\n");
        } else {
            printf("[M55HE] Successfully un-initialized.\n");
        }
    }

    printf("[M55HE] Blinky leaving!\n");
}

/*******************************************************************************
 * Static functions
 ******************************************************************************/

/*** end of file ***/
