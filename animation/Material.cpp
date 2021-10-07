//
//  Material.cpp
//  
//
//  Created by 补锌 on 2020/11/16.
//

#include "Material.hpp"
Material::Material(Shader* _shader,unsigned int _diffuse,unsigned int _specular,glm::vec3 _ambient,float _shininess):
    shader(_shader),
    diffuse(_diffuse),
    specular(_specular),
    //normal(_normal),
    ambient(_ambient),
    shininess(_shininess)
{
    
}
Material::~Material(){
    
}
