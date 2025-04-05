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

void drawShape(int screenX,int screenY, float radius, int noSides) {
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
    GLFWwindow* window = glfwCreateWindow(800, 800, "2D Gravity", nullptr, nullptr);

    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glViewport(0, 0, 800, 800);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glOrtho(0, screenX, screenY, 0, -1, 1); 

    float radius = 50.0f;
    float positionY = 300.0f;
    float velocityY = 0.0f;
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
        drawShape(screenX / 2.0f, positionY, radius, 100);

        velocityY += GRAVITY_EARTH * dt;
        positionY += velocityY * dt;

        if (positionY >= groundLevel) {
            positionY = groundLevel;
            velocityY *= -0.7f;
            collisionCount++;
        }

        if (debugTimer >= 0.01f) { // every 10ms
            std::cout << "Time: " << currentTime
                << "s | Y-Position: " << positionY

                << " | Collisions: " << collisionCount << "\n";
            debugTimer = 0.0f;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
