//
//  Mesh.hpp
//  triangle
//
//  Created by 补锌 on 2020/11/19.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include "Shader.hpp"
#include <string>
#include <GL/glew.h>
#include <vector>
struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture{
    unsigned int id;
    std::string type;
    std::string path;
};
class Mesh{
public:
    std::vector<Vertex> vertices;//list function
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    Mesh(float vertices[]);
    Mesh(std::vector<Vertex> vertices,std::vector<unsigned int> indices,std::vector<Texture> textures);
    ~Mesh();
    
    void Draw(Shader* shader);
    void BindForWriting();
    void BindForReading(GLenum TextureUnit);
private:
    unsigned int VAO,VBO,EBO,FBO,shadowMap;
    void setupMesh();
};
#endif /* Mesh_hpp */
