//
//  Mesh.hpp
//  Lab3
//
//  Created by 补锌 on 2021/3/20.
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
class Mesh{
public:
    Mesh(const std::string& filename);
    std::vector<Vertex> vertices;
    std::vector<glm::vec3> positions; //vertex positions
    std::vector<glm::vec2> tex_coords;   //texture coordinates
    std::vector<glm::vec3> normals;  //normals
    std::vector<std::vector<int>> indices; //connectivity
    bool read_obj(const std::string& filename);
    void renderObj();
    void decompressToVertexArray();
    void Draw();
private:
    unsigned int VAO,VBO,EBO;
    void setupMesh();
};
#endif /* Mesh_hpp */
