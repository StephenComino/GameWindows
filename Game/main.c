#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <cglm.h>   /* for library call (this also includes cglm.h) */

#include "triangle.h"
#include "menu.h" // Menu to do user building
#include "menu_box.h" // A box for the menu
#include "texture.h"
#include "initShaders.h"
#include "initButtonTexture.h"

double get_mouse_x_position(GLFWwindow* window);
double get_mouse_y_position(GLFWwindow* window);
/*
//  TODO:
//  1. Build Menu/ Decide top, bottom, left or right
//
//
//
//
//
        */
const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n"
"layout(location = 2) in vec2 aTexCoord;\n"

"uniform mat4 projection;\n"
"uniform mat4 model;\n"
//"uniform mat4 view;\n"

"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"

"void main()\n"
"{\n"
"    gl_Position = projection * model * vec4(aPos, 1.0);\n"
"    ourColor = aColor;\n"
"    TexCoord = aTexCoord;\n"
"}\n\0";

const char* fragmentShaderSource = "#version 330 core\n"
//#version 330 core
"out vec4 FragColor;\n"

"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"

"uniform sampler2D ourTexture;\n"

"void main()\n"
"{\n"
"    FragColor = texture(ourTexture, TexCoord);\n"
"}\n\0";


static const char* fragmentMenuButton1 = "#version 330 core\n"
//#version 330 core
"out vec4 FragColor;\n"

"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"

"uniform sampler2D texture2;\n"

