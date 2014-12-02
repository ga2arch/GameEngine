//
//  Mesh.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 29/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef __GameEngine__Mesh__
#define __GameEngine__Mesh__

#include <stdio.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"

class Mesh {
    
public:
    Mesh(const Material& mat): material(mat) {};
    
    Program& get_program() { return material.program; };
    Material& get_material() { return material; };
    
    void setup() {
        setup_vbo();
        setup_ibo();
        setup_vao();
    }
    
    void draw(const glm::mat4& proj,
              const glm::mat4& view);
    
    void setup_vao();
    void setup_vbo();
    void setup_ibo();
    void update(const glm::vec3& pos);
    
    virtual void _draw();
    
protected:
    Material material;
    
    std::vector<GLushort> indices;
    std::vector<GLfloat>  buffer;
    
    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    
    glm::mat4 model = glm::mat4(1.0);
};

#endif /* defined(__GameEngine__Mesh__) */
