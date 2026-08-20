#include "app_debug_console.h"
#include "app.h"

#ifdef SDK_DEBUGCONSOLE
#include "fsl_debug_console.h"
#endif

#if defined(SERIAL_PORT_TYPE_USBCDC) && (SERIAL_PORT_TYPE_USBCDC == 1)
#include "usb.h"
#include "usb_device_config.h"
#include "usb_phy.h"

static status_t APP_InitUsbClock(void)
{
#if defined(USB_DEVICE_CONFIG_EHCI) && (USB_DEVICE_CONFIG_EHCI > 0U)
    usb_status_t status = kStatus_USB_Success;

    CLOCK_EnableUsbhs0PhyPllClock(kCLOCK_Usbphy480M, 480000000U);
    CLOCK_EnableUsbhs0Clock(kCLOCK_Usb480M, 480000000U);

    status = USB_EhciPhyInit(kUSB_ControllerEhci0, BOARD_XTAL0_CLK_HZ, NULL);
    if (status != kStatus_USB_Success)
    {
        return kStatus_Fail;
    }
#endif

    return kStatus_Success;
}
#endif

status_t APP_InitDebugConsole(void)
{
    status_t status;

#if defined(SERIAL_PORT_TYPE_USBCDC) && (SERIAL_PORT_TYPE_USBCDC == 1)
    status = APP_InitUsbClock();
    if (status != kStatus_Success)
    {
        return status;
    }

    status = DbgConsole_Init(kSerialManager_UsbControllerEhci0, 0U, kSerialPort_UsbCdc, 0U);
#elif defined(SERIAL_PORT_TYPE_UART) && (SERIAL_PORT_TYPE_UART == 1)
    status = DbgConsole_Init(1U, LPUART1_config.baudRate_Bps, kSerialPort_Uart, LPUART1_CLOCK_SOURCE);
#else
    status = kStatus_Success;
#endif

    return status;
}
