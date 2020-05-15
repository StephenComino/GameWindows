#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <cglm.h>

#include "camera.h"

// One function Initialises the Camera
void initCamera(int myProgram, int screenWidth, int screenHeight, float fov, float near, float far, vec3 cameraPos, vec3 cameraFront, vec3 cameraUp) {


	// pass projection matrix to shader (note that in this case it could change every frame)
	//mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	

	// camera/view transformation
	vec3 direction;
	glm_vec3_add(cameraPos, cameraFront, direction);
	mat4* view = setUpView(cameraPos, direction, cameraFront, cameraUp);
	mat4* projection = setUpPerspective(fov, screenWidth, screenHeight, near, far);
	glUniformMatrix4fv(glGetUniformLocation(myProgram, "view"), 1, GL_FALSE, view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(myProgram, "projection"), 1, GL_FALSE, projection[0][0]);
}


// I have to set the Vertex shader to use these Matrices!!
mat4 * setUpView(vec3 cameraPos, vec3 direction, vec3 cameraFront, vec3 cameraUp) {
	mat4 * view = malloc (sizeof (mat4));
	glm_mat4_identity(view);
	glm_lookat(cameraPos, direction, cameraUp, view);
	return view;
}

mat4* setUpPerspective(float fov, int screenWidth, int screenHeight, float near, float far) {
	mat4* projection = malloc (sizeof (mat4));
	glm_mat4_identity(projection);
	glm_perspective(glm_rad(fov), (float)screenWidth / (float)screenHeight, near, far, projection);
	return projection;
}