//
//  Material.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 29/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef __GameEngine__Material__
#define __GameEngine__Material__

#include <stdio.h>
#include "Program.h"

class Material {
    
public:
    Material(const Program& prog): program(prog) {};
    
protected:
    Program program;
    
};

#endif /* defined(__GameEngine__Material__) */
