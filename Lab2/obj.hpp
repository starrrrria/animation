//
//  obj.hpp
//  Lab2
//
//  Created by 补锌 on 2021/3/2.
//

#ifndef obj_hpp
#define obj_hpp

#include <stdio.h>
#pragma once
#include <vector>
#include <iostream>
#include <GL/glut.h>

using namespace std;

class ObjLoader
{
public:
    struct vertex
    {
        float x;
        float y;
        float z;
    };
    ObjLoader(string filename);//读取函数
    void Draw();//绘制函数
private:
    vector<vector<GLfloat>> v;//存放顶点(x,y,z)坐标
    vector<vector<GLint>> f;//存放面的三个顶点索引
};


#endif /* obj_hpp */
