if(CONFIG_APP_BOARD_config.memory.use_ocram_for_data)
    mcux_remove_armgcc_linker_script(
        BASE_PATH ${SdkRootDirPath}
        TARGETS flexspi_nor_debug flexspi_nor_release
        LINKER ${device_root}/${soc_portfolio}/${soc_series}/${device}/gcc/${CONFIG_MCUX_TOOLCHAIN_LINKER_DEVICE_PREFIX}_flexspi_nor.ld
    )

    mcux_add_armgcc_linker_script(
        BASE_PATH ${SdkRootDirPath}
        TARGETS flexspi_nor_debug flexspi_nor_release
        LINKER ${device_root}/${soc_portfolio}/${soc_series}/${device}/gcc/${CONFIG_MCUX_TOOLCHAIN_LINKER_DEVICE_PREFIX}_flexspi_nor_ocram.ld
    )

    set(_data_section_is_cacheable 1)
else()
    set(_data_section_is_cacheable 0)
endif()

mcux_add_macro(
    TARGETS flexspi_nor_debug flexspi_nor_release
    CC " \
        DATA_SECTION_IS_CACHEABLE=${_data_section_is_cacheable} \
        USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE=${_data_section_is_cacheable} \
    "
    CX " \
        DATA_SECTION_IS_CACHEABLE=${_data_section_is_cacheable} \
        USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE=${_data_section_is_cacheable} \
    "
)

mcux_add_macro(
    TARGETS debug release
    CC " \
        DATA_SECTION_IS_CACHEABLE=0 \
        USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE=0 \
    "
    CX " \
        DATA_SECTION_IS_CACHEABLE=0 \
        USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE=0 \
    "
)
