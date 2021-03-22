#include <iostream>

//#include "scene.h"
//#include "config.h"


int main(int argc, char** argv) {
    std::cout << "Hello Animation" << std::endl;

#if defined(_WIN32)
    // Enable memory-leak reports
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));
#endif
#if __APPLE__
    const char* glslVersion = "#version 150";
#else
    const char* glslVersion = NULL;
#endif
/*
	global_camera.screen_width = default_setting.window_width;
    global_camera.screen_width = default_setting.window_height;

    if (glfwInit() == 0) {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        return -1;
    };

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    bool fullscreen = false;
    if (fullscreen)
        global_mainWindow = glfwCreateWindow(1920, 1080, default_setting.window_name.c_str(), glfwGetPrimaryMonitor(), NULL);
    else
        global_mainWindow = glfwCreateWindow(global_camera.screen_width, global_camera.screen_height, default_setting.window_name.c_str(), NULL, NULL);

    if (global_mainWindow == NULL) {
        std::cerr << "Failed to open GLFW global_mainWindow." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(global_mainWindow);

    // Load OpenGL functions using glad
    int version = gladLoadGL(glfwGetProcAddress);
    printf("GL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

//    glfwSetScrollCallback(global_mainWindow, ScrollCallback);
//    glfwSetWindowSizeCallback(global_mainWindow, ResizeWindowCallback);
//    glfwSetKeyCallback(global_mainWindow, KeyCallback);
//    glfwSetCharCallback(global_mainWindow, CharCallback);
//    glfwSetMouseButtonCallback(global_mainWindow, MouseButtonCallback);
//    glfwSetCursorPosCallback(global_mainWindow, MouseMotionCallback);
//    glfwSetScrollCallback(global_mainWindow, ScrollCallback);

    scene my_scene;


*/
    return 0;
}