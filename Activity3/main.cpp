#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>

#define numVOAs 1

GLuint renderingProgram;
GLuint voa[numVOAs];

std::string readShaderSource(const char *filePath){
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);
    std::string line = "";

    while(!fileStream.eof()){
        getline(fileStream, line);
        content.append(line);
        content.append("\n");
    }

    fileStream.close();

    return content;
}

void printShaderLog(GLuint shader){
    int len = 0;
    int chWritten = 0;
    char *log;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

    if (len > 0)
    {
        log = (char *)malloc(len);
        glGetShaderInfoLog(shader, len, &chWritten, log);
        std::cout << "Shader log: " << log << std::endl;
        free(log);
    }
}

void printProgramLog(int program){
    int len = 0;
    int chWritten = 0;
    char *log;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

    if (len > 0)
    {
        log = (char *)malloc(len);
        glGetProgramInfoLog(program, len, &chWritten, log);
        std::cout << "Program log: " << log << std::endl;
        free(log);
    }
}

bool checkOpenGLError(){
    bool foundError = false;
    int glError = glGetError();

    while(glError != GL_NO_ERROR){
        std::cout << "gl error: " << glError << std::endl;
        foundError = true;
        glError = glGetError();
    }

    return foundError;
}

GLuint createShaderProgram(){
    std::string vshaderSourceStr = readShaderSource("glsl/vertShader.glsl");
    std::string fshaderSourceStr = readShaderSource("glsl/fragShader.glsl");

    const char* vshaderSource = vshaderSourceStr.c_str();
    const char* fshaderSource = fshaderSourceStr.c_str();

    GLint vertCompiled;
    GLint fragCompiled;
    GLint linked;

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vShader, 1, &vshaderSource, NULL);
    glShaderSource(fShader, 1, &fshaderSource, NULL);

    glCompileShader(vShader);
    checkOpenGLError();
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
    if(vertCompiled != 1){
        std::cout << "Vertex compilation failed" << std::endl;
        printShaderLog(vShader);
    }

    glCompileShader(fShader);
    checkOpenGLError();
    glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
    if(fragCompiled != 1){
        std::cout << "Fragment compilation failed" << std::endl;
        printShaderLog(fShader);
    }

    GLuint vfProgram = glCreateProgram();
    glAttachShader(vfProgram, vShader);
    glAttachShader(vfProgram, fShader);

    glLinkProgram(vfProgram);
    checkOpenGLError();
    glGetProgramiv(vfProgram, GL_COMPILE_STATUS, &linked);
    if(linked != 1){
        std::cout << "Linking failed" << std::endl;
        printProgramLog(vfProgram);
    }

    return vfProgram;
}

void init(GLFWwindow* window){
    renderingProgram = createShaderProgram();
    glGenVertexArrays(numVOAs, voa);
    glBindVertexArray(voa[0]);
}

void display(GLFWwindow* window, double currTime){
    glUseProgram(renderingProgram);
    glPointSize(30.0f);
    glDrawArrays(GL_POINTS, 0, 1);
}

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(600, 600, "practice v2", NULL, NULL);

    glfwMakeContextCurrent(window);
    glewInit();
    glfwSwapInterval(1);

    init(window);

    while(!glfwWindowShouldClose(window)){
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}