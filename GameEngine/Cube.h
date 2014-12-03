//
//  Cube.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 29/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef __GameEngine__Cube__
#define __GameEngine__Cube__

#include <stdio.h>
#include <vector>
#include "Mesh.h"
#include "Material.h"

class Cube: public Mesh {
    
public:
    Cube(const Material& mat);
//    
//    void update(const glm::vec3& v) {
//        model = glm::rotate(model, (glm::mediump_float)1.0, glm::vec3(0.0, 1.0, 0.0));
//    }
//    
};
#endif /* defined(__GameEngine__Cube__) */
