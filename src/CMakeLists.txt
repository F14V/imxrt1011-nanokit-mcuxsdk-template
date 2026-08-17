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

mcux_add_source(
    SOURCES
        *.c
        *.h
)

mcux_add_include(
    INCLUDES
        .
)

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
