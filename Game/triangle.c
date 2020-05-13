#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm.h>   /* for library call (this also includes cglm.h) */

#include "triangle.h"
#include "vertexCoords.h"

mat4 model = GLM_MAT4_IDENTITY_INIT;

void drawTriangle(triangle tri, int myProgram) {
    
    unsigned int VAO, VBO;

    float vertices[] = {
        tri.one.x, tri.one.y, tri.one.z, // left  
         tri.two.x, tri.two.y, tri.two.z, // right 
         tri.three.x,  tri.three.y, tri.three.z  // top   
    };
    
    glUseProgram(myProgram);

    glUniformMatrix4fv(glGetUniformLocation(myProgram, "model"), 1, GL_FALSE, &model[0][0]);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0,3);

}

void setModel(float valueX, float valueY) {
    model[3][0] = valueX;
    model[3][1] = valueY;
}

double getModelX() {
    return model[3][0];
}

double getModelY() {
    return model[3][1];
}