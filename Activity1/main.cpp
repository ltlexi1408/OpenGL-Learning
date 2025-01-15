#include <GL/glew.h>
#include <GLFW/glfw3.h>

void init(GLFWwindow* window){}

void display(GLFWwindow* window, double currTime){
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow* window = glfwCreateWindow(600, 600, "practice v1", NULL, NULL);

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