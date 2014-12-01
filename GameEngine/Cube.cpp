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
    auto a_norm = get_program().get_attribute("normal");

    vao = GLUtils::make_vao(GL_ARRAY_BUFFER, vbo);
    
    GLUtils::bind_vao(a_pos, 3, 6*sizeof(GLfloat));
    GLUtils::bind_vao(a_norm, 3, 6*sizeof(GLfloat), 3*sizeof(GLfloat));
}

void Cube::setup_vbo() {
    vbo = GLUtils::make_vbo(GL_ARRAY_BUFFER, buffer, sizeof(buffer));
}

void Cube::setup_ibo() {
    ibo = GLUtils::make_ibo(indices, sizeof(indices));
}

void Cube::update(const glm::vec3& pos) {
    model = glm::translate(model, pos);
}

void Cube::draw(const glm::mat4& proj,
                const glm::mat4& view) {
    
    material.begin(proj, view, model);
    
    auto a_pos = get_program().get_attribute("position");
    auto a_norm = get_program().get_attribute("normal");

    glEnableVertexAttribArray(a_pos);
    glEnableVertexAttribArray(a_norm);

    glBindVertexArray(vao);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(GL_TRIANGLE_STRIP,
                   sizeof(indices)/sizeof(GLushort),
                   GL_UNSIGNED_SHORT, nullptr);
    
    glDisableVertexAttribArray(a_pos);
    glDisableVertexAttribArray(a_norm);

}
