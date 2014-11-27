//
//  Renderer.h
//  Renderer
//
//  Created by Gabriele Carrettoni on 27/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef __Renderer__Renderer__
#define __Renderer__Renderer__

#include <stdio.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLUtils.h"
#include "Shape.h"

class Engine {
    
public:
    Engine(int w, int h, const char* title, std::string vs, std::string fs) {
        window.w = w;
        window.h = h;
        window.title = title;
        
        vertex_source = vs;
        fragment_source = fs;
        
        setup();
    }
    
    void setup();
    
    void setup_window();
    void setup_shaders();
    void setup_attributes();
    void setup_uniforms();
    void setup_matrices();
    
    void update();
    void draw();
    
    void run();

    void add_shape(std::shared_ptr<Shape> shape);
    
    
private:
    std::vector<std::shared_ptr<Shape>> scene;
    
    std::string vertex_source, fragment_source;
    Shaders shaders;
    GLuint program;
    glm::mat4 view, proj;
    
    // Structs

    struct {
        int w, h;
        GLFWwindow* win;
        const char* title;
    } window;
    
    struct {
        GLint position;
    } attributes;
    
    struct {
        GLint proj;
        GLint view;
    } uniforms;
    
    struct {
        
    } varyings;
    
};

#endif /* defined(__Renderer__Renderer__) */
