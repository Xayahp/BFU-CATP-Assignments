#ifndef OPENGLFRAMEWORK_CONFIG_H
#define OPENGLFRAMEWORK_CONFIG_H

#include <vector>
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
std::vector<glm::vec3> mouse_input_points;
bool printed = false;

// ------------------------------ callback functions ------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        //getting cursor position
        glfwGetCursorPos(window, &xpos, &ypos);
        mouse_input_points.emplace_back(glm::vec3(xpos,ypos,0.f));
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
