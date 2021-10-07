//
//  Camera.cpp
//  
//
//  Created by 补锌 on 2020/11/15.
//

#include "Camera.hpp"
#include <iostream>
#include <glm/gtx/quaternion.hpp>
Camera::Camera(glm::vec3 position, glm::vec3 target,glm::vec3 worldup){
    Position = position;
    WorldUp  = worldup;
    Forward = glm::normalize(target - position);
    Right = glm::normalize(glm::cross(Forward, WorldUp));
    Up = glm::normalize(glm::cross(Forward, Right)); //叉乘
    
}
Camera::Camera(glm::vec3 position, float pitch,float yaw,float roll){
    Position = position;
    Pitch = pitch;
    Yaw = yaw;
    Roll = roll;
    glm::quat MyQuaternion;
    glm::vec3 EulerAngles(90, 45, 0);
    MyQuaternion = glm::quat(EulerAngles);
    
    FVector.w = glm::cos(Roll/2)*glm::cos(Yaw/2)*glm::cos(Pitch/2)+glm::sin(Roll/2)*glm::sin(Yaw/2)*glm::sin(Pitch/2);
    FVector.x = glm::sin(Roll/2)*glm::cos(Yaw/2)*glm::cos(Pitch/2)-glm::cos(Roll/2)*glm::sin(Yaw/2)*glm::sin(Pitch/2);
    FVector.y = glm::cos(Roll/2)*glm::sin(Yaw/2)*glm::cos(Pitch/2)+glm::sin(Roll/2)*glm::cos(Yaw/2)*glm::sin(Pitch/2);
    FVector.z = glm::cos(Roll/2)*glm::cos(Yaw/2)*glm::sin(Pitch/2)-glm::sin(Roll/2)*glm::sin(Yaw/2)*glm::cos(Pitch/2);
    
    x2 = FVector.x * FVector.x;
    y2 = FVector.y * FVector.y;
    z2 = FVector.z * FVector.z;
    xy = FVector.x * FVector.y;
    xz = FVector.x * FVector.z;
    yz = FVector.y * FVector.z;
    wx = FVector.w * FVector.x;
    wy = FVector.w * FVector.y;
    wz = FVector.w * FVector.z;
    
    Right.x = 2.0f * (xz + wy);
    Right.y = 2.0f * (yz - wx);
    Right.z = 1.0f - 2.0f * (x2 + y2);
    Up.x = 2.0f * (xy - wz);
    Up.y = 1.0f - 2.0f * (x2 + z2);
    Up.z = 2.0f * (yz + wx);
    Forward.x = 1.0f - 2.0f * (y2 + z2);
    Forward.y = 2.0f * (xy + wz);
    Forward.z = 2.0f * (xz - wy);
    
//    Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
//    Forward.y = glm::sin(Pitch);
//    Forward.z = glm::cos(Pitch)*glm::cos(Yaw);
//    Up.x = glm::sin(Pitch)*glm::sin(Yaw)*glm::sin(Roll)+ glm::cos(Yaw)*glm::cos(Roll);
//    Up.y = glm::cos(Pitch)* glm::sin(Roll);
//    Up.z = glm::sin(Pitch)*glm::cos(Yaw)*glm::cos(Roll)- glm::sin(Yaw)*glm::cos(Roll);
//    Forward3.x = glm::cos(pitch)*glm::sin(glm::radians(0.0f));
//    Forward3.y = glm::sin(pitch);
//    Forward3.z = glm::cos(pitch)*glm::cos(glm::radians(0.0f));
    Forward3.x = 1.0f - 2.0f * (glm::cos(roll/2)*glm::sin(yaw/2)*glm::cos(pitch/2)+glm::sin(roll/2)*glm::cos(yaw/2)*glm::sin(pitch/2) *glm::cos(roll/2)*glm::sin(yaw/2)*glm::cos(pitch/2)+glm::sin(roll/2)*glm::cos(yaw/2)*glm::sin(pitch/2) + glm::cos(roll/2)*glm::cos(yaw/2)*glm::sin(pitch/2)-glm::sin(roll/2)*glm::sin(yaw/2)*glm::cos(pitch/2) *glm::cos(roll/2)*glm::cos(yaw/2)*glm::sin(pitch/2)-glm::sin(roll/2)*glm::sin(yaw/2)*glm::cos(pitch/2));
    Forward3.y = 2.0f * (glm::sin(roll/2)*glm::cos(yaw/2)*glm::cos(pitch/2)-glm::cos(roll/2)*glm::sin(yaw/2)*glm::sin(pitch/2)* glm::cos(roll/2)*glm::sin(yaw/2)*glm::cos(pitch/2)+glm::sin(roll/2)*glm::cos(yaw/2)*glm::sin(pitch/2)+ glm::cos(roll/2)*glm::cos(yaw/2)*glm::cos(pitch/2)+glm::sin(roll/2)*glm::sin(yaw/2)*glm::sin(pitch/2) *glm::cos(roll/2)*glm::cos(yaw/2)*glm::sin(pitch/2)-glm::sin(roll/2)*glm::sin(yaw/2)*glm::cos(pitch/2));
    Forward3.z = 2.0f * (glm::sin(roll/2)*glm::cos(yaw/2)*glm::cos(pitch/2)-glm::cos(roll/2)*glm::sin(yaw/2)*glm::sin(pitch/2) * glm::cos(roll/2)*glm::cos(yaw/2)*glm::sin(pitch/2)-glm::sin(roll/2)*glm::sin(yaw/2)*glm::cos(pitch/2)- glm::cos(roll/2)*glm::cos(yaw/2)*glm::cos(pitch/2)+glm::sin(roll/2)*glm::sin(yaw/2)*glm::sin(pitch/2) *glm::cos(roll/2)*glm::sin(yaw/2)*glm::cos(pitch/2)+glm::sin(roll/2)*glm::cos(yaw/2)*glm::sin(pitch/2));
    Up3.x = 2.0f * (glm::sin(roll/2)*glm::cos(yaw/2)*glm::cos(pitch/2)-glm::cos(roll/2)*glm::sin(yaw/2)*glm::sin(pitch/2) * glm::cos(roll/2)*glm::sin(yaw/2)*glm::cos(pitch/2)+glm::sin(roll/2)*glm::cos(yaw/2)*glm::sin(pitch/2) - glm::cos(roll/2)*glm::cos(yaw/2)*glm::cos(pitch/2)+glm::sin(roll/2)*glm::sin(yaw/2)*glm::sin(pitch/2) * glm::cos(roll/2)*glm::cos(yaw/2)*glm::sin(pitch/2)-glm::sin(roll/2)*glm::sin(yaw/2)*glm::cos(pitch/2));
    Up3.y = 1.0f - 2.0f * (glm::sin(roll/2)*glm::cos(yaw/2)*glm::cos(pitch/2)-glm::cos(roll/2)*glm::sin(yaw/2)*glm::sin(pitch/2) * glm::sin(roll/2)*glm::cos(yaw/2)*glm::cos(pitch/2)-glm::cos(roll/2)*glm::sin(yaw/2)*glm::sin(pitch/2) + glm::cos(roll/2)*glm::cos(yaw/2)*glm::sin(pitch/2)-glm::sin(roll/2)*glm::sin(yaw/2)*glm::cos(pitch/2) * glm::cos(roll/2)*glm::cos(yaw/2)*glm::sin(pitch/2)-glm::sin(roll/2)*glm::sin(yaw/2)*glm::cos(pitch/2));
    Up3.z = 2.0f * (glm::cos(roll/2)*glm::sin(yaw/2)*glm::cos(pitch/2)+glm::sin(roll/2)*glm::cos(yaw/2)*glm::sin(pitch/2) * glm::cos(roll/2)*glm::cos(yaw/2)*glm::sin(pitch/2)-glm::sin(roll/2)*glm::sin(yaw/2)*glm::cos(pitch/2) + glm::cos(roll/2)*glm::cos(yaw/2)*glm::cos(pitch/2)+glm::sin(roll/2)*glm::sin(yaw/2)*glm::sin(pitch/2) * glm::cos(roll/2)*glm::cos(yaw/2)*glm::sin(pitch/2)-glm::sin(roll/2)*glm::sin(yaw/2)*glm::cos(pitch/2));
//    Right = glm::normalize(glm::cross(Forward, Up));

}
Camera::~Camera(){
    
}

