cmake_minimum_required (VERSION 3.14.0)

set( CMAKE_CXX_COMPILER "D:/Programs/msys64/clang64/bin/clang++.exe" )
set( CMAKE_C_COMPILER "D:/Programs/msys64/clang64/bin/clang.exe" )
set( CMAKE_GENERATOR "MinGW Makefiles" )

project(LianLianKanSolver)
set(CMAKE_BUILD_TYPE Debug)

include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${CMAKE_SOURCE_DIR}/src)

file (GLOB_RECURSE ui_RESOURCES CONFIGURE_DEPENDS "src/*/*.c")
add_executable(gui ${ui_RESOURCES})

target_include_directories(gui PRIVATE ${GTK4_INCLUDE_DIRS})
target_link_libraries(gui PRIVATE ${GTK4_LINK_LIBRARIES})