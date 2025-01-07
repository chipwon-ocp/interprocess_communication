/**
 * @file msg_comm.h
 * @brief This header file contains the export of main communication routine.
 * @copyright Copyright (c) 2023-2025 ChipWon Technology. All rights reserved.
 */

#ifndef MSG_COMM_H
#define MSG_COMM_H

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
void msg_comm_main(void *p_argument);

#ifdef __cplusplus
}
#endif

#endif /* MSG_COMM_H */

/*** end of file ***/