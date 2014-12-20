//
//  Program.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 05/12/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef GameEngine_Program_h
#define GameEngine_Program_h

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLUtils.h"
#include "Camera.h"
#include "Material.h"
#include "Light.h"
#include "Shader.h"

class Program {
    
public:
    Program(Shader&& v, Shader&& f): vertex(std::move(v)), fragment(std::move(f)) {
        GLUtils::link_shaders(std::make_pair(v(), f()), program);
    }
    
    void use() { glUseProgram(program); }
    
    void set_uniform(const char* name, const glm::mat4& v, int i = 0) {
        auto u = glGetUniformLocation(program, name);
        glUniformMatrix4fv(u+i*4, 1, GL_FALSE, glm::value_ptr(v));
    }
    
    void set_uniform(const char* name, const glm::vec3& v, int i = 0) {
        auto u = glGetUniformLocation(program, name);
        glUniform3fv(u+i, 1, glm::value_ptr(v));
    }
    
    void set_uniform(const char* name, const glm::ivec2& v, int i = 0) {
        auto u = glGetUniformLocation(program, name);
        glUniform2iv(u+i, 1, glm::value_ptr(v));
    }
    
    void set_uniform(const char* name, int v, int i = 0) {
        auto u = glGetUniformLocation(program, name);
        glUniform1i(u+i, v);
    }
    
    void set_uniform(const char* name, float v, int i = 0) {
        auto u = glGetUniformLocation(program, name);
        glUniform1f(u+i, v);
    }
    
    void set_uniform(const char* name, bool v, int i = 0) {
        auto u = glGetUniformLocation(program, name);
        glUniform1i(u+i, v ? 1 : 0);
    }
    
    void set_uniforms(const Light& light,
                      int w, int h,
                      int i = 0,
                      bool shadow_pass = false) {
        
        auto lv = light.light_view(w, h);
        
        set_uniform("light_view", lv, i);
        
        if (!shadow_pass) {
            std::string s = "lights["+ std::to_string(i) +"].";
            
            set_uniform((s+"is_enabled").c_str(), light.is_enabled);
            set_uniform((s+"is_local").c_str(), light.is_local);
            set_uniform((s+"is_spot").c_str(), light.is_spot);
            
            set_uniform((s+"pos").c_str(), light.pos);
            set_uniform((s+"eye_pos").c_str(), light.eye_pos);
            set_uniform((s+"dir").c_str(), light.dir);
            set_uniform((s+"ambient").c_str(), light.ambient);
            set_uniform((s+"color").c_str(), light.color);
            set_uniform((s+"half_vector").c_str(), light.half_vector);
            
            set_uniform((s+"irradiance").c_str(), light.irradiance);
            set_uniform((s+"spot_umbra").c_str(), light.spot_umbra);
            set_uniform((s+"spot_penumbra").c_str(), light.spot_penumbra);
            set_uniform((s+"spot_exp").c_str(), light.spot_exp);
            set_uniform((s+"constant_attenuation").c_str(), light.constant_attenuation);
            set_uniform((s+"linear_attenuation").c_str(), light.linear_attenuation);
            set_uniform((s+"quadratic_attenuation").c_str(), light.quadratic_attenuation);
            
        }
    }
    
    void set_uniforms(const Material& material, int i = 0) {
        std::string s = "material.";
        
        set_uniform((s+"emission").c_str(), material.emission);
        set_uniform((s+"ambient").c_str(), material.ambient);
        set_uniform((s+"diffuse").c_str(), material.diffuse);
        set_uniform((s+"specular").c_str(), material.specular);
        set_uniform((s+"shininess").c_str(), material.shininess);
        set_uniform((s+"ks").c_str(), material.ks);
        set_uniform((s+"kd").c_str(), material.kd);
    }
    
    void set_uniforms(Camera& cam) {
        set_uniform("proj", cam.proj);
        set_uniform("view", cam.view);
        set_uniform("camera", cam.pos);
    }
    
private:
    Shader vertex;
    Shader fragment;
    
    GLuint program;
    
};

#endif
