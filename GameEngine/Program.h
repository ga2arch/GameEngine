//
//  Program.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 05/12/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef GameEngine_Program_h
#define GameEngine_Program_h

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLUtils.h"
#include "Shader.h"

class Program {
    
public:
    Program(Shader&& v, Shader&& f): vertex(std::move(v)), fragment(std::move(f)) {
        GLUtils::link_shaders(std::make_pair(v(), f()), program);
    }
    
    void use() { glUseProgram(program); }
    
    void set_uniform(const char* name, glm::mat4& v, int i = 0) {
        auto u = glGetUniformLocation(program, name);
        glUniformMatrix4fv(u+i, 1, GL_FALSE, glm::value_ptr(v));
    }
    
    void set_uniform(const char* name, glm::vec3& v, int i = 0) {
        auto u = glGetUniformLocation(program, name);
        glUniform3fv(u+i, 1, glm::value_ptr(v));
    }
    
    void set_uniform(const char* name, int v) {
        auto u = glGetUniformLocation(program, name);
        glUniform1i(u, v);
    }
    
private:
    Shader vertex;
    Shader fragment;
    
    GLuint program;
    
};

#endif
