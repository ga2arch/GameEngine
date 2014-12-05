//
//  Program.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 04/12/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef __GameEngine__Program__
#define __GameEngine__Program__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <iostream>
#include "GLUtils.h"

class Shader {
    
public:
    Shader() {};
    
    Shader(const std::string source, GLenum type): type(type) {
        s = GLUtils::compile_shader_from_file(source, type);
    }
  
    GLuint operator()() { return s; }
    
private:
    GLenum type;
    GLuint s;
    
};

class Program {
    
public:
    Program() {};
    
    Program(Shader v, Shader f): v(v), f(f) {
        auto shs = std::make_pair(v(), f());
        GLUtils::link_shaders(shs, p);
    };
    
    void use() { glUseProgram(p); }
    
    void set_uniform(const char* name, glm::mat4 v) {
        auto u = glGetUniformLocation(p, name);
        glUniformMatrix4fv(u, 1, GL_FALSE, glm::value_ptr(v));
    }
    
    void set_uniform(const char* name, int v) {
        auto u = glGetUniformLocation(p, name);
        glUniform1i(u, v);
    }

    
private:
    Shader v;
    Shader f;
    
    GLuint p;
    
};

#endif /* defined(__GameEngine__Program__) */
