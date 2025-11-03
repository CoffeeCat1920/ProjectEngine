add_executable(game)

# Find all game source files
file(GLOB_RECURSE GAME_SOURCES
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

target_sources(game
  PRIVATE ${GAME_SOURCES}
)

# Includes
target_include_directories(game
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link engine (which already links raylib)
target_link_libraries(game PRIVATE engine)

# Copy assets automatically to bin directory (optional)
add_custom_command(TARGET game POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:game>/assets
)
