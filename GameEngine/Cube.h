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
    
};
#endif /* defined(__GameEngine__Cube__) */
