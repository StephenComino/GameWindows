#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm.h>   /* for library call (this also includes cglm.h) */

#ifndef vertexCoords_H
#define vertexCoords_H

typedef struct vertex {
	float x;
	float y;
	float z;
} vertex;

typedef struct indicesVertex {
	unsigned int x;
	unsigned int y;
	unsigned int z;
} indicesVertex;

typedef struct normalVertex {
	float x;
	float y;
	float z;
} normalVertex;

typedef struct texVertex {
	float x;
	float y;
} texVertex;

typedef struct triangle {
	vertex one;
	vertex two;
	vertex three;
	mat4 model;

} triangle;

typedef struct line {
	vertex beginning;
	vertex end;
} line;


double getX(vertex input);
double getY(vertex input);
double getX(vertex input);

// Triangle Specific
vertex getOne(vertex input);
vertex getTwo(vertex input);
vertex getThree(vertex input);
#endif