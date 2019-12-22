#ifndef TRIANGLE_H
#define TRIANGLE_H

void drawTriangle(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO, int myProgram);
void setModel(float valueX, float valueY);

double getModelX();
double getModelY();
#endif