cmake_minimum_required(VERSION 2.8)
project(wolves)

SET(CMAKE_CXX_FLAGS_DEBUG  "-Wall -fno-rtti -O0 -g")

find_package(GLUT REQUIRED)
#find_package(OpenGL REQUIRED)

add_library (main
	display.cpp display.h
	input.cpp input.h
)

add_subdirectory(graphics)

add_executable(wolves
	main.cpp
)

target_link_libraries(wolves 
	main
	graphics
	${GLUT_LIBRARY} 
	${OPENGL_LIBRARY}
	${GLU_LIBRARY} 
	${OpenGL_LIBS} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${GLUT_LIBRARY}
)
