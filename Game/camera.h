#ifndef CAMERA_H
#define CAMERA_H

/*typedef struct cameraPositions {
	vec3 cameraPos;
	vec3 cameraFront;
	vec3 cameraUp;
} cameraPositions;*/

void initCamera(int myProgram, int screenWidth, int screenHeight, float fov, float near, float far, vec3 cameraPos, vec3 cameraFront, vec3 cameraUp);
mat4* setUpView(vec3 cameraPos, vec3 direction, vec3 cameraFront, vec3 cameraUp);
mat4* setUpPerspective(float fov, int screenWidth, int screenHeight, float near, float far);

#endif