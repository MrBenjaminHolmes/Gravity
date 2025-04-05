#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);  

    GLFWwindow* window = glfwCreateWindow(800, 800, "2D Gravity", nullptr, nullptr);

    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glViewport(0, 0, 800, 800);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glOrtho(0, 800, 800, 0, -1, 1); 

    const float pi = 3.141592653589;
    int screenX = 800;
    int screenY = 800;
    float centerX = screenX/2.0f;
    float centerY = screenY/2.0f;
    float radius = 50.0f;
    int resolution = 4; //Side of Shape!!

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);  

        glBegin(GL_TRIANGLE_FAN);  
        glVertex2f(centerX, centerY);  

        for (int i = 0; i <= resolution; ++i) {
            float angle = 2.0f * 3.14f * (static_cast<float>(i) / resolution); 
            float x = centerX + cos(angle) * radius;  
            float y = centerY + sin(angle) * radius;
            glVertex2f(x, y);  
        }
        glEnd(); 

        glfwSwapBuffers(window);  
        glfwPollEvents();  
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
