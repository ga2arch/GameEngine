//
//  Program.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 29/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef __GameEngine__Program__
#define __GameEngine__Program__

#include <stdio.h>
#include <map>
#include "GLUtils.h"
#include "Shader.h"

class Program {
    
public:
    Program(Shader vertex, Shader fragment);
    
    void use();
    void add_uniform(const std::string name);
    void add_attribute(const std::string name);
    
    GLuint get_uniform(const std::string name);
    GLuint get_attribute(const std::string name);

protected:
    GLuint program;
    
    std::map<std::string, GLuint> uniforms;
    std::map<std::string, GLuint> attributes;

};

#endif /* defined(__GameEngine__Program__) */
