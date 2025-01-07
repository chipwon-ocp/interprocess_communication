/**
 * @file blinky.h
 * @brief This header file contains the export of LED blink API.
 * @copyright Copyright (c) 2023-2025 ChipWon Technology. All rights reserved.
 */

#ifndef BLINKY_H
#define BLINKY_H

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
void blinky_main(void *p_argument);

#ifdef __cplusplus
}
#endif

#endif /* BLINKY_H */

/*** end of file ***/