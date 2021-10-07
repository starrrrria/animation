#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 LightPos;
    vec3 ViewPos;
    vec3 Normal;
} fs_in;
struct Material{
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
    float shininess;
};

uniform Material material;
uniform sampler2D diffuseMap;
uniform sampler2D normalMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
     // obtain normal from normal map in range [0,1]
    vec3 normal = texture(normalMap, fs_in.TexCoords).rgb;
    // transform normal vector to range [-1,1]
    normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space
   
    // get diffuse color
    vec3 color = texture(diffuseMap, fs_in.TexCoords).rgb;
    // ambient
    vec3 ambient = 0.5 * color;
    // diffuse
    vec3 lightDir = normalize(fs_in.LightPos - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // specular
    vec3 viewDir = normalize(fs_in.ViewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 specular = vec3(0.2) * spec;
    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
