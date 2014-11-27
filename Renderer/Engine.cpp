//
//  Renderer.cpp
//  Renderer
//
//  Created by Gabriele Carrettoni on 27/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include "Engine.h"

void Engine::setup() {
    setup_window();
    setup_shaders();
    setup_attributes();
    setup_uniforms();
    setup_matrices();
}

void Engine::setup_window() {
    GLUtils::create_window(window.title, window.w, window.h, window.win);
}

void Engine::setup_shaders() {
    auto r = GLUtils::compile_shaders(vertex_source, fragment_source);
    if (!GLUtils::link_shaders(r, program)) {
        throw std::runtime_error("Error linking program");
    }
}

void Engine::setup_matrices() {
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 0.0f, 0.0f),
                       glm::vec3(0.0f, 1.0f, 0.0f));
    
    proj = glm::perspective(45.0f, 800.0f / 600.0f, 1.0f, 10.0f);
}

void Engine::setup_uniforms() {
    uniforms.proj = glGetUniformLocation(program, "proj");
    uniforms.view = glGetUniformLocation(program, "view");
}

void Engine::setup_attributes() {
    
}