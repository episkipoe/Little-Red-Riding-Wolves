cmake_minimum_required(VERSION 2.8)
project(wolves)

SET(CMAKE_CXX_FLAGS_DEBUG  "-Wall -fno-rtti -O0 -g")

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

add_library (main
	display.cpp display.h
	input.cpp input.h
	world.cpp world.h
	images/load_png.cpp
)

add_library (agents
	red/red.cpp red/red.h
	wolf/wolf.cpp wolf/wolf.h
)

add_subdirectory(graphics)
add_subdirectory(common)

add_executable(wolves
	main.cpp
)

target_link_libraries(wolves 
	main
	agents
	graphics
	common
	${PNG_LIBRARY}
	${OPENGL_LIBRARIES} ${GLUT_LIBRARIES}
)
