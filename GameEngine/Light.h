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
    
    virtual void update(glm::mat4& m) {
        model = m;
    }
    
    virtual std::pair<glm::vec2,glm::vec2> bounding_box(int w, int h) {
        int rect[4] = { 0, 0, w, h };
        float d;
        
        float r  = radius;
        float r2 = r * r;
        
        auto l  = pos;
        auto l2 = pos*pos;
        
        float e1 = 1.2f;
        float e2 = 1.2f * w/h;
        
        d = r2 * l2.x - (l2.x + l2.z) * (r2 - l2.z);
        if (d >= 0) {
            d = sqrtf(d);
            
            float nx1 = (r*l.x + d) / (l2.x + l2.z);
            float nx2=(r*l.x - d)/(l2.x+l2.z);
            
            float nz1=(r-nx1*l.x)/l.z;
            float nz2=(r-nx2*l.x)/l.z;
            
            float e=1.25f;
            float a=w/h;
            
            float pz1=(l2.x+l2.z-r2)/(l.z-(nz1/nx1)*l.x);
            float pz2=(l2.x+l2.z-r2)/(l.z-(nz2/nx2)*l.x);
            
            if (pz1<0) {
                float fx=nz1*e1/nx1;
                int ix=(int)((fx+1.0f)*w*0.5f);
                
                float px=-pz1*nz1/nx1;
                if (px<l.x)
                    rect[0]=fmax(rect[0],ix);
                else
                    rect[2]=fmin(rect[2],ix);
            }
            
            if (pz2 < 0) {
                float fx=nz2*e1/nx2;
                int ix=(int)((fx+1.0f)*w*0.5f);
                
                float px=-pz2*nz2/nx2;
                if (px<l.x)
                    rect[0]=fmax(rect[0],ix);
                else
                    rect[2]=fmin(rect[2],ix);
                
            }
        }
        
        d=r2*l2.y - (l2.y+l2.z)*(r2-l2.z);
        if (d >= 0) {
            d=sqrtf(d);
            
            float ny1=(r*l.y + d)/(l2.y+l2.z);
            float ny2=(r*l.y - d)/(l2.y+l2.z);
            
            float nz1=(r-ny1*l.y)/l.z;
            float nz2=(r-ny2*l.y)/l.z;
            
            float pz1=(l2.y+l2.z-r2)/(l.z-(nz1/ny1)*l.y);
            float pz2=(l2.y+l2.z-r2)/(l.z-(nz2/ny2)*l.y);
            
            if (pz1 < 0) {
                float fy=nz1*e2/ny1;
                int iy=(int)((fy+1.0f)*h*0.5f);
                
                float py=-pz1*nz1/ny1;
                if (py<l.y)
                    rect[1]=fmax(rect[1],iy);
                else
                    rect[3]=fmin(rect[3],iy);
            }
            
            if (pz2 < 0) {
                float fy=nz2*e2/ny2;
                int iy=(int)((fy+1.0f)*h*0.5f);
                
                float py=-pz2*nz2/ny2;
                if (py<l.y)
                    rect[1]=fmax(rect[1],iy);
                else
                    rect[3]=fmin(rect[3],iy);
            }
        }
        
        return std::pair<glm::vec2,glm::vec2>(glm::vec2(rect[0], rect[1]),
                                              glm::vec2(rect[2], rect[3]));
    }
    
    glm::mat4 model = glm::mat4();
    
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
    
    float radius = 1;
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
              const glm::vec3& d,
              glm::vec3 color_ = glm::vec3(.8, .5, 1)) {
        
        pos = p;
        dir = d;
        
        is_enabled = true;
        is_local = true;
        is_spot = true;
        
        ambient = glm::vec3(.1, .1, .1);
        color = color_;
        irradiance = glm::vec3(20);
        
        spot_exp = 1.0;
        spot_umbra = cos(20 * 0.0174532925);
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
