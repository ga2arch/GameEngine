//
//  Light.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 07/12/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef GameEngine_Light_h
#define GameEngine_Light_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Program.h"

class Light {
    
public:
    Light(const glm::vec3& pos, const glm::vec3& dir): pos(pos), dir(dir) {}
    
    glm::mat4 light_view() {
        auto light_view = glm::perspective(45.0f, 1.0f, 1.0f, 100.0f);
        light_view *= glm::lookAt(pos, dir, glm::vec3(0,1,0));
        
        return light_view;
    }
    
    void set_uniforms(Program& program, int i = 0) {
        auto lv = light_view();
        
        program.set_uniform("light_view", lv, i);
        program.set_uniform("light_pos", pos, i);
        program.set_uniform("light_dir", dir, i);
    }
    
    glm::vec3 pos;
    glm::vec3 dir;
};

#endif