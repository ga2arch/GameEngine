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
    Light(const glm::vec3& pos, const glm::vec3& dir): pos(pos), dir(dir) {
        is_enabled = true;
        is_local = true;
        is_spot = false;
        
        ambient = glm::vec3(.1, .1, .1);
        color = glm::vec3(1, 1, 1);
        irradiance = glm::vec3(30);
        
        spot_exp = 2.0;
        constant_attenuation = 1.0;
        linear_attenuation = 0.8;
        quadratic_attenuation = 0.0;
    }
    
    glm::mat4 light_view() {
        auto light_view = glm::perspective(45.0f, 1.0f, 1.0f, 100.0f);
        light_view *= glm::lookAt(pos, dir, glm::vec3(0,1,0));
        
        return light_view;
    }
    
    void set_uniforms(Program& program, int i = 0, bool shadow_pass = false) {
        auto lv = light_view();
        
        program.set_uniform("light_view", lv, i);
        
        if (!shadow_pass) {
            std::string s = "lights["+ std::to_string(i) +"].";
            
            program.set_uniform((s+"is_enabled").c_str(), is_enabled);
            program.set_uniform((s+"is_local").c_str(), is_local);
            program.set_uniform((s+"is_spot").c_str(), is_spot);
            
            program.set_uniform((s+"pos").c_str(), pos);
            program.set_uniform((s+"dir").c_str(), dir);
            program.set_uniform((s+"ambient").c_str(), ambient);
            program.set_uniform((s+"color").c_str(), color);
            program.set_uniform((s+"half_vector").c_str(), half_vector);
            
            program.set_uniform((s+"irradiance").c_str(), irradiance);
            program.set_uniform((s+"spot_cos_cutff").c_str(), spot_cos_cutff);
            program.set_uniform((s+"spot_exp").c_str(), spot_exp);
            program.set_uniform((s+"constant_attenuation").c_str(), constant_attenuation);
            program.set_uniform((s+"linear_attenuation").c_str(), linear_attenuation);
            program.set_uniform((s+"quadratic_attenuation").c_str(), quadratic_attenuation);

        }
    }
   
    bool is_enabled;
    bool is_local;
    bool is_spot;
    
    glm::vec3 pos;
    glm::vec3 dir;
    glm::vec3 ambient;
    glm::vec3 color;
    glm::vec3 half_vector;
    glm::vec3 irradiance;

    float spot_cos_cutff;
    float spot_exp;
    float constant_attenuation;
    float linear_attenuation;
    float quadratic_attenuation;
};

#endif
