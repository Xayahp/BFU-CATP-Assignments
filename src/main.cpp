// STB IMAGE IMPLEMENTATION
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

// USER HEADERS
#include "Assignment_4.h"
#include "Assignment_3.h"

// LOAD INTERFACE
#include "OpenGL_interface.h"
#include "Imgui_interface.h"

int main(int argc, char **argv) {

    /* --------------------------------------------------
     *           Initialize the Rendering System
     * -------------------------------------------------- */

    GLFWwindow *window;
    OPENGL_INTERFACE::WINDOW_NAME = "Hello Hina"; // Your Name Here :P
    OPENGL_INTERFACE::OPENGL_INIT(window);
    IMGUI_INTERFACE::IMGUI_CREATE(window);

    /* --------------------------------------------------
     *           Load Scenes here !
     * -------------------------------------------------- */

    // change Assignment_1 to Assignment_2
    std::unique_ptr<SceneTEMPLATE> scene = std::make_unique<Assignment_3>(OPENGL_INTERFACE::WIDTH, OPENGL_INTERFACE::HEIGHT, true);
    scene->init();
    scene->load();

    /* --------------------------------------------------
     *           Rendering Loop here
     * -------------------------------------------------- */

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        OPENGL_INTERFACE::PROCESS_INPUT(window);
        OPENGL_INTERFACE::OPENGL_CLEAR_BUFFER();

        scene->view = OPENGL_INTERFACE::GET_VIEW_MATRIX();
        scene->projection = OPENGL_INTERFACE::GET_PROJECTION_MATRIX();
        scene->render(OPENGL_INTERFACE::deltaTime);

        scene->scene_state = OPENGL_INTERFACE::scene_state ? STATE_ACTIVE : STATE_PAUSE;

        IMGUI_INTERFACE::hello_imgui();
        glfwSwapBuffers(window);
    }

    /* --------------------------------------------------
     *           Rendering System terminate here
     * -------------------------------------------------- */

    IMGUI_INTERFACE::IMGUI_SHUTDOWN();
    OPENGL_INTERFACE::OPENGL_SHUTDOWN(window);

    return 0;
}