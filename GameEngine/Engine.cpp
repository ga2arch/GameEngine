//
//  Engine.cpp
//  GameEngine
//
//  Created by Gabriele Carrettoni on 29/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include "Engine.h"

Engine::Engine(int w, int h, const char* title) {
    window.w = w;
    window.h = h;
    window.title = title;
    
    GLUtils::create_window(window.title, window.w, window.h, window.win);
    view = glm::lookAt(glm::vec3(3.0f, 3.0f, -5.0f),
                       glm::vec3(0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 1.0f, 0.0f));
    
    proj = glm::perspective(45.0f, 800.0f / 600.0f, 1.0f, 10.0f);
}

void Engine::add_mesh(std::shared_ptr<Mesh> mesh) {
    scene.push_back(mesh);
}

void Engine::draw() {
    for (auto& m: scene) {
        m->draw(proj, view, glm::vec3(0.0,0.0,0.0));
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
    }
}