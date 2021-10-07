//
//  Shader.cpp
//  triangle
//
//  Created by 补锌 on 2020/10/24.
//

#include "Shader.hpp"
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    ifstream  vertexFile;
    ifstream fragmentFile;
    stringstream vertexSStream;
    stringstream fragmentSStream;
    
    vertexFile.open(vertexPath);//开档
    fragmentFile.open(fragmentPath);
    vertexFile.exceptions(ifstream::failbit | ifstream::badbit);
    fragmentFile.exceptions(ifstream::failbit | ifstream::badbit);
    
    try {
        if (!vertexFile.is_open()|| !fragmentFile.is_open()) {
            std::logic_error ex("open file error");
            throw exception(ex);
        }
        
        vertexSStream << vertexFile.rdbuf(); //从硬盘读到file再导入stream
        fragmentSStream << fragmentFile.rdbuf();
        
        vertexString = vertexSStream.str(); //转string
        fragmentString = fragmentSStream.str();
        
        vertexSource = vertexString.c_str(); //转char array
        fragmentSource = fragmentString.c_str();
        
        unsigned int vertex,fragment;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex,1,&vertexSource,NULL); //只传一个字符串，往上抽一层&，每个字符串长度NULL
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        
        fragment  = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment,1,&fragmentSource,NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");
        
        ID = glCreateProgram();
        glAttachShader(ID,vertex); //将shader链接到program
        glAttachShader(ID,fragment);
        glLinkProgram(ID); //二进制代码attach完
        checkCompileErrors(ID, "PROGRAM");
        
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        
    } catch (const std::exception&ex) {
        printf("%s", ex.what());
    }
}

void Shader::use(){
    glUseProgram(ID);
}
void Shader::SetUniform3f(const char* paramNameString,glm::vec3 param){
    glUniform3f(glGetUniformLocation(ID,paramNameString),param.x,param.y,param.z);
}
void Shader::SetUniform1f(const char* paramNameString,float param){
    glUniform1f(glGetUniformLocation(ID,paramNameString),param);
}
void Shader::SetUniform1i(const char* paramNameString,int slot){
    glUniform1i(glGetUniformLocation(ID,paramNameString),slot);
}
void Shader::checkCompileErrors(unsigned int ID,std::string type){
    int success;
    char infoLog[512];
    
    if (type != "PROGRAM") { //不是program就查shader
        glGetShaderiv(ID,GL_COMPILE_STATUS,&success); //番号，存入success回复
        if (!success) {
            glGetShaderInfoLog(ID,512,NULL,infoLog); //取得错误，最多回报512字符，不用知道长度，空数组infolog
            cout << "shader compile error:" << infoLog << endl;
        }
    }
    else{ //是program
        glGetProgramiv(ID,GL_LINK_STATUS,&success);
        if (!success) {
            glGetProgramInfoLog(ID,512,NULL,infoLog);
            cout << "program linking error:" << infoLog <<endl;
        }
    }
};

