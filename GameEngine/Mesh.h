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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Material.h"

class Mesh {
    
public:
    Mesh(const Material& mat): material(mat) {};
    
    Program& get_program() { return material.program; };
    Material& get_material() { return material; };
    
    virtual void setup_vao() =0;
    virtual void setup_vbo() =0;
    virtual void setup_ibo() =0;
    
    virtual void update(const glm::vec3& pos) =0;
    virtual void draw(const glm::mat4& proj,
                      const glm::mat4& view) =0;
    
protected:
    Material material;
    
    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    
    glm::mat4 model;
};

#endif /* defined(__GameEngine__Mesh__) */
