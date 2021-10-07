//
//  Model.hpp
//  triangle
//
//  Created by 补锌 on 2020/11/19.
//

#ifndef Model_hpp
#define Model_hpp

#include <vector>
#include <string>
#include "Mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "Shader.hpp"
#include <stdio.h>

class Model {
    
public:
    Model(std::string path,unsigned int modelID, std::string name);
    Model(std::string path);
    ~Model();
    
    bool gammaCorrection;
    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;
    glm::vec3 position;
    void Draw(Shader* shader,unsigned int cubemapTexture);
    void GetPosition(glm::vec3 Pos);
    void PickState();
    void PutState(int judge);
    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset);
    void updateVectors();
    glm::vec3 Eangles;
    glm::vec3 Forward;
    glm::vec3 Right;
    glm::vec3 Up;
    float Pitch;
    float Yaw;
    float SenseX=0.001f;
    float SenseY=0.001f;
    int pick = 0;
    unsigned int modelID;
    std::string Name;
private:
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(std::string const path);
    void processNode(aiNode *node,const aiScene* scene);
    Mesh processMesh(aiMesh* mesh,const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char *path, const std::string &directory);
};

#endif /* Model_hpp */
