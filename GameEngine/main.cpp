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
    
    auto camera = Camera(glm::vec3(0,20,20), glm::vec3(0,0,0));
    std::array<std::unique_ptr<Light>, 3> lights {
        std::unique_ptr<Light>(new SpotLight(glm::vec3(5,5,5), glm::vec3(0,0,0))),
        std::unique_ptr<Light>(new SpotLight(glm::vec3(-14,20,20), glm::vec3(0,0,0))),
        std::unique_ptr<Light>(new DirectionalLight(glm::vec3(20,10,10), glm::vec3(0,0,0)))
    };
    
    std::array<GLuint, 2> shadows;
    
    auto scene = Mesh();
    scene.load_mesh("scene2.obj");
   // scene.translate(glm::vec3(1,1,1));
    
    auto sphere = Mesh();
    sphere.load_mesh("sphere.obj");
    sphere.translate(lights[0]->pos);
    sphere.scale(glm::vec3(10,10,10));

    TestMaterial mat;
    scene.use_material(mat);
    //cube.rotate(glm::vec3(1,0,0), 90);
    

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
 
        program.use();
        program.set_uniform("p_tex", 1);
        program.set_uniform("n_tex", 2);
        
        program.set_uniforms(camera);

        //for (int i=0; i < lights.size(); i++) {
            program.set_uniforms(*lights[0], w, h, 0);
            program.set_uniforms(scene.material);
            sphere.draw(program);
        //}
                
        glfwPollEvents();
        glfwSwapBuffers(win);
        
        glfwSwapInterval(1);
    }
}