glm::mat4 Camera::GetfirstViewMatrix(){
    //std::cout << Forward.x << std::endl;
    Position = firstPosition;
    glm::mat4 result = glm::lookAt(Position, Position+Forward, Up);
    
    return result;
//    return RotationMatrix;
}
glm::mat4 Camera::GetthirdViewMatrix(){
    //std::cout << Forward.x << std::endl;
    return  glm::lookAt(Position, Position+glm::vec3(0,0,-1.0f), Up3);
}

void Camera::UpdataCameraVectors(){
//    Forward.x = glm::cos(Pitch)*glm::sin(Yaw);
//    Forward.y = glm::sin(Pitch);
//    Forward.z = glm::cos(Pitch)*glm::cos(Yaw);
//    Right.x = glm::sin(Pitch)*glm::sin(Yaw)*glm::cos(Roll)- glm::cos(Yaw)*glm::sin(Roll);
//    Right.y = glm::cos(Pitch)* glm::cos(Roll);
//    Right.z = glm::sin(Pitch)*glm::cos(Yaw)*glm::cos(Roll)+ glm::sin(Yaw)*glm::sin(Roll);
////    Right = glm::normalize(glm::cross(Forward, WorldUp));
////    Up = glm::normalize(glm::cross(Right, Forward));
//    Up.x = glm::sin(Pitch)*glm::sin(Yaw)*glm::sin(Roll)+ glm::cos(Yaw)*glm::cos(Roll);
//    Up.y = glm::cos(Pitch)* glm::sin(Roll);
//    Up.z = glm::sin(Pitch)*glm::cos(Yaw)*glm::cos(Roll)- glm::sin(Yaw)*glm::cos(Roll);
    
    FVector.w = glm::cos(Roll/2)*glm::cos(Yaw/2)*glm::cos(Pitch/2)+glm::sin(Roll/2)*glm::sin(Yaw/2)*glm::sin(Pitch/2);
    FVector.x = glm::sin(Roll/2)*glm::cos(Yaw/2)*glm::cos(Pitch/2)-glm::cos(Roll/2)*glm::sin(Yaw/2)*glm::sin(Pitch/2);
    FVector.y = glm::cos(Roll/2)*glm::sin(Yaw/2)*glm::cos(Pitch/2)+glm::sin(Roll/2)*glm::cos(Yaw/2)*glm::sin(Pitch/2);
    FVector.z = glm::cos(Roll/2)*glm::cos(Yaw/2)*glm::sin(Pitch/2)-glm::sin(Roll/2)*glm::sin(Yaw/2)*glm::cos(Pitch/2);
    
    x2 = FVector.x * FVector.x;
    y2 = FVector.y * FVector.y;
    z2 = FVector.z * FVector.z;
    xy = FVector.x * FVector.y;
    xz = FVector.x * FVector.z;
    yz = FVector.y * FVector.z;
    wx = FVector.w * FVector.x;
    wy = FVector.w * FVector.y;
    wz = FVector.w * FVector.z;
    
    Right.x = 2.0f * (xz + wy);
    Right.y = 2.0f * (yz - wx);
    Right.z = 1.0f - 2.0f * (x2 + y2);
    Up.x = 2.0f * (xy - wz);
    Up.y = 1.0f - 2.0f * (x2 + z2);
    Up.z = 2.0f * (yz + wx);
    Forward.x = 1.0f - 2.0f * (y2 + z2);
    Forward.y = 2.0f * (xy + wz);
    Forward.z = 2.0f * (xz - wy);
//
//    Right.x = R.x*m[2][0];
//    Right.y = R.y*m[2][1];
//    Right.z = R.z*m[2][2];
//    Up.x = U.x*m[1][0];
//    Up.y = U.y*m[1][1];
//    Up.z = U.z*m[1][2];
//    Forward.x = F.x*m[0][0];
//    Forward.y = F.y*m[0][1];
//    Forward.z = F.z*m[0][2];
    
    m[0][0] = Forward.x;
    m[0][1] = Forward.y;
    m[0][2] = Forward.z;
    m[1][0] = Up.x;
    m[1][1] = Up.y;
    m[1][2] = Up.z;
    m[2][0] = Right.x;
    m[2][1] = Right.y;
    m[2][2] = Right.z;
    
    glm::mat4 trans =  glm::mat4(
                             1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
                           2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx), 0.0f,
                           2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (x2 + y2), 0.0f,
                             0.0f, 0.0f, 0.0f, 1.0f);
    RotationMatrix = trans * temp;
    temp = RotationMatrix;
    
//    glm::mat4 RotationMatrix = glm::toMat4(FVector);
}

void Camera::ProcessMouseMovement(float deltaX, float deltaY,float deltaZ){
    
    Pitch -= deltaY * SenseX;
    Yaw -= deltaX * SenseY;
    Roll -= deltaZ * SenseZ;
    UpdataCameraVectors();
}

void Camera::UpdateCameraPos(){
    firstPosition += Forward * speedZ * 0.1f + Right * speedX * 0.1f + Up * speedY * 0.1f;
}
