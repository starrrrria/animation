#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
//layout (location = 2) in vec2 aTexCoord;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

//uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

//out vec4 vertexColor;
//out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main(){
    FragPos = vec3(modelMat * vec4(aPos.xyz, 1.0)); //补1表示顶点
    Normal = mat3(transpose(inverse(modelMat))) * aNormal;
    gl_Position = projMat * viewMat * vec4(FragPos,1.0);
    TexCoord = aTexCoord;
    //vertexColor = vec4(aColor.x,aColor.y,aColor.z,1.0);
    //TexCoord = aTexCoord;
}
