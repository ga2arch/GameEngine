//
//  main.cpp
//  Renderer
//
//  Created by Gabriele Carrettoni on 27/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLUtils.h"
#include "Engine.h"
#include "Cube.h"

int main(int argc, const char * argv[]) {
    
    Engine engine(800, 600, "Test", "s.vertex", "s.fragment");
    auto cube = std::make_shared<Cube>();

    engine.add_shape(cube);
    
    engine.run();
    
}
