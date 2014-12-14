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
#include "GBuffer.h"

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
    GBuffer gbuffer;
    
    auto program = Program(Shader("shader.vertex", Shader::Vertex),
                           Shader("shader.fragment", Shader::Fragment));
    
    auto shadow_program = Program(Shader("shadow.vertex", Shader::Vertex),
                                  Shader("shadow.fragment", Shader::Fragment));
    
    auto defer_program = Program(Shader("deferred.vertex", Shader::Vertex),
                                 Shader("deferred.fragment", Shader::Fragment));
    
    auto camera = Camera(glm::vec3(0,25,25), glm::vec3(0,0,0));
    std::array<std::unique_ptr<Light>, 1> lights {
        std::unique_ptr<Light>(new SpotLight(glm::vec3(-3,15,15), glm::vec3(0,0,0))),
        //std::unique_ptr<Light>(new SpotLight(glm::vec3(-3,3,3), glm::vec3(0,0,0)))
        //std::unique_ptr<Light>(new DirectionalLight(glm::vec3(20,10,10), glm::vec3(0,0,0)))
    };
    
    std::array<GLuint, 1> shadows;
    
    auto scene = Mesh();
    scene.load_mesh("scene2.obj");
   // scene.translate(glm::vec3(1,1,1));
    
    auto sphere = Mesh();
    sphere.load_mesh("sphere.obj");
    sphere.model = glm::translate(glm::mat4(), lights[0]->pos);
    sphere.scale(glm::vec3(15,15,15));
    
    TestMaterial mat;
    scene.use_material(mat);
    //cube.rotate(glm::vec3(1,0,0), 90);
    sphere.use_material(mat);
    
    glEnable (GL_CULL_FACE); // cull face
    glCullFace (GL_BACK); // cull back face
    glFrontFace (GL_CCW); // GL_CCW for counter clock-wise
    glViewport(0, 0, w, h);

    gbuffer.init(w, h);

    while (!glfwWindowShouldClose(win)) {
       
        glClearDepth(1.0f);
        glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        gbuffer.bind_writing();
        
        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);
        
        defer_program.use();
        defer_program.set_uniforms(camera);
        scene.draw(defer_program);
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(0.0f, 0.0f, 0.0f, 0.8f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        shadow_program.use();
        
        for (int i=0; i < lights.size(); i++) {
            shadow_program.set_uniforms(*lights[i], w, h, 0, true);
            shadows[i] = scene.shadows(shadow_program, w, h);
        }
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(0.0f, 0.0f, 0.0f, 0.8f);
        glClear (GL_COLOR_BUFFER_BIT);

        glEnable (GL_BLEND); // --- could reject background frags!
        glBlendEquation (GL_FUNC_ADD);
        glBlendFunc (GL_ONE, GL_ONE); // addition each time
        glDisable (GL_DEPTH_TEST);
        glDepthMask (GL_FALSE);
     
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gbuffer.textures[0]);
        
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, gbuffer.textures[1]);
        
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, gbuffer.textures[2]);
 
        program.use();
        program.set_uniform("p_tex", 1);
        program.set_uniform("n_tex", 2);
        program.set_uniform("w_tex", 3);

        program.set_uniform("shadow_map", 4);
        
        program.set_uniforms(camera);

        for (int i=0; i < lights.size(); i++) {
            glActiveTexture(GL_TEXTURE4);
            glBindTexture(GL_TEXTURE_2D, shadows[i]);
            
            program.set_uniforms(*lights[i], w, h, 0);
            
            sphere.draw(program);
        }
                
        glfwPollEvents();
        glfwSwapBuffers(win);
        
        glfwSwapInterval(1);
    }
}
