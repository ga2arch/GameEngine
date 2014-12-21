//
//  Mesh.h
//  GameEngine
//
//  Created by Gabriele Carrettoni on 06/12/14.
//  Copyright (c) 2014 Gabriele Carrettoni. All rights reserved.
//

#ifndef GameEngine_Mesh_h
#define GameEngine_Mesh_h

#include <iostream>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "GLUtils.h"
#include "Program.h"
#include "Material.h"

class Mesh {
    
    struct MeshEntry {
        GLuint vbo, vao, ibo;
        std::vector<GLfloat> buffer;
        std::vector<GLushort> indices;
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
        
        for (int i = 0; i < mesh->mNumFaces; i++) {
            auto face = &mesh->mFaces[i];
            assert(face->mNumIndices == 3);

            m.indices.push_back(face->mIndices[0]);
            m.indices.push_back(face->mIndices[1]);
            m.indices.push_back(face->mIndices[2]);
        }
        
        m.vbo = GLUtils::make_vbo(GL_ARRAY_BUFFER,
                                m.buffer.data(),
                                static_cast<int>(m.buffer.size()*sizeof(GLfloat)));
        m.vao = GLUtils::make_vao(GL_ARRAY_BUFFER, m.vbo);
        
        GLUtils::bind_vao(0, 3, 8*sizeof(GLfloat));
        GLUtils::bind_vao(1, 3, 8*sizeof(GLfloat), 3*sizeof(GLfloat));
        GLUtils::bind_vao(2, 2, 8*sizeof(GLfloat), 6*sizeof(GLfloat));
        
        m.ibo = GLUtils::make_ibo(m.indices.data(),
                                  static_cast<int>(m.indices.size()*sizeof(GLushort)));
        
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
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.ibo);

        glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m.buffer.size()/8));
//        glDrawElements(GL_TRIANGLES, m.indices.size(), GL_UNSIGNED_SHORT, nullptr);
        
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
        
        program.set_uniform("model", node.model * model);
        if (!shadow_pass) program.set_uniforms(material);
        
        for (auto& m: node.meshes)
            draw(m);
        
        for (auto& n: node.nodes)
            draw(program, n);
    }
    
    void translate(const glm::vec3& v) {
        model = glm::translate(model, v);
    }
    
    void move(const glm::vec3& v) {
        model = glm::translate(glm::mat4(), v);
    }
    
    void scale(const glm::vec3& v) {
        model = glm::scale(model, v);
    }
    
    void rotate(const glm::vec3& v, float angle) {
        model = glm::rotate(model, angle, v);
    }
    
    GLuint shadows(Program& shadow_program,
                   int w, int h) {
        GLuint shadow_map_tex, fbo;
        
        glGenTextures(1, &shadow_map_tex);
        glBindTexture(GL_TEXTURE_2D, shadow_map_tex);
        glTexImage2D(GL_TEXTURE_2D, 0,
                     GL_DEPTH_COMPONENT32, w, h, 0,
                     GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        // ShadowMap-FBO
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER,
                               GL_DEPTH_ATTACHMENT,
                               GL_TEXTURE_2D,
                               shadow_map_tex, 0);
        
        glDrawBuffer(GL_NONE);
        GLenum result = glCheckFramebufferStatus (GL_FRAMEBUFFER);
        
        if (GL_FRAMEBUFFER_COMPLETE != result) {
            throw std::runtime_error("ERROR: Framebuffer not complete.\n");
        }
        
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        
        glClearDepth(1.0f);
        glClear(GL_DEPTH_BUFFER_BIT);

        glDisable(GL_CULL_FACE);
        glViewport(0, 0, w, h);
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(2.0f, 4.0f);

        //glCullFace(GL_FRONT);
        draw(shadow_program, true);
        
        glDisable(GL_POLYGON_OFFSET_FILL);
        
        return shadow_map_tex;
     }
    
    void use_material(const Material& m) {
        material = m;
    }
    
    Material material;
    glm::mat4 model = glm::mat4(1.0);
    
    std::vector<MeshEntry> meshes;
    Node root;
};

#endif
