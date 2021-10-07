//
//  Model.cpp
//  triangle
//
//  Created by 补锌 on 2020/11/19.
//
#include <vector>
#include "Model.hpp"
#include <iostream>
#include "stb_image.h"
#include <fstream>
#include <sstream>
#include <string>
#include "maths_funcs.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<glm/common.hpp>
#include <glm/gtc/quaternion.hpp>
Model::Model(std::string path,unsigned int ID, std::string name){
    loadModel(path);
    modelID = ID;
    Name = name;
}
Model::Model(std::string path){
    loadModel(path);
}
Model::~Model(){
    
}
void Model::Draw(Shader* shader,unsigned int cubemapTexture){
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].Draw(shader,cubemapTexture);
    }
}
void Model::GetPosition(glm::vec3 Pos){
    position = Pos;
}
void Model::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset)
{
    xoffset *= SenseX;
    yoffset *= SenseY;

    Yaw += xoffset;
    Pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (Pitch > 89.0f)
            Pitch = 89.0f;
    if (Pitch < -89.0f)
            Pitch = -89.0f;
    

    // Update Front, Right and Up Vectors using the updated Eular angles
    //this->updateCameraVectors();
    updateVectors();
}
void Model::updateVectors() {
        
        glm::mat4 R;

//        if (isEuler)
//        {
//            //euler angles
//            float xR[16] = {
//                1.0f,0,0,0,
//                0,cos(-Eangles.x),-sin(-Eangles.x),0,
//                0,sin(-Eangles.x),cos(-Eangles.x),0,
//                0,0,0,1.0f
//            };
//            glm::mat4 xRot = glm::make_mat4(xR);
//            float yR[16] = {
//                cos(-Eangles.y),0,sin(-Eangles.y),0,
//                0,1.0f,0,0,
//                -sin(-Eangles.y),0,cos(-Eangles.y),0,
//                0,0,0,1.0f
//            };
//            glm::mat4 yRot = glm::make_mat4(yR);
//
//            float zR[16] = {
//                cos(-Eangles.z),-sin(-Eangles.z),0,0,
//                sin(-Eangles.z),cos(-Eangles.z),0,0,
//                0,0,1.0f,0,
//                0,0,0,1.0f
//            };
//            glm::mat4 zRot = glm::make_mat4(zR);
//
//            R= xRot*yRot*zRot;
//
//        }
//        else {

            //quaternions

            versor qX = quat_from_axis_rad(Eangles.x, 0.0f, 1.0f, 0.0f);
            versor qY = quat_from_axis_rad(Eangles.y, 1.0f, 0.0f, 0.0f);
            versor qZ = quat_from_axis_rad(Eangles.z, 0.0f, 0.0f, 1.0f);


            versor q = qX*qY*qZ;

            float w = q.q[0];
            float x = q.q[1];
            float y = q.q[2];
            float z = q.q[3];

            float quat[16]
            {
                1.0f - 2.0f * y * y - 2.0f * z * z,
                2.0f * x * y - 2.0f * w * z,
                2.0f * x * z + 2.0f * w * y,
                0.0f,

                2.0f * x * y + 2.0f * w * z,
                1.0f - 2.0f * x * x - 2.0f * z * z,
                2.0f * y * z - 2.0f * w * x,
                0.0f,

                2.0f * x * z - 2.0f * w * y,
                2.0f * y * z + 2.0f * w * x,
                1.0f - 2.0f * x * x - 2.0f * y * y,
                0.0f,

                0.0f,
                0.0f,
                0.0f,
                1.0f
            };

            glm::mat4 qMatrix = glm::make_mat4(quat);
            R = qMatrix;
//        }
    
        glm::vec4 forward = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
        forward = R*forward;
        glm::vec4 up= glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        up = R*up;
        glm::vec4 right = glm::vec4(-1.0f, 0.0f, 0.0f, 1.0f);
        right = R*right;

        // Calculate the new Front vector
        glm::vec3 front;
        front.x = forward.x;
        front.y = forward.y;
        front.z = forward.z;
        
        glm::vec3 upV3;
        upV3.x = up.x;
        upV3.y = up.y;
        upV3.z = up.z;

        glm::vec3 rightV3;
        rightV3.x = right.x;
        rightV3.y = right.y;
        rightV3.z = right.z;

        Forward = glm::normalize(front);
        Up = glm::normalize(upV3);
        Right = glm::normalize(rightV3);
        //this->Right= glm::normalize(glm::cross(this->Front, this->WorldUp));

    }
