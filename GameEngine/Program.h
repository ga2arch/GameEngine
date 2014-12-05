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

#include "GLUtils.h"
#include "Shader.h"

class Program {
    
public:
    Program(Shader&& v, Shader&& f): vertex(std::move(v)), fragment(std::move(f)) {
        GLUtils::link_shaders(std::make_pair(v(), f()), program);
    }
    
private:
    Shader vertex;
    Shader fragment;
    
    GLuint program;
    
};

#endif