"void main()\n"
"{\n"
"    FragColor = texture(texture2, TexCoord);\n"
"}\n\0";
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 1000;
mat4 projection = GLM_MAT4_IDENTITY_INIT;
mat4 lookAt = GLM_MAT4_IDENTITY_INIT;
mat4 menuBox = GLM_MAT4_IDENTITY_INIT;
mat4 model = GLM_MAT4_IDENTITY_INIT;
// SHader programs
static int myProgram; //= initShaders(vertexShaderSource, fragmentShaderSource);
static int myShader;// = initShaders(vertexShaderSource, fragmentMenuButton1);
int setSkeleton = 0;
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Game", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // What does this do?
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    // Initialise and compile the Shaders
    myProgram = initShaders(vertexShaderSource, fragmentShaderSource);
    myShader = initShaders(vertexShaderSource, fragmentMenuButton1);
   // unsigned int* VAO, * VBO, * EBO;

    vec3 eye = { 0, 0, 1 };
    vec3 center = { 0, 0, 0 };
    vec3 up = { 0, 1, 0 };
    glm_lookat(eye, center, up, lookAt);
    // Send the projection matrix to the shader

    unsigned int texture1 = initTexture(myProgram, myShader);
    unsigned int texture2 = initButtonTexture(myShader);

    vec3 newLoc = { 1.0f, 0.0f, -0.5f};

    glm_ortho(-(2.0f), 2.0f, 2.0f, -2.0f, -1.0f, 1.0f, projection);

    // Triangle matrix;

    // While the window is open render
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUniformMatrix4fv(glGetUniformLocation(myProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
        
        glUseProgram(myProgram);
        glUniform1i(glGetUniformLocation(myProgram, "texture1"), 0);
       // glm_translate(model, newLoc);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        //glBindTexture(GL_TEXTURE_2D, texture1);
        // render container
        //glBindVertexArray(VAO); 
        //glBindVertexArray(VAO); 
        
        drawTriangle(myProgram, model);
        glUniformMatrix4fv(glGetUniformLocation(myProgram, "projection"), 1, GL_FALSE, &projection[0][0]);


        //glBindVertexArray(VAO);
        initMenu(myProgram);

        glUseProgram(myShader);

        glUniform1i(glGetUniformLocation(myShader, "texture2"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture2);
        
        initMenuBox(menuBox, myShader);

        if (setSkeleton == 1) {
            mat4 model = GLM_MAT4_IDENTITY_INIT;

            // Get mouse position
            // get x;
            //vec3 newPosition = GLM_VEC3_ONE_INIT;
            double x = get_mouse_x_position(window);
            double y = get_mouse_y_position(window);
            vec3 newPosition = { x, y, 0.5f };
            // get y;
            glm_translate(model, newLoc);
           // int myS = initShaders(vertexShaderSource, fragmentShaderSource);
            drawTriangle(myProgram, model);
            // ****************************************
            // TODO:
            // 1. Add a linked list
            //     a. Each entry will have an id, and the model
            //     b. This means each entry can be manipulated separetly
            // 2. Add each model made to the list
            // 3. Use this list to maniuplate each shape

        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        
       
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        //deleteTriangleBuffers();
        //deleteMenuBuffers();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    //deleteTriangleBuffers();
    deleteMenuBuffers();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    int newState;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
   // else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
   //     glm_translate_x(model, -0.001f);
   // }
    
    else if ((newState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) == GLFW_PRESS) {
        double x = get_mouse_x_position(window);
        double y = get_mouse_y_position(window);
        double modelX = getModelX();
        double modelY = getModelY();
        

        // Check if the click coordinates were within the centre box;
        // If the menuButton was clicked then flag building
        // if X > x between 1.2 -> 1.35
        /* int oldState = GL_RELEASE;
        int newState = glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT);
        if (newState == GL_RELEASE && oldState == GL_PRESS) {
            // whatever
        }
        oldState = newState; */ 
        if ( newState == GLFW_PRESS && (x >= 1.20f && x <= 1.35) && (y <= -1.15f && y >= -1.40f)) {
            printf("Here %lf", x);
            if (setSkeleton == 0) {
                setSkeleton = 1;
                newState = GLFW_RELEASE;
                return;
            }
            else {
                setSkeleton = 0;
                newState = GLFW_RELEASE;
                return;
            }
            newState = GLFW_RELEASE;
            // This should make the pointer into an object which than can be placed onto the map.
            // I.E a Building which can be placed on the the stage

        }
        else {

            setModel((float)x, (float)y);
        }
        //model[3][0] = (float)x;
        //model[3][1] = (float)y;
 
        return;
    }

}

double get_mouse_x_position(GLFWwindow* window) {

    double x;
    double y;
    glfwGetCursorPos(window, &x, &y);
    // printf("\n x: %lf, y: %lf\n", x, y);
    if (x == 0.000000f) {
        x = (double)0.000001f;
    }
    else if (y == 0.000000f) {
        y = (double)0.000001f;
    }

    // upto 800. so range [1600, 800] / 1600 * -2 = [-1, -1]
    // No values between [0, -1]
    if (x <= 800) {
        //printf("\nmodel: %lf, position: %lf\n ", model[3][0], (((800 - x) / 1600)) * -2);
        x = (double)(((800 - x) / 800)) * -2;
    }
    else {
        // > 800
        x = (double)((x - 800) / 800) * 2;
        // printf("\nx: %lf\n ", x);
    }
    if (y <= 500) {
        y = (double)(((500 - y) / 500)) * -2;
        // printf("\ny: %lf\n ", y);
    }
    else {
        y = (double)((y - 500) / 500) * 2;
        // printf("\ny: %lf\n ", y);
    }

    //vec3 positionVec = malloc(sizeof(vec3) * 1);
    
    return x;
}

double get_mouse_y_position(GLFWwindow* window) {

    double x;
    double y;
    glfwGetCursorPos(window, &x, &y);
    // printf("\n x: %lf, y: %lf\n", x, y);
    if (x == 0.000000f) {
        x = (double)0.000001f;
    }
    else if (y == 0.000000f) {
        y = (double)0.000001f;
    }

    // upto 800. so range [1600, 800] / 1600 * -2 = [-1, -1]
    // No values between [0, -1]
    if (x <= 800) {
        //printf("\nmodel: %lf, position: %lf\n ", model[3][0], (((800 - x) / 1600)) * -2);
        x = (double)(((800 - x) / 800)) * -2;
    }
    else {
        // > 800
        x = (double)((x - 800) / 800) * 2;
        // printf("\nx: %lf\n ", x);
    }
    if (y <= 500) {
        y = (double)(((500 - y) / 500)) * -2;
        // printf("\ny: %lf\n ", y);
    }
    else {
        y = (double)((y - 500) / 500) * 2;
        // printf("\ny: %lf\n ", y);
    }

    //vec3 positionVec = malloc(sizeof(vec3) * 1);

    return y;
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}