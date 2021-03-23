# -------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5)
project(Assignment0)
set(CMAKE_CXX_FLAGS "-std=c++17")
# -------------------------------------------------------------------------------
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glfw-3.3.2)
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/assimp-5.0.1)
# -------------------------------------------------------------------------------
file(GLOB PROJECT_HEADERS "Headers/*.h" "Headers/*.hpp" "Headers/utils/*.h" "Headers/utils/*.hpp")
#file(GLOB PROJECT_TESTS "test_example/*.h" "test_example/*.hpp")
file(GLOB PROJECT_SOURCES "src/*.cpp" "src/*.c")
# -------------------------------------------------------------------------------
add_executable(Assignment0 ${PROJECT_SOURCES} ${PROJECT_HEADERS} Headers/physics/Scene.h Headers/physics/BasicShapes.h Headers/physics/BasicShapes.cpp Headers/physics/Scene.cpp)
# -------------------------------------------------------------------------------
target_include_directories(Assignment0
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/Headers/physics
        ${PROJECT_SOURCE_DIR}/Headers/utils
#        ${PROJECT_SOURCE_DIR}/test_example
        ${PROJECT_SOURCE_DIR}/vendor/assimp-5.0.1/include
        ${PROJECT_SOURCE_DIR}/vendor/glfw-3.3.2/include
)
target_link_libraries(Assignment0 glfw assimp)
# -------------------------------------------------------------------------------
add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
# -------------------------------------------------------------------------------