# reinit by make_cmake.sh
cmake_minimum_required(VERSION 3.25)
project(experimental_homework VERSION 1.0)
include_directories(${PROJECT_SOURCE_DIR}/inc)
# aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
# add lib purpose
add_library(avl ${PROJECT_SOURCE_DIR}/src/link_stack.c ${PROJECT_SOURCE_DIR}/src/avl_binary_tree.c)
add_library(menu ${PROJECT_SOURCE_DIR}/src/menu.c)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(main  ${PROJECT_SOURCE_DIR}/src/main.c)
target_link_libraries(main avl)

add_executable(test_link_stack  ${PROJECT_SOURCE_DIR}/src/test_link_stack.c)
target_link_libraries(test_link_stack avl)

add_executable(test_avl_binary_tree  ${PROJECT_SOURCE_DIR}/src/test_avl_binary_tree.c)
target_link_libraries(test_avl_binary_tree avl)

add_executable(test_menu  ${PROJECT_SOURCE_DIR}/src/test_menu.c)
target_link_libraries(test_menu menu)