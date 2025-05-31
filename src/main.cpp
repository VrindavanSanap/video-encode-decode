#include <stdio.h>
#include <GLFW/glfw3.h>
int main(int argc, const char** argv	){
    printf("hello world \n");
    if(!glfwInit()){
        printf("Cant initliase glfw\n");
        return 1;
    }
    GLFWwindow* window;
    window= glfwCreateWindow(640, 480, "Hello world!", NULL, NULL);
    if (!window){
        printf("Failed to create a window");
        return 1;
    }
    
    glfwMakeContextCurrent(window);
    unsigned char* data = new unsigned char [100*100*3];
    for (int y = 0; y< 100;y++){
        for (int x= 0; x< 100;x++){
            data[y*100*3+x*3] = 0xff;
            data[y*100*3+x*3+1] = 0x00;
            data[y*100*3+x*3+2] = 0x00;
        }
    }
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawPixels(100, 100,  GL_RGB,GL_UNSIGNED_BYTE, data );
        glfwSwapBuffers(window);
        glfwWaitEvents();
        
    }
    //cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
    delete[] data;

    return 0;
}
