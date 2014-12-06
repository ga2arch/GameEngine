//
//  main.cpp
//  GameEngine
//
//  Created by Gabriele Carrettoni on 05/12/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include <stdio.h>

#include "GLUtils.h"
#include "Program.h"
#include "Shader.h"
#include "Mesh.h"

int main() {
    int w = 800;
    int h = 600;
    
    GLFWwindow* win;
    GLUtils::create_window("test", w, h, win);
    
    auto proj = glm::perspective((float) 45, (float) w / (float) h, 0.1f, 100.0f);
    auto view = glm::lookAt(glm::vec3(0,5,0), glm::vec3(0, 0, -5), glm::vec3(0,1,0));
    
    auto program = Program(Shader("shader.vertex", Shader::Vertex),
                           Shader("shader.fragment", Shader::Fragment));
    
    auto cube = Mesh();
    cube.load_mesh("cube.dae");
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    program.use();
    
    while (!glfwWindowShouldClose(win)) {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, w, h);
        glClearColor(0.0f, 0.0f, 0.0f, 0.8f);
        
        program.set_uniform("proj", proj);
        program.set_uniform("view", view);
        
        cube.draw(program);
        
        glfwPollEvents();
        glfwSwapBuffers(win);
    }
    
}
