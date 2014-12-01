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
    void _draw() override;
    
private:
    const GLfloat buffer[6*4*12] = {
        // front
        -1.0, -1.0,  1.0, 0.0, 0.0, 1.0,
        1.0, -1.0,  1.0,  0.0, 0.0, 1.0,
        1.0,  1.0,  1.0,  0.0, 0.0, 1.0,
        -1.0,  1.0,  1.0, 0.0, 0.0, 1.0,
        // top
        -1.0,  1.0,  1.0, 0.0, 1.0, 0.0,
        1.0,  1.0,  1.0,  0.0, 1.0, 0.0,
        1.0,  1.0, -1.0,  0.0, 1.0, 0.0,
        -1.0,  1.0, -1.0, 0.0, 1.0, 0.0,
        // back
        1.0, -1.0, -1.0,  0.0, 0.0, -1.0,
        -1.0, -1.0, -1.0, 0.0, 0.0, -1.0,
        -1.0,  1.0, -1.0, 0.0, 0.0, -1.0,
        1.0,  1.0, -1.0,  0.0, 0.0, -1.0,
        // bottom
        -1.0, -1.0, -1.0, 0.0, -1.0, 0.0,
        1.0, -1.0, -1.0,  0.0, -1.0, 0.0,
        1.0, -1.0,  1.0,  0.0, -1.0, 0.0,
        -1.0, -1.0,  1.0, 0.0, -1.0, 0.0,
        // left
        -1.0, -1.0, -1.0, -1.0, 0.0, 0.0,
        -1.0, -1.0,  1.0, -1.0, 0.0, 0.0,
        -1.0,  1.0,  1.0, -1.0, 0.0, 0.0,
        -1.0,  1.0, -1.0, -1.0, 0.0, 0.0,
        // right
        1.0, -1.0,  1.0,  1.0, 0.0, 0.0,
        1.0, -1.0, -1.0,  1.0, 0.0, 0.0,
        1.0,  1.0, -1.0,  1.0, 0.0, 0.0,
        1.0,  1.0,  1.0,  1.0, 0.0, 0.0,
    };
    
    const GLushort indices[6*6] = {
        // front
        0,  1,  2,
        2,  3,  0,
        // top
        4,  5,  6,
        6,  7,  4,
        // back
        8,  9, 10,
        10, 11,  8,
        // bottom
        12, 13, 14,
        14, 15, 12,
        // left
        16, 17, 18,
        18, 19, 16,
        // right
        20, 21, 22,
        22, 23, 20,
    };
};

#endif /* defined(__GameEngine__Cube__) */
