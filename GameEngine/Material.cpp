//
//  Material.cpp
//  GameEngine
//
//  Created by Gabriele Carrettoni on 29/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include "Material.h"

void Material::begin() {
    auto u_color_diff  = program.get_uniform("color_diff");
    auto u_color_spec  = program.get_uniform("color_spec");
    auto u_irr = program.get_uniform("irr");

    glUniform3fv(u_color_diff, 1, glm::value_ptr(color_diff));
    glUniform3fv(u_color_spec, 1, glm::value_ptr(color_spec));
    glUniform3fv(u_irr, 1, glm::value_ptr(irr));
    
    _begin();
}