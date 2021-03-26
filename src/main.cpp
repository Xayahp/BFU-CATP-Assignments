// STB IMAGE IMPLEMENTATION
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
// INTERFACE
#include "OpenGL_interface.h"
#include "Imgui_interface.h"
// UTILS
#include "PhysicalObjects.h"
#include "BasicShapes.h"

Eigen::Matrix4f g2e(glm::mat4 mat) {
    Eigen::Matrix4f res;
    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < 4; ++j)
            res(j, i) = mat[i][j];

    return res;
}

int main(int argc, char **argv) {

    GLFWwindow *window;
    OPENGL_INTERFACE::OPENGL_INIT(window);
    IMGUI_INTERFACE::IMGUI_CREATE(window);

    std::string SHADER_DIRECTORY = PROJECT_SHADER_DIR;
    std::string vertex_triangles_shader_path = SHADER_DIRECTORY + "/3D/" + "default_triangles_shader.vert";
    std::string fragment_triangles_shader_path = SHADER_DIRECTORY + "/3D/" + "default_triangles_shader.frag";

    std::string groundv = SHADER_DIRECTORY + "/" + "Ground_default.vert";
    std::string groundf = SHADER_DIRECTORY + "/" + "Ground_default.frag";

    Texture tex1;

    tex1.id = Model::load_texture("tex1.jpg", "/Users/polaris/Desktop/Graphics/计算机动画原理与技术-实验设计/AssignmentFramework/Textures");
    tex1.type = "texture_diffuse";
    tex1.path = "/Users/polaris/Desktop/Graphics/计算机动画原理与技术-实验设计/AssignmentFramework/Textures/tex1.jpg";

    /*
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

    sphere->set_draw_mode(POLYGON);*/


    auto ground = std::make_unique<Ground>(30.f, 30.f);
    ground->load_shader(groundv, groundf);
    ground->set_position(Eigen::Vector3f(0.f, -3.f, 0.f));
    ground->set_draw_mode(FILL);

    ground->meshes[0].textures.push_back(tex1);


    auto ball = std::make_unique<Ball>(0.2);
    ball->load_shader(vertex_triangles_shader_path, fragment_triangles_shader_path);
    ball->set_draw_mode(POLYGON);


    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        OPENGL_INTERFACE::PROCESS_INPUT(window);
        OPENGL_INTERFACE::OPENGL_CLEAR_BUFFER();

// ------------------------------ RENDERING LOOP FIELD ------------------------------

        glm::mat4 p = glm::perspective(glm::radians(OPENGL_INTERFACE::camera.Zoom),
                                       (float) OPENGL_INTERFACE::WIDTH / (float) OPENGL_INTERFACE::HEIGHT, 0.1f,
                                       100.0f);
        glm::mat4 v = OPENGL_INTERFACE::camera.GetViewMatrix();

        glm::mat4 m = glm::mat4(1.f);
        m = glm::scale(m, glm::vec3(0.2, 0.2, 0.2));
        m = glm::rotate(m, (float) glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        m = glm::rotate(m, (float) glfwGetTime(), glm::vec3(0.0f, 1.0f, 1.0f));
        m = glm::rotate(m, (float) glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));

        Eigen::Matrix4f model, view, projection;

        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                model(j, i) = m[i][j];
                view(j, i) = v[i][j];
                projection(j, i) = p[i][j];
            }
        }

        for (int i = 0; i < 25; ++i) {
            ball->sub_step(0.01);
        }


        model = ball->generate_translation_mat() * model;
        ball->set_projection(projection);
        ball->set_view(view);
        ball->set_model(model);
        ball->draw();


        model = ground->generate_scale_mat();
        model = ground->generate_translation_mat() * model;
        ground->set_projection(projection);
        ground->set_view(view);
        ground->set_model(model);
        ground->draw();





//        plane->set_MVP(model, view, projection);
//        plane->draw();

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