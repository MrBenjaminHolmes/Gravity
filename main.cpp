#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <iostream>

const float pi = 3.141592653589;
const float GRAVITY_MERCURY = 3.7f * 100;
const float GRAVITY_VENUS = 8.87f * 100;
const float GRAVITY_EARTH = 9.810f * 100;
const float GRAVITY_MARS = 3.71f * 100;
const float GRAVITY_JUPITER = 24.79f * 100;
const float GRAVITY_SATURN = 10.44f * 100;
const float GRAVITY_URANUS = 8.69f * 100;
const float GRAVITY_NEPTUNE = 11.15f * 100;
const float GRAVITY_PLUTO = 0.62f * 100;

void drawShape(int posX,int posY, float radius, int noSides) {
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(posX, posY);

    for (int i = 0; i <= noSides; ++i) {
        float angle = 2.0f * pi * (static_cast<float>(i) / noSides);
        float x = posX + cos(angle) * radius;
        float y = posY + sin(angle) * radius;
        glVertex2f(x, y);
    }
    glEnd();

}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);  
    int screenX = 800;
    int screenY = 800;
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
    std::vector<float> Earthposition = { 400.0f,300.0f };
    std::vector<float> Earthvelocity = { 0.0f,0.0f };
    std::vector<float> Plutoposition = { 400.0f,300.0f };
    std::vector<float> Plutovelocity = { 0.0f,0.0f };

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);  
        drawShape(1200.0f, Earthposition[1], 50.0f, 100);//EARTH BALL
        drawShape(600.0f, Plutoposition[1], 50.0f, 100);// PLUTO BALL
        Plutovelocity[0] += GRAVITY_PLUTO;
        Plutoposition[1] += Plutovelocity[0];
        Earthvelocity[0] += GRAVITY_EARTH;
        Earthposition[1] += Earthvelocity[0];
        glfwSwapBuffers(window);  
        glfwPollEvents();  
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
