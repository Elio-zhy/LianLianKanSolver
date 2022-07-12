cmake_minimum_required (VERSION 3.14.0)

set( CMAKE_CXX_COMPILER "D:/Programs/msys64/clang64/bin/clang++.exe" )
set( CMAKE_C_COMPILER "D:/Programs/msys64/clang64/bin/clang.exe" )
set( CMAKE_GENERATOR "Ninja" )

project(LianLianKanSolver)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(LianLianKanSolver
    ${PROJECT_SOURCE_DIR}/src/main.c
    ${PROJECT_SOURCE_DIR}/src/board.c
    ${PROJECT_SOURCE_DIR}/src/calculate.c
    ${PROJECT_SOURCE_DIR}/src/click.c
    ${PROJECT_SOURCE_DIR}/src/main.c
    ${PROJECT_SOURCE_DIR}/src/solution.c
    ${PROJECT_SOURCE_DIR}/src/solve.c
)

target_link_libraries(LianLianKanSolver PRIVATE Threads::Threads)