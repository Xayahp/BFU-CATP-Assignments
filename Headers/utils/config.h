#ifndef OPENGLFRAMEWORK_CONFIG_H
#define OPENGLFRAMEWORK_CONFIG_H

// screen size
const unsigned WIDTH = 800;
const unsigned HEIGHT = 600;

// window name
const char *WINDOW_NAME = "Assignment"; // Your Name Here :P

// directories paths
std::string PROJECT_DIRECTORY = PROJECT_SOURCE_DIR; // define in CMakeLists.txt
std::string SHADER_DIRECTORY = PROJECT_DIRECTORY + "/Shaders/";
std::string TEXTURE_DIRECTORY = PROJECT_DIRECTORY + "/Textures/";

// mouse click event recorder
std::vector<Eigen::Vector2f> mouse_input_points;
bool printed = false;

// ------------------------------ callback functions ------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
//    if (key >= 0 && key < 1024) {
//        if (action == GLFW_PRESS)
//            Breakout.Keys[key] = true;
//        else if (action == GLFW_RELEASE) {
//            Breakout.Keys[key] = false;
//            Breakout.KeysProcessed[key] = false;
//        }
//    }
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        xpos = 2 * xpos / (WIDTH - 1.f) - 1.f;
        ypos = 1.f - 2 * ypos / (HEIGHT - 1.f);
        mouse_input_points.emplace_back(Eigen::Vector2f(xpos, ypos));
        printed = false;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        mouse_input_points.clear();
        std::cout << "CLEAR!" << std::endl;
    }
}

// ------------------------------ common functions ------------------------------
void processInput(GLFWwindow *window) {
    /** Keyboard control **/ // If key did not get pressed it will return GLFW_RELEASE
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}


#endif //OPENGLFRAMEWORK_CONFIG_H
