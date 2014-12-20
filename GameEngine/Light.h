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

#include <cmath>
#include "Mesh.h"

class Light {
    
public:
    virtual ~Light() {};
    
    virtual glm::mat4 light_view(int w, int h) const =0;

    //Mesh mesh;
    
    bool is_enabled;
    bool is_local;
    bool is_spot;
    
    glm::vec3 pos;
    glm::vec3 eye_pos;
    glm::vec3 dir;
    glm::vec3 ambient;
    glm::vec3 color;
    glm::vec3 half_vector;
    glm::vec3 irradiance;

    float spot_exp;
    float spot_umbra;
    float spot_penumbra;
    float constant_attenuation;
    float linear_attenuation;
    float quadratic_attenuation;
};

class DirectionalLight: public Light {
    
public:
    DirectionalLight(const glm::vec3& p,
                     const glm::vec3& d) {
        
        pos = p;
        dir = d;

        is_enabled = true;
        is_local = true;
        is_spot = false;
        
        ambient = glm::vec3(.1, .1, .1);
        color = glm::vec3(.2, .8, 1);
        irradiance = glm::vec3(10);
        
        constant_attenuation = 0.2;
        linear_attenuation = 0.1;
        quadratic_attenuation = 0.0;
    }
    
    glm::mat4 light_view(int w, int h) const override {
        auto light_view = glm::ortho<float>(-10,10,-10,10,-10,50);//glm::perspective(45.0f, 1.33f, 1.0f, 100.0f);
        light_view *= glm::lookAt(pos, dir, glm::vec3(0,1,0));
        
        return light_view;
    }
    
};

class SpotLight: public Light {
    
public:
    SpotLight(const glm::vec3& p,
              const glm::vec3& d) {
        
        pos = p;
        dir = d;
        
        is_enabled = true;
        is_local = true;
        is_spot = true;
        
        ambient = glm::vec3(.1, .1, .1);
        color = glm::vec3(.2, .8, 1);
        irradiance = glm::vec3(60);
        
        spot_exp = 2.0;
        spot_umbra = cos(30 * 0.0174532925);
        spot_penumbra = cos(20 * 0.0174532925);
        
        constant_attenuation = 0.5;
        linear_attenuation = 0.3;
        quadratic_attenuation = 0.0;
    }
    
    glm::mat4 light_view(int w, int h) const override {
        auto light_view = glm::perspective(45.0f, (float)w/(float)h, 1.0f, 100.0f);
        light_view *= glm::lookAt(pos, dir, glm::vec3(0,1,0));
        
        return light_view;
    }

};

#endif
