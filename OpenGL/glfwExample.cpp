#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLSL.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
bool isTPressed = 0;
int CheckGLErrors(const char *s)
{
    int errCount = 0;
    
    return errCount;
}

int main(void)
{
    
    /* Initialize the library */
    if (!glfwInit()) {
        exit (-1);
    }

    // throw std::runtime_error("Error! initialization of glfw failed!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    int winWidth = 1000;
    float aspectRatio = 1.0; // 16.0 / 9.0; // winWidth / (float)winHeight;
    int winHeight = winWidth / aspectRatio;
    
    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "OpenGL Example", NULL, NULL);
    if (!window) {
        std::cerr << "GLFW did not create a window!" << std::endl;
        
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err=glewInit();
    if(err != GLEW_OK) {
        std::cerr <<"GLEW Error! glewInit failed, exiting."<< std::endl;
        exit(EXIT_FAILURE);
    }

    const GLubyte* renderer = glGetString (GL_RENDERER);
    const GLubyte* version = glGetString (GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << std::endl;


    GLint major_version;
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    std::cout << "OpenGL Major Version: " << major_version << std::endl;

    GLint minor_version;
    glGetIntegerv(GL_MINOR_VERSION, &minor_version);
    std::cout << "OpenGl Minor Version: " << minor_version << std::endl;

    GLint maxTexture;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexture);
    std::cout << "OpenGL Max Texture Size " << maxTexture << std::endl;

    GLint depthTest;
    glGetIntegerv(GL_DEPTH_TEST,&depthTest);
    std::cout << "Depth Test default: " << depthTest << std::endl;

    GLfloat line_width;
    glGetFloatv(GL_LINE_WIDTH, &line_width);
    std::cout << "OpenGL Line Width: " << line_width << std::endl;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(1.0, 0.0, 1.0, 1.0);
    
    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);

    double timeDiff = 0.0, startFrameTime = 0.0, endFrameTime = 0.0;
    glfwSwapInterval(1);


    
    glfwSetKeyCallback(window, key_callback);


    float left = -7.5f;
    float right = 7.5f;
    float bottom = -4.2f;
    float top = 4.2f;
    float near = -10.0f;
    float far = 10.0f;

    //step 1
    GLuint m_triangleVBO;
    glGenBuffers(1, &m_triangleVBO);

    //step 2
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO);
    std::vector< float > host_VertexBuffer{-0.5f, -0.5f, 0.0f,1.0f,1.0f,0.0f,
                                            0.5f, -0.5f, 0.0f,1.0f,0.0f,1.0f,
                                            0.0f, 0.5f, 0.0f,0.0f,1.0f,1.0f
                                             }; 
    int numBytes = host_VertexBuffer.size() * sizeof(float);
    
    //step 3
    glBufferData(GL_ARRAY_BUFFER, numBytes, host_VertexBuffer.data(), GL_STATIC_DRAW);
    host_VertexBuffer.clear();


    GLuint m_VAO;
    glGenVertexArrays(1, &m_VAO);  // Step 1 above
    glBindVertexArray(m_VAO);      // Step 2 above

    glEnableVertexAttribArray(0);  // enable attrib 0 (Step 3)
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO);  // Step 4
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const GLvoid *)12);

    // When done binding a VAO, you can unbind it by passing 0 to the bind call
    glBindVertexArray(0);

    sivelab::GLSLObject shader;
    shader.addShader( "vertexShader_passthroughLAB.glsl", sivelab::GLSLObject::VERTEX_SHADER );
    shader.addShader( "fragmentShader_passthroughLAB.glsl", sivelab::GLSLObject::FRAGMENT_SHADER );
    shader.createProgram();
    GLuint projMatrixID = shader.createUniform( "projMatrix" );
    shader.activate();
    glm::mat4 projMatrix = glm::ortho(left, right, bottom, top, near, far);
    glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, glm::value_ptr(projMatrix));
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */

        endFrameTime = glfwGetTime();
        timeDiff = endFrameTime - startFrameTime;
        startFrameTime = glfwGetTime();

        if (isTPressed == 1)
        {
            std::cout << 1.0 / timeDiff << std::endl;
            isTPressed = 0;
        }

        


        //std::cout << timeDiff << std::endl;
        // Clear the window's buffer (or clear the screen to our
        // background color)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        shader.activate();

        glBindVertexArray(m_VAO);            // bind the VAO 
        glDrawArrays(GL_TRIANGLES, 0, 3);    // tell OpenGL to render it
        glBindVertexArray(0);

        shader.deactivate();

        // Swap the front and back buffers
        // glfwSwapInterval(0);
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        if (glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, 1);
        
        
    }
  
    glfwTerminate();
    
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    
    if (key == GLFW_KEY_T && action == GLFW_PRESS)
        isTPressed = 1;
   
}
