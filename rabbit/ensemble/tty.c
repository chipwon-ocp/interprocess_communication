/**
 * @file tty.c
 * @brief A thread is demonstrating being used for teletype or teletypewriter.
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
#include "tty.h"
#include "cmsis_os2.h"

/*******************************************************************************
 * Private macros, defines, enumerations, structures(with typedefs)
 ******************************************************************************/

/*******************************************************************************
 * Private typedefs
 ******************************************************************************/

/*******************************************************************************
 * Global variables
 ******************************************************************************/

/*******************************************************************************
 * Static variables
 ******************************************************************************/
static volatile bool sb_exit                = false;
static uint8_t       s_runtime_cursor_idx   = 0u;
static const char    s_runtime_cursor_tbl[] = {'-', '\\', '|', '/'};

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
tty_main(void *p_argument)
{
    (void)p_argument;
    osDelay (100);
    printf("[M55HP] TTY running!\n");
    for (; false == sb_exit;)
    {
        s_runtime_cursor_idx++;
        s_runtime_cursor_idx %= (sizeof(s_runtime_cursor_tbl) / sizeof(char));
        printf("\x1B[?25l%c\b", s_runtime_cursor_tbl[s_runtime_cursor_idx]);
        fflush(stdout);
        osDelay (1000);
    }
    printf("[M55HP] TTY leaving!\n");
}

/*******************************************************************************
 * Static functions
 ******************************************************************************/

/*** end of file ***/
