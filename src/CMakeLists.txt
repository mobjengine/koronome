add_subdirectory(rxi)

add_executable(
    koronome
    k_main.c
    k_player.c
    k_lump.c
    k_world.c
)
set_target_properties(
    koronome PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
target_include_directories(
    koronome PRIVATE
    ${SDL2_INCLUDE_DIRS}
)
target_link_libraries(
    koronome PRIVATE
    ${SDL2_LIBRARIES} SDL2_image
    zip
    rxi
)
