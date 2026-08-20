cmake_minimum_required(VERSION 3.25.0)

set(CUSTOM_BOARD_ROOT "${CMAKE_CURRENT_LIST_DIR}/boards" CACHE PATH "Custom board root")

# Use the custom board while preserving the SDK-associated EVK for Config Tools.
if(board STREQUAL "evkmimxrt1010")
    set(_config_tools_board "${board}")
    set(board "imxrt1011-nanokit" CACHE STRING "Selected board" FORCE)
endif()

include(${SdkRootDirPath}/cmake/extension/mcux.cmake)

project(imxrt1011-nanokit-mcuxsdk-template LANGUAGES C CXX ASM)

include(${SdkRootDirPath}/CMakeLists.txt)

add_subdirectory(${board})
add_subdirectory(src)

mcux_convert_binary(BINARY ${APPLICATION_BINARY_DIR}/${MCUX_SDK_PROJECT_NAME}.bin)

# Restore the SDK-associated board for Config Tools project matching.
if(DEFINED _config_tools_board)
    set(board "${_config_tools_board}" CACHE STRING "Selected board" FORCE)
endif()
