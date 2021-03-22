# -------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.8)
project(Assignment2)
# -------------------------------------------------------------------------------
add_subdirectory(${PROJECT_SOURCE_DIR}/../box2d-2.4.1 cmake-build-debug)
# -------------------------------------------------------------------------------
FILE(GLOB ASSIGNMENT2_HEADER_FILES headers/*.h headers/*.hpp)
FILE(GLOB ASSIGNMENT2_SOURCE_FILES srcs/*.c srcs/*.cpp main.cpp)
add_executable(assignment2 ${ASSIGNMENT2_HEADER_FILES} ${ASSIGNMENT2_SOURCE_FILES} headers/scene.h srcs/scene.cpp headers/camera.h headers/config.h)
target_include_directories(assignment2 PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
		${PROJECT_SOURCE_DIR}/include
		${PROJECT_SOURCE_DIR}/headers
		${PROJECT_SOURCE_DIR}/shaders
		)
target_link_libraries(assignment2 PUBLIC box2d glfw imgui sajson glad)
set_target_properties(assignment2 PROPERTIES
	CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
# Copy font files, etc
add_custom_command(
        TARGET assignment2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/data/
                ${CMAKE_CURRENT_BINARY_DIR}/data/)
add_definitions(-DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")