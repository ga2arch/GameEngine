//
//  Engine.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 29/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef __GameEngine__Engine__
#define __GameEngine__Engine__

#include <stdio.h>
#include <map>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLUtils.h"
#include "Mesh.h"

class Engine {
    
public:
    Engine(int w, int h, const char* title);
    
    void add_mesh(std::shared_ptr<Mesh> mesh);
    
    void draw();
    void run();
    
private:
    glm::mat4 view, proj;

    std::map<Program, std::vector<std::shared_ptr<Mesh>>> scene;

    struct {
        int w, h;
        GLFWwindow* win;
        const char* title;
    } window;
};

#endif /* defined(__GameEngine__Engine__) */
