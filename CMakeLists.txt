cmake_minimum_required(VERSION 3.10)

# set the project name
project(FudgeLang VERSION 1.0.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include test framework
option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()

# include sub projects
add_subdirectory(fudge)
add_subdirectory(fudgecli)

# target dependency for copying cli files to bin
add_custom_command(
	OUTPUT ${CMAKE_SOURCE_DIR}/bin/fudge
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:fudgecli> ${CMAKE_SOURCE_DIR}/bin/fudge
	DEPENDS fudgecli)

# actual target for copying bin files
add_custom_target(copy_bin ALL
	DEPENDS ${CMAKE_SOURCE_DIR}/bin/fudge)

# export commands for VSCode
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)