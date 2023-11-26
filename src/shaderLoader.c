//
// Function for loading shader files
//
#include "shaderLoader.h"

GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path) {

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    FILE *VertexShaderStream = fopen(vertex_file_path, "r");
    if (VertexShaderStream == NULL) {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
        getchar();
        return 0;
    }

    fseek(VertexShaderStream, 0, SEEK_END);
    long VertexShaderCodeSize = ftell(VertexShaderStream);
    fseek(VertexShaderStream, 0, SEEK_SET);
    
    char *VertexShaderCode = (char *)malloc(VertexShaderCodeSize + 1);
    fread(VertexShaderCode, 1, VertexShaderCodeSize, VertexShaderStream);
    fclose(VertexShaderStream);
    VertexShaderCode[VertexShaderCodeSize] = '\0';

    // Read the Fragment Shader code from the file
    FILE *FragmentShaderStream = fopen(fragment_file_path, "r");
    if (FragmentShaderStream == NULL) {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", fragment_file_path);
        getchar();
        free(VertexShaderCode);
        return 0;
    }

    fseek(FragmentShaderStream, 0, SEEK_END);
    long FragmentShaderCodeSize = ftell(FragmentShaderStream);
    fseek(FragmentShaderStream, 0, SEEK_SET);
    
    char *FragmentShaderCode = (char *)malloc(FragmentShaderCodeSize + 1);
    fread(FragmentShaderCode, 1, FragmentShaderCodeSize, FragmentShaderStream);
    fclose(FragmentShaderStream);
    FragmentShaderCode[FragmentShaderCodeSize] = '\0';

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    printf("OpenGL: Compiling shader: %s\n", vertex_file_path);
    const char *VertexSourcePointer = VertexShaderCode;
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        char *VertexShaderErrorMessage = (char *)malloc(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, VertexShaderErrorMessage);
        printf("%s\n", VertexShaderErrorMessage);
        free(VertexShaderErrorMessage);
    }

    // Compile Fragment Shader
    printf("OpenGL: Compiling shader: %s\n", fragment_file_path);
    const char *FragmentSourcePointer = FragmentShaderCode;
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        char *FragmentShaderErrorMessage = (char *)malloc(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, FragmentShaderErrorMessage);
        printf("%s\n", FragmentShaderErrorMessage);
        free(FragmentShaderErrorMessage);
    }

    // Link the program
    printf("OpenGL: Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        char *ProgramErrorMessage = (char *)malloc(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, ProgramErrorMessage);
        printf("%s\n", ProgramErrorMessage);
        free(ProgramErrorMessage);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    free(VertexShaderCode);
    free(FragmentShaderCode);

    return ProgramID;
}
