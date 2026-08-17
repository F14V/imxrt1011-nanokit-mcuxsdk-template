# RAM linker script
include(${SdkRootDirPath}/arch/arm/target/ram.cmake)
# FLASH linker script
include(${SdkRootDirPath}/arch/arm/target/flexspi_nor.cmake)
# Target-specific startup initialization and memory settings
include(${SdkRootDirPath}/examples/_common/project_setting/RT1xxx.cmake)

# XIP boot header config
mcux_add_cmakelists(${CMAKE_CURRENT_LIST_DIR}/xip)

# Board header and source files
mcux_add_source(SOURCES board.h board.c)
mcux_add_include(INCLUDES .)
