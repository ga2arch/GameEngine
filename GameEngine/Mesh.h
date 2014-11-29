//
//  Mesh.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 29/11/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef __GameEngine__Mesh__
#define __GameEngine__Mesh__

#include <stdio.h>
#include "Material.h"

class Mesh {
    
public:
    Mesh(const Material& mat): material(mat) {};
    
    void setup();
    
    virtual void setup_vao() =0;
    virtual void setup_vertices() =0;
    
    virtual void draw() =0;
    
protected:
    Material material;
    GLuint vao;
    
};

#endif /* defined(__GameEngine__Mesh__) */
