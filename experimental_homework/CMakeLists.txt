# reinit by make_cmake.sh
cmake_minimum_required(VERSION 3.25)
project(experimental_homework VERSION 1.0)
include_directories(${PROJECT_SOURCE_DIR}/inc)
# aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
# add lib purpose
add_library(avl ${PROJECT_SOURCE_DIR}/src/avl_tree.c)
add_library(menu ${PROJECT_SOURCE_DIR}/src/menu.c)
add_library(linked_list ${PROJECT_SOURCE_DIR}/src/linked_list.c)
add_library(interactor ${PROJECT_SOURCE_DIR}/src/interactor.c ${PROJECT_SOURCE_DIR}/src/linked_list.c ${PROJECT_SOURCE_DIR}/src/menu.c ${PROJECT_SOURCE_DIR}/src/avl_tree.c)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(main ${PROJECT_SOURCE_DIR}/src/main.c)
target_link_libraries(main interactor)

add_executable(test_avl_tree ${PROJECT_SOURCE_DIR}/test/test_avl_tree.c)
target_link_libraries(test_avl_tree avl)

add_executable(test_menu ${PROJECT_SOURCE_DIR}/test/test_menu.c)
target_link_libraries(test_menu menu)

add_executable(test_int_linked_list ${PROJECT_SOURCE_DIR}/test/test_int_linked_list.c)
target_link_libraries(test_int_linked_list linked_list)