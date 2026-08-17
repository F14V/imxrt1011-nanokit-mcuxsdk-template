#ifndef _BOARD_H_
#define _BOARD_H_


/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The board name */
#define BOARD_NAME "Makerdiary_iMX_RT1011_Nano_Kit"

/*! @brief The flash size */
#define BOARD_FLASH_SIZE (0x1000000U)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/

void BOARD_ConfigMPU(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
