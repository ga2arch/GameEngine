//
//  Cube.cpp
//  GameEngine
//
//  Created by Gabriele Carrettoni on 29/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include "Cube.h"

void Cube::setup_vao() {
    auto a_pos = get_program().get_attribute("position");
    vao = GLUtils::make_vao(GL_ARRAY_BUFFER, vbo);
    
    GLUtils::bind_vao(a_pos, 3, 0);
}

void Cube::setup_vbo() {
    vbo = GLUtils::make_vbo(GL_ARRAY_BUFFER, vertices, 24*sizeof(GLfloat));
}

void Cube::setup_ibo() {
    ibo = GLUtils::make_ibo(indices, 14*sizeof(GLushort));
}

void Cube::update(const glm::vec3& pos) {
    model = glm::translate(model, pos);
}

void Cube::draw(const glm::mat4& proj,
                const glm::mat4& view) {
    
    material.begin(proj, view, model);
    
    auto a_pos = get_program().get_attribute("position");
    
    glEnableVertexAttribArray(a_pos);
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(GL_TRIANGLE_STRIP, 14, GL_UNSIGNED_SHORT, nullptr);
    //glDrawArrays(GL_TRIANGLES, 0, 12*3);
    
    glDisableVertexAttribArray(a_pos);
}
