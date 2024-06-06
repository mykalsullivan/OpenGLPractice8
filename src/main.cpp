//
// Created by msullivan on 5/31/24.
//

#include <iostream>
#include <memory>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "window.h"
#include "mesh.h"
#include "shader.h"
#include "camera.h"

namespace
{
    // Shader stuff
    const char* vertexShader = "/home/msullivan/Projects/CLionProjects/OpenGLPractice8/src/Shaders/shader.vert";
    const char* fragmentShader = "/home/msullivan/Projects/CLionProjects/OpenGLPractice8/src/Shaders/shader.frag";

    unsigned int uniformProjection = 0, uniformModel = 0, uniformView = 0;
    std::vector<std::shared_ptr<Mesh>> meshes;
    std::vector<std::shared_ptr<Shader>> shaders;
    Camera camera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 10.0f, 0.5f);

    float deltaTime = 0.0f;
    float lastTime = 0.0f;
}

void createObjects()
{
    unsigned int indices[] = {
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2
    };

    // Create vertex coordinates
    float vertices[] = {
            -1.0f, -1.0f, 0.0f,
            0.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 0.0f,
            1.0f, 1.0f, 0.0f
    };

    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    mesh->create(vertices, indices, 12, 12);
    meshes.emplace_back(mesh);
}

void createShaders()
{
    std::shared_ptr<Shader> shader = std::make_shared<Shader>();
    shader->createFromFiles(vertexShader, fragmentShader);
    shaders.emplace_back(shader);
}

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cout << "GLFW failed to initialize\n";

        // Unload GLFW memory
        glfwTerminate();
        return 1;
    }

    GLWindow window(800, 600);
    window.init();

    // Allow modern extension features
    glewExperimental = true;

    // Setup GLEW
    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW failed to initialize\n";
        glfwTerminate();
        return 1;
    }

    createObjects();
    createShaders();

    glm::mat4 projection = glm::perspective(45.0f, 16.0f/9.0f, 0.1f, 100.0f);
    glm::mat4 model(1.0f);

    model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));


    // Main loop
    while (!window.shouldClose())
    {
        // Used to keep framerate consistent
        auto now = (float) glfwGetTime();   // SDL_GetPerformanceCounter();
        deltaTime = now - lastTime;         // (now - lastTime) * 1000/SDL_GetPerformanceFrequency();
        lastTime = now;

        // Get/handle user input
        glfwPollEvents();

        // Control camera
        camera.keyControl(window.getKeys(), deltaTime);
        camera.mouseControl(window.getChangeX(), window.getChangeY());

        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaders[0]->use();
        uniformProjection = shaders[0]->getProjectionLocation();
        uniformModel = shaders[0]->getModelLocation();
        uniformView = shaders[0]->getViewLocation();

        glUniformMatrix4fv((int) uniformModel, 1, false, glm::value_ptr(model));
        glUniformMatrix4fv((int) uniformProjection, 1, false, glm::value_ptr(projection));
        glUniformMatrix4fv((int) uniformView, 1, false, glm::value_ptr(camera.calculateViewMatrix()));

        for (const auto& mesh : meshes) mesh->render();

        glUseProgram(0);

        // Swap display buffers
        window.swapBuffers();
    }
    return 0;
}