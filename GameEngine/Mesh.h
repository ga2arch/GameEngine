//
//  Mesh.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 06/12/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef GameEngine_Mesh_h
#define GameEngine_Mesh_h

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Program.h"

class Mesh {
    
public:
    Mesh() {};
    Mesh(std::vector<GLfloat>&& buffer): buffer(buffer) {};
    
    void load_mesh(const char* filename) {
        auto scene = aiImportFile(filename, aiProcess_Triangulate
                                  | aiProcess_GenSmoothNormals
                                  | aiProcess_FlipUVs);
        
        auto stream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT,NULL);
        aiAttachLogStream(&stream);
        
        if (scene) {
            load_scene(scene);
        }
    };
    
    void load_scene(const aiScene* scene) {
        auto mesh = scene->mMeshes[0];
        
        const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            const auto pos = &(mesh->mVertices[i]);
            const auto normal = mesh->HasNormals() ? &(mesh->mNormals[i]) : &Zero3D;
            const auto texcoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero3D;
            
            buffer.push_back(pos->x);
            buffer.push_back(pos->y);
            buffer.push_back(pos->z);
            
            buffer.push_back(texcoord->x);
            buffer.push_back(texcoord->y);
            
            buffer.push_back(normal->x);
            buffer.push_back(normal->y);
            buffer.push_back(normal->z);
        }
    }
    
    void draw(bool shadow_pass = false) {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        
        vbo = GLUtils::make_vbo(GL_ARRAY_BUFFER, buffer.data(), buffer.size()*sizeof(GLfloat));
        vao = GLUtils::make_vao(GL_ARRAY_BUFFER, vbo);
        
        GLUtils::bind_vao(0, 3, 8*sizeof(GLfloat));
        GLUtils::bind_vao(1, 3, 8*sizeof(GLfloat), 3*sizeof(GLfloat));
        GLUtils::bind_vao(2, 2, 8*sizeof(GLfloat), 6*sizeof(GLfloat));
        
        glDrawArrays(GL_TRIANGLES, 0, buffer.size()/3);
    }
    
private:
    GLuint vbo, vao;
    
    std::vector<GLfloat> buffer;
    //std::vector<GLushort> indices;
    
};

#endif
