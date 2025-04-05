#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <iostream>

const float pi = 3.141592653589;
const float GRAVITY_MERCURY = 3.7f;
const float GRAVITY_VENUS = 8.87f;
const float GRAVITY_EARTH = 9.81f;
const float GRAVITY_MARS = 3.71f;
const float GRAVITY_JUPITER = 24.79f;
const float GRAVITY_SATURN = 10.44f;
const float GRAVITY_URANUS = 8.69f;
const float GRAVITY_NEPTUNE = 11.15f;
const float GRAVITY_PLUTO = 0.62f;


class Object {
    public:
        std::vector<float> position;
        std::vector<float> velocity;
        float radius;
        Object(std::vector<float> position, std::vector<float> velocity, float radius =15.0f) {
            this->position = position;
            this->velocity = velocity;
            this->radius = radius;
        }
        void accelerate(float x, float y) {
            this->velocity[0] += x;
            this->velocity[1] += y;
        }
        void updatePos() {
            this->position[0] += this->velocity[0];
            this->position[1] += this->velocity[1];
        }
        void drawShape() {
            glBegin(GL_TRIANGLE_FAN);

            glVertex2f(this->position[0], this->position[1]);

            for (int i = 0; i <= 50; ++i) {
                float angle = 2.0f * pi * (static_cast<float>(i) / 50);
                float x = this->position[0] + cos(angle) * radius;
                float y = this->position[1] + sin(angle) * radius;
                glVertex2f(x, y);
            }
            glEnd();

        }
};

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
    std::vector<Object> objs = {
        Object(std::vector<float>{200.0f,500.0f},std::vector<float>{5.0f,0.0f}),
        Object(std::vector<float>{700.0f,500.0f},std::vector<float>{5.0f,0.0f})
    };

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        for (auto& obj : objs) {
            obj.accelerate(0.0f, 0.981);
            obj.updatePos();
            obj.drawShape();
            //Bottom Bounds
            if (obj.position[1] <= 0) {
                obj.position[1] = 0;  
                obj.velocity[1] *= -0.98; 
            }
            //Top Bounds
            if (obj.position[1] >= screenY) {
                obj.position[1] = screenY;  
                obj.velocity[1] *= -0.98;  
            }
            //Left Bounds
            if (obj.position[0] <= 0) {
                obj.position[0] = 0; 
                obj.velocity[0] *= -0.98; 
            }
            //Right Bounds
            if (obj.position[0] >= screenX) {
                obj.position[0] = screenX; 
                obj.velocity[0] *= -0.98; 
            }



        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
