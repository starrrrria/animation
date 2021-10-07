
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h> //目录下的档案
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<glm/common.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <assert.h>
#include <AntTweakBar.h>
#include "stdio.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <math.h>
#include <glm/gtx/dual_quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/vector_relational.hpp>
#if GLM_HAS_TRIVIAL_QUERIES
#    include <type_traits>
#endif

#define GLUT_DISABLE_ATEXIT_HACK
#include "Shader.hpp"
#include "Material.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "maths_funcs.h"
using namespace::glm;


float skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

std::vector<std::string> faces
    {
        "/Users/buxin/Documents/Real-time- Animations/animation/skybox/right.jpg",
        "/Users/buxin/Documents/Real-time- Animations/animation/skybox/left.jpg",
        "/Users/buxin/Documents/Real-time- Animations/animation/skybox/top.jpg",
        "/Users/buxin/Documents/Real-time- Animations/animation/skybox/bottom.jpg",
        "/Users/buxin/Documents/Real-time- Animations/animation/skybox/front.jpg",
        "/Users/buxin/Documents/Real-time- Animations/animation/skybox/back.jpg"
    };

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera camera(glm::vec3(0,2.0f,-15.0f),glm::radians(0.0f),glm::radians(180.0f),glm::radians(0.0f));
float lastX;
float lastY;
float Angle = 0;
void update(){
    float lastTime = 0;
    float currTime = (float)glfwGetTime();
    float  delta = (currTime - lastTime) * 0.001f;
    if (delta > 0.03f){
        delta = 0.03f;
        lastTime = currTime;
        Angle += 0.2f;
    }
    
}
bool firstMouse = true;
unsigned int LoadImageToGPU(const char* filename,GLint internalFormat, GLenum format,int textureSlot){
    unsigned int TexBuffer;
    glGenTextures(1, &TexBuffer); //产生buffer
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, TexBuffer);
    
    int width,height,nrChannel;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filename,&width,&height,&nrChannel,0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } //第几登记mipmap,不给边缘
    else{
        printf("load image failed.");
    }
    stbi_image_free(data);
    return TexBuffer;
}
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void processInput(GLFWwindow *window)
{
    float deltaX,deltaY,deltaZ;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//        camera.speedZ = 1.0f;
        deltaY = -2.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//        camera.speedZ = -1.0f;
        deltaY = 2.0f;

    }
    else{
//        camera.speedZ = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//        camera.speedX = 1.0f;
        deltaX = 2.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//        camera.speedX = -1.0f;
        deltaX = -2.0f;
    }
    else{
//        camera.speedX = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
//        camera.speedY = -1.0f;
        deltaZ = 2.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
//        camera.speedY = 1.0f;
        deltaZ = -2.0f;
    }
    else{
//        camera.speedY = 0;
    }
    camera.ProcessMouseMovement(deltaX, deltaY,deltaZ);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float deltaX,deltaY,deltaZ;
    deltaX = xpos - lastX;
    deltaY = ypos - lastY;
    deltaZ = 0;
    
    lastX = xpos;
    lastY = ypos;
    
    camera.ProcessMouseMovement(deltaX, deltaY,deltaZ);
}
static void key_callback(GLFWwindow *window,int key, int scancode, int action, int mods){
    
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) { //change first and third camera
        camera.changeNumber += 1;
        printf("%d",camera.changeNumber);
    }
}
unsigned int loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(int argc, const char * argv[]) {
    std::string exePath = argv[0];
    //std::cout << exePath.substr(0,exePath.find_last_of('/'))+ '/Structure/Structure/Wall-Window.obj' << std::endl;
    //Open window
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lab1", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); //终止
        return -1;
    }
    glfwMakeContextCurrent(window); //绑定使用
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//取消鼠标
    glfwSetCursorPosCallback(window, mouse_callback);
    
//    glEnable(GL_CULL_FACE);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glCullFace(GL_BACK);
    
    //Init GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        printf("Init GLEW fault");
        glfwTerminate();
        return -1;
    }
    
    glViewport(0, 0, 800, 600); //设置窗口大小起始坐标终止坐标
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    //stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);
    
    printf("Press W,S rotate around x axis, A,D rotate around z axis, Q,E rotate around y axis. ");
    Shader* skyShader = new Shader("/Users/buxin/Documents/Real-time- Animations/animation/animation/skyBoxVertex.vert","/Users/buxin/Documents/Real-time- Animations/animation/animation/skyBoxFragment.frag");
    Shader* modelShader = new Shader("/Users/buxin/Documents/Real-time- Animations/animation/animation/vertexSource.vert","/Users/buxin/Documents/Real-time- Animations/animation/animation/fragementSource.frag");
    Shader* SphereShader = new Shader("/Users/buxin/Documents/Real-time- Animations/animation/animation/vertexSource.vert","/Users/buxin/Documents/Real-time- Animations/animation/animation/fragementSource.frag");
    unsigned int cubemapTexture = loadCubemap(faces);
    unsigned int modelTexture = loadTexture("/Users/buxin/Documents/Real-time- Animations/animation/ka27/texture/ka27.png");
    
