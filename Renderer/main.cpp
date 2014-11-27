//
//  main.cpp
//  Renderer
//
//  Created by Gabriele Carrettoni on 27/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include <iostream>
#include "GLUtils.h"
#include "Cube.h"

int main(int argc, const char * argv[]) {
    
    int w, h;
    GLFWwindow* win;
    
    GLUtils::create_window("OpenGL", 480, 320, win);
    
    auto sh = GLUtils::compile_shaders_from_file("s.vertex", "s.fragment");
    
    GLuint program;
    if (GLUtils::link_shaders(sh, program)) {
        Cube cube(10, 10, 10);
        cube.setup(program);
        
        while (!glfwWindowShouldClose(win)) {
            glfwGetWindowSize(win, &w, &h);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
            glViewport(0, 0, w, h);
            glClearColor(0.0f, 0.0f, 0.0f, 0.8f);
            glUseProgram(program);
            
            cube.draw();
            
            glfwPollEvents();
            glfwSwapBuffers(win);
        }
    }
}
