#define _USE_MATH_DEFINES

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <iostream>

const float pi = M_PI;
const float GRAVITY_MERCURY = 3.7f * 100;
const float GRAVITY_VENUS = 8.87f * 100;
const float GRAVITY_EARTH = 9.81f * 1000;
const float GRAVITY_MARS = 3.71f * 100;
const float GRAVITY_JUPITER = 24.79f * 100;
const float GRAVITY_SATURN = 10.44f * 100;
const float GRAVITY_URANUS = 8.69f * 100;
const float GRAVITY_NEPTUNE = 11.15f * 100;
const float GRAVITY_PLUTO = 0.62f * 100;

void drawShape(int screenX, int screenY, float radius, int noSides) {
    glBegin(GL_TRIANGLE_FAN);
    float centerX = screenX / 2.0f;
    float centerY = screenY / 2.0f;
    glVertex2f(centerX, centerY);

    for (int i = 0; i <= noSides; ++i) {
        float angle = 2.0f * pi * (static_cast<float>(i) / noSides);
        float x = centerX + cos(angle) * radius;
        float y = centerY + sin(angle) * radius;
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
    GLFWwindow* window = glfwCreateWindow(screenX, screenY, "2D Gravity", nullptr, nullptr);

    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glViewport(0, 0, screenX, screenY);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glOrtho(0, screenX, screenY, 0, -1, 1);

    float radius = 50.0f;
    float positionY = 300.0f;
    float velocityY = 0.0f;
    std::vector<float> position = { 800.0f,300.0f };
    std::vector<float> velocity = { 0.0f,0.0f };
    float groundLevel = 1500.0f;

    float lastTime = glfwGetTime();
    float debugTimer = 0.0f;
    int collisionCount = 0;


    while (!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();
        float dt = currentTime - lastTime;
        lastTime = currentTime;
        debugTimer += dt;

        glClear(GL_COLOR_BUFFER_BIT);
        drawShape(screenX, position[1], radius, 100);

        velocity[1] += GRAVITY_EARTH * dt;
        position[1] += velocity[1] * dt;

        if (position[1] >= groundLevel) {
            position[1] = groundLevel;
            velocity[1] *= -0.9f;
            collisionCount++;
        }

        //if (debugTimer >= 0.01f) { 
            //std::cout << "Time: " << currentTime
                //<< "s | Y-Position: " << position[1]
                //<< " | Velocity: " << velocity[1]
                //<< " | Collisions: " << collisionCount << "\n";
            //debugTimer = 0.0f;


        //}

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
