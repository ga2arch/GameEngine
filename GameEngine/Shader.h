//
//  Shader.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 29/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef __GameEngine__Shader__
#define __GameEngine__Shader__

#include <stdio.h>
#include "GLUtils.h"

class Shader {
    
public:
    Shader(const std::string& source, GLenum type);
    
    GLuint operator()();
    
protected:
    GLuint shader;
    GLenum type;
    
};

#endif /* defined(__GameEngine__Shader__) */
