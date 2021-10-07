//
//  parse.cpp
//  Lab2
//
//  Created by 补锌 on 2021/3/1.
//

#include "parse.hpp"

#include <stdlib.h>
#include <stdio.h>
 
#include <iostream>
using namespace std;
#include <vector>
 
typedef vector<float> mypoint;
typedef vector<mypoint> myskeleton;
typedef vector<myskeleton> myskeletons;
 
 
 
myskeleton reshape_mk(myskeleton mk);
 
void get_mk_box(myskeleton mk, float *box);
 
myskeleton readsingle(string name)
{
    FILE *fp = fopen(name.c_str(), "r");
 
    int num = 1;
    int jo = 15;
 
    float x = 0, y = 0, z = 0;
 
 
    myskeleton mk;
    mk.resize(jo);
 
    for (int j = 0; j< jo; j++)
    {
        mypoint mp;
        mp.resize(3);
 
        fscanf(fp, "%f %f %f\n", &x, &y, &z);
        mp[0] = x;
        mp[1] = y;
        mp[2] = z;
 
        mk[j] = mp;
    }
 
 
    return reshape_mk(mk);
}
 
myskeleton reshape_mk(myskeleton mk)
{
 
    int jo = 15;
 
    float box[4];
    get_mk_box(mk, box);
 
    float len = box[3] - box[2];
 
    for (int j = 0; j< jo; j++)
    {
        mk[j][0] *= 100/len;
        mk[j][1] *= 100/len;
        mk[j][2] *= 100/len;
    }
 
    mypoint mp = mk[8];
 
    for (int j = 0; j< jo; j++)
    {
        mk[j][0] -= mp[0];
        mk[j][1] -= mp[1];
        mk[j][2] -= mp[2];
    }
 
    return mk;
}
 
void get_mk_box(myskeleton mk, float *box)
{
    //x
    box[0] = 100000000;
    box[1] = -100000000;
    //y
    box[2] = 100000000;
    box[3] = -100000000;
 
    for (int j = 0; j< mk.size(); j++)
    {
        mypoint mp = mk[j];
 
        // x
        if (box[0] > mp[0])
        {
            box[0] = mp[0];
        }
        if (box[1] < mp[0])
        {
            box[1] = mp[0];
        }
 
        // y
        if (box[2] > mp[1])
        {
            box[2] = mp[1];
        }
        if (box[3] < mp[1])
        {
            box[3] = mp[1];
        }
    }
}

