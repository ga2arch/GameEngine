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
    
    float prev_time = 0.0f;
    GLFWwindow* win;
    
    GLUtils::create_window("test", w, h, win);
    GBuffer gbuffer;
    gbuffer.init(w, h);

    auto program = Program(Shader("shader.vertex", Shader::Vertex),
                           Shader("shader.fragment", Shader::Fragment));
    
    auto shadow_program = Program(Shader("shadow.vertex", Shader::Vertex),
                                  Shader("shadow.fragment", Shader::Fragment));
    
    auto defer_program = Program(Shader("deferred.vertex", Shader::Vertex),
                                 Shader("deferred.fragment", Shader::Fragment));
    
    auto camera = Camera(glm::vec3(0,10,10), glm::vec3(0,10,10));
    std::array<std::unique_ptr<Light>, 2> lights {
        std::unique_ptr<Light>(new SpotLight(glm::vec3(-3,15,15), glm::vec3(0,0,0))),
        std::unique_ptr<Light>(new SpotLight(glm::vec3(5,15,15), glm::vec3(0,0,0)))
        //std::unique_ptr<Light>(new DirectionalLight(glm::vec3(20,10,10), glm::vec3(0,0,0)))
    };
    
    std::array<GLuint, 2> shadows;
    
    auto scene = Mesh();
    scene.load_mesh("scene2.obj");
   // scene.translate(glm::vec3(1,1,1));
    
    auto sphere = Mesh();
    sphere.load_mesh("sphere.obj");

    
    TestMaterial mat;
    scene.use_material(mat);
    //cube.rotate(glm::vec3(1,0,0), 90);
    sphere.use_material(mat);
    
    glEnable (GL_CULL_FACE); // cull face
    glCullFace (GL_BACK); // cull back face
    glFrontFace (GL_CCW); // GL_CCW for counter clock-wise
    glViewport(0, 0, w, h);


    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    while (!glfwWindowShouldClose(win)) {
       
        float time = glfwGetTime();
        float delta_time = (time - prev_time);
        prev_time = time;

        // Update
        
        camera.update(win, delta_time);
        scene.rotate(glm::vec3(0,1,0), 1);
        
        // Render
        
        // Deferred pass
        gbuffer.start();
        
        defer_program.use();
        defer_program.set_uniforms(camera);
        scene.draw(defer_program);
        
        gbuffer.stop();
        
        // Shadow pass
        shadow_program.use();
        for (int i=0; i < lights.size(); i++) {
            lights[i]->eye_pos = glm::vec3(camera.view * glm::vec4(lights[i]->pos, 1.0));
            shadow_program.set_uniforms(*lights[i], w, h, 0, true);
            shadows[i] = scene.shadows(shadow_program, w, h);
        }
        
        // Final pass
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(0.0f, 0.0f, 0.0f, 0.8f);
        glClear (GL_COLOR_BUFFER_BIT);

        glEnable (GL_BLEND); // --- could reject background frags!
        glBlendEquation (GL_FUNC_ADD);
        glBlendFunc (GL_ONE, GL_ONE); // addition each time
        glDisable (GL_DEPTH_TEST);
        glDepthMask (GL_FALSE);
     
        gbuffer.activate_textures();
 
        program.use();
        program.set_uniform("p_tex", 0);
        program.set_uniform("n_tex", 1);
        program.set_uniform("w_tex", 2);
        program.set_uniform("shadow_map", (int)gbuffer.textures.size());
        
        program.set_uniforms(camera);

        for (int i=0; i < lights.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + gbuffer.textures.size());
            glBindTexture(GL_TEXTURE_2D, shadows[i]);
            
            program.set_uniforms(*lights[i], w, h, 0);
            
            sphere.translate(lights[i]->pos);
            sphere.scale(glm::vec3(15,15,15));
            sphere.draw(program);
            
            sphere.model = glm::mat4();
        }

        glfwSetCursorPos(win, w / 2, h / 2);
        
        glfwPollEvents();
        glfwSwapBuffers(win);
        
        glfwSwapInterval(1);
    }
}
