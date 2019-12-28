
file(GLOB_RECURSE sourceFiles
	source/*.cpp)

add_executable(fudgecli ${sourceFiles})

target_link_libraries(fudgecli LINK_PUBLIC fudge)
