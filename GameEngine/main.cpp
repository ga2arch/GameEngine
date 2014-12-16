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
    
    glm::vec3 position;
    glm::vec2 angles(3.14f, 0.0f);
    float prev_time = 0.0f;
    
    const float mousespeed = 0.001;
    const float movespeed  = 10;
    
    
    GLFWwindow* win;
    
    GLUtils::create_window("test", w, h, win);
    GBuffer gbuffer;
    
    auto program = Program(Shader("shader.vertex", Shader::Vertex),
                           Shader("shader.fragment", Shader::Fragment));
    
    auto shadow_program = Program(Shader("shadow.vertex", Shader::Vertex),
                                  Shader("shadow.fragment", Shader::Fragment));
    
    auto defer_program = Program(Shader("deferred.vertex", Shader::Vertex),
                                 Shader("deferred.fragment", Shader::Fragment));
    
    auto camera = Camera(glm::vec3(0,10,10), glm::vec3(0,10,10));
    position = camera.pos;
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

    gbuffer.init(w, h);

    while (!glfwWindowShouldClose(win)) {
       
        gbuffer.bind_writing();
        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);

        glClearDepth(1.0f);
        glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
            
            sphere.translate(lights[i]->pos);
            sphere.scale(glm::vec3(15,15,15));
            sphere.draw(program);
            
            sphere.model = glm::mat4();
        }
        
        // Camera movements
        
        double xpos, ypos;
        
        glfwGetCursorPos(win, &xpos, &ypos);
        int dx = xpos - w / 2;
        int dy = ypos - h / 2;

        // Do something with dx and dy here
        angles.x += dx * mousespeed;
        angles.y += dy * mousespeed;
        
        if(angles.x < -M_PI)
            angles.x += M_PI * 2;
        else if(angles.x > M_PI)
            angles.x -= M_PI * 2;
        
        if(angles.y < -M_PI / 2)
            angles.y = -M_PI / 2;
        if(angles.y > M_PI / 2)
            angles.y = M_PI / 2;
        
        glm::vec3 lookat;
        lookat.x = sinf(angles.x) * cosf(angles.y);
        lookat.y = sinf(angles.y);
        lookat.z = cosf(angles.x) * cosf(angles.y);
        
        camera.dir = camera.pos + lookat;
        
        float time = glfwGetTime();
        float delta_time = (time - prev_time);
        prev_time = time;
        
        auto right_dir = glm::vec3(sinf(angles.x - 3.14f/2.0f),
                                   0,
                                   cosf(angles.x - 3.14f/2.0f));
                                   
        auto up_dir = glm::cross(right_dir, lookat);
        
        // Update camera position
        if(glfwGetKey(win, GLFW_KEY_D))
            position += right_dir * movespeed * delta_time;
        
        if(glfwGetKey(win, GLFW_KEY_A))
            position -= right_dir * movespeed * delta_time;
        
        if(glfwGetKey(win, GLFW_KEY_W))
            position += lookat * movespeed * delta_time;
        
        if(glfwGetKey(win, GLFW_KEY_S))
            position -= lookat * movespeed * delta_time;
        
        if (glfwGetKey(win, GLFW_KEY_SPACE))
            position.y += movespeed * delta_time;
        
        if (glfwGetKey(win, GLFW_KEY_LEFT_ALT))
            position.y -= movespeed * delta_time;

        camera.up = up_dir;
        camera.pos = position;
        camera.view = glm::lookAt(camera.pos, camera.dir, camera.up);
        
        glfwSetCursorPos(win, w / 2, h / 2);
        
        glfwPollEvents();
        glfwSwapBuffers(win);
        
        glfwSwapInterval(1);
    }
}
