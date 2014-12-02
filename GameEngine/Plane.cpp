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
        -1.0, -1.0, 0.0, 0.0, 0.0, -1.0,
         1.0, -1.0, 0.0, 0.0, 0.0, -1.0,
         1.0,  1.0, 0.0, 0.0, 0.0, -1.0,
        -1.0,  1.0, 0.0, 0.0, 0.0, -1.0,
    };
    
    indices = {
        0,  1,  2,
        2,  3,  0,
    };
    
    setup();
    
    model = glm::scale(model, glm::vec3(5, 5, 5));
}