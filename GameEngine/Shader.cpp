//
//  Shader.cpp
//  GameEngine
//
//  Created by Gabriele Carrettoni on 29/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include "Shader.h"

Shader::Shader(const std::string& source, GLenum type_) {
    type = type_;
    shader = GLUtils::compile_shader_from_file(source, type);
}

GLuint Shader::operator()() {
    return shader;
}