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
file(GLOB PROJECT_HEADERS "Headers/*.h" "Headers/*.hpp" "Headers/utils/*.h" "Headers/utils/*.hpp" "Headers/physics/*.h" "Headers/physics/*.hpp" "Headers/display/*.h" "Headers/display/*.hpp")
file(GLOB PROJECT_HEADERS_SOURCES "Headers/*.cpp" "Headers/utils/*.cpp" "Headers/physics/*.cpp" "Headers/display/*.cpp")
file(GLOB PROJECT_SOURCES "src/*.cpp" "src/*.c")
file(GLOB OTHER_SOURCES
        "include/glad/glad.c"
        "vendor/imgui-1.82/backends/imgui_impl_glfw.h"
        "vendor/imgui-1.82/backends/imgui_impl_opengl3.h"
        "vendor/imgui-1.82/backends/imgui_impl_glfw.cpp"
        "vendor/imgui-1.82/backends/imgui_impl_opengl3.cpp"
        "vendor/imgui-1.82/*.h"
        "vendor/imgui-1.82/*.cpp")
# -------------------------------------------------------------------------------
add_executable(Assignment0 ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_HEADERS_SOURCES} ${OTHER_SOURCES})
# -------------------------------------------------------------------------------
target_include_directories(Assignment0
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/Headers
        ${PROJECT_SOURCE_DIR}/Headers/physics
        ${PROJECT_SOURCE_DIR}/Headers/utils
        ${PROJECT_SOURCE_DIR}/Headers/display
        ${PROJECT_SOURCE_DIR}/vendor/assimp-5.0.1/include
        ${PROJECT_SOURCE_DIR}/vendor/glfw-3.3.2/include
        ${PROJECT_SOURCE_DIR}/vendor/imgui-1.82
)
target_link_libraries(Assignment0 PUBLIC glfw assimp)
# -------------------------------------------------------------------------------
add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
# -------------------------------------------------------------------------------