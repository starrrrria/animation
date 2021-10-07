//
//  Shader.hpp
//  triangle
//
//  Created by 补锌 on 2020/10/24.
//

#ifndef Shader_hpp
#define Shader_hpp
#include <string>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "math_3d.h"
class Shader
{
public:
    Shader(const char* vertexPath,const char* fragmentPath);
    //~Shader(); //解构函数
    std::string vertexString;
    std::string fragmentString;
    const char* vertexSource;
    const char* fragmentSource;
    unsigned int ID; //Shader program ID
    
    enum Slot{
        DIFFUSE,
        SPECULAR,
        NORMAL
    };
    static const uint MAX_BONES = 100;
    void use();
    void SetUniform3f(const char* paramNameString,glm::vec3 param);
    void SetUniform1f(const char* paramNameString,float param);
    void SetUniform1i(const char* paramNameString,int slot);
    void SetBoneTransform(uint Index, const Matrix4f& Transform);
private:
    void checkCompileErrors(unsigned int ID,std::string type);
    uint m_boneLocation[MAX_BONES];
};
#endif /* Shader_hpp */