//    Material* myMaterial = new Material(modelShader,
//                                        LoadImageToGPU("/Users/buxin/Documents/Real-time- Animations/animation/ka27/texture/ka27.png", GL_RGBA, GL_RGBA, Shader::DIFFUSE),
//                                        1.0f,
//                                        glm::vec3 (1.0f,1.0f,1.0f),
//                                        32.0f);
    
    Model model("/Users/buxin/Documents/Real-time- Animations/animation/ka27/ka27.FBX");
    Model sphereModel("/Users/buxin/Documents/Real-time- Animations/animation/Lightning_Propeller/Propeller_V1_new.obj");
    mat4x4 modelMat = mat4x4(1.0f);
    mat4x4 sphereMat = mat4x4(1.0f);
    glm::mat4 viewMat = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
    
    // cube VAO
//    unsigned int cubeVAO, cubeVBO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &cubeVBO);
//    glBindVertexArray(cubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    //skybox
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        //Process input
        processInput(window); //下一帧输入
        glfwSetKeyCallback(window, key_callback);
        //Clear screen
        glClearColor(0.8f,0.8f,0.8f,1.0f); //r,g,b,
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        
        viewMat = glm::mat4(glm::mat3(camera.GetfirstViewMatrix()));
        if((camera.changeNumber%2) == 0){
            viewMat = camera.GetthirdViewMatrix();
            view = glm::translate(glm::mat4(1.0f), glm::vec3(0,-2.0f,-10.0f));
        }
        else{
            viewMat = camera.GetfirstViewMatrix();
            view = glm::translate(glm::mat4(1.0f), glm::vec3(0,-4.0f,2.0f));
        }
        
        modelShader -> use();
//        modelMat = scale(modelMat, vec3(0.5f,0.5f,0.5f));

        glm::vec3 eulerAngles(0.0f, 45.0f, 0.0f);
        //quaternions

//        versor qX = quat_from_axis_rad(eulerAngles.x, 0.0f, 1.0f, 0.0f);
//        versor qY = quat_from_axis_rad(eulerAngles.y, 1.0f, 0.0f, 0.0f);
//        versor qZ = quat_from_axis_rad(eulerAngles.z, 0.0f, 0.0f, 1.0f);
//        versor q = qX*qY*qZ;
//        float w = q.q[0];
//        float x = q.q[1];
//        float y = q.q[2];
//        float z = q.q[3];
//        float quat[16]
//        {
//            1.0f - 2.0f * y * y - 2.0f * z * z,
//            2.0f * x * y - 2.0f * w * z,
//            2.0f * x * z + 2.0f * w * y,
//            0.0f,
//            2.0f * x * y + 2.0f * w * z,
//            1.0f - 2.0f * x * x - 2.0f * z * z,
//            2.0f * y * z - 2.0f * w * x,
//            0.0f,
//            2.0f * x * z - 2.0f * w * y,
//            2.0f * y * z + 2.0f * w * x,
//            1.0f - 2.0f * x * x - 2.0f * y * y,
//            0.0f,
//            0.0f,
//            0.0f,
//            0.0f,
//            1.0f
//        };
//        glm::mat4 qMatrix = glm::make_mat4(quat);
//        modelMat *= qMatrix;
        
//        //euler angles
//        float xR[16] = {
//            1.0f,0,0,0,
//            0,cos(-eulerAngles.x),-sin(-eulerAngles.x),0,
//            0,sin(-eulerAngles.x),cos(-eulerAngles.x),0,
//            0,0,0,1.0f
//        };
//        mat4 xRot = make_mat4(xR);
//
//        float yR[16] = {
//            cos(-eulerAngles.y),0,sin(-eulerAngles.y),0,
//            0,1.0f,0,0,
//            -sin(-eulerAngles.y),0,cos(-eulerAngles.y),0,
//            0,0,0,1.0f
//        };
//        mat4 yRot = make_mat4(yR);
//
//        float zR[16] = {
//            cos(-eulerAngles.z),-sin(-eulerAngles.z),0,0,
//            sin(-eulerAngles.z),cos(-eulerAngles.z),0,0,
//            0,0,1.0f,0,
//            0,0,0,1.0f
//        };
//        mat4 zRot = make_mat4(zR);
//
//        modelMat *= xRot *yRot* zRot;
//        mat4x4 R2 = yawPitchRoll(0,5,0);
        
        modelMat = glm::translate(glm::mat4x4(1.0f), glm::vec3(0,3.0f,-5.0f));
