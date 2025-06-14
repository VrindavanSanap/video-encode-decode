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
    for (int y = 25; y< 75;y++){
        for (int x= 25; x< 75;x++){
            data[y*100*3+x*3] = 0x00;
            data[y*100*3+x*3+1] = 0x00;
            data[y*100*3+x*3+2] = 0xff;
        }
    }
    GLuint tex_handle;
    
    glfwMakeContextCurrent(window);
    glGenTextures(1, &tex_handle);
    glBindTexture(GL_TEXTURE_2D, tex_handle);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 100, 100, 0, GL_RGB, GL_UNSIGNED_BYTE,data);
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // setup orthographic projection
        int window_width,window_height;
        glfwGetFramebufferSize(window, &window_width, &window_height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0,window_width, 0, window_height, -1,1);
        
        glMatrixMode(GL_MODELVIEW);
        
        // Render whatever you want
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex_handle);
        glBegin(GL_QUADS);
        glTexCoord2d(0,0);glVertex2d(0, 0);
        glTexCoord2d(1,0);glVertex2d(100, 0);
        glTexCoord2d(1,1);glVertex2d(100, 100);
        glTexCoord2d(0,1);glVertex2d(0, 100);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glfwSwapBuffers(window);
        glfwWaitEvents();
        
    }
    //cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
    delete[] data;

    return 0;
}
