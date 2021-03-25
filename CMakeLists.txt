# -------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5)
project(AssignmentFramework)
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
file(GLOB PROJECT_HEADERS "Headers/*.h" "Headers/*.hpp" "Headers/*.cpp")
file(GLOB PROJECT_UTILS "Headers/utils/*.h" "Headers/utils/*.hpp" "Headers/utils/*.cpp")
file(GLOB OTHER_SOURCES
        "include/glad/glad.c"
        "include/stb/stb_image.cpp"
        "vendor/imgui-1.82/backends/imgui_impl_glfw.h"
        "vendor/imgui-1.82/backends/imgui_impl_glfw.cpp"
        "vendor/imgui-1.82/backends/imgui_impl_opengl3.h"
        "vendor/imgui-1.82/backends/imgui_impl_opengl3.cpp"
        "vendor/imgui-1.82/*.h"
        "vendor/imgui-1.82/*.cpp")
file(GLOB SOME_SAMPLES "Samples/*.h" "Samples/*.cpp")
# -------------------------------------------------------------------------------
set(TEST_TARGET "src/main.cpp")
add_executable(AssignmentSample ${TEST_TARGET} ${PROJECT_HEADERS} ${PROJECT_UTILS} ${OTHER_SOURCES} ${SOME_SAMPLES})
target_include_directories(AssignmentSample
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/Headers
        ${PROJECT_SOURCE_DIR}/Headers/utils
        ${PROJECT_SOURCE_DIR}/vendor/assimp-5.0.1/include
        ${PROJECT_SOURCE_DIR}/vendor/glfw-3.3.2/include
        ${PROJECT_SOURCE_DIR}/vendor/imgui-1.82
)
target_link_libraries(AssignmentSample PUBLIC glfw assimp)
# -------------------------------------------------------------------------------
add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\"
                -DPROJECT_SHADER_DIR=\"${PROJECT_SOURCE_DIR}/Shaders\"
                -DPROJECT_DATA_DIR=\"${PROJECT_SOURCE_DIR}/data\")
# -------------------------------------------------------------------------------