//
//  Cube.cpp
//  Renderer
//
//  Created by Gabriele Carrettoni on 27/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include "Cube.h"

void Cube::setup_vbo() {
    vbo = GLUtils::make_vbo(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
}

void Cube::setup_vao() {
    vao = GLUtils::make_vao(GL_ARRAY_BUFFER, vbo, 3, 0);
}

void Cube::update() { return; }
void Cube::_setup_uniforms() { return; }
void Cube::_setup_attributes() { return; }

void Cube::_draw() {
    glDrawArrays(GL_TRIANGLES, 0, 12*3);
}