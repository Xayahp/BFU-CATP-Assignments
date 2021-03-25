// STB IMAGE IMPLEMENTATION
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
// INTERFACE
#include "OpenGL_interface.h"
#include "Imgui_interface.h"
// UTILS
#include "Model.h"

#include "glm/gtx/string_cast.hpp"

#include "BasicShapes.h"

int main(int argc, char **argv) {

    GLFWwindow *window;
    OPENGL_INTERFACE::OPENGL_INIT(window);
    IMGUI_INTERFACE::IMGUI_CREATE(window);

    std::string SHADER_DIRECTORY = PROJECT_SHADER_DIR;
    std::string vertex_triangles_shader_path = SHADER_DIRECTORY + "/3D/" + "default_triangles_shader.vert";
    std::string fragment_triangles_shader_path = SHADER_DIRECTORY + "/3D/" + "default_triangles_shader.frag";

    auto plane = std::make_unique<Plane>();
    plane->load_shader(vertex_triangles_shader_path, fragment_triangles_shader_path);

    auto sphere = std::make_unique<Sphere>();
    sphere->load_shader(vertex_triangles_shader_path, fragment_triangles_shader_path);

    auto cube = std::make_unique<Cube>();
    cube->load_shader(vertex_triangles_shader_path, fragment_triangles_shader_path);

    auto cylinder = std::make_unique<Cylinder>();
    cylinder->load_shader(vertex_triangles_shader_path, fragment_triangles_shader_path);

    auto cone = std::make_unique<Cone>();
    cone->load_shader(vertex_triangles_shader_path, fragment_triangles_shader_path);

    auto corner_ball = std::make_unique<Corner_ball>();
    corner_ball->load_shader(vertex_triangles_shader_path, fragment_triangles_shader_path);

    auto torus = std::make_unique<Torus>();
    torus->load_shader(vertex_triangles_shader_path, fragment_triangles_shader_path);

    sphere->set_draw_mode(POINT);




    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        OPENGL_INTERFACE::PROCESS_INPUT(window);
        OPENGL_INTERFACE::OPENGL_CLEAR_BUFFER();

// ------------------------------ RENDERING LOOP FIELD ------------------------------

        glm::mat4 p = glm::perspective(glm::radians(OPENGL_INTERFACE::camera.Zoom), (float)OPENGL_INTERFACE::WIDTH / (float)OPENGL_INTERFACE::HEIGHT, 0.1f, 100.0f);
        glm::mat4 v = OPENGL_INTERFACE::camera.GetViewMatrix();
        glm::mat4 m = glm::mat4(1.f);
        m = glm::scale(m, glm::vec3( 0.5f, 0.5f, 0.5f ));
        m = glm::rotate(m, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        m = glm::rotate(m, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 1.0f));
        m = glm::rotate(m, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));

        Eigen::Matrix4f model, view, projection;

        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                model(j, i) = m[i][j];
                view(j, i) = v[i][j];
                projection(j, i) = p[i][j];
            }
        }

//        plane->set_MVP(model, view, projection);
//        plane->draw();

        sphere->set_MVP(model, view, projection);
        sphere->draw();
//
//        cube->set_MVP(model, view, projection);
//        cube->draw();
//
//        cylinder->set_MVP(model, view, projection);
//        cylinder->draw();
//
//        torus->set_MVP(model, view, projection);
//        torus->draw();

















// ------------------------------ RENDERING LOOP FIELD ------------------------------

        IMGUI_INTERFACE::hello_imgui();
        glfwSwapBuffers(window);
    }

    IMGUI_INTERFACE::IMGUI_SHUTDOWN();
    OPENGL_INTERFACE::OPENGL_SHUTDOWN(window);
    return 0;
}