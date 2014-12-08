//
//  Camera.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 06/12/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef GameEngine_Camera_h
#define GameEngine_Camera_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Program.h"

class Camera {
    
public:
    Camera(const glm::vec3& pos,
           const glm::vec3& dir,
           const glm::vec3& up = glm::vec3(0,1,0),
           int w = 800,
           int h = 600,
           float fov = 45.0f,
           float near = 0.1f,
           float far  = 100.0f): pos(pos), dir(dir) {
        
        proj = glm::perspective(fov,
                                (float) w / (float) h,
                                near, far);
        
        view = glm::lookAt(pos, dir, up);
    }
    
    void set_uniforms(Program& program) {
        program.set_uniform("proj", proj);
        program.set_uniform("view", view);
        program.set_uniform("camera", pos);
    }
    
    void move(const glm::vec3& v) {
        pos += v;
        dir += v;
        view = glm::lookAt(pos, dir, up);
    }
    
    glm::vec3 pos;
    glm::vec3 dir;
    glm::vec3 up = glm::vec3(0,1,0);
    
    glm::mat4 proj;
    glm::mat4 view;
    
};

#endif
