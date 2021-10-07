#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aNormal;
layout (location = 1) in vec2 aTexCoords;
layout (location = 3) in ivec4 BoneIDs;;
layout (location = 4) in vec4  Weights;

out VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 LightPos;
    vec3 ViewPos;
    vec3 Normal;  
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

const int MAX_BONES = 100;
uniform mat4 gBones[MAX_BONES];

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
    BoneTransform     += gBones[BoneIDs[1]] * Weights[1];
    BoneTransform     += gBones[BoneIDs[2]] * Weights[2];
    BoneTransform     += gBones[BoneIDs[3]] * Weights[3];
    
    vs_out.FragPos = vec3(BoneTransform * model * vec4(aPos, 1.0));
    vs_out.TexCoords = aTexCoords;
    
    vec4 NormalL   = BoneTransform * vec4(aNormal, 0.0);
    vs_out.Normal   = (model * NormalL).xyz;
    vs_out.LightPos = lightPos;
    vs_out.ViewPos  = viewPos;
        
    gl_Position = projection * view * model * vec4(vs_out.FragPos, 1.0);
}
