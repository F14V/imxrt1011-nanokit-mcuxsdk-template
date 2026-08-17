cmake_minimum_required(VERSION 3.25.0)

set(CUSTOM_BOARD_ROOT "${CMAKE_CURRENT_LIST_DIR}/boards" CACHE PATH "Custom board root")

include(${SdkRootDirPath}/cmake/extension/mcux.cmake)

project(imxrt1011-nanokit-mcuxsdk-template LANGUAGES C CXX ASM)

include(${SdkRootDirPath}/CMakeLists.txt)

add_subdirectory(${board})
add_subdirectory(src)

mcux_convert_binary(BINARY ${APPLICATION_BINARY_DIR}/${MCUX_SDK_PROJECT_NAME}.bin)