void Model::loadModel(std::string const path){
        // read file via ASSIMP
        Assimp::Importer importer; //obj
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);// 三角面化，uv翻转，
        // check for errors
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return;
        }
        // retrieve the directory path of the filepath
        directory = path.substr(0, path.find_last_of('/'));//最后一个'\'
        //std::cout << directory<< std::endl;
        // process ASSIMP's root node recursively
        processNode(scene->mRootNode, scene);
}
void Model::processNode(aiNode *node, const aiScene *scene)
    {
        // process each mesh located at the current node
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            // the node object only contains indices to index the actual objects in the scene.
            // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            //std::cout <<"mesh"<< node->mMeshes[i] << std::endl;
            meshes.push_back(processMesh(mesh, scene));
        }
        // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
        
//        std::cout <<"name"<< node->mName.data << std::endl;
        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
//            std::cout <<"children"<< node->mChildren[i] << std::endl;
        }

    }

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
    {
        // data to fill
        std::vector<Vertex> tempvertices;
        std::vector<unsigned int> tempindices;
        std::vector<Texture> temptextures;

        // walk through each of the mesh's vertices
        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex tempvertex;
             // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
            tempvertex.Position.x = mesh->mVertices[i].x;
            tempvertex.Position.y = mesh->mVertices[i].y;
            tempvertex.Position.z = mesh->mVertices[i].z;
            
            // normals
            if (mesh->HasNormals())
            {
            tempvertex.Normal.x = mesh->mNormals[i].x;
            tempvertex.Normal.y = mesh->mNormals[i].y;
            tempvertex.Normal.z = mesh->mNormals[i].z;
            
            }
            // texture coordinates
            if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                tempvertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
                tempvertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
                // tangent
                tempvertex.Tangent.x = mesh->mTangents[i].x;
                tempvertex.Tangent.y = mesh->mTangents[i].y;
                tempvertex.Tangent.z = mesh->mTangents[i].z;
              // bitangent
                tempvertex.Bitangent.x = mesh->mBitangents[i].x;
                tempvertex.Bitangent.y = mesh->mBitangents[i].y;
                tempvertex.Bitangent.z = mesh->mBitangents[i].z;
            }
            else{
                tempvertex.TexCoords = glm::vec2(0.0f, 0.0f);
            }
            tempvertices.push_back(tempvertex);
        }
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            // retrieve all indices of the face and store them in the indices vector
            for(unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
                tempindices.push_back(mesh->mFaces[i].mIndices[j]);
        }
        // process materials
         aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
        // Same applies to other texture as the following list summarizes:
        // diffuse: texture_diffuseN
        // specular: texture_specularN
        // normal: texture_normalN

        // 1. diffuse maps
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        temptextures.insert(temptextures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        temptextures.insert(temptextures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        temptextures.insert(temptextures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        temptextures.insert(temptextures.end(), heightMaps.begin(), heightMaps.end());
        
        // return a mesh object created from the extracted mesh data
        return Mesh(tempvertices, tempindices,temptextures);
}

unsigned int Model::TextureFromFile(const char *path, const std::string &directory)
{
    std::string filename = std::string(path);
    //std::cout << filename << directory << std::endl;
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
//        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
    {
        std::vector<Texture> textures;
        for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            bool skip = false;
            for(unsigned int j = 0; j < textures_loaded.size(); j++)
            {
                if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(textures_loaded[j]);
                    skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                    break;
                }
            }
            if(!skip)
            {   // if texture hasn't been loaded already, load it
                Texture texture;
                texture.id = TextureFromFile(str.C_Str(),this->directory);
                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
            }
        }
        return textures;
};





