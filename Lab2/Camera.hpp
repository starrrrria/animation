//
//  Camera.hpp
//  
//
//  Created by 补锌 on 2020/11/15.
//
#pragma once
//#ifndef Camera_hpp
//#define Camera_hpp
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>


class Camera{
public:
    Camera(glm::vec3 position, glm::vec3 target,glm::vec3 worldup);
    Camera(glm::vec3 position, float pitch,float yaw,glm::vec3 worldup);
    ~Camera();
    
    glm::vec3 Position;
    glm::vec3 firstPosition;
    glm::vec3 Forward;
    glm::vec3 Right;
    glm::vec3 Up;
    glm::vec3 WorldUp;
    float Pitch;
    float Yaw;
    float SenseX=0.001f;
    float SenseY=0.001f;
    float speedZ = 0;
    float speedX = 0;
    float speedY = 0;
    int changeNumber = 0;
    int length = 5;
    
    glm::mat4 GetfirstViewMatrix();
    void ProcessMouseMovement(float deltaX,float deltaY);
    void UpdateCameraPos();
private:
    void UpdataCameraVectors();
};
//#endif /* Camera_hpp */
