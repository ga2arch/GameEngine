//
//  main.cpp
//  GameEngine
//
//  Created by Gabriele Carrettoni on 05/12/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>

#include "GLUtils.h"
#include "Camera.h"
#include "Program.h"
#include "Shader.h"
#include "Mesh.h"
#include "Light.h"

int main() {
    int w = 800;
    int h = 600;
    
    GLFWwindow* win;
    GLUtils::create_window("test", w, h, win);
    auto program = Program(Shader("shader.vertex", Shader::Vertex),
                           Shader("shader.fragment", Shader::Fragment));
    
    auto shadow_program = Program(Shader("shadow.vertex", Shader::Vertex),
                                  Shader("shadow.fragment", Shader::Fragment));
    
    auto camera = Camera(glm::vec3(0,20,20), glm::vec3(0,0,0));
    auto light1  = Light(glm::vec3(5,20,20), glm::vec3(0,0,0));
    auto light2  = Light(glm::vec3(-10,1,1), glm::vec3(0,0,0));

    auto scene = Mesh();
    scene.load_mesh("scene2.obj");
    //cube.rotate(glm::vec3(1,0,0), 90);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    
    program.use();
    
    while (!glfwWindowShouldClose(win)) {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, w, h);
        glClearColor(0.0f, 0.0f, 0.0f, 0.8f);
        
        shadow_program.use();
        light1.set_uniforms(shadow_program);
        scene.shadows(shadow_program, program, w, h);
        
        camera.set_uniforms(program);
        light1.set_uniforms(program);
        light2.set_uniforms(program, 1);
        scene.draw(program);
        
        glfwPollEvents();
        glfwSwapBuffers(win);
        
        usleep(16 * 1000);
    }
    
}
