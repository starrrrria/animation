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
#include <set>

class Model {
    
public:
    Model();
    ~Model();
    
    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;
    void Draw(Shader* shader);
    enum Mode { neutral,l_n_w,kiss,l_b_r,j_o,r_e_u_o,r_e_c,r_s,r_b_l,l_b_n,r_n_w,l_s,r_e_l_o,r_b_r,l_sad,l_p,l_e_u_o,r_p,l_e_c,l_b_l,l_e_l_o,r_b_n, r_smile,l_smile,r_sad };
    Mode expression;
    void loadModel(std::string const path);
    void get_files_in_directory(std::set<std::string> &out,const std::string &directory);
private:
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    
    void processNode(aiNode *node,const aiScene* scene);
    Mesh processMesh(aiMesh* mesh,const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char *path, const std::string &directory);
};

#endif /* Model_hpp */
