if (CONFIG_MCUX_COMPONENT_board.boot_header)
    # mcux_add_source(
    #     SOURCES
    #         ${board}_flexspi_nor_config.c
    #         ${board}_flexspi_nor_config.h
    # )

    # mcux_add_include(
    #     INCLUDES .
    # )

    mcux_add_source(
        BASE_PATH ${SdkRootDirPath}
        SOURCES
            examples/_boards/evkmimxrt1010/xip/evkmimxrt1010_flexspi_nor_config.c
            examples/_boards/evkmimxrt1010/xip/evkmimxrt1010_flexspi_nor_config.h
    )

    mcux_add_include(
        BASE_PATH ${SdkRootDirPath}
        INCLUDES examples/_boards/evkmimxrt1010/xip
    )
endif()

if (CONFIG_MCUX_PRJSEG_module.board.suite)
    mcux_add_configuration(
        TARGETS flexspi_nor_debug flexspi_nor_release
        CC "-DXIP_BOOT_HEADER_ENABLE=1"
        CX "-DXIP_BOOT_HEADER_ENABLE=1"
    )
endif()
