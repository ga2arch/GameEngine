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

#include "Program.h"
#include "GLUtils.h"

glm::vec3 light_pos(-2.0, 2.0, -2);
glm::vec3 cube_pos(0.0, 0.0, -5.0);
glm::vec3 plane_pos(1,-1,-6);
glm::vec3 plane_scale(7,1,7);

std::vector<GLfloat> cube_buffer = {
    // Front-face
    // Pos              // Color          //Tex       // Norm
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Top-left
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Top-right
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Bottom-right
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Bottom-right
    -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //Bottom-left
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Top-left
    
    // Left-side-face
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, //Top-left
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, //Top-right
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, //Bottom-right
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, //Bottom-right
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, //Bottom-left
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, //Top-left.
    // Right-side-face
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //Left-top
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, //Right-top
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //Bottom-right
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //Bottom-right
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, //Bottom-left
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //Left-top
    
    // Top-face
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Front-left
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // Back-left
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // Back-right
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // Back-right
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Front-right
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Front-left
    
    // Bottom-face
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, // Front-left
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, // Front-right
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, // Back-right
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, // Back-right
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, // Back-left
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, // Front-left
    
    // Back-face
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, // Top-left
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, // Bottom-left
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, // Bottom-right
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, // Bottom-right
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, // Top-right
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, // Top-left
};
std::vector<GLfloat> plane_buffer = {
    // Front-face
    // Pos              // Color          //Tex       // Norm
    -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Top-left
    1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Top-right
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Bottom-right
    
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Bottom-right
    -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //Bottom-left
    -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Top-left
};

GLuint cube_vao, plane_vao;
GLuint cube_vbo, plane_vbo;
GLuint cube_ibo, plane_ibo;

Program program, shadow_program;

GLuint u_proj, u_view, u_model, u_cam_to_shadow;
GLuint shadowMapFBO, shadowMapTex, shadowMapTexDepth;

glm::mat4 model = glm::mat4(1.0);
glm::mat4 proj, view, mat;

int w = 800;
int h = 600;

void draw_cubes(Program& program, bool shadow_pass) {
    
    if (!shadow_pass) {
        program.set_uniform("do_texture", 1);
    }
    
    model = glm::translate(glm::mat4(), cube_pos);
    program.set_uniform("model", model);
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    if (!shadow_pass) {
        program.set_uniform("do_texture", 0);
    }
    
    model = glm::translate(glm::mat4(), plane_pos);
    model = glm::scale(model, plane_scale);

    program.set_uniform("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    if (!shadow_pass) {
        model = glm::translate(glm::mat4(), light_pos);
        model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
        program.set_uniform("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0);

}

void render_pass() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    program.use();
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, w, h);
    glClearColor(0.0f, 0.0f, 0.0f, 0.8f);
    
    proj = glm::perspective((float) 45, (float) w / (float) h, 0.1f, 100.0f);
    view = glm::lookAt(glm::vec3(0,5,0), glm::vec3(0, 0, -5), glm::vec3(0,1,0));
    
    program.set_uniform("proj", proj);
    program.set_uniform("view", view);
    program.set_uniform("shadow_matrix", mat);
    program.set_uniform("shadow_map", 0);
    
    glBindVertexArray(cube_vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, shadowMapTex);
    
    draw_cubes(program, false);
}

void shadow_pass() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, shadowMapFBO);
    
    shadow_program.use();
    
    glClearDepth(1.0f);
    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, w, h);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(2.0f, 4.0f);


    shadow_program.set_uniform("shadow_matrix", mat);
    glBindVertexArray(cube_vao);
    glEnableVertexAttribArray(0);
    
    draw_cubes(shadow_program, true);
    glDisable(GL_POLYGON_OFFSET_FILL);
}

int main(int argc, const char * argv[]) {
    
    
    GLFWwindow* win;
    GLUtils::create_window("shadows", w, h, win);
    
    // Programs
    program = Program(Shader("shader.vertex",GL_VERTEX_SHADER),
                      Shader("shader.fragment",GL_FRAGMENT_SHADER));
    
    shadow_program = Program(Shader("shadow.vertex",GL_VERTEX_SHADER),
                             Shader("shadow.fragment",GL_FRAGMENT_SHADER));

    // Bindings
    
    cube_vbo = GLUtils::make_vbo(GL_ARRAY_BUFFER,cube_buffer.data(),cube_buffer.size()*sizeof(GLfloat));
    //cube_ibo = GLUtils::make_ibo(cube_indices.data(),cube_indices.size()*sizeof(GLushort));
    
    cube_vao = GLUtils::make_vao(GL_ARRAY_BUFFER, cube_vbo);
    
    GLUtils::bind_vao(0, 3, 11*sizeof(GLfloat));
    GLUtils::bind_vao(1, 3, 11*sizeof(GLfloat), 8*sizeof(GLfloat));
    GLUtils::bind_vao(2, 2, 11*sizeof(GLfloat), 6*sizeof(GLfloat));
    
    
    plane_vbo = GLUtils::make_vbo(GL_ARRAY_BUFFER,plane_buffer.data(),plane_buffer.size()*sizeof(GLfloat));
    //plane_ibo = GLUtils::make_ibo(plane_indices.data(),plane_indices.size()*sizeof(GLushort));
    
    plane_vao = GLUtils::make_vao(GL_ARRAY_BUFFER, plane_vbo);
    
    GLUtils::bind_vao(0, 3, 8*sizeof(GLfloat));
    GLUtils::bind_vao(1, 3, 8*sizeof(GLfloat), 3*sizeof(GLfloat));
    GLUtils::bind_vao(2, 2, 8*sizeof(GLfloat), 6*sizeof(GLfloat));
    
    // Matrices
    proj = glm::perspective((float) 45, (float) w / (float) h, 0.1f, 100.0f);
    view = glm::lookAt(glm::vec3(0,5,0), glm::vec3(0, 0, -5), glm::vec3(0,1,0));
    
    mat = glm::perspective(60.0f, 1.0f, 1.0f, 10.0f);
    mat *= glm::lookAt(light_pos, cube_pos, glm::vec3(0,1,0));
    
    // Shadow
    
    glGenTextures(1, &shadowMapTex);
    glBindTexture(GL_TEXTURE_2D, shadowMapTex);
    glTexImage2D(GL_TEXTURE_2D, 0,
                 GL_DEPTH_COMPONENT32, w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // ShadowMap-FBO
    glGenFramebuffers(1, &shadowMapFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMapTex, 0);
    
    glDrawBuffer(GL_NONE);
    GLenum result = glCheckFramebufferStatus (GL_FRAMEBUFFER);
    
    if (GL_FRAMEBUFFER_COMPLETE != result) {
        printf ("ERROR: Framebuffer not complete.\n");
        return -1;	
    }
    
    // Loop
    
  
    while (!glfwWindowShouldClose(win)) {
        glfwGetWindowSize(win, &w, &h);
        
        shadow_pass();
        render_pass();
        
        glfwPollEvents();
        glfwSwapBuffers(win);
    }
    
}
