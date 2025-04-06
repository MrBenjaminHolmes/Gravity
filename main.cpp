#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <array>
#include <ctime> 
#include <iostream>
#include <cstdlib>

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
double lastMouseX = 0.0, lastMouseY = 0.0;
bool isPanning = false;
float panX = 0.0f, panY = 0.0f;

class Object {
public:
    std::vector<float> position;
    std::vector<float> velocity;
    float radius;
    std::array<float, 3> colour = { 0.0f, 0.0f, 0.0f };
    Object(std::vector<float> position, std::vector<float> velocity, float radius = 15.0f, std::array<float, 3> colour = { 0.0f, 0.0f, 0.0f }) {
        this->position = position;
        this->velocity = velocity;
        this->radius = radius;
        this->colour = colour;
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
        glColor3f(colour[0], colour[1], colour[2]);
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
    void collision(Object& other) {
        float dx = this->position[0] - other.position[0];
        float dy = this->position[1] - other.position[1];
        float distance = sqrt((dx * dx) + (dy * dy));

        if (distance < this->radius + other.radius)
        {
            float angle = atan2(dy, dx);
            float speed1 = sqrt(this->velocity[0] * this->velocity[0] + this->velocity[1] * this->velocity[1]);
            float speed2 = sqrt(other.velocity[0] * other.velocity[0] + other.velocity[1] * other.velocity[1]);
            this->velocity[0] = speed2 * cos(angle);
            this->velocity[1] = speed2 * sin(angle);

            other.velocity[0] = speed1 * cos(angle + pi);
            other.velocity[1] = speed1 * sin(angle + pi);
        }
    }
    void checkCollisions(std::vector<Object>& objs) {
        for (auto& other : objs) {
            if (&other != this) {  
                collision(other);
            }
        }
    }
};


int main() {
    srand(static_cast<unsigned>(time(0)));
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0 + panX, 800 + panX, 800 + panY, 0 + panY, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    std::vector<Object> objs = {
        //Object(std::vector<float>{float(rand() % 801),float(rand() % 801)},std::vector<float>{0.0f, 0.0f},15.0f,std::array<float, 3>{float(rand() % 256) / 255.0f, float(rand() % 256) / 255.0f, float(rand() % 256)/255.0f}),
        //Object(std::vector<float>{float(rand() % 801),float(rand() % 801)},std::vector<float>{0.0f, 0.0f},15.0f,std::array<float, 3>{float(rand() % 256) / 255.0f, float(rand() % 256) / 255.0f, float(rand() % 256) / 255.0f}),
        //Object(std::vector<float>{float(rand() % 801),float(rand() % 801)},std::vector<float>{0.0f, 0.0f},15.0f,std::array<float, 3>{float(rand() % 256) / 255.0f, float(rand() % 256) / 255.0f, float(rand() % 256) / 255.0f}),
        //Object(std::vector<float>{float(rand() % 801),float(rand() % 801)},std::vector<float>{0.0f, 0.0f},15.0f,std::array<float, 3>{float(rand() % 256) / 255.0f, float(rand() % 256) / 255.0f, float(rand() % 256) / 255.0f})
        Object(std::vector<float>{400.0f,400.0f},std::vector<float>{0.0f, 0.0f},15.0f,std::array<float, 3>{float(rand() % 256) / 255.0f, float(rand() % 256) / 255.0f, float(rand() % 256) / 255.0f}),
        Object(std::vector<float>{400.0f,500.0f},std::vector<float>{0.0f, 0.0f},15.0f,std::array<float, 3>{float(rand() % 256) / 255.0f, float(rand() % 256) / 255.0f, float(rand() % 256) / 255.0f}),

    };
    float arrowForce = 0.5f;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glOrtho(0 + panX, 800 + panX, 800 + panY, 0 + panY, -1, 1);
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Detect middle mouse press/release
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
            if (!isPanning) {
                isPanning = true;
                lastMouseX = mouseX;
                lastMouseY = mouseY;
            }
            else {
                double deltaX = mouseX - lastMouseX;
                double deltaY = mouseY - lastMouseY;

                panX += static_cast<float>(deltaX);
                panY += static_cast<float>(deltaY);

                lastMouseX = mouseX;
                lastMouseY = mouseY;
            }
        }
        else {
            isPanning = false;
        }

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0 + panX, 800 + panX, 800 + panY, 0 + panY, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        float forceX = 0.0f;
        float forceY = 0.0f;

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            forceY -= arrowForce;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            forceY += arrowForce;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            forceX -= arrowForce;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            forceX += arrowForce;
        }

        for (auto& obj : objs) {
            
            obj.accelerate(0.00f, GRAVITY_EARTH / 12.0f);

            obj.accelerate(forceX, forceY);

            obj.updatePos();
            obj.checkCollisions(objs);

            // Wall collision bounds
            if (obj.position[1] <= 0) {
                obj.position[1] = 0;
                obj.velocity[1] *= -0.98;
            }
            if (obj.position[1] >= screenY) {
                obj.position[1] = screenY;
                obj.velocity[1] *= -0.98;
            }
            if (obj.position[0] <= 0) {
                obj.position[0] = 0;
                obj.velocity[0] *= -0.98;
            }
            if (obj.position[0] >= screenX) {
                obj.position[0] = screenX;
                obj.velocity[0] *= -0.98;
            }

            obj.drawShape();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}