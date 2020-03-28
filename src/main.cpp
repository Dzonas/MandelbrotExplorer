#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stdexcept>
#include <string>
#include "Shader.h"

const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 800;
const int FPS_ARRAY_LENGTH = 100;
const float STEP_SIZE = 0.1f;
const float ZOOM = 0.5f;
const int COLORMAP_SIZE = 16;

void error_callback(int error_code, const char *description);

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

void window_size_callback(GLFWwindow* window, int width, int height);

static float vertices[] = {
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f
};

static float colormap[COLORMAP_SIZE][3] = {
    {66, 30, 15},
    {25, 7, 26},
    {9, 1, 47},
    {4, 4, 73},
    {0, 7, 100},
    {12, 44, 138},
    {24, 82, 177},
    {57, 125, 209},
    {134, 181, 229},
    {211, 236, 248},
    {241, 233, 191},
    {248, 201, 95},
    {255, 170, 0},
    {204, 128, 0},
    {153, 87, 0},
    {106, 52, 3}
};

struct Camera {
    float center_x;
    float center_y;
    float width;
    float height;
};

int main() {
    glfwSetErrorCallback(&error_callback);
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    Camera camera{0.0f, 0.0f, 2.0f * static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT), 2.0f};

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Mandelbrot Explorer", nullptr, nullptr);
    glfwSetKeyCallback(window, &key_callback);
    glfwSetWindowSizeCallback(window, &window_size_callback);
    glfwSetWindowUserPointer(window, &camera);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwTerminate();
        throw std::runtime_error("failed to initialize GLAD");
    }

    glfwShowWindow(window);

    Shader shader;
    shader.init("shaders/vertex.glsl", "shaders/fragment.glsl");
    shader.use();
    float scaled_colormap[COLORMAP_SIZE][3];
    for(int i = 0; i < COLORMAP_SIZE; i++) {
        for(int j = 0; j < 3; j++) {
            scaled_colormap[i][j] = colormap[i][j] / 255.0f;
        }
    }
    shader.set_vec3("colormap", scaled_colormap[0], COLORMAP_SIZE);

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    double start = glfwGetTime();
    double end, dt;
    double fps[FPS_ARRAY_LENGTH];

    int i = 0;
    while (!glfwWindowShouldClose(window)) {
        end = glfwGetTime();
        dt = end - start;
        fps[i] = dt;
        start = end;
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::scale(view, glm::vec3(camera.width, camera.height, 1.0f));
        view = glm::translate(view, glm::vec3(camera.center_x * (1.0f / camera.width),
                                              camera.center_y * (1.0f / camera.height), 0.0f));
        shader.set_mat4("view", view);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (i < FPS_ARRAY_LENGTH - 1) {
            i++;
        } else {
            i = 0;
            double sum = 0.0;
            for (auto v : fps) {
                sum += v;
            }
            std::cout << "FPS: " << static_cast<float>(FPS_ARRAY_LENGTH) / sum << std::endl;
        }
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    shader.destroy();

    glfwTerminate();
    return 0;
}

void error_callback(int error_code, const char *description) {
    throw std::runtime_error(std::to_string(error_code) + ": " + description);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto camera = (Camera *) glfwGetWindowUserPointer(window);
    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        camera->center_x += camera->width * STEP_SIZE;
    }
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        camera->center_x -= camera->width * STEP_SIZE;
    }
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        camera->center_y += camera->height * STEP_SIZE;
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        camera->center_y -= camera->height * STEP_SIZE;
    }
    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        camera->width *= ZOOM;
        camera->height *= ZOOM;
    }
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        camera->width *= 1.0f / ZOOM;
        camera->height *= 1.0f / ZOOM;
    }
}

void window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
