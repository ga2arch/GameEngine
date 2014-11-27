//
//  main.cpp
//  Renderer
//
//  Created by Gabriele Carrettoni on 27/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLUtils.h"
#include "Cube.h"

int main(int argc, const char * argv[]) {
    
    int w, h;
    GLFWwindow* win;
    
    GLUtils::create_window("OpenGL", 800, 600, win);
    
    auto sh = GLUtils::compile_shaders_from_file("s.vertex", "s.fragment");
    
    GLuint program;
    if (GLUtils::link_shaders(sh, program)) {
        
        auto view = glm::lookAt(glm::vec3(1.2f, 3.2f, -4.2f),
                                glm::vec3(0.0f, 0.0f, 0.0f),
                                glm::vec3(0.0f, 1.0f, 0.0f));
        
        auto proj = glm::perspective(45.0f, 800.0f / 600.0f, 1.0f, 10.0f);
        
        auto u_proj = glGetUniformLocation(program, "proj");
        auto u_view = glGetUniformLocation(program, "view");
        
        Cube cube(1, 1, 1);
        cube.setup(program);
        
        while (!glfwWindowShouldClose(win)) {
            glfwGetWindowSize(win, &w, &h);
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
            glViewport(0, 0, w, h);
            glClearColor(0.0f, 0.0f, 0.0f, 0.8f);
            glUseProgram(program);

            glUniformMatrix4fv(u_proj, 1, GL_FALSE, glm::value_ptr(proj));
            glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view));

            cube.draw();
            
            glfwPollEvents();
            glfwSwapBuffers(win);
        }
    }
}
