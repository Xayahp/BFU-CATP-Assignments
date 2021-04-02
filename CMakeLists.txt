# -------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5)
project(AssignmentFramework)
set(CMAKE_CXX_FLAGS "-std=c++14")
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
file(GLOB PROJECT_HEADERS "Headers/*.h" "Headers/*.hpp" "Headers/*.cpp" "Headers/Shapes/*.h" "Headers/Shapes/*.hpp" "Headers/Shapes/*.cpp" "Headers/Objects/*.h" "Headers/Objects/*.hpp" "Headers/Objects/*.cpp" "Headers/Solvers/*.h" "Headers/Solvers/*.hpp" "Headers/Solvers/*.cpp" "Headers/ParticleSystem/*.h" "Headers/ParticleSystem/*.hpp" "Headers/ParticleSystem/*.cpp" "Headers/Collision/*.h" "Headers/Collision/*.hpp" "Headers/Collision/*.cpp")
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
file(GLOB SOME_SAMPLE_SCENES "Headers/Scenes/*.h" "Headers/Scenes/*.cpp")
# -------------------------------------------------------------------------------
set(ALL_FILES ${PROJECT_HEADERS} ${PROJECT_UTILS} ${OTHER_SOURCES} ${SOME_SAMPLE_SCENES})
add_executable(AssignmentSample src/main.cpp ${PROJECT_HEADERS} ${PROJECT_UTILS} ${OTHER_SOURCES} ${SOME_SAMPLE_SCENES} Headers/Scenes/Assignment_0.cpp Headers/Scenes/Assignment_0.h)
target_include_directories(AssignmentSample
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/Headers/utils
        ${PROJECT_SOURCE_DIR}/Headers/Shapes
        ${PROJECT_SOURCE_DIR}/Headers/Objects
        ${PROJECT_SOURCE_DIR}/Headers/ParticleSystem
        ${PROJECT_SOURCE_DIR}/Headers/Solvers
        ${PROJECT_SOURCE_DIR}/Headers/Collision
        ${PROJECT_SOURCE_DIR}/Headers/Scenes
        ${PROJECT_SOURCE_DIR}/vendor/assimp-5.0.1/include
        ${PROJECT_SOURCE_DIR}/vendor/glfw-3.3.2/include
        ${PROJECT_SOURCE_DIR}/vendor/imgui-1.82
        )
target_link_libraries(AssignmentSample PRIVATE glfw assimp)
# -------------------------------------------------------------------------------
add_definitions(-DGLFW_INCLUDE_NONE
        -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\"
        -DPROJECT_SHADER_DIR=\"${PROJECT_SOURCE_DIR}/Shaders\"
        -DPROJECT_TEXTURE_DIR=\"${PROJECT_SOURCE_DIR}/Textures\"
        -DPROJECT_DATA_DIR=\"${PROJECT_SOURCE_DIR}/data\")
# -------------------------------------------------------------------------------
macro(source_group_by_dir source_files)
    if (MSVC)
        set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
        foreach (sgbd_file ${${source_files}})
            string(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
            string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
            string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
            string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
            if (sgbd_nogroup)
                set(sgbd_group_name "\\")
            endif (sgbd_nogroup)
            source_group(${sgbd_group_name} FILES ${sgbd_file})
        endforeach (sgbd_file)
    endif (MSVC)
endmacro(source_group_by_dir)
source_group_by_dir(ALL_FILES)
# -------------------------------------------------------------------------------