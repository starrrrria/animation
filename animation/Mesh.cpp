//
//  Mesh.cpp
//  triangle
//
//  Created by 补锌 on 2020/11/19.
//

#include "Mesh.hpp"
#include <glm/glm.hpp>
#include "Shader.hpp"
#include <string>
#include <vector>
Mesh::Mesh(float vertices[]){
    this->vertices.resize(36);
    memcpy(&(this->vertices[0]), vertices, 36*8*sizeof(float));
    setupMesh();
    //BindForWriting();
}
Mesh::Mesh(std::vector<Vertex> vertices,std::vector<unsigned int> indices,std::vector<Texture> textures){
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    
    setupMesh();
};
Mesh::~Mesh(){
    
};
void Mesh::Draw(Shader* shader,unsigned int cubemapTexture){
    // bind appropriate textures
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
            // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if(name == "texture_diffuse")
        {
            glActiveTexture(GL_TEXTURE0+i);
            number = std::to_string(diffuseNr++);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
            shader->SetUniform1i((name+number).c_str(), i);
        }
        else if(name == "texture_specular"){
            glActiveTexture(GL_TEXTURE0+i);
            number = std::to_string(specularNr++);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
            shader->SetUniform1i((name+number).c_str(), i);
        }// transfer unsigned int to stream
        else if(name == "texture_normal"){
            glActiveTexture(GL_TEXTURE0 + i);
            number = std::to_string(normalNr++);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
            shader->SetUniform1i((name+number).c_str(), i);
        }
        else if(name == "texture_height"){
            glActiveTexture(GL_TEXTURE0 +i);
            number = std::to_string(heightNr++); // transfer unsigned int to stream
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
            shader->SetUniform1i((name+number).c_str(), i);
        }
            
    }
    // now set the sampler to the correct texture unit
    
    // and finally bind the texture
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 36);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    // always good practice to set everything back to defaults once configured.
    // draw mesh
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
            
}
void Mesh::setupMesh(){
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex)* vertices.size(),&vertices[0],GL_STATIC_DRAW);
    
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)* indices.size(),&indices[0],GL_STATIC_DRAW);
    
//    glGenFramebuffers(1, &FBO);
//    glGenTextures(1, &shadowMap);
//    glBindTexture(GL_TEXTURE_2D, shadowMap);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 800, 600, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
//    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);
//    glDrawBuffer(GL_NONE);
//
//    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
//    if (Status != GL_FRAMEBUFFER_COMPLETE) {
//        printf("FB error, status: 0x%x\n", Status);
//    }

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(3*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(6*sizeof(GL_FLOAT)));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(8*sizeof(GL_FLOAT)));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4,3, GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(11*sizeof(GL_FLOAT)));
    
    glBindVertexArray(0);
}
void Mesh::BindForWriting()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
}
void Mesh::BindForReading(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
}
