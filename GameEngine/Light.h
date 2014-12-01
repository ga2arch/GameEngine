//
//  Light.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 01/12/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef __GameEngine__Light__
#define __GameEngine__Light__

#include <stdio.h>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Program.h"

class Light {
    
public:
    virtual void set_uniforms(Program& program);
    
protected:
    glm::vec3 position;
    
    glm::vec3 irradiance;
    glm::vec3 color_diffuse;
    glm::vec3 color_specular;
    
    glm::vec3 Kd;
    glm::vec3 Ks;
};

class DirectionalLigth: public Light {
    
public:
    DirectionalLigth(glm::vec3 p, glm::vec3 i, glm::vec3 cd, glm::vec3 cs) {
        position       = p;
        irradiance     = i;
        color_diffuse  = cd;
        color_specular = cs;
        
        Kd = ((2.0f + 8) / (8.0f * (float)M_PI)) * color_specular;
        Ks = color_diffuse / (float)M_PI;
    }
};

#endif /* defined(__GameEngine__Light__) */
