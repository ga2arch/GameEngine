//
//  Cube.cpp
//  GameEngine
//
//  Created by Gabriele Carrettoni on 29/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include "Cube.h"

void Cube::setup_vao() {
    vao = GLUtils::make_vao(GL_ARRAY_BUFFER, vbo_verts, 3, 0);
}

void Cube::setup_vertices() {
    vbo_verts = GLUtils::make_vbo(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
}

void Cube::draw(const glm::mat4& proj,
                const glm::mat4& view,
                const glm::vec3& pos) {
    
    model = glm::translate(model, pos);
    material.begin(proj, view, model);
    
    auto a_pos = material.program.get_attribute("position");
    
    glEnableVertexAttribArray(a_pos);
    glBindVertexArray(vao);
    
    glDrawArrays(GL_TRIANGLES, 0, 12*3);
    
    glDisableVertexAttribArray(a_pos);
}
