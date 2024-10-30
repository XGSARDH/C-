# reinit by make_cmake.sh
cmake_minimum_required(VERSION 3.25)
project(experimental_homework VERSION 1.0)
include_directories(${PROJECT_SOURCE_DIR}/inc)
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
# add lib purpose
add_library(binarytree ${PROJECT_SOURCE_DIR}/src/binarytree.c)

add_executable(main  ${SRC_LIST})
set(HOME /home/sardh/code/c_homework/experimental_homework)
set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin)
# link lib with executable file
target_link_libraries(main binarytree)