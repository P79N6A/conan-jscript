# Test for jscript Conan package manager
# Dmitriy Vetutnev, Odant, 2018


project(PackageTest CXX)
cmake_minimum_required(VERSION 3.0)


include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)


# Copy fake Odant framework and node module
execute_process(COMMAND ${CMAKE_COMMAND} "-E" "copy_directory" ${CMAKE_SOURCE_DIR}/web ${CMAKE_BINARY_DIR}/bin/web)
execute_process(COMMAND ${CMAKE_COMMAND} "-E" "copy_directory" ${CMAKE_SOURCE_DIR}/node_modules ${CMAKE_BINARY_DIR}/bin/node_modules)


enable_testing()


# CONAN_PKG imported targets
add_executable(test_jscript_CONAN_PKG test_jscript.cpp)
target_link_libraries(test_jscript_CONAN_PKG CONAN_PKG::jscript)
set_target_properties(test_jscript_CONAN_PKG
    PROPERTIES
    INSTALL_RPATH "$ORIGIN"
    BUILD_WITH_INSTALL_RPATH True
)
add_test(
    NAME test_jscript_CONAN_PKG
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
    COMMAND test_jscript_CONAN_PKG
)


# Normal imported targets
find_package(JScript REQUIRED)

add_executable(test_jscript test_jscript.cpp)
target_link_libraries(test_jscript JScript::JScript)
set_target_properties(test_jscript
    PROPERTIES
    INSTALL_RPATH "$ORIGIN"
    BUILD_WITH_INSTALL_RPATH True
)
add_test(
    NAME test_jscript
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
    COMMAND test_jscript
)
