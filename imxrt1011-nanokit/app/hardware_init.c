#include "app.h"

void BOARD_InitHardware(void)
{
    /* Init board MPU */
    BOARD_ConfigMPU();
    /* Init boot clocks */
    BOARD_InitBootClocks();
    /* Init boot pins */
    BOARD_InitBootPins();
    /* Init boot peripherals */
    BOARD_InitBootPeripherals();
}
