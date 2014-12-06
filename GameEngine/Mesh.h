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
    
    struct MeshEntry {
        GLuint vbo, vao;
        std::vector<GLfloat> buffer;
    };
    
    struct Node {
        glm::mat4 model;
        std::vector<MeshEntry> meshes;
        std::vector<Node> nodes;
    };

    
public:
    Mesh() {};
    
    void load_mesh(const char* filename) {
        auto scene = aiImportFile(filename, aiProcess_Triangulate
                                  | aiProcess_GenSmoothNormals
                                  | aiProcess_FlipUVs);
        
        auto stream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT,NULL);
        aiAttachLogStream(&stream);
        
        if (scene) {
            load_scene(scene);
        } else {
            throw std::runtime_error("Cannot load mesh");
        }
    };
    
    void load_scene(const aiScene* scene) {
        for (int i=0; i < scene->mNumMeshes; i++)
            load_mesh(scene->mMeshes[i]);
        
        if (scene->mRootNode != nullptr) {
            root = load_node(scene->mRootNode);
        }
    }
    
    void load_mesh(const aiMesh* mesh) {
        MeshEntry m;
        
        const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
        
        for (int i = 0; i < mesh->mNumVertices; i++) {
            const auto pos = &(mesh->mVertices[i]);
            const auto normal = mesh->HasNormals() ? &(mesh->mNormals[i]) : &Zero3D;
            const auto texcoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero3D;
            
            m.buffer.push_back(pos->x);
            m.buffer.push_back(pos->y);
            m.buffer.push_back(pos->z);
            
            m.buffer.push_back(normal->x);
            m.buffer.push_back(normal->y);
            m.buffer.push_back(normal->z);
            
            m.buffer.push_back(texcoord->x);
            m.buffer.push_back(texcoord->y);
            
        }
                
        m.vbo = GLUtils::make_vbo(GL_ARRAY_BUFFER,
                                m.buffer.data(),
                                static_cast<int>(m.buffer.size()*sizeof(GLfloat)));
        m.vao = GLUtils::make_vao(GL_ARRAY_BUFFER, m.vbo);
        
        GLUtils::bind_vao(0, 3, 8*sizeof(GLfloat));
        GLUtils::bind_vao(1, 3, 8*sizeof(GLfloat), 3*sizeof(GLfloat));
        GLUtils::bind_vao(2, 2, 8*sizeof(GLfloat), 6*sizeof(GLfloat));
        
        meshes.push_back(m);
    }
    
    Node load_node(const aiNode* node) {
        Node n;
        
        n.model = glm::transpose(glm::make_mat4(node->mTransformation[0]));
        
        for (int i=0; i< node->mNumMeshes; i++) {
            n.meshes.push_back(meshes[node->mMeshes[i]]);
        }
        
        for (int i=0; i< node->mNumChildren; i++) {
            n.nodes.push_back(load_node(node->mChildren[i]));
        }
        
        return n;
    }
    
    void draw(const MeshEntry& m, bool shadow_pass = false) {
        glEnableVertexAttribArray(0);
        if (!shadow_pass) {
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
        }
        
        glBindVertexArray(m.vao);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m.buffer.size()/8));
        
        glDisableVertexAttribArray(0);
        if (!shadow_pass) {
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(2);
        }
    }
    
    void draw(Program& program, bool shadow_pass = false) {
        draw(program, root, shadow_pass);
    }
    
    void draw(Program& program,
              Node node,
              bool shadow_pass = false) {
        
        glm::mat4 toggle(1, 0, 0, 0,
                         0, 0, 1, 0,
                         0, 1, 0, 0,
                         0, 0, 0, 1);
        
        node.model = node.model * model;
        program.set_uniform("model", node.model);
        for (auto& m: node.meshes)
            draw(m);
        
        for (auto& n: node.nodes)
            draw(program, n);
    }
    
    void translate(const glm::vec3& v) {
        model = glm::translate(model, v);
    }
    
    void scale(const glm::vec3& v) {
        model = glm::scale(model, v);
    }
    
    void rotate(const glm::vec3& v, float angle) {
        model = glm::rotate(model, angle, v);
    }
    
private:
    glm::mat4 model = glm::mat4(1.0);
    
    std::vector<MeshEntry> meshes;
    Node root;
};

#endif
