//
//  Mesh.cpp
//  Lab3
//
//  Created by 补锌 on 2021/3/20.
//

#include "Mesh.hpp"

Mesh::Mesh(const std::string& filename){
    read_obj(filename);
//    decompressToVertexArray();
    setupMesh();
}
bool Mesh::read_obj(const std::string& filename)
{
    char   s[200];
    float  x, y, z;


    // open file (in ASCII mode)
    FILE* in = fopen(filename.c_str(), "r");
    if (!in) return false;


    // clear line once
    memset(&s, 0, 200);


    // parse line by line (currently only supports vertex positions & faces
    while (in && !feof(in) && fgets(s, 200, in))
    {
        // comment
        if (s[0] == '#' || isspace(s[0])) continue;

        // vertex
        else if (strncmp(s, "v ", 2) == 0)
        {
            if (sscanf(s, "v %f %f %f", &x, &y, &z))
            {
                positions.push_back(glm::vec3(x, y, z));
            }
        }
        // normal
        else if (strncmp(s, "vn ", 3) == 0)
        {
            if (sscanf(s, "vn %f %f %f", &x, &y, &z))
            {
                normals.push_back(glm::vec3(x, y, z));
            }
        }

        // texture coordinate
        else if (strncmp(s, "vt ", 3) == 0)
        {
            if (sscanf(s, "vt %f %f", &x, &y))
            {
                tex_coords.push_back(glm::vec2(x, y));
            }
        }

        // face
        else if (strncmp(s, "f ", 2) == 0)
        {
            int component(0), nV(0);
            bool endOfVertex(false);
            char *p0, *p1(s + 1);

            std::vector<int> polygon;

            // skip white-spaces
            while (*p1 == ' ') ++p1;

            while (p1)
            {
                p0 = p1;

                // overwrite next separator

                // skip '/', '\n', ' ', '\0', '\r' <-- don't forget Windows
                while (*p1 != '/' && *p1 != '\r' && *p1 != '\n' && *p1 != ' ' && *p1 != '\0') ++p1;

                // detect end of vertex
                if (*p1 != '/')
                {
                    endOfVertex = true;
                }

                // replace separator by '\0'
                if (*p1 != '\0')
                {
                    *p1 = '\0';
                    p1++; // point to next token
                }

                // detect end of line and break
                if (*p1 == '\0' || *p1 == '\n')
                {
                    p1 = 0;
                }

                // read next vertex component
                if (*p0 != '\0')
                {
                    switch (component)
                    {
                    case 0: // vertex
                    {
                        polygon.push_back(atoi(p0) - 1);
                        break;
                    }
                    case 1: // texture coord
                    {
                        //add code for saving texture coordinate index
                        break;
                    }
                    case 2: // normal
                      //add code for saving normal coordinate index
                        break;
                    }
                }

                ++component;

                if (endOfVertex)
                {
                    component = 0;
                    nV++;
                    endOfVertex = false;
                }
            }
            indices.push_back(polygon);
        }
        // clear line
        memset(&s, 0, 200);
    }

    fclose(in);
    return true;
}

void Mesh::setupMesh(){
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3)* positions.size(),&positions[0],GL_STATIC_DRAW);
    
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)* indices.size(),&indices[0],GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(glm::vec3),(void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(3*sizeof(GL_FLOAT)));
//    glEnableVertexAttribArray(2);
//    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(6*sizeof(GL_FLOAT)));
    
    glBindVertexArray(0);
}
void Mesh::Draw(){
    
    // and finally bind the texture
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 36);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    // always good practice to set everything back to defaults once configured.
    // draw mesh
}
