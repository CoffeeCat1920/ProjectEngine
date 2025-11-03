add_library(engine)

# Source and headers
file(GLOB_RECURSE ENGINE_SOURCES
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB_RECURSE ENGINE_HEADERS
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

target_sources(engine
  PRIVATE ${ENGINE_SOURCES}
  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
    FILES ${ENGINE_HEADERS}
)

# Include directories
target_include_directories(engine
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/vendor/json/include
    ${CMAKE_SOURCE_DIR}/vendor/raylib/include
)

# Link raylib (precompiled)
target_link_libraries(engine
  PUBLIC
    ${CMAKE_SOURCE_DIR}/vendor/raylib/lib/libraylib.a
    m pthread dl
)
