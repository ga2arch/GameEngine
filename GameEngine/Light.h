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
#include "GLUtils.h"

class Light {
    
public:
    Light(glm::vec3 p): position(p) {}
    
    virtual void precompute(glm::vec3 color_diffuse,
                            glm::vec3 color_specular) =0;
    
    void upload(Program& program) {
        auto u_p = program.get_uniform("light_pos");
        auto u_kd = program.get_uniform("Kd");
        auto u_ks = program.get_uniform("Ks");
        
        glUniform3fv(u_p,  1, glm::value_ptr(position));
        glUniform3fv(u_kd, 1, glm::value_ptr(Kd));
        glUniform3fv(u_ks, 1, glm::value_ptr(Ks));
    }
    
protected:
    glm::vec3 position;

    glm::vec3 Kd;
    glm::vec3 Ks;
};

class DirectionalLight: public Light {
    
public:
    DirectionalLight(glm::vec3 p): Light(p) {}
    
    void precompute(glm::vec3 color_diffuse,
                    glm::vec3 color_specular) {
        
        Kd = color_diffuse / (float)M_PI;
        Ks = ((2.0f + 8) / (8.0f * (float)M_PI)) * color_specular;
    }
};

#endif /* defined(__GameEngine__Light__) */
