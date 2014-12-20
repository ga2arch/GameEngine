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
#include <glm/gtx/rotate_vector.hpp>
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
        yaw = pitch = 0.0f;
    }
        
    void update(GLFWwindow* win, float delta_time) {
        double xpos, ypos;
        
        glfwGetCursorPos(win, &xpos, &ypos);
        
        int dx = (xpos - w / 2);
        int dy = (ypos - h / 2);
        
        pitch += mousespeed * dy;
        yaw   += mousespeed * dx;

        if (pitch < -80) pitch = -80;
        if (pitch > +80) pitch = +80;
        
        forward.x = cosf(pitch)*sinf(yaw);
        forward.y = sinf(pitch);
        forward.z = cosf(pitch)*cosf(yaw);
        
        auto right = glm::vec3(sinf(yaw-3.14f/2.0f),0,cosf(yaw-3.14f/2.0f));
        up = glm::cross(right, forward);

        if(glfwGetKey(win, GLFW_KEY_W))
            pos += forward * movespeed * delta_time;
        
        if(glfwGetKey(win, GLFW_KEY_A))
            pos += -right  * movespeed * delta_time;
        
        if(glfwGetKey(win, GLFW_KEY_S))
            pos += -forward * movespeed * delta_time;
        
        if(glfwGetKey(win, GLFW_KEY_D))
            pos += right * movespeed * delta_time;

        if(glfwGetKey(win, GLFW_KEY_LEFT_ALT))
            pos += -up  * movespeed * delta_time;
        
        if(glfwGetKey(win, GLFW_KEY_SPACE))
            pos += up * movespeed * delta_time;
        
        //view = glm::lookAt(pos, pos + forward, up);
    }
    
    glm::vec3 pos;
    glm::vec3 dir;
    glm::vec3 up = glm::vec3(0,1,0);
    glm::vec3 forward;
    
    glm::mat4 proj;
    glm::mat4 view;
    
    int w, h;
    float yaw, pitch;
    float mousespeed = .001;
    float movespeed = 10;
};

#endif
