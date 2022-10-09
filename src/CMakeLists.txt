# include dependencies as a target
add_subdirectory(shl)

# our super program!
add_executable(using-shl main.c)
target_compile_features(using-shl PRIVATE c_std_90)
target_link_libraries(using-shl shl)
set_target_properties(using-shl PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
