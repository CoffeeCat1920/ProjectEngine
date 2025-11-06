project(Space_Invaders LANGUAGES CXX)

file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(${PROJECT_NAME} ${GAME_SOURCES})

# Add local include directory
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/engine/include
    ${CMAKE_SOURCE_DIR}/vendor/json/include
    ${CMAKE_SOURCE_DIR}/vendor/raylib/include
)

# Link against the engine and raylib
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    engine
    ${CMAKE_SOURCE_DIR}/vendor/raylib/lib/libraylib.a
    m pthread dl
)
