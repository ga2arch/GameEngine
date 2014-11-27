//
//  Cube.cpp
//  Renderer
//
//  Created by Gabriele Carrettoni on 27/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include "Cube.h"

void Cube::setup(GLuint program) {
    vbo = GLUtils::make_vbo(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
    vao = GLUtils::make_vao(GL_ARRAY_BUFFER, vbo, 3, 0);
    attributes.position = glGetAttribLocation(program, "position");
}

void Cube::draw() {
    glEnableVertexAttribArray (attributes.position);
    glBindVertexArray (vao);

    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/3);
    
    glDisableVertexAttribArray(attributes.position);
}