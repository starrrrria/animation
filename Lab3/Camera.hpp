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
#include <glm/gtc/quaternion.hpp>

class Camera{
public:
    Camera(glm::vec3 position, glm::vec3 target,glm::vec3 worldup);
    Camera(glm::vec3 position, float pitch,float yaw,float roll);
    ~Camera();
    
    glm::vec3 Position;
    glm::vec3 firstPosition;
    glm::vec3 thirdPosition;
    glm::vec3 Forward;
    glm::vec3 Forward3;
    glm::vec3 Up3;
    glm::vec3 Right;
    glm::vec3 Up;
    glm::vec3 WorldUp;
    glm::vec3 R;
    glm::vec3 U;
    glm::vec3 F;
    glm::quat FVector;
    glm::mat4 RotationMatrix;
    float Pitch;
    float Yaw;
    float Roll;
    float SenseX=0.005f;
    float SenseY=0.005f;
    float SenseZ=0.008f;
    float speedZ = 0;
    float speedX = 0;
    float speedY = 0;
    float x2;
    float y2;
    float z2;
    float xy;
    float xz;
    float yz;
    float wx;
    float wy;
    float wz;
    glm::mat4 temp = glm::mat4(1.0f);
    glm::mat3 m = glm::mat3(1.0f);
    int changeNumber = 0;
    int length = 5;
    glm::mat4 GetthirdViewMatrix();
    glm::mat4 GetfirstViewMatrix();
    void ProcessMouseMovement(float deltaX,float deltaY,float deltaZ);
    void UpdateCameraPos();
private:
    void UpdataCameraVectors();
};
//#endif /* Camera_hpp */
