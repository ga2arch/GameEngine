//
//  Cube.h
//  Renderer
//
//  Created by Gabriele Carrettoni on 27/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef __Renderer__Shape__
#define __Renderer__Shape__

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLUtils.h"

class Shape {
    
public:
    ~Shape() {};
    
    virtual void setup_vbo()=0;
    virtual void setup_vao()=0;
    virtual void update()=0;
    virtual void _setup_uniforms()=0;
    virtual void _setup_attributes()=0;
    virtual void _draw()=0;
    
    void setup(GLuint program);
    void setup_attributes();
    void setup_uniforms();
    void draw();
    
protected: 
    GLuint program;
    GLuint vbo, vao;
    glm::mat4 model = glm::mat4(1.0f);
    
    struct {
        GLint position;
    } attributes;
    
    struct {
        GLint model;
    } uniforms;
    
};

#endif /* defined(__Renderer__Cube__) */
