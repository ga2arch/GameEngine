//
//  Material.cpp
//  GameEngine
//
//  Created by Gabriele Carrettoni on 29/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include "Material.h"

void Material::begin(const glm::mat4& proj,
                     const glm::mat4& view,
                     const glm::mat4& model) {

    auto u_proj  = program.get_uniform("proj");
    auto u_view  = program.get_uniform("view");
    auto u_model = program.get_uniform("model");
    
    glUniformMatrix4fv(u_proj,  1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(u_view,  1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));
    
    _begin();
}