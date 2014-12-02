//
//  Cube.cpp
//  GameEngine
//
//  Created by Gabriele Carrettoni on 29/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include "Cube.h"

void Cube::_draw() {
    glDrawElements(GL_TRIANGLE_STRIP,
                   indices.size(),
                   GL_UNSIGNED_SHORT, nullptr);
}