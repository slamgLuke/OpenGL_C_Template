#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path);

#endif
