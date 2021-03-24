#ifndef OPENGLFRAMEWORK_INITIALIZE_H
#define OPENGLFRAMEWORK_INITIALIZE_H


// initialize GLFW
glfwInit();
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_NAME, NULL, NULL);
if (window == NULL) {
    std::cout << "Failed to create GLFW window." << std::endl;
    glfwTerminate();
    return -1;
}
glfwMakeContextCurrent(window);

// register callback functions
glfwSetKeyCallback(window, key_callback);
glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
glfwSetMouseButtonCallback(window, mouse_button_callback);

// initialize GLAD
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD." << std::endl;
    glfwTerminate(); // This line isn't in the official source code, but I think that it should be added here.
    return -1;
}


#endif //OPENGLFRAMEWORK_INITIALIZE_H
