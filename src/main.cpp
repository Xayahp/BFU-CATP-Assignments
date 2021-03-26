// STB IMAGE IMPLEMENTATION
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

// LOAD INTERFACE
#include "OpenGL_interface.h"
#include "Imgui_interface.h"

// USER HEADERS
#include "Scene01.h"

int main(int argc, char **argv) {

    /* --------------------------------------------------
     *           Initialize the Rendering System
     * -------------------------------------------------- */

    GLFWwindow *window;
    OPENGL_INTERFACE::WINDOW_NAME = "Your Name Here :P";
    OPENGL_INTERFACE::OPENGL_INIT(window);
    IMGUI_INTERFACE::IMGUI_CREATE(window);

    /* --------------------------------------------------
     *           Load Game here !
     * -------------------------------------------------- */

    Scene01 scene;
    scene.load();

    /* --------------------------------------------------
     *           Rendering Loop here
     * -------------------------------------------------- */

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        OPENGL_INTERFACE::PROCESS_INPUT(window);
        OPENGL_INTERFACE::OPENGL_CLEAR_BUFFER();

        scene.view = OPENGL_INTERFACE::GET_VIEW_MATRIX();
        scene.projection = OPENGL_INTERFACE::GET_PROJECTION_MATRIX();
        scene.render();

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