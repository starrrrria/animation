//
//  Material.hpp
//  
//
//  Created by 补锌 on 2020/11/16.
//

#ifndef Material_hpp
#define Material_hpp

#include <stdio.h>
#include "Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Material{
public:
    Shader * shader;
    unsigned int diffuse;
    unsigned int specular;
    //unsigned int normal;
    glm::vec3 ambient;
    float shininess;
    
    Material(Shader* _shader,unsigned int _diffuse,unsigned int _specular,glm::vec3 _ambient,float _shininess);
    
    ~Material();
};
#endif /* Material_hpp */
