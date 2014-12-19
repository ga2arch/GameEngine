//
//  Camera.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 06/12/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef GameEngine_Camera_h
#define GameEngine_Camera_h

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLUtils.h"

class Camera {
    
public:
    Camera(const glm::vec3& pos,
           const glm::vec3& dir,
           const glm::vec3& up = glm::vec3(0,1,0),
           int w_ = 800,
           int h_ = 600,
           float fov = 45.0f,
           float near = 0.1f,
           float far  = 100.0f): pos(pos), dir(dir) {
        
        w = w_;
        h = h_;

        proj = glm::perspective(fov,
                                (float) w / (float) h,
                                near, far);
        
        view = glm::lookAt(pos, dir, up);
    }
        
    void update(GLFWwindow* win, float delta_time) {
        double xpos, ypos;
        
        glfwGetCursorPos(win, &xpos, &ypos);
        int dx = xpos - w / 2;
        int dy = ypos - h / 2;
        
        // Do something with dx and dy here
        angles.x += dx * mousespeed;
        angles.y += dy * mousespeed;
        
//        if(angles.x < -M_PI)
//            angles.x += M_PI * 2;
//        else if(angles.x > M_PI)
//            angles.x -= M_PI * 2;
//        
//        if(angles.y < -M_PI / 2)
//            angles.y = -M_PI / 2;
//        if(angles.y > M_PI / 2)
//            angles.y = M_PI / 2;
//        
//        glm::vec3 lookat;
//        lookat.x = sinf(angles.x) * cosf(angles.y);
//        lookat.y = sinf(angles.y);
//        lookat.z = cosf(angles.x) * cosf(angles.y);
//        
//        dir = pos + lookat;
//
//        auto right_dir = glm::vec3(sinf(angles.x - 3.14f/2.0f),
//                                   0,
//                                   cosf(angles.x - 3.14f/2.0f));
//        
//        up = glm::cross(right_dir, lookat);
//        
//        // Update camera position
        
        if(glfwGetKey(win, GLFW_KEY_W))
            view = glm::translate(view, glm::vec3(0,0,1)  * movespeed * delta_time);
        
        if(glfwGetKey(win, GLFW_KEY_A))
            view = glm::translate(view, glm::vec3(1,0,0)  * movespeed * delta_time);
        
        if(glfwGetKey(win, GLFW_KEY_S))
            view = glm::translate(view, glm::vec3(0,0,-1)  * movespeed * delta_time);
        
        if(glfwGetKey(win, GLFW_KEY_D))
            view = glm::translate(view, glm::vec3(-1,0,0)  * movespeed * delta_time);

        if(glfwGetKey(win, GLFW_KEY_LEFT_ALT))
            view = glm::translate(view, glm::vec3(0,1,0)  * movespeed * delta_time);
        
        if(glfwGetKey(win, GLFW_KEY_SPACE))
            view = glm::translate(view, glm::vec3(0,-1,0)  * movespeed * delta_time);
    }
    
    glm::vec2 angles = glm::vec2(-M_PI/2.0f, 0.0f);
    
    glm::vec3 pos;
    glm::vec3 dir;
    glm::vec3 up = glm::vec3(0,1,0);
    
    glm::mat4 proj;
    glm::mat4 view;
    
    int w, h;
    float mousespeed = 0.001;
    float movespeed = 10;
};

#endif
