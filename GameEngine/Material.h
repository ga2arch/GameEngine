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
    
    
    glm::vec3 emission;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    
    float ks;
    glm::vec3 kd;
    
};

#endif
