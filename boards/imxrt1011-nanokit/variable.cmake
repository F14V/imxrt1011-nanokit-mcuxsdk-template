mcux_set_variable(board imxrt1011-nanokit)

if (NOT DEFINED device)
    mcux_set_variable(device MIMXRT1011)
endif()

if (NOT DEFINED soc_series)
    mcux_set_variable(soc_series RT1010)
endif()

if (NOT DEFINED soc_portfolio)
    mcux_set_variable(soc_portfolio RT)
endif()

if (NOT DEFINED device_root)
    mcux_set_variable(device_root devices)
endif()

include(${SdkRootDirPath}/${device_root}/${soc_portfolio}/${soc_series}/${device}/variable.cmake)
