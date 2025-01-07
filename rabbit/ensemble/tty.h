/**
 * @file tty.h
 * @brief This header file contains the export of teletype or teletypewriter
 * function.
 * @copyright Copyright (c) 2023-2025 ChipWon Technology. All rights reserved.
 */

#ifndef TTY_H
#define TTY_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*******************************************************************************
 * Macros, defines, enumerations, structures(with typedefs)
 ******************************************************************************/

/*******************************************************************************
 * Typedefs
 ******************************************************************************/

/*******************************************************************************
 * Exported variables
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes
 ******************************************************************************/
void tty_main(void *p_argument);

#ifdef __cplusplus
}
#endif

#endif /* TTY_H */

/*** end of file ***/