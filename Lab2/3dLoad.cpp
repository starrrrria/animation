//
//  3dLoad.cpp
//  Lab2
//
//  Created by 补锌 on 2021/3/2.
//

#include "3dLoad.hpp"

oGlModel::oGlModel()
{

}

oGlModel::oGlModel(string filename)
{
    load(filename);
}

//Load a .mtl file into a struct and add it to the list
void oGlModel::loadMaterial(string matFile)
{
    ifstream matf(matFile.c_str());
    string line;
    oGlMatInfo material;
    material.name = "";
    while(matf.good())
    {
        getline(matf, line);
        vector<string> lineItems = splitString(line, ' ');
        if(lineItems[0] == "newmtl")
        {
            if(material.name != "")
                materials.push_back(material);
            material.name = lineItems[1];
            material.illum = 0;
            material.Ns = 0;
        }
        else if(lineItems[0] ==  "Ka")
        {
            material.Ka.x = atof(lineItems[1].c_str());
            material.Ka.y = atof(lineItems[2].c_str());
            material.Ka.z = atof(lineItems[3].c_str());
        }
        else if(lineItems[0] == "Kd")
        {
            material.Kd.x = atof(lineItems[1].c_str());
            material.Kd.y = atof(lineItems[2].c_str());
            material.Kd.z = atof(lineItems[3].c_str());
        }
        else if(lineItems[0] ==  "Ks")
        {
            material.Ks.x = atof(lineItems[1].c_str());
            material.Ks.y = atof(lineItems[2].c_str());
            material.Ks.z = atof(lineItems[3].c_str());
        }
        else if(lineItems[0] == "illum")
        {
            material.illum = atoi(lineItems[1].c_str());
        }
        else if(lineItems[0] == "Ns")
        {
            material.Ns = atof(lineItems[1].c_str());
        }
    }
    materials.push_back(material);
}

//Load a .obj file to the class
void oGlModel::load(string filename)
{
    string line;
    vector<string> lineItems;
    ifstream objFile(filename.c_str());

    //instead of doing this, just count how many of each thing there is and THEN resize, and load
    objFile.seekg (0, ios::end);
    int length = objFile.tellg();
    objFile.seekg (0, ios::beg);
    vertexes.reserve((int)length / 25);
    faces.reserve((int)length / 25);
    textureCoords.reserve((int)length / 25);

    while(objFile.good())
    {
        getline(objFile, line);

        lineItems = splitString(line, ' ');

        if(lineItems[0] == "v")
        {
            oGlVertex v;

            v.x = atof(lineItems[1].c_str());
            v.y = atof(lineItems[2].c_str());
            v.z = atof(lineItems[3].c_str());

            vertexes.push_back(v);
        }
        else if (lineItems[0] == "vn")
        {
            oGlVertex v;

            v.x = atof(lineItems[1].c_str());
            v.y = atof(lineItems[2].c_str());
            v.z = atof(lineItems[3].c_str());

            normalVectors.push_back(v);
        }
        else if(lineItems[0] == "vt")
        {
            oGlVertex v;

            v.x = atof(lineItems[1].c_str());
            v.y = atof(lineItems[2].c_str());
            v.z = atof(lineItems[3].c_str());

            textureCoords.push_back(v);

        }
        else if(lineItems[0] == "f")
        {
            oGlFace face;
            for(int i = 1; i < lineItems.size(); i++)
            {
                vector<string> faceVs = splitString(lineItems[i],'/');
                oGlVTN vtn;
                if(lineItems[i] == "")
                    continue;
                switch(faceVs.size())
                {
                case 3:
                    vtn.norm = atoi(faceVs[2].c_str());
                    vtn.vert = atoi(faceVs[0].c_str());
                    vtn.tex = atoi(faceVs[1].c_str());
                    if(faceVs[1] == "")
                        vtn.tex = -1;
                    break;
                case 2:
                    vtn.vert = atoi(faceVs[0].c_str());
                    vtn.tex = atoi(faceVs[1].c_str());
                    vtn.norm = -1;
                    break;
                case 1:
                    vtn.vert = atoi(faceVs[0].c_str());
                    vtn.norm = -1;
                    vtn.tex = -1;
                    break;
                }
                face.vtnPairs.push_back(vtn);
            }
            faces.push_back(face);
        }
        else if(lineItems[0] == "mtllib")
        {
            int strI = filename.size() - 1;
            for(;strI >= 0 && filename[strI] != '/'; strI--);
            string nf = filename.substr(0, strI+1);
            nf += lineItems[1];
            loadMaterial(nf);
        }
        else if(lineItems[0] == "usemtl")
        {
            int mi = -1;
            for(int ti = 0; ti < materials.size(); ti++)
            {
                if(materials[ti].name == lineItems[1])
                {
                    mi = ti;
                    break;
                }
            }
            oGlMatIndex matI;
            matI.matIndex = mi;
            matI.fIndex = faces.size();
            matIndexes.push_back(matI);
        }
    }
}

//split a string by a given delimiter, i just decided this was nice to have here
vector<string> oGlModel::splitString(string s, char delim)
{
    vector<string> retTok;

    string temp;
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] != delim)
            temp += s[i];
        else
        {
            retTok.push_back(temp);
            temp = "";
        }

    }
    retTok.push_back(temp);
    return retTok;

}

//calculate the normal vector for a given face, cross products, boo yah
oGlVertex oGlModel::calcNormal(oGlVertex a, oGlVertex b, oGlVertex c)
{
    /*
    So for a triangle p1, p2, p3, if the vector U = p2 - p1 and the vector V = p3 - p1 then the normal N = U X V and can be calculated by:
    Nx = UyVz - UzVy
    Ny = UzVx - UxVz
    Nz = UxVy - UyVx
            */

    oGlVertex norm;
    oGlVertex U;
    oGlVertex V;

    U.x = b.x  - a.x;
    U.y = b.y  - a.y;
    U.z = b.z  - a.z;

    V.x = c.x  - a.x;
    V.y = c.y  - a.y;
    V.z = c.z  - a.z;

    norm.x = (U.y * V.z) - (U.z * V.y);
    norm.y = (U.z * V.x) - (U.x * V.z);
    norm.z = (U.x * V.y) - (U.y * V.x);


    //norm.x = (U.z * V.y) - (U.y * V.z);
    //norm.y = (U.x * V.z) - (U.z * V.x);
    //norm.z = (U.y * V.x) - (U.x * V.y);

    return norm;
}
