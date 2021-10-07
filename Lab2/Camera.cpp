//
//  Camera.cpp
//  
//
//  Created by 补锌 on 2020/11/15.
//

#include "Camera.hpp"
#include <iostream>
Camera::Camera(glm::vec3 position, glm::vec3 target,glm::vec3 worldup){
    Position = position;
    WorldUp  = worldup;
    Forward = glm::normalize(target - position);
    Right = glm::normalize(glm::cross(Forward, WorldUp));
    Up = glm::normalize(glm::cross(Forward, Right)); //叉乘
    
}
Camera::Camera(glm::vec3 position, float pitch,float yaw,glm::vec3 worldup){
    Position = position;
    WorldUp = worldup;
    Pitch = pitch;
    Yaw = yaw;
    Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
    Forward.y = glm::sin(Pitch);
    Forward.z = glm::cos(Pitch)*glm::cos(Yaw);
    Right = glm::normalize(glm::cross(Forward, WorldUp));
    Up = glm::normalize(glm::cross(Forward, Right));
}
Camera::~Camera(){
    
}

glm::mat4 Camera::GetfirstViewMatrix(){
    //std::cout << Forward.x << std::endl;
    Position = firstPosition;
    return  glm::lookAt(Position, Position+Forward, WorldUp);
}

void Camera::UpdataCameraVectors(){
    Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
    Forward.y = glm::sin(Pitch);
    Forward.z = glm::cos(Pitch)*glm::cos(Yaw);
    Right = glm::normalize(glm::cross(Forward, WorldUp));
    Up = glm::normalize(glm::cross(Right, Forward));
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY){
    
    Pitch -= deltaY * SenseX;
    Yaw -= deltaX * SenseY;
    UpdataCameraVectors();
}

void Camera::UpdateCameraPos(){
    firstPosition += Forward * speedZ * 0.1f + Right * speedX * 0.1f + Up * speedY * 0.1f;
}
