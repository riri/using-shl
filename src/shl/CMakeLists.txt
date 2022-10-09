include(FetchContent)

### Nuklear single header library

FetchContent_Declare(
    nuklear
    GIT_REPOSITORY https://github.com/Immediate-Mode-UI/Nuklear.git
    GIT_TAG master
    GIT_SHALLOW ON
)

FetchContent_GetProperties(nuklear)
if(NOT nuklear_POPULATED)
    FetchContent_Populate(nuklear)
    add_library(nuklear INTERFACE ${nuklear_SOURCE_DIR}/nuklear.h)
    target_compile_features(nuklear INTERFACE c_std_90)
    target_include_directories(nuklear INTERFACE ${nuklear_SOURCE_DIR})
endif()

### stb single header library

FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb
    GIT_TAG master
    GIT_SHALLOW ON
)

FetchContent_GetProperties(stb)
if(NOT stb_POPULATED)
    FetchContent_Populate(stb)
    add_library(stb INTERFACE
        ${stb_SOURCE_DIR}/stb_ds.h
        ${stb_SOURCE_DIR}/stb_image.h
    )
    target_compile_features(stb INTERFACE c_std_90)
    target_include_directories(stb INTERFACE ${stb_SOURCE_DIR})
endif()

### the "compile all SHLs" static library

add_library(shl STATIC shl.c)
target_compile_features(shl PRIVATE c_std_90)
if(${CMAKE_C_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(shl PRIVATE -pedantic -Wall -Wextra -Wno-unused-function)
endif()
target_link_libraries(shl PUBLIC nuklear stb)
