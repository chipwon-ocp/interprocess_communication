/**
 * @file tty.c
 * @brief An application is demonstrating the communication between two cores.
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
#include "msg_comm.h"
#include "FreeRTOS.h"
#include "task.h"
#include "mhu_control.h"
#include "services_lib_interface.h"

/*******************************************************************************
 * Private macros, defines, enumerations, structures(with typedefs)
 ******************************************************************************/

/*******************************************************************************
 * Private typedefs
 ******************************************************************************/
#define CONSOLE_RX_BUFF_SIZE    (32)
#define SERVICES_MSG_BUFF_SIZE  (128) // Message buffer for 'north<->south' comms.

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
msg_comm_main(void *p_argument)
{
    (void)p_argument;

    uint32_t error_code = SERVICES_REQ_SUCCESS;
    uint32_t rnd_value = 0;
    int32_t service_error_code = 0;
    payload_t msg_from_he;
    const TickType_t tick_delay = (3000 / portTICK_PERIOD_MS);

    vTaskDelay(1 / portTICK_PERIOD_MS);

    printf("[M55HP] Message communication running!\n");

    MhuInit();

    for (uint32_t loop_cntr = 1; ; loop_cntr++) {
        printf("[M55HP]\n");
        printf("[M55HP]\n");
        printf("[M55HP] Round %d...\n", loop_cntr);
        vTaskDelay(tick_delay);

        printf("[M55HP] Create a communication through MHUs in RTSS world.\n");
        MhuReceiveMsg();
        MhuGetPayload(&msg_from_he);
        printf("[M55HP] \x1B[1;92mTurtle     <\x1B[0m \"%s\"\n", msg_from_he.msg);
        vTaskDelay(tick_delay);
        MhuSendUserMsg("Rabbit echo! What is your instruction? Over!");
        printf("[M55HP] \x1B[1;93mMe         >\x1B[0m \"%s\"\n", "Rabbit echo! What is your instruction? Over!");
        MhuReceiveMsg();
        MhuGetPayload(&msg_from_he);
        printf("[M55HP] \x1B[1;92mTurtle     <\x1B[0m \"%s\"\n", msg_from_he.msg);
        vTaskDelay(tick_delay);
        MhuSendUserMsg("Roger that! Over and out!");
        printf("[M55HP] \x1B[1;93mMe         >\x1B[0m \"%s\"\n", "Roger that! Over and out!");

        printf("[M55HP] Spinning in HP thread. Get a random number via MHUs from SESS.\n");
        error_code = SERVICES_cryptocell_get_rnd(services_handle, sizeof(uint32_t), &rnd_value, &service_error_code);
        printf("[M55HP] Random Value = %08Xh; Service error code = %d\n", rnd_value, service_error_code);

        SERVICES_wait_ms(100);
        __WFI();

        vTaskDelay(tick_delay);
        vTaskDelay(tick_delay);
        vTaskDelay(tick_delay);
    }

    printf("[M55HE] Message communication leaving!\n");
}

/*******************************************************************************
 * Static functions
 ******************************************************************************/

/*** end of file ***/
