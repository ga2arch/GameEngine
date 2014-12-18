//
//  Renderer.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 18/12/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef GameEngine_Renderer_h
#define GameEngine_Renderer_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include "Mesh.h"
#include "Light.h"

class Renderer {
    
public:
    
    void draw(Program& program, Light& light, int w, int h) {
        program.set_uniforms(light, w, h, 0);
        
        light.mesh.translate(light.pos);
        light.mesh.scale(glm::vec3(15,15,15));
        light.mesh.draw(program);
    }
    
};


#endif
