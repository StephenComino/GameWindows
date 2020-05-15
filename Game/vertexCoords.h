#ifndef vertexCoords_H
#define vertexCoords_H

typedef struct vertex {
	float x;
	float y;
	float z;
} vertex;

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