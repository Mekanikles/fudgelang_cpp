file(GLOB_RECURSE sourceFiles
	source/*.h
	source/*.cpp)

add_library(fudge SHARED ${sourceFiles})
target_include_directories(fudge PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/api)
target_include_directories(fudge PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source)
set_target_properties(fudge PROPERTIES CXX_VISIBILITY_PRESET hidden)

# build a separate executable for tests using the source files directly
if(PACKAGE_TESTS)
	file(GLOB_RECURSE testFiles tests/*.cpp)
	set(allFiles ${sourceFiles} ${testFiles})
	add_executable(fudgetests ${allFiles})
	target_include_directories(fudgetests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/api)
	target_include_directories(fudgetests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source)
	target_include_directories(fudgetests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tests)
	target_link_libraries(fudgetests gtest gmock gtest_main)
	gtest_discover_tests(fudgetests)
endif()

