#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <cglm.h>  
#include "vector.h"
#include "vertexCoords.h"
#include "modelLoader.h"
#include "vector.h"


vector vecInfo;
vector uvInfo;
vector normInfo;

// Indices
vector vertexIndices;
vector uvIndices;
vector normalIndices;

// Out Indices Struct
vector outVertex;
float arrayFloat[43031 * 3] = { 0.0 };
unsigned int indicesArray[43031 * 3] = { 0 };
float vertexArray[23382 * 3] = { 0.0 };

// TexVertices & normals
float texArray[] = { 0.0 };
float normArray[] = { 0.0 };

int loadModel(int myProgram) {
	vector_init(&vecInfo); // vertices
	vector_init(&uvInfo); // tex coords
	vector_init(&normInfo); // normals

	//Indices:
	vector_init(&vertexIndices); // indices vertices
	vector_init(&uvIndices); // indices tex coord
	vector_init(&normalIndices); // indices normals

	// Out_vertices: Do the same with the texss and normals
	vector_init(&outVertex); // indices vertices
	//vector_init(&uvIndices); // indices tex coord
	//vector_init(&normalIndices); // indices normals
	
	// File Pointer
	char* path = "C:\\Users\\scomi\\Desktop\\mike2.obj";
	//char* path = "C:\\Users\\scomi\\Desktop\\build.obj";
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return 0;
	}
	// Open File

	// Read file and load vertex data
	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// Position
		if (strcmp(lineHeader, "v") == 0) {
			vertex* shape = malloc(sizeof(vertex));
			fscanf(file, "%f %f %f\n", &(shape->x), &(shape->y), &(shape->z));
			vector_add(&vecInfo, shape);
		}
		// Texture Coordinate
		else if (strcmp(lineHeader, "vt") == 0) {
			texVertex* tex = malloc(sizeof(texVertex));
			fscanf(file, "%f %f\n", &(tex->x), &(tex->y));
			vector_add(&uvInfo, tex);
		}
		// Normal
		else if (strcmp(lineHeader, "vn") == 0) {
			normalVertex* nTex = malloc(sizeof(normalVertex));
			fscanf(file, "%f %f %f\n", &(nTex->x), &(nTex->y), &(nTex->z));
			vector_add(&normInfo, nTex);
		}

		// Indices!
		else if (strcmp(lineHeader, "f") == 0) {
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return 0;
			}
			printf("Vals: %u, %u, %u\n", vertexIndex[0], vertexIndex[1], vertexIndex[2]);
			indicesVertex* vI = malloc(sizeof(indicesVertex));
			vI->x = vertexIndex[0];
			vI->y = vertexIndex[1];
			vI->z = vertexIndex[2];
			vector_add(&vertexIndices, vI);
			//vector_add(&vertexIndices, (vertexIndex + 1));
			//vector_add(&vertexIndices, (vertexIndex + 2));

			vector_add(&uvIndices, &uvIndex[0]);
			vector_add(&uvIndices, &uvIndex[1]);
			vector_add(&uvIndices, &uvIndex[2]);

			vector_add(&normalIndices, &normalIndex[0]);
			vector_add(&normalIndices, &normalIndex[1]);
			vector_add(&normalIndices, &normalIndex[2]);
		}

	}
	// Put ther vertices in an array - to access them in a linear order

	int size = vector_total(&vertexIndices);
	printf("size: %d\n", size); // 2834
	int j = 0;
	for (int i = 0; i < size; i++, j += 3) {

		// For each indices Vertex - find the info 
		indicesVertex* index = (indicesVertex*)vector_get(&vertexIndices, i);

		indicesArray[j] = (index->x - 1);
		indicesArray[j + 1] = (index->y - 1);
		indicesArray[j + 2] = (index->z - 1);
	}

	// vertexes 
	int sizeVertex = vector_total(&vecInfo);
	printf("vertex size: %d\n", sizeVertex);
	j = 0;
	for (int i = 0; i < sizeVertex; i++, j += 3) {
		vertex* index = (vertex*)vector_get(&vecInfo, i);
		vertexArray[j] = index->x;
		vertexArray[j + 1] = index->y;
		vertexArray[j + 2] = index->z;

	}

	// texCoords
	/*int texSizeVertex = vector_total(&uvInfo);
	j = 0;
	for (int i = 0; i < texSizeVertex; i++, j += 2) {
		vertex* index = (vertex*)vector_get(&uvInfo, i);
		texArray[j] = index->x;
		texArray[j + 1] = index->y;
	}

	// normals
	int normSizeVertex = vector_total(&normInfo);
	j = 0;
	for (int i = 0; i < normSizeVertex; i++, j += 3) {
		vertex* index = (vertex*)vector_get(&normInfo, i);
		normArray[j] = index->x;
		normArray[j + 1] = index->y;
		normArray[j + 2] = index->z;

	}
	for (int i = 0; i < size; i++) {
		vertex* vertexTemp = (vertex*)vector_get(&vecInfo, (indicesArray[i]));
		vector_add(&outVertex, vertexTemp);
	}*/
	// Get the Indexed vertices into another vector
	// Pass this data onto a Struct which then can be used to draw the shape
	return 1;// Return when finished
}

void draw(int myProgram) {
	
	/*int size = vector_total(&outVertex);
	int j = 0;
	printf("sizeOutVert: %d\n", size); // 2834
	float indicesArray[2834 * 3] = { 0.0 };
	for (int i = 0; i < size; i++, j += 3) {
		printf("i = : %d\n", i);
		vertex* vertexTemp = (vertex*)vector_get(&outVertex, i);
		printf("iA: %lf, %lf, %lf\n", vertexTemp->x, vertexTemp->y, vertexTemp->z);
		indicesArray[j] = vertexTemp->x;
		indicesArray[j + 1] = vertexTemp->y;
		indicesArray[j + 2] = vertexTemp->z;
	}*/
	
	

	
	mat4 model = GLM_MAT4_IDENTITY_INIT;
	unsigned int VAO, VBO, EBO;
	glUseProgram(myProgram);

	glUniformMatrix4fv(glGetUniformLocation(myProgram, "model"), 1, GL_FALSE, &model[0][0]);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
    

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesArray), indicesArray, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesArray), indicesArray, GL_STATIC_DRAW);
	// position attribute
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(vertexArray) * 3);
	glDrawElements(
		GL_TRIANGLES,      // mode
		sizeof(indicesArray),    // count
		GL_UNSIGNED_INT,   // type
		NULL         // element array buffer offset
	);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

/*
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);

	glBindVertexArray(*VAO);

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,* EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
*/