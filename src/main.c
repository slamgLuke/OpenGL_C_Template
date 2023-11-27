#include "initWindow.h"
#include "shaderLoader.h"

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>


#define SHADER_PATH "shaders/"
#define VERT_SHADER SHADER_PATH "vert.glsl"
#define FRAG_SHADER SHADER_PATH "frag.glsl"

#define WIDTH 600
#define HEIGHT 400


int main()
{
    glewExperimental = 1;
    GLFWwindow* window = initWindow(WIDTH, HEIGHT, "Hello World! :)");
    if (window == NULL) return 1;
    printf("OpenGL: version supported by this platform (%s): \n", glGetString(GL_VERSION));

    static const GLfloat vertexData[] = {
        0.15f, 0.15f, 1.f, // bottom left
        0.5f, 0.85f, 1.f, // top
        0.85f, 0.15f, 1.f // bottom right
    };

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // vertex coords
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // uv coords
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertexData), (void*)(sizeof(vec3) + sizeof(vec2)));


    glBindVertexArray(0);


    GLuint programID = LoadShaders(VERT_SHADER, FRAG_SHADER);


    // Main loop
    do {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.f, 1.f, 1.f, 1.f);

        glUseProgram(programID);


        // Draw triangle
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && // Exit if the ESC key was pressed
           glfwWindowShouldClose(window) == 0);                 // or window was closed
    

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(programID);


    glfwTerminate();
    return 0;
}
