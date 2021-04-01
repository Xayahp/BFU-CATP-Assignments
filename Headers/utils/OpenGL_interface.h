#ifndef ASSIGNMENT_FRAMEWORK_OPENGL_INTERFACE_H
#define ASSIGNMENT_FRAMEWORK_OPENGL_INTERFACE_H

// PREREQUISITE
#include "glad/glad.h" // [ Ensure "glad" is included ahead of "GLFW" ]
#include "GLFW/glfw3.h"

#include "Eigen/Eigen"
#include <vector>
#include <string>
#include <iostream>

#include "Camera.h"

namespace OPENGL_INTERFACE {

    bool scene_state = 1;

    bool reset = false;

    const unsigned WIDTH = 800;
    const unsigned HEIGHT = 600;

//    Camera camera({0.0f, 5.0f, 10.0f});
    Camera camera({0.0f, 0.f, 3.f});
    float lastX = WIDTH / 2.0f;
    float lastY = HEIGHT / 2.0f;
    bool firstMouse = true;

    // timing
    float deltaTime = 0.0f;    // time between current frame and last frame
    float lastFrame = 0.0f;

    std::string WINDOW_NAME = "SET YOUR WINDOW NAME IN OPENGL_INTERFACE::WINDOW_NAME";

    std::vector<Eigen::Vector2f> mouse_input_points;
    bool printed = false;

    static Eigen::Matrix4f GET_PROJECTION_MATRIX() {
        glm::mat4 p = glm::perspective(glm::radians(OPENGL_INTERFACE::camera.Zoom),
                                       (float) OPENGL_INTERFACE::WIDTH / (float) OPENGL_INTERFACE::HEIGHT, 0.1f,
                                       100.0f);
        Eigen::Matrix4f projection;

        for (size_t i = 0; i < 4; ++i)
            for (size_t j = 0; j < 4; ++j)
                projection(j, i) = p[i][j];

        return projection;
    }

    static Eigen::Matrix4f GET_VIEW_MATRIX() {
        glm::mat4 v = OPENGL_INTERFACE::camera.GetViewMatrix();
        Eigen::Matrix4f view;

        for (size_t i = 0; i < 4; ++i)
            for (size_t j = 0; j < 4; ++j)
                view(j, i) = v[i][j];

        return view;
    }

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    static void mouse_callback(GLFWwindow *window, double xpos, double ypos);

    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

    static void OPENGL_INIT(GLFWwindow *&window) {

        // initialize GLFW
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_NAME.c_str(), nullptr, nullptr);
        if (window == nullptr) {
            std::cout << "Failed to create GLFW window." << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);

        // register callback functions
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
        glfwSetMouseButtonCallback(window, mouse_button_callback);

//        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // initialize GLAD
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD." << std::endl;
            glfwTerminate(); // This line isn't in the official source code, but I think that it should be added here.
        }

        glEnable(GL_DEPTH_TEST);
    }

    static void PROCESS_INPUT(GLFWwindow *&window) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        /** Keyboard control **/ // If key did not get pressed it will return GLFW_RELEASE
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            scene_state = !scene_state;
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
            reset = true;
    }

    static void OPENGL_CLEAR_BUFFER() {
        glClearColor(1.f, 1.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT + GL_DEPTH_BUFFER_BIT);
    }

    static void OPENGL_SHUTDOWN(GLFWwindow *&window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

// ------------------------------ callback functions ------------------------------
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
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

    static void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
    }

    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
        camera.ProcessMouseScroll(yoffset);
    }
}
#endif //OPENGLFRAMEWORK_INITIALIZE_H
