//
//  Cube.cpp
//  Renderer
//
//  Created by Gabriele Carrettoni on 27/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include "Shape.h"

void Shape::setup(GLuint p) {
    program = p;
    
    setup_vbo();
    setup_vao();
    setup_attributes();
    setup_uniforms();
}

void Shape::setup_attributes() {
    attributes.position = glGetAttribLocation(program, "position");
    _setup_attributes();
}

void Shape::setup_uniforms() {
    uniforms.model = glGetUniformLocation(program, "model");
    _setup_uniforms();
}

void Shape::draw() {
    glEnableVertexAttribArray (attributes.position);
    glBindVertexArray (vao);

    glUniformMatrix4fv(uniforms.model, 1, GL_FALSE, glm::value_ptr(model));
    _draw();
    
    glDisableVertexAttribArray(attributes.position);
}
