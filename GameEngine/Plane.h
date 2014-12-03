//
//  Plane.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 02/12/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef __GameEngine__Plane__
#define __GameEngine__Plane__

#include <stdio.h>
#include "Mesh.h"
#include "Material.h"

class Plane: public Mesh {
    
public:
    Plane(const Material& mat);
    
//    void draw(const glm::mat4& proj,
//              const glm::mat4& view);
};

#endif /* defined(__GameEngine__Plane__) */
