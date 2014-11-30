//
//  Cube.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 29/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef __GameEngine__Cube__
#define __GameEngine__Cube__

#include <stdio.h>
#include "Mesh.h"
#include "Material.h"

class Cube: public Mesh {
    
public:
    Cube(const Material& mat): Mesh(mat) {
        setup_vbo();
        setup_ibo();
        setup_vao();
    };
    
    void setup_vao() override;
    void setup_vbo() override;
    void setup_ibo() override;
    
    void update(const glm::vec3& pos) override;
    void draw(const glm::mat4& proj,
              const glm::mat4& view) override;
    
    void move(const glm::vec3& v) {
        model = glm::translate(model, v);
    }

private:
    const GLfloat vertices[24] = {
        -1.0, -1.0,  1.0,
        1.0, -1.0,  1.0,
        -1.0,  1.0,  1.0,
        1.0,  1.0,  1.0,
        -1.0, -1.0, -1.0,
        1.0, -1.0, -1.0,
        -1.0,  1.0, -1.0,
        1.0,  1.0, -1.0,
    };
    
    const GLushort indices[14] = {
        0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1
    };
};

#endif /* defined(__GameEngine__Cube__) */