//        modelMat = camera.RotationMatrix*modelMat;
//        modelMat = glm::rotate(modelMat, glm::radians(45.0f), glm::vec3(0.0f,1.0f,0.0f));
//        if(camera.Forward.z <= 0){
        modelMat = glm::rotate(modelMat, 1.0f*camera.Roll, glm::vec3(0,0.0f,-1.0f));
        modelMat = glm::rotate(modelMat, -1.0f*camera.Pitch, glm::vec3(1.0f,0.0f,0.0f));
        modelMat = glm::rotate(modelMat, 1.2f*camera.Yaw, glm::vec3(0.0f,1.0f,0.0f));
        glm::mat4 gloabl1  = modelMat;
//        }
//        else if(camera.Forward.z > 0){
//            modelMat = rotate(modelMat, 1.0f*camera.Forward.x+ radians(180.0f), vec3(0,0.0f,1.0f));
//        }
//        qua<float> q = qua<float>(radians(vec3(0.0f, 0.0f, 45.0f)));
//        modelMat = mat4_cast(q)* modelMat;
        glUniformMatrix4fv(glGetUniformLocation(modelShader->ID,"modelMat"),1,GL_FALSE,value_ptr(gloabl1));
        glUniformMatrix4fv(glGetUniformLocation(modelShader->ID,"viewMat"),1,GL_FALSE,value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(modelShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(modelShader->ID,"ambientColor"),1.0f,1.0f,1.0f);//环境光
        glUniform3f(glGetUniformLocation(modelShader->ID,"lightPos"), 1.5f,6.5f, -3.0f);
        glUniform3f(glGetUniformLocation(modelShader->ID,"lightColor"),1.0f,1.0f,1.0f);
        glUniform3f(glGetUniformLocation(modelShader->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);
        glUniform1f(glGetUniformLocation(modelShader->ID,"specNum"),32.0f);
//        myMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
        model.Draw(modelShader,modelTexture);
        // cubes
//        glBindVertexArray(cubeVAO);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glBindVertexArray(0);
        
        glm::mat4 gloabl2 = glm::mat4(1.0f);
        sphereMat = glm::translate(glm::mat4(1.0f), glm::vec3(0,1.0f,1.5f));
        sphereMat = glm::rotate(sphereMat,glm::radians(180.0f),glm::vec3(1.0f,0.0f,0.0f));
        sphereMat = glm::rotate(sphereMat,(float)glfwGetTime()*2.5f,glm::vec3(0.0f,1.0f,0.0f));
        sphereMat = glm::scale(sphereMat, glm::vec3(0.025f,0.025f,0.025f));
        sphereMat = glm::scale(sphereMat, glm::vec3(1.0f,0.025f,1.0f));
        gloabl2  = gloabl1 * sphereMat;
        glUniformMatrix4fv(glGetUniformLocation(SphereShader->ID,"modelMat"),1,GL_FALSE,value_ptr(gloabl2));
        glUniformMatrix4fv(glGetUniformLocation(SphereShader->ID,"viewMat"),1,GL_FALSE,value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(SphereShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(SphereShader->ID,"ambientColor"),0.8f,0.8f,0.8);//环境光
        glUniform3f(glGetUniformLocation(SphereShader->ID,"lightPos"), 1.5f,4.5f, -3.0f);
        glUniform3f(glGetUniformLocation(SphereShader->ID,"lightColor"),1.0f,1.0f,1.0f);
        glUniform3f(glGetUniformLocation(SphereShader->ID,"cameraPos"),camera.Position.x,camera.Position.y,camera.Position.z);
        glUniform1f(glGetUniformLocation(SphereShader->ID,"specNum"),32.0f);
//        myMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
        sphereModel.Draw(SphereShader,modelTexture);
        
        glDepthFunc(GL_LEQUAL);
        skyShader -> use();
        glUniformMatrix4fv(glGetUniformLocation(skyShader->ID,"viewMat"),1,GL_FALSE,value_ptr(viewMat));
        glUniformMatrix4fv(glGetUniformLocation(skyShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform1i(glGetUniformLocation(skyShader->ID,"skybox"),0);
        
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default
        

        //Clean up,prepare for next render loop
        glfwSwapBuffers(window); //切换前后buffer
        glfwPollEvents();
        camera.UpdateCameraPos();
    }
    //Exit Program
    glfwTerminate();
    return 0;
}

