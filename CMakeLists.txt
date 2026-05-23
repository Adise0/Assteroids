cmake_minimum_required(VERSION 3.25)
project(Assteroids VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(local.cmake OPTIONAL)

find_package(Crow2D REQUIRED
  PATHS "${CROW2D_SDK_PATH}"
  NO_DEFAULT_PATH
)

file(GLOB_RECURSE SOURCES
  CONFIGURE_DEPENDS
  "${CMAKE_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_SOURCE_DIR}/src/*.cxx"
  "${CMAKE_SOURCE_DIR}/src/*.h"
  "${CMAKE_SOURCE_DIR}/src/*.hpp"
)


add_executable(Assteroids ${SOURCES}  ./release/icon.rc)

set_target_properties(Assteroids PROPERTIES
  WIN32_EXECUTABLE $<NOT:$<CONFIG:Debug>>
  LINK_FLAGS_RELEASE "/ENTRY:mainCRTStartup"
  LINK_FLAGS_RELWITHDEBINFO "/ENTRY:mainCRTStartup"
)

file(GLOB_RECURSE Assteroids_ALL_HEADERS "${CMAKE_SOURCE_DIR}/src/*.h")
set(Assteroids_INCLUDE_DIRS "")

foreach(_header ${Assteroids_ALL_HEADERS})
  get_filename_component(_dir "${_header}" DIRECTORY)
  list(APPEND Assteroids_INCLUDE_DIRS "${_dir}")
endforeach()

list(REMOVE_DUPLICATES Assteroids_INCLUDE_DIRS)

target_include_directories(Assteroids PRIVATE
  "${CMAKE_SOURCE_DIR}/src"
  ${Assteroids_INCLUDE_DIRS}
)

target_link_libraries(Assteroids PRIVATE Crow2D::Crow2D)
target_include_directories(Assteroids PRIVATE third_party)

crow2d_copy_runtime(Assteroids)
crow2d_copy_assets(Assteroids)


install(TARGETS Assteroids
  RUNTIME DESTINATION .
)

install(DIRECTORY "${CMAKE_BINARY_DIR}/"
  DESTINATION .
  FILES_MATCHING
  PATTERN "*.dll"
  PATTERN "CMakeFiles" EXCLUDE
  PATTERN "default" EXCLUDE
)

install(DIRECTORY "${CMAKE_BINARY_DIR}/assets"
  DESTINATION .
  PATTERN "*.css.map" EXCLUDE
)

install(DIRECTORY "${CMAKE_BINARY_DIR}/resources"
  DESTINATION .
)
