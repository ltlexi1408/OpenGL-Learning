#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define numVOAs 1

GLuint renderingProgram;
GLuint voa[numVOAs];

GLuint createShaderProgram(){
    const char *vshaderSource = 
        "#version 430   \n"
        "void main(void)\n"
        "{gl_Position = vec4(0.0, 0.0, 0.0, 1.0);}";
    const char *fshaderSource = 
        "#version 430   \n"
        "out vec4 color;\n"
        "void main(void)\n"
        "{color = vec4(0.0, 0.0, 1.0, 1.0);}";

        GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
        GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(vShader, 1, &vshaderSource, NULL);
        glShaderSource(fShader, 1, &fshaderSource, NULL);
        glCompileShader(vShader);
        glCompileShader(fShader);

        GLuint vfProgram = glCreateProgram();
        glAttachShader(vfProgram, vShader);
        glAttachShader(vfProgram, fShader);
        glLinkProgram(vfProgram);

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