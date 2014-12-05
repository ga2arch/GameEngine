//
//  Shader.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 05/12/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef GameEngine_Shader_h
#define GameEngine_Shader_h

#include "GLUtils.h"

class Shader {
    
public:
    enum Type { Vertex = GL_VERTEX_SHADER,
                Fragment = GL_FRAGMENT_SHADER };
    
    Shader(const char* filename, Type type) {
        shader_id = GLUtils::compile_shader_from_file(filename, type);
    }
    
    GLuint operator()() { return shader_id; }
    
private:
    GLuint shader_id;
    
};

#endif
