# reinit by make_cmake.sh
cmake_minimum_required(VERSION 3.25)
project(experimental_homework VERSION 1.0)
include_directories(${PROJECT_SOURCE_DIR}/inc)
# aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
# add lib purpose
# add_library(binarytree ${PROJECT_SOURCE_DIR}/src/binarytree.c)
add_library(avl_binary_tree ${PROJECT_SOURCE_DIR}/src/avl_binary_tree.c)
add_library(link_stack ${PROJECT_SOURCE_DIR}/src/link_stack.c)
# add_library(link_queue ${PROJECT_SOURCE_DIR}/src/link_queue.c)

add_executable(main  ${PROJECT_SOURCE_DIR}/src/main.c)
add_executable(test_link_stack  ${PROJECT_SOURCE_DIR}/src/test_link_stack.c)
set(HOME /home/sardh/code/c_homework/experimental_homework)
set(EXECUTABLE_OUTPUT_PATH ${HOME}/bin)
# link lib with executable file
# target_link_libraries(main binarytree)
target_link_libraries(main avl_binary_tree)
target_link_libraries(main link_stack)
target_link_libraries(test_link_stack link_stack)
target_link_libraries(test_link_stack avl_binary_tree)
# target_link_libraries(main link_queue)