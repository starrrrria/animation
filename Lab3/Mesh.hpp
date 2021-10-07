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
};

struct Texture{
    unsigned int id;
    std::string type;
    std::string path;
};
class Mesh{
public:
    std::vector<glm::vec3> positions; //vertex positions
    std::vector<glm::vec2> tex_coords;   //texture coordinates
    std::vector<glm::vec3> normals; 
    std::vector<Vertex> vertices;//list function
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    Mesh(float vertices[]);
    Mesh(std::vector<Vertex> vertices,std::vector<unsigned int> indices,std::vector<Texture> textures);
    Mesh(std::vector<Vertex> vertices,std::vector<unsigned int> indices);
    ~Mesh();
    
    void Draw(Shader* shader);
private:
    unsigned int VAO,VBO,EBO,FBO;
    void setupMesh();
};
#endif /* Mesh_hpp */
