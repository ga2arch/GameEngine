//
//  Material.cpp
//  GameEngine
//
//  Created by Gabriele Carrettoni on 29/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include "Material.h"

void Material::begin() {
    auto u_irr = program.get_uniform("irr");

    glUniform3fv(u_irr, 1, glm::value_ptr(irr));
    
    _begin();
}