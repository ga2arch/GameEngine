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

#include "Cube.h"
#include "Plane.h"
#include "Program.h"
#include "Material.h"
#include "Engine.h"

int main(int argc, const char * argv[]) {
    
    Engine engine(800, 600, "Test");
    
    auto p = Program(Shader("s.vertex", GL_VERTEX_SHADER),
                     Shader("s.fragment", GL_FRAGMENT_SHADER));
    
    engine.add_mesh(std::make_shared<Cube>(Simple(p)));
    engine.set_light(std::make_shared<DirectionalLight>(glm::vec3(-100.0f, -100.0f, -200.0f)));
//    auto c = std::make_shared<Cube>(Simple(p));
//    c->update(glm::vec3(2.0f, 1.0f, 1.0f));
//    
//    engine.add_mesh(c);
    
    engine.run();
    
}
