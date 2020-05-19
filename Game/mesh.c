#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm.h>   /* for library call (this also includes cglm.h) */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

struct Vertex {
    vec3 Position;
    vec3 Normal;
    vec2 TexCoords;
} Vertex;

struct Texture {
    unsigned int id;
    char* type; // string
} Texture;

vector vertices;
vector indices;
vector textures;
unsigned int VAO, VBO, EBO;

/*void setUpMesh() {
    vector_init(&vertices);
    vector_init(&indices);
    vector_init(&textures);


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.total * sizeof(struct Vertex), &vertices.items[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.total * sizeof(unsigned int),
        &indices.items[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void*)offsetof(struct Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (void*)offsetof(struct Vertex, TexCoords));

    glBindVertexArray(0);

}

void Draw(int myProgram)
{
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.total; i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        char * number;
        char* name;
        vector_add(&vertices, &Vertex);
        vector_add(&textures, &Texture);

        strcpy(name, textures.items[i].type);
        
        if (name == "texture_diffuse") {
            diffuseNr++;
            itoa(diffuseNr, number, 10);
        }
        else if (name == "texture_specular") {
            specularNr++;
            itoa(diffuseNr, number, 10);
            // transfer unsigned int to stream
        }
        else if (name == "texture_normal") {
            normalNr++;
            itoa(normalNr, number, 10);
            // transfer unsigned int to stream
        }
        else if (name == "texture_height") {
            heightNr++;
            itoa(heightNr, number, 10);
            // transfer unsigned int to stream
        }

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(myProgram, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures.items[i].id);
    }

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.total, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}*/