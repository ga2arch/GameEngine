//
//  Plane.cpp
//  GameEngine
//
//  Created by Gabriele Carrettoni on 02/12/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include "Plane.h"

Plane::Plane(const Material& mat): Mesh(mat) {
    
    buffer = {
        -1.0, -1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
         1.0, -1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0,
         1.0,  1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0,
        -1.0,  1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0
    };
    
    indices = {
        0,  1,  2,
        2,  3,  0,
    };
    
    texture = GLUtils::load_texture("/Users/Gabriele/Dropbox/Progetti/c/GameEngine/GameEngine/hippie.png");
    setup();
    
    model = glm::scale(model, glm::vec3(5, 5, 5));
    model = glm::rotate(model, (glm::mediump_float)90.0, glm::vec3(1.0, 0.0, 0.0));
    model = glm::translate(model, glm::vec3(0.5,-0.5,0.5));
}

//void Plane::draw(const glm::mat4 &proj, const glm::mat4 &view) {
//    
//    auto u_proj  = get_program().get_uniform("proj");
//    auto u_view  = get_program().get_uniform("view");
//    auto u_model = get_program().get_uniform("model");
//    
//    glUniformMatrix4fv(u_proj,  1, GL_FALSE, glm::value_ptr(proj));
//    glUniformMatrix4fv(u_view,  1, GL_FALSE, glm::value_ptr(view));
//    glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));
//    
//    material.begin();
//    
//    auto a_pos = get_program().get_attribute("position");
//    auto a_norm = get_program().get_attribute("normal");
//    
//    glEnableVertexAttribArray(a_pos);
//    glEnableVertexAttribArray(a_norm);
//    glBindVertexArray(vao);
//    
//    _draw();
//    
//    glDisableVertexAttribArray(a_pos);
//    glDisableVertexAttribArray(a_norm);
//    //glDeleteTextures(1, &texture);
//}