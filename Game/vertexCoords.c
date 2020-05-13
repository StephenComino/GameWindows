#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm.h>   /* for library call (this also includes cglm.h) */

#include "vertexCoords.h"

/* I need a data structure to hold the data coordinates of the object */
double getX(vertex input) {
	return input.x;
}

double getY(vertex input) {
	return input.y;
}

double getZ(vertex input) {
	return input.z;
}

vertex getOne(triangle input) {
	return input.one;
}

vertex getTwo(triangle input) {
	return input.two;
}

vertex getThree(triangle input) {
	return input.three;
}
