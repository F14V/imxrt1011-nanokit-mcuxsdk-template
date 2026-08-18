mcux_add_source(
    SOURCES
        board/*.c
        board/*.h
)

mcux_add_include(
    INCLUDES
        board/
)

mcux_add_source(
    SOURCES
        app/*.c
        app/*.h
)

mcux_add_include(
    INCLUDES
        app/
)

mcux_add_config_mex_path(PATH .)

include(${CMAKE_CURRENT_LIST_DIR}/reconfig.cmake)
