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
    auto u_texture = get_program().get_uniform("tex");

    glUniformMatrix4fv(u_proj,  1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(u_view,  1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));
    glUniform1i(u_texture, 0);
    
    material.begin();
    
    auto a_pos = get_program().get_attribute("position");
    auto a_norm = get_program().get_attribute("normal");
    auto a_uv = get_program().get_attribute("uv");

    glEnableVertexAttribArray(a_pos);
    glEnableVertexAttribArray(a_norm);
    glEnableVertexAttribArray(a_uv);

    glBindVertexArray(vao);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    
    _draw();
    
    glDisableVertexAttribArray(a_pos);
    glDisableVertexAttribArray(a_norm);
    glDisableVertexAttribArray(a_uv);
    //glDeleteTextures(1, &texture);
}

void Mesh::setup_vao() {
    auto a_pos = get_program().get_attribute("position");
    auto a_norm = get_program().get_attribute("normal");
    auto a_uv = get_program().get_attribute("uv");

    vao = GLUtils::make_vao(GL_ARRAY_BUFFER, vbo);
    
    GLUtils::bind_vao(a_pos,  3, 8*sizeof(GLfloat));
    GLUtils::bind_vao(a_norm, 3, 8*sizeof(GLfloat), 3*sizeof(GLfloat));
    GLUtils::bind_vao(a_uv,   2, 8*sizeof(GLfloat), 6*sizeof(GLfloat));

}

void Mesh::setup_vbo() {
    auto count = static_cast<int>(buffer.size());
    vbo = GLUtils::make_vbo(GL_ARRAY_BUFFER,
                            buffer.data(),
                            count*sizeof(GLfloat));
}

void Mesh::setup_ibo() {
    auto count = static_cast<int>(indices.size());
    ibo = GLUtils::make_ibo(indices.data(),
                            count*sizeof(GLushort));
}

void Mesh::setup_texture() {
}

void Mesh::update(const glm::vec3& pos) {
    model = glm::translate(model, pos);
}

void Mesh::_draw() {
    auto count = static_cast<int>(indices.size());
    glDrawElements(GL_TRIANGLE_STRIP,
                   count,
                   GL_UNSIGNED_SHORT,
                   nullptr);
}
