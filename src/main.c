#include "app.h"

#ifdef SDK_DEBUGCONSOLE
#include "fsl_debug_console.h"
#include "platform/debug_console/app_debug_console.h"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Main function
 */
int main(void)
{
    status_t status;
    (void)status;

    /* Init board hardware */
    BOARD_InitHardware();

#ifdef SDK_DEBUGCONSOLE
    /* Init debug console */
    status = APP_InitDebugConsole();
    if (status != kStatus_Success)
    {
        return -1;
    }

    PRINTF("MCUX SDK version: %s\r\n", MCUXSDK_VERSION_FULL_STR);
#endif

    while (true)
    {
        __WFI();
    }

    return 0;
}
