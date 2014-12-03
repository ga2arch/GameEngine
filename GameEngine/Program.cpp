//
//  Program.cpp
//  GameEngine
//
//  Created by Gabriele Carrettoni on 29/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include "Program.h"

Program::Program(Shader vertex, Shader fragment) {
    
    auto shaders = std::make_pair(vertex(), fragment());
    GLUtils::link_shaders(shaders, program);
    
    add_uniform("proj");
    add_uniform("view");
    add_uniform("model");
    
    add_attribute("position");
    add_attribute("normal");
    add_attribute("uv");
    
    add_uniform("light_pos");
    add_uniform("irr");
    add_uniform("Ks");
    
    add_uniform("tex");
}

void Program::use() {
    glUseProgram(program);
}

void Program::add_attribute(const std::string name) {
    auto a = glGetAttribLocation(program, name.c_str());
    attributes.insert(std::make_pair(name, a));
}

void Program::add_uniform(const std::string name) {
    auto a = glGetUniformLocation(program, name.c_str());
    uniforms.insert(std::make_pair(name, a));
}

GLuint Program::get_attribute(const std::string name) {
    return attributes.at(name);
}

GLuint Program::get_uniform(const std::string name) {
    return uniforms.at(name);
}