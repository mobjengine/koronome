add_executable(
    koronome
    k_main.cc
    k_lump.cc
)
set_target_properties(
    koronome PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
target_link_libraries(
    koronome PRIVATE
    sfml-graphics sfml-window sfml-system
    zip
)
