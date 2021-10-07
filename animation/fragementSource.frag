#version 330 core
//in vec4 vertexColor;
//in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;//u v坐标

struct Material{
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;
uniform sampler2D ourTexture;
uniform sampler2D ourFace;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;
uniform float specNum;

out vec4 FragColor;

void main(){
    
    // ambient
    vec3 ambient = ambientColor * texture(material.diffuse, TexCoord).rbg;
        
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(lightDir,norm), 0.0);
    vec3 diffuse = diff * lightColor*texture(material.diffuse, TexCoord).rbg;
    vec3 cameraVec = normalize(cameraPos - FragPos);
    // specular
    float specularStrength = 1.0;
    vec3 reflectDir = normalize(reflect(-lightDir, norm));
    float spec = pow(max(dot(cameraVec, reflectDir), 0.0), specNum);
    vec3 specular = specularStrength * spec * lightColor;
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
//    FragColor = vec4(diffuse,1.0);
}

