//
//  Mesh.cpp
//  GameEngine
//
//  Created by Gabriele Carrettoni on 29/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include "Mesh.h"

void Mesh::draw(const glm::mat4 &proj, const glm::mat4 &view) {
    
    auto u_proj  = get_program().get_uniform("proj");
    auto u_view  = get_program().get_uniform("view");
    auto u_model = get_program().get_uniform("model");
    
    glUniformMatrix4fv(u_proj,  1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(u_view,  1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));
    
    material.begin();
    
    auto a_pos = get_program().get_attribute("position");
    auto a_norm = get_program().get_attribute("normal");
    
    glEnableVertexAttribArray(a_pos);
    glEnableVertexAttribArray(a_norm);
    
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    
    _draw();
    
    glDisableVertexAttribArray(a_pos);
    glDisableVertexAttribArray(a_norm);
}

void Mesh::setup_vao() {
    auto a_pos = get_program().get_attribute("position");
    auto a_norm = get_program().get_attribute("normal");
    
    vao = GLUtils::make_vao(GL_ARRAY_BUFFER, vbo);
    
    GLUtils::bind_vao(a_pos, 3, 6*sizeof(GLfloat));
    GLUtils::bind_vao(a_norm, 3, 6*sizeof(GLfloat), 3*sizeof(GLfloat));
}

void Mesh::setup_vbo() {
    vbo = GLUtils::make_vbo(GL_ARRAY_BUFFER,
                            buffer.data(),
                            buffer.size()*sizeof(GLfloat));
}

void Mesh::setup_ibo() {
    ibo = GLUtils::make_ibo(indices.data(),
                            indices.size()*sizeof(GLushort));
}

void Mesh::update(const glm::vec3& pos) {
    model = glm::translate(model, pos);
}

void Mesh::_draw() {
    glDrawElements(GL_TRIANGLE_STRIP,
                   indices.size(),
                   GL_UNSIGNED_SHORT, nullptr);
}
