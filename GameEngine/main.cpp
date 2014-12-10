//
//  main.cpp
//  GameEngine
//
//  Created by Gabriele Carrettoni on 05/12/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <array>

#include "GLUtils.h"
#include "Camera.h"
#include "Program.h"
#include "Shader.h"
#include "Mesh.h"
#include "Light.h"

int main() {
    int w = 800;
    int h = 600;
//    float last_time = 0.0;
//    float speed = 2.0;
//    double xpos, ypos;
//    float h_angle = 3.14f, v_angle = 0;
//    
    
    GLFWwindow* win;
    
    GLUtils::create_window("test", w, h, win);
    auto program = Program(Shader("shader.vertex", Shader::Vertex),
                           Shader("shader.fragment", Shader::Fragment));
    
    auto shadow_program = Program(Shader("shadow.vertex", Shader::Vertex),
                                  Shader("shadow.fragment", Shader::Fragment));
    
    auto camera = Camera(glm::vec3(0,20,20), glm::vec3(0,0,0));
    std::array<std::unique_ptr<Light>, 3> lights {
        std::unique_ptr<Light>(new SpotLight(glm::vec3(5,20,20), glm::vec3(0,0,0))),
        std::unique_ptr<Light>(new SpotLight(glm::vec3(-14,20,20), glm::vec3(0,0,0))),
        std::unique_ptr<Light>(new DirectionalLight(glm::vec3(20,20,20), glm::vec3(0,0,0)))
    };
    
    std::array<GLuint, 2> shadows;
    
    auto scene = Mesh();
    scene.load_mesh("scene2.obj");
    
    TestMaterial mat;
    scene.use_material(mat);
    //cube.rotate(glm::vec3(1,0,0), 90);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_MULTISAMPLE);

    while (!glfwWindowShouldClose(win)) {
        
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, w, h);
        glClearColor(0.0f, 0.0f, 0.0f, 0.8f);
        
        shadow_program.use();
        
        for (int i=0; i < lights.size(); i++) {
            shadow_program.set_uniforms(*lights[i], 0, true);
            shadows[i] = scene.shadows(shadow_program, w, h);
        }
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, w, h);
        glClearColor(0.0f, 0.0f, 0.0f, 0.8f);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);

        program.use();
        
        for (int i=0; i < lights.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, shadows[i]);
            
            program.set_uniform("shadow_map", i, i);
            program.set_uniforms(*lights[i], i);
        }
        
        camera.set_uniforms(program);
        program.set_uniform("lights_num", (int)lights.size());
        scene.draw(program);
        
        
//        // Camera
//        double current_time = glfwGetTime();
//        float delta_time = float(current_time - last_time);
//        last_time = current_time;
//        
//        glfwGetCursorPos(win, &xpos, &ypos);
//        
//        h_angle += .005 * delta_time * float(w/2 - xpos );
//        v_angle += .005 * delta_time * float(h/2 - ypos );
//        
//        glm::vec3 direction(cos(v_angle) * sin(h_angle),
//                            sin(v_angle),
//                            cos(v_angle) * cos(h_angle));
//        
//        glm::vec3 right = glm::vec3(sin(h_angle - 3.14f/2.0f),
//                                    0,
//                                    cos(h_angle - 3.14f/2.0f));
//        
//        glm::vec3 up = glm::cross( right, direction );
//        
//        camera.update(direction, up);
////        
//        if (glfwGetKey(win, GLFW_KEY_UP ) == GLFW_PRESS){
//            camera.move(direction * delta_time * speed);
//        }
//        // Move backward
//        if (glfwGetKey(win, GLFW_KEY_DOWN ) == GLFW_PRESS){
//            camera.move(-direction * delta_time * speed);
//        }
//        // Strafe right
//        if (glfwGetKey(win, GLFW_KEY_RIGHT ) == GLFW_PRESS){
//            camera.move(right * delta_time * speed);
//        }
//        // Strafe left
//        if (glfwGetKey(win, GLFW_KEY_LEFT ) == GLFW_PRESS){
//            camera.move(-right * delta_time * speed);
//        }
////
        glfwPollEvents();
        glfwSwapBuffers(win);
        
        //usleep(5 * 1000);
    }
    
}
