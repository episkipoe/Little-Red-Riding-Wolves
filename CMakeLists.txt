cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_FLAGS_DEBUG  "-Wall -fno-rtti -O0 -g")

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

add_library (main
	main.cpp
	display.cpp display.h
	input.cpp input.h
)


project(wolves)

target_link_libraries(wolves 
	main
	graphics
	${OPENGL_LIBRARY}
)
