// INTERFACE
#include "OpenGL_interface.h"
#include "Imgui_interface.h"

#include <glm/gtx/string_cast.hpp>

// USER HEADERS
#include "World2D.h"
#include "World3D.h"

// _TEST
#include "_test_scenes.h"

using namespace W3D;

int main(int argc, char **argv) {

    GLFWwindow *window;
    OPENGL_INTERFACE::OPENGL_INIT(window);
    IMGUI_INTERFACE::IMGUI_CREATE(window);

//    World2D world(Eigen::Vector2f(0, -0.000098f));
//    TEST_SCENE::scene01(world);

    World3D world(Eigen::Vector3f(0, -0.000098f, 0.f));
    auto cube = std::make_unique<Cuboid>(Eigen::Vector3f(0.f, 0.f, 0.f), 0.2f, 0.2f, 0.2f);
    cube->set_color(0x4d4398).set_draw_mode(W3D::TRIANGLES);
    world.add(std::move(cube));



    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        OPENGL_INTERFACE::PROCESS_INPUT(window);
        OPENGL_INTERFACE::OPENGL_CLEAR_BUFFER();

// ------------------------------ RENDERING LOOP FIELD ------------------------------







//        if (!OPENGL_INTERFACE::mouse_input_points.empty()) {
//            for (Eigen::Vector2f &p : OPENGL_INTERFACE::mouse_input_points) {
//                auto temp = std::make_unique<Rectangle>(p, 0.1f, 0.1f);
//                temp->set_color(0x4d4398).set_draw_mode(LINES);
//                world.add(std::move(temp));
//            }
//            OPENGL_INTERFACE::mouse_input_points.clear();
//        }







        world.solve();
        world.display();









// ------------------------------ RENDERING LOOP FIELD ------------------------------

        IMGUI_INTERFACE::hello_imgui();
        glfwSwapBuffers(window);
    }

    IMGUI_INTERFACE::IMGUI_SHUTDOWN();
    OPENGL_INTERFACE::OPENGL_SHUTDOWN(window);
    return 0;
}