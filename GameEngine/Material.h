//
//  Material.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 29/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef __GameEngine__Material__
#define __GameEngine__Material__

#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Program.h"

class Material {
    
public:
    Material(const Program& prog): program(prog) {

    };
    
    virtual void _begin() {};
    
    void begin();
    
    Program program;
    
    glm::vec3 color_diff;
    glm::vec3 color_spec;
    glm::vec3 irr;
};

class Simple: public Material {
    
public:
    Simple(const Program& prog): Material(prog) {
        color_diff = glm::vec3(1.0, 0.0, 0.0);
        color_spec = glm::vec3(0.5, 0.5, 0.0);
        irr = glm::vec3(10.0);
    };
    
    void _begin() {}
    
};

#endif /* defined(__GameEngine__Material__) */
