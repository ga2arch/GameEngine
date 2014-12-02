//
//  Engine.cpp
//  GameEngine
//
//  Created by Gabriele Carrettoni on 29/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include "Engine.h"

//std::default_random_engine rng_gen;
//std::uniform_real_distribution<float> rng_dist(0.0f, 1.0f);
//float rng() { return rng_dist(rng_gen); }

Engine::Engine(int w, int h, const char* title) {
    window.w = w;
    window.h = h;
    window.title = title;
    
    GLUtils::create_window(window.title, window.w, window.h, window.win);
    view = glm::lookAt(glm::vec3(-6.0f, 6.0f, 6.0f),
                       glm::vec3(0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 1.0f, 0.0f));
    
    proj = glm::perspective(45.0f, 800.0f / 600.0f, 1.0f, 100.0f);
}

void Engine::add_mesh(std::shared_ptr<Mesh> mesh) {
    auto& program = mesh->get_program();
    
    try {
        auto& m = scene.at(program);
        m.push_back(mesh);

    } catch (std::out_of_range&) {
        scene[program] = std::vector<std::shared_ptr<Mesh>>{mesh};
    }
    
}

void Engine::lighting() {
    
}

void Engine::draw() {
    for (const auto& kv: scene) {
        auto p = kv.first;
        p.use();
        
        auto ms = kv.second;
        
        for (auto& m: ms) {
            m->update(glm::vec3(0.0,0.0,0.0));
            
            //for (auto& l: lights) {
            auto& mat = m->get_material();
            light->precompute(mat.color_diff, mat.color_spec);
            
            //}
            light->upload(p);
            
            m->draw(proj, view);
        }
    }
}

void Engine::run() {
    while (!glfwWindowShouldClose(window.win)) {
        glfwGetWindowSize(window.win, &window.w, &window.h);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, window.w, window.h);
        glClearColor(0.0f, 0.0f, 0.0f, 0.8f);
        
        draw();
        
        glfwPollEvents();
        glfwSwapBuffers(window.win);
        
        usleep(16 * 1000);
    }
}