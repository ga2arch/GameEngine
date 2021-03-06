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
#include "Mesh.h"
#include "Light.h"
#include "GBuffer.h"

#include <chrono>
#include <OpenGL/OpenGL.h>

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
    
    auto camera = Camera(glm::vec3(0,15,15), glm::vec3(0,0,0));
    std::array<std::unique_ptr<Light>, 9> lights {
        std::unique_ptr<Light>(new SpotLight(glm::vec3(-4,8,0), glm::vec3(0,0,0), glm::vec3(.2, .4, .9))),
        std::unique_ptr<Light>(new SpotLight(glm::vec3(5,10,-5), glm::vec3(-5,0,-5))),
        std::unique_ptr<Light>(new SpotLight(glm::vec3(0,10,-5), glm::vec3(0,0,-5), glm::vec3(.2, .3, .9))),
        std::unique_ptr<Light>(new SpotLight(glm::vec3(2,6,3), glm::vec3(2,0,3))),
        std::unique_ptr<Light>(new SpotLight(glm::vec3(-8,3,3), glm::vec3(-8,0,3))),
        std::unique_ptr<Light>(new SpotLight(glm::vec3(-8,9,3), glm::vec3(-8,0,3))),
        std::unique_ptr<Light>(new SpotLight(glm::vec3(-1,3,3), glm::vec3(-8,0,3))),
        std::unique_ptr<Light>(new SpotLight(glm::vec3(8,3,3), glm::vec3(-8,0,3))),
        std::unique_ptr<Light>(new SpotLight(glm::vec3(2,3,3), glm::vec3(-8,0,3))),

    };
    
    std::array<GLuint, 1> shadows;
    
    auto scene = Mesh();
    scene.load_mesh("scene2.obj");
   // scene.translate(glm::vec3(1,1,1));
    
    auto sphere = Mesh();
    sphere.load_mesh("sphere.obj");

    
    TestMaterial mat;
    scene.use_material(mat);
    //cube.rotate(glm::vec3(1,0,0), 90);
    
    mat.emission = glm::vec3(1.0);
    sphere.use_material(mat);
    
    glEnable (GL_CULL_FACE); // cull face
    glCullFace (GL_BACK); // cull back face
    glFrontFace (GL_CCW); // GL_CCW for counter clock-wise
    glViewport(0, 0, w, h);

    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    
    std::vector<glm::ivec2> tiles;
    
    GLuint tex_tile_lights;
    glGenTextures(1, &tex_tile_lights);
    
    GLuint buffer_lights;
    glGenBuffers(1,&buffer_lights);
    
    while (!glfwWindowShouldClose(win)) {
        GLUtils::update_fps_counter(win);
        
        GLint VS_GPU, FS_GPU;
        
        CGLGetParameter(CGLGetCurrentContext(), kCGLCPGPUVertexProcessing,   &VS_GPU);
        CGLGetParameter(CGLGetCurrentContext(), kCGLCPGPUFragmentProcessing, &FS_GPU);
        
        printf("%s: Found %s vertex processing and %s fragment processing.\n",
               __FUNCTION__, (VS_GPU ? "GPU" : "CPU"), (FS_GPU ? "GPU" : "CPU"));
        
        float time = glfwGetTime();
        float delta_time = (time - prev_time);
        prev_time = time;

        tiles.clear();
        for (int i=0; i < (w/32)*(h/32); i++) {
            tiles.push_back(glm::ivec2(0, 0));
        }
        // Update
        
        //camera.update(win, delta_time);
        //scene.rotate(glm::vec3(0,1,0), 1);
        
        // Render
        
//        shadow_program.use();
//        for (int i=0; i < lights.size(); i++) {
////            lights[i]->eye_pos = glm::vec3(camera.view * glm::vec4(lights[i]->pos, 1.0));
//            shadow_program.set_uniforms(*lights[i], w, h, 0, true);
//            shadows[i] = scene.shadows(shadow_program, w, h);
//        }
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);
        
        int offset = 0;
        std::vector<float> tile_lights;
        
        for (int i=0; i < tiles.size(); i++) {
            for (int l=0; l < lights.size(); l++) {
                auto bbox = lights[l]->bounding_box(w, h);
                auto v1 = bbox.first/32.0f;
                auto v2 = bbox.second/32.0f;

                int start_tile_index = v1.x + v1.y * 800/32;
                int end_tile_index = v2.x + v2.y * 800/32;
                
                if (i >= start_tile_index && i <= end_tile_index) {
                    tile_lights.push_back(l);
                    
                    tiles[i].x += 1;
                    tiles[i].y = offset;
                }
            }
            offset += tiles[i].x;
        }
        
        program.use();
        program.set_uniforms(camera);
        
        glBindBuffer(GL_TEXTURE_BUFFER, buffer_lights);
        glBufferData(GL_TEXTURE_BUFFER, tile_lights.size()*sizeof(float),
                     tile_lights.data(), GL_STATIC_DRAW);
        //glBindBuffer(GL_TEXTURE_BUFFER, 0);
        
        glBindTexture(GL_TEXTURE_BUFFER, tex_tile_lights);
        glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, buffer_lights);
        
        GLenum errCode;
        const GLubyte *errString;
        
        if ((errCode = glGetError()) != GL_NO_ERROR) {
            errString = gluErrorString(errCode);
            fprintf (stderr, "OpenGL Error: %s\n", errString);
        }
        
        program.set_uniform("tex_tile_lights", 0);
        
        for (int i=0; i < tiles.size(); i++) {
            program.set_uniform("tiles", tiles[i], i);
        }
        
        for (int i=0; i < lights.size(); i++) {
            lights[i]->model = glm::rotate(lights[i]->model, 2.0f, glm::vec3(0,1,0));
            program.set_uniforms(*lights[i], camera, w, h, i);
            
            sphere.move(glm::vec3(lights[i]->model * glm::vec4(lights[i]->pos, 1.0)));
            sphere.scale(glm::vec3(.1,.1,.1));
            sphere.draw(program);
        }
        
        scene.draw(program);
        
        glfwSetCursorPos(win, w / 2, h / 2);
        
        glfwSwapInterval(1);
        glfwPollEvents();
        glfwSwapBuffers(win);
    }
}
