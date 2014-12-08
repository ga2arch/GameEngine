//
//  Material.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 07/12/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef GameEngine_Material_h
#define GameEngine_Material_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Program.h"

class Material {
    
public:
    Material() {
        emission = glm::vec3(0.0);
        ambient = glm::vec3(.1);
        diffuse = glm::vec3(.5);
        specular = glm::vec3(1);
        
        shininess = 80;
        
        ks = (float)(shininess+2)/(8);
        kd = diffuse/ (float)3.14;
    }
    
    void set_uniforms(Program& program, int i = 0) {
        std::string s = "material.";
        
        program.set_uniform((s+"emission").c_str(), emission);
        program.set_uniform((s+"ambient").c_str(), ambient);
        program.set_uniform((s+"diffuse").c_str(), diffuse);
        program.set_uniform((s+"specular").c_str(), specular);
        program.set_uniform((s+"shininess").c_str(), shininess);
        program.set_uniform((s+"ks").c_str(), ks);
        program.set_uniform((s+"kd").c_str(), kd);
    }
    
    glm::vec3 emission;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    
    float ks;
    glm::vec3 kd;
    
};

#endif
