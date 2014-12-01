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