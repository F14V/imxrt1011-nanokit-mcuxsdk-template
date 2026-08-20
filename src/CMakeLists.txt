set(WARNING_OPTIONS
    -Wall
    -Wextra
    -Wshadow
    -Wdouble-promotion
    -Wformat=2
    -Wundef
    # -Wconversion
    # -Wsign-conversion
    -Wno-unused-parameter
)

file(
    GLOB_RECURSE APP_SOURCES
    CONFIGURE_DEPENDS
    RELATIVE "${CMAKE_CURRENT_LIST_DIR}"
        *.c
        *.cpp
        *.h
        *.hpp
        *.S
)

mcux_add_source(
    SOURCES
        ${APP_SOURCES}
)

mcux_add_include(
    INCLUDES
        .
)

if(NOT CONFIG_APP_BOARD_config.debug_console.disabled)
    target_compile_definitions(
        ${MCUX_SDK_PROJECT_NAME}
        PRIVATE
            SDK_DEBUGCONSOLE=1
    )
endif()

target_compile_options(
    ${MCUX_SDK_PROJECT_NAME}
    PRIVATE
        "$<$<COMPILE_LANGUAGE:C,CXX>:${WARNING_OPTIONS}>"
)

set_target_properties(
    ${MCUX_SDK_PROJECT_NAME}
    PROPERTIES
        C_STANDARD 23
        C_STANDARD_REQUIRED ON
        C_EXTENSIONS ON
        CXX_STANDARD 26
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS ON
        INTERPROCEDURAL_OPTIMIZATION_RELEASE ON
        INTERPROCEDURAL_OPTIMIZATION_FLEXSPI_NOR_RELEASE ON
)
