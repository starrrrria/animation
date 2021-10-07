//
//  main.cpp
//  Lab3
//
//  Created by 补锌 on 2021/3/20.
//

#include "stdio.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h> //目录下的档案
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<glm/common.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <assert.h>
#include <AntTweakBar.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <math.h>
#include <glm/gtx/dual_quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/epsilon.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/vector_relational.hpp>
#if GLM_HAS_TRIVIAL_QUERIES
#    include <type_traits>
#endif

#include <fstream>
#include <set>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include "Camera.hpp"
#include "Mesh.hpp"
#include "maths_funcs.h"
#include "Shader.hpp"
#include "Model.hpp"
using namespace::glm;
using namespace std;
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Sparse>
#include <eigen3/Eigen/Core>
//Camera camera(glm::vec3(0,2.0f,-15.0f),glm::radians(0.0f),glm::radians(180.0f),glm::radians(0.0f));
//void my_direct_manip_method(...)
//{
//    unsigned int  num_rows = 2;
//    unsigned int  num_cols = 2;
//
//    Eigen::MatrixXf A;
//    Eigen::VectorXf b；
//    //setup left-hand side
//    Eigen::MatrixXf B(num_rows,num_cols); //the delta-blendshape matrix + additional weight normalization
//
//    // fill the matrix B by acessing element-wise B(row,column)=???
//
//
//    // setup right-hand side
//    Eigen::VectorXf b(num_rows);
//    // fill the vector b by acessing element-wise b(row)=???
//
//
//    //solve the least-squares problem A * w = b with A=BtB and b= Btb
//    //the function B.transpose() returns the transpose of a matrix
//
//    Eigen::LDLT<Eigen::MatrixXf> solver(A);
//    Eigen::VectorXf w = solver.solve(b);
//
//    //copy back the weights my_weights[row] = w(row)
//
//}
bool isclick = true;
float clickPointX;
float clickPointY;
float radius = 3.0f;
float xOffset;
float yOffset;
float depth  = -1.0f;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float weight[25] = {0};
float countNum = 0.0f;
int changeNumber;
int frameNum;
float lastTime = 0;
int update(int Num){
    int frame = 0;
    float currTime = (float)glfwGetTime();
    float  delta = currTime - lastTime;

    if (delta > 0.04f){
        countNum+=1;
        frame = floor(countNum / 10.0f);
        frame = frame % Num;
        delta = 0.03f;
    }
    lastTime = currTime;
    return frame;
}
std::vector<GLuint> constraints;
//MatrixType m0;
Eigen::VectorXd m0;
std::vector<Model> modelist;
std::vector<std::string> out;
Model original;
Model model;
Model circle;
Model circle1;

std::vector<float> F0;
std::vector<std::vector<float>> B;
std::vector<std::vector<float>> weight_animation;

vector<vector<float> > transpose(vector<vector<float> > &matrix)
{

    vector<vector<float>>v(matrix[0].size(),vector<float>());
    for(int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            v[j].push_back(matrix[i][j]);
        }
    }

    return v;

}
std::vector<std::vector<float>> read_txt(const std::string& filename)
{
        char   s[200];
        float  w1, w2, w3,w4, w5, w6,w7, w8, w9,w10, w11, w12,w13, w14, w15,w16, w17, w18,w19, w20, w21,w22, w23, w24;
         
        // open file (in ASCII mode)
        FILE* in = fopen(filename.c_str(), "r");
        

        // clear line once
        memset(&s, 0, 200);

        std::vector<std::vector<float>> weights;
    
        // parse line by line (currently only supports vertex positions & faces
        while (in && !feof(in) && fgets(s, 200, in))
        {
            if (sscanf(s, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", &w1, &w2, &w3,&w4, &w5, &w6,&w7, &w8, &w9,&w10, &w11, &w12,&w13, &w14, &w15,&w16, &w17, &w18,&w19, &w20, &w21,&w22, &w23, &w24))
            {
                std::vector<float> temp;
                temp.push_back(w1);
                temp.push_back(w2);
                temp.push_back(w3);
                temp.push_back(w4);
                temp.push_back(w5);
                temp.push_back(w6);
                temp.push_back(w7);
                temp.push_back(w8);
                temp.push_back(w9);
                temp.push_back(w10);
                temp.push_back(w11);
                temp.push_back(w12);
                temp.push_back(w13);
                temp.push_back(w14);
                temp.push_back(w15);
                temp.push_back(w16);
                temp.push_back(w17);
                temp.push_back(w18);
                temp.push_back(w19);
                temp.push_back(w20);
                temp.push_back(w21);
                temp.push_back(w22);
                temp.push_back(w23);
                temp.push_back(w24);
                weights.push_back(temp);
            }
        }

        fclose(in);
    return weights;
}
void get_files_in_directory(
    std::vector<std::string> &out, //list of file names within directory
    const std::string &directory //absolute path to the directory
    )
{
    DIR *dir;
    class dirent *ent;
    class stat st;

    dir = opendir(directory.c_str());
    while ((ent = readdir(dir)) != NULL) {
        const std::string file_name = ent->d_name;
        const std::string full_file_name = directory + "/" + file_name;

        if (file_name[0] == '.')
            continue;

        if (stat(full_file_name.c_str(), &st) == -1)
            continue;

        const bool is_directory = (st.st_mode & S_IFDIR) != 0;

        if (is_directory)
            continue;

        out.push_back(full_file_name);
    }
    closedir(dir);
}
inline void TwEventMousePosGLFW3(GLFWwindow* window, double xpos, double ypos)
{   TwMouseMotion(int(xpos), int(ypos));
    clickPointX = xpos;
    clickPointY = ypos;
    xOffset = xpos;
    yOffset = ypos;
//    xOffset = xpos -400;
//    yOffset = 300 - ypos;
//    xOffset = xOffset/260;
//    yOffset = yOffset/260;
}
inline void TwEventMouseButtonGLFW3(GLFWwindow* window, int button, int action, int mods)
{   TwEventMouseButtonGLFW(button, action);
    if(action == GLFW_PRESS) switch (button){
        case GLFW_MOUSE_BUTTON_LEFT:
            glfwSetCursorPosCallback(window, (GLFWcursorposfun)TwEventMousePosGLFW3);
            
//            clickPointX = (-1) + (clickPointX/SCR_WIDTH) * 2;
//            clickPointY = 1 - (clickPointY/SCR_HEIGHT) * 2;
//            printf("mouse coordinates are %f,%f\n",xOffset,yOffset);
            isclick = false;
            break;
    }
}
inline void TwWindowSizeGLFW3(GLFWwindow* window, int width, int height)
{TwWindowSize(width, height);}
inline void TwEventMouseWheelGLFW3(GLFWwindow* window, double xoffset, double yoffset)
{TwEventMouseWheelGLFW(yoffset);}
inline void TwEventKeyGLFW3(GLFWwindow* window, int key, int scancode, int action, int mods)
{   TwEventKeyGLFW(key, action);
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) { //change first and third camera
        changeNumber += 1;
    }
}
inline void TwEventCharGLFW3(GLFWwindow* window, int codepoint)
{TwEventCharGLFW(codepoint, GLFW_PRESS);}

void processInput(GLFWwindow *window)
{
    
}

glm::vec3 vertexPicker(int x,int y,glm::mat4 VM,glm::mat4 P,Mesh mesh){
    glm::vec3 window;
    window.x = x;
    window.y = SCR_HEIGHT - y - 1;
    glReadPixels(x, SCR_HEIGHT - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &window.z);

    glm::vec3 object = glm::unProject(window, VM, P, glm::vec4(0.0f,0.0f,SCR_WIDTH,SCR_HEIGHT));
    printf("object coordinates are %s,%s,%s\n",std::to_string(object.x).c_str(),std::to_string(object.y).c_str(),std::to_string(object.z).c_str());

    GLfloat dist = 10;
    GLfloat temp = 0.0f;
    
    GLuint v_index = 0;

    for (int j = 0; j < mesh.vertices.size(); j++) {
        temp = glm::distance(glm::vec3(2,5,2), mesh.vertices[j].Position);
        if (temp <= dist) {
            dist = temp;
            v_index = j;
        }
    }
    
    glm::vec3 vertex1 = mesh.vertices[v_index].Position;
    printf("vertex coordinates are %f,%f,%f\n",vertex1.x,vertex1.y,vertex1.z);

    constraints.push_back(v_index);
    m0.conservativeResize(constraints.size()*3);
    m0(3*constraints.size() - 3)  = vertex1.x;
    m0(3*constraints.size() - 2)  = vertex1.y;
    m0(3*constraints.size() - 1)  = vertex1.z;

    return vertex1;
}

glm::vec3 FindVertex(float x,float y,glm::mat4 VM,glm::mat4 P,Model model){
    float depth1;
    glm::vec3 window;
    printf("window coordinate %f,%f\n",x,y);
    window.x = x;
    window.y = SCR_HEIGHT - y - 1;
    glReadPixels(x, SCR_HEIGHT - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth1);
    printf("window coordinate after manipulate%f,%f,%f\n",window.x,window.y,depth1);
    glm::vec3 object = glm::unProject(glm::vec3(window.x,window.y,depth1), VM, P, glm::vec4(0.0f,0.0f,SCR_WIDTH,SCR_HEIGHT));
    
    printf("object coordinates are %s,%s,%s\n",std::to_string(object.x).c_str(),std::to_string(object.y).c_str(),std::to_string(object.z).c_str());

    GLfloat dist = 10;
    GLfloat temp = 0.0f;
    GLuint m_index = 0;
    GLuint v_index = 0;
    for(int i = 0;i < model.meshes.size();i++){
        for (int j = 0; j < model.meshes[i].vertices.size(); j++) {
            temp = glm::distance(object, model.meshes[i].vertices[j].Position);
            if (temp <= dist) {
                dist = temp;
                m_index = i;
                v_index = j;
            }
        }
    }

    glm::vec3 vertexP = model.meshes[m_index].vertices[v_index].Position;
    depth = model.meshes[m_index].vertices[v_index].Position.z;
    printf("vertex coordinates are %f,%f,%f\n",vertexP.x,vertexP.y,vertexP.z);
    return vertexP;
}
int main(int argc, const char * argv[]) {
    std::string exePath = argv[0];
    //std::cout << exePath.substr(0,exePath.find_last_of('/'))+ '/Structure/Structure/Wall-Window.obj' << std::endl;
    //Open window
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    
    
    TwBar *bar;
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lab3", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); //终止
        return -1;
    }
    glfwMakeContextCurrent(window); //绑定使用
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//取消鼠标
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetMouseButtonCallback(window, mouse_button_callback);
//    glEnable(GL_CULL_FACE);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glCullFace(GL_BACK);
    //Init GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        printf("Init GLEW fault");
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600); //设置窗口大小起始坐标终止坐标
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    //stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);

    // Initialize AntTweakBar
    TwInit(TW_OPENGL_CORE, NULL);
    TwDefine(" GLOBAL fontSize=24 ");
    TwWindowSize(1600, 1150);
    // Create a tweak bar
    TwBar *mainBar = TwNewBar("Main");
    TwDefine(" Main label='Main TweakBar' refresh=0.5 position='16 16' size='400 400' alpha=0"); // Message added to the help bar.
    TwAddVarRW(mainBar, "point X_Pos", TW_TYPE_FLOAT, &xOffset,"keyIncr=u keyDecr=U");
    TwAddVarRW(mainBar, "point Y_Pos", TW_TYPE_FLOAT, &yOffset,"keyIncr=u keyDecr=U");
    TwAddVarRW(mainBar, "point depth", TW_TYPE_FLOAT, &depth,"keyIncr=u keyDecr=U");
    TwEnumVal expressionEV[] = {{ Model::neutral,  "neutral" }, //i=11
                                { Model::l_n_w, "Mery_l_nose_wrinkle"},
                                { Model::kiss,  "Mery_kiss" },
                                { Model::l_b_r, "Mery_l_brow_raise" },
                                { Model::j_o, "Mery_jaw_open"},
                                { Model::r_e_u_o,  "Mery_r_eye_upper_open" },
                                { Model::r_e_c, "Mery_r_eye_closed" },
                                { Model::r_s,  "Mery_r_suck" },
                                { Model::r_b_l, "Mery_r_brow_lower" },
                                { Model::l_b_n, "Mery_l_brow_narrow"},
                                { Model::r_n_w,  "Mery_r_nose_wrinkle" },
                                { Model::l_s, "Mery_l_suck" },
                                { Model::r_e_l_o, "Mery_r_eye_lower_open" },
                                { Model::r_b_r, "Mery_r_brow_raise"},
                                { Model::l_sad,  "Mery_l_sad" },
                                { Model::l_p, "Mery_l_puff" },
                                { Model::l_e_u_o,  "Mery_l_eye_upper_open" },
                                { Model::r_p, "Mery_r_puff" },
                                { Model::l_e_c, "Mery_l_eye_closed"},
                                { Model::l_b_l,  "Mery_l_brow_lower" },
                                { Model::l_e_l_o, "Mery_l_eye_lower_open" },
                                { Model::r_b_n,  "Mery_r_brow_narrow" },
                                { Model::r_smile, "Mery_r_smile" },
                                { Model::l_smile, "Mery_l_smile"},
                                { Model::r_sad,  "Mery_r_sad" }
    };
    TwType expressionType = TwDefineEnum( "Expression Mode", expressionEV, 25 );
    TwAddVarRW(mainBar, "Expression", expressionType, &model.expression,
                   " help='Change the expression mode.' ");
    TwAddVarRW(mainBar, "weight1", TW_TYPE_FLOAT, &weight[1], "label='l_nose_wrinkle' min=0 max=1 step=0.1 keyIncr=u keyDecr=U" );
    TwAddVarRW(mainBar, "weight2", TW_TYPE_FLOAT, &weight[2], "label='Kiss' min=0 max=1 step=0.1 keyIncr=u keyDecr=U help='Rotation speed (turns/second)'");
    TwAddVarRW(mainBar, "weight3", TW_TYPE_FLOAT, &weight[3], "label='l_brow_raise' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");
    TwAddVarRW(mainBar, "weight4", TW_TYPE_FLOAT, &weight[4], "label='jaw_open' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");
    TwAddVarRW(mainBar, "weight5", TW_TYPE_FLOAT, &weight[5], "label='r_eye_upper_open' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");
    TwAddVarRW(mainBar, "weight6", TW_TYPE_FLOAT, &weight[6], "label='r_eye_closed' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");
    TwAddVarRW(mainBar, "weight7", TW_TYPE_FLOAT, &weight[7], "label='r_suck' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");
    TwAddVarRW(mainBar, "weight8", TW_TYPE_FLOAT, &weight[8], "label='r_brow_lower' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");
    TwAddVarRW(mainBar, "weight9", TW_TYPE_FLOAT, &weight[9], "label='l_brow_narrow' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");
    TwAddVarRW(mainBar, "weight10", TW_TYPE_FLOAT, &weight[10], "label='r_nose_wrinkle' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");
    TwAddVarRW(mainBar, "weight11", TW_TYPE_FLOAT, &weight[11], "label='l_suck' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");
    TwAddVarRW(mainBar, "weight12", TW_TYPE_FLOAT, &weight[12], "label='r_eye_lower_open' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");
    TwAddVarRW(mainBar, "weight13", TW_TYPE_FLOAT, &weight[13], "label='r_brow_raise' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");
    TwAddVarRW(mainBar, "weight14", TW_TYPE_FLOAT, &weight[14], "label='l_sad' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");
    TwAddVarRW(mainBar, "weight15", TW_TYPE_FLOAT, &weight[15], "label='l_puff' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");
    TwAddVarRW(mainBar, "weight16", TW_TYPE_FLOAT, &weight[16], "label='l_eye_upper_open' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");
    TwAddVarRW(mainBar, "weight17", TW_TYPE_FLOAT, &weight[17], "label='r_puff' min=0 max=1 step=0.1 keyIncr=u keyDecr=U h");
    TwAddVarRW(mainBar, "weight18", TW_TYPE_FLOAT, &weight[18], "label='l_eye_closed' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");
    TwAddVarRW(mainBar, "weight19", TW_TYPE_FLOAT, &weight[19], "label='l_brow_lower' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");
    TwAddVarRW(mainBar, "weight20", TW_TYPE_FLOAT, &weight[20], "label='l_eye_lower_open' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");
    TwAddVarRW(mainBar, "weight21", TW_TYPE_FLOAT, &weight[21], "label='r_brow_narrow' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");
    TwAddVarRW(mainBar, "weight22", TW_TYPE_FLOAT, &weight[22], "label='r_smile' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");
    TwAddVarRW(mainBar, "weight23", TW_TYPE_FLOAT, &weight[23], "label='l_smile' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");
    TwAddVarRW(mainBar, "weight24", TW_TYPE_FLOAT, &weight[24], "label='r_sad' min=0 max=1 step=0.1 keyIncr=u keyDecr=U ");

    // - Directly redirect GLFW mouse button events to AntTweakBar
//    glfwSetWindowSizeCallback(window, (GLFWwindowposfun)TwWindowSizeGLFW3);

    glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)TwEventMouseButtonGLFW3);
//    glfwSetCursorPosCallback(window, (GLFWcursorposfun)TwEventMousePosGLFW3);
    glfwSetScrollCallback(window, (GLFWscrollfun)TwEventMouseWheelGLFW3);
    glfwSetKeyCallback(window, (GLFWkeyfun)TwEventKeyGLFW3);
    glfwSetCharCallback(window, (GLFWcharfun)TwEventCharGLFW3);
    
//    GLuint VertexArrayID;
//    glGenVertexArrays(1, &VertexArrayID);
//    glBindVertexArray(VertexArrayID);
    weight_animation = read_txt("/Users/buxin/Documents/Real-time- Animations/blendshape_animation.txt");
    
    Shader* modelShader = new Shader("/Users/buxin/Documents/Real-time- Animations/animation/Lab3/vertexSource.vert","/Users/buxin/Documents/Real-time- Animations/animation/Lab3/fragementSource.frag");
    Shader* circleShader = new Shader("/Users/buxin/Documents/Real-time- Animations/animation/Lab3/vertexSource.vert","/Users/buxin/Documents/Real-time- Animations/animation/Lab3/fragementSource.frag");
    Shader* circleShader1 = new Shader("/Users/buxin/Documents/Real-time- Animations/animation/Lab3/vertexSource.vert","/Users/buxin/Documents/Real-time- Animations/animation/Lab3/fragementSource.frag");
    
    get_files_in_directory(out,"/Users/buxin/Downloads/High-res Blendshape Model");
    original.loadModel("/Users/buxin/Downloads/High-res Blendshape Model/neutral.obj");
    circle.loadModel("/Users/buxin/Downloads/only_quad_sphere.obj");
    circle1.loadModel("/Users/buxin/Downloads/only_quad_sphere.obj");
    
    modelist.push_back(original);
    for (int i = 0; i < original.meshes[0].positions.size(); i++) {
        F0.push_back(original.meshes[0].positions[i].x);
        F0.push_back(original.meshes[0].positions[i].y);
        F0.push_back(original.meshes[0].positions[i].z);
    }
    
    for (int i = 0; i < out.size(); i++) { //i-11 neural
        if (i == 11) {
            continue;
        }else{
            Model model1;
            model1.loadModel(out[i]);
            std::vector<float> temp;
            for (int j = 0; j < model1.meshes[0].positions.size(); j++) {
                temp.push_back(model1.meshes[0].positions[j].x-original.meshes[0].positions[j].x);
                temp.push_back(model1.meshes[0].positions[j].y-original.meshes[0].positions[j].y);
                temp.push_back(model1.meshes[0].positions[j].z-original.meshes[0].positions[j].z);
            }

            B.push_back(temp);
            modelist.push_back(model1);
        }
    }
    
//    GLuint vertexbuffer;
//    glGenBuffers(1, &vertexbuffer);
//       // 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
//    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//       // glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER, mesh.positions.size() * sizeof(glm::vec3), &mesh.positions[0], GL_STATIC_DRAW);
//
//    GLuint uvbuffer;
//    glGenBuffers(1, &uvbuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
//       //glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER, mesh.tex_coords.size() * sizeof(glm::vec2), &mesh.tex_coords[0], GL_STATIC_DRAW);

    glm::mat4 projMat = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
    glm::vec3 pos = glm::vec3(0, 0, radius); // Camera is at (4,3,3), in World Space
    glm::vec3 lookAtPos = glm::vec3(0, 0, 0);
    glm::vec3 up = glm::vec3(0, 1, 0);
    // Camera matrix
    glm::mat4 View = glm::lookAt(pos, lookAtPos, up);
    glm::mat4 ModelMat = glm::mat4(1.0f);
    glm::mat4 circleMat = glm::mat4(1.0f);
    glm::mat4 circleMat1 = glm::mat4(1.0f);
    
    glm::mat4 MVP = projMat * View * ModelMat;
    glm::mat4 VM =  ModelMat*View;
    glm::vec3 pixel = glm::vec3(0,0,0);
    glm::mat4 invVP = glm::inverse(View * projMat);

    while (!glfwWindowShouldClose(window)) {
        //Process input
        processInput(window); //下一帧输入
        //Clear screen
        glClearColor(0.8f,0.8f,0.8f,1.0f); //r,g,b,
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        circleShader -> use();
        circleMat = glm::translate(glm::mat4(1.0f), glm::vec3(xOffset, yOffset, 0));
//        Model = glm::rotate(Model,(float)glfwGetTime(),glm::vec3(0.0f,1.0f,0.0f));
        circleMat = glm::scale(circleMat, glm::vec3(0.025,0.025,0.025));

        glUniformMatrix4fv(glGetUniformLocation(circleShader->ID,"modelMat"),1,GL_FALSE,value_ptr(circleMat));
        glUniformMatrix4fv(glGetUniformLocation(circleShader->ID,"viewMat"),1,GL_FALSE,value_ptr(View));
        glUniformMatrix4fv(glGetUniformLocation(circleShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(circleShader->ID,"cameraPos"),radius,0,radius);
        glUniform3f(glGetUniformLocation(circleShader->ID,"ambientColor"),0.0f,0.8f,0.0f);//环境光
        glUniform3f(glGetUniformLocation(circleShader->ID,"lightPos"), -2.0f,5.5f, 2.0f);
        glUniform3f(glGetUniformLocation(circleShader->ID,"lightColor"),0.0f,0.8f,0.0f);
        glUniform1f(glGetUniformLocation(circleShader->ID,"specNum"),8.0f);
        circle.Draw(circleShader);
        
        circleShader1 -> use();
        circleMat1 = glm::translate(glm::mat4(1.0f), glm::vec3(pixel.x/10,pixel.y/10,0));
//        Model = glm::rotate(Model,(float)glfwGetTime(),glm::vec3(0.0f,1.0f,0.0f));
        circleMat1 = glm::scale(circleMat1, glm::vec3(0.025,0.025,0.025));

        glUniformMatrix4fv(glGetUniformLocation(circleShader1->ID,"modelMat"),1,GL_FALSE,value_ptr(circleMat1));
        glUniformMatrix4fv(glGetUniformLocation(circleShader1->ID,"viewMat"),1,GL_FALSE,value_ptr(View));
        glUniformMatrix4fv(glGetUniformLocation(circleShader1->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(circleShader1->ID,"cameraPos"),radius,0,radius);
        glUniform3f(glGetUniformLocation(circleShader1->ID,"ambientColor"),0.0f,0.0f,0.8f);//环境光
        glUniform3f(glGetUniformLocation(circleShader1->ID,"lightPos"), -2.0f,5.5f, 2.0f);
        glUniform3f(glGetUniformLocation(circleShader1->ID,"lightColor"),0.0f,0.0f,0.8f);
        glUniform1f(glGetUniformLocation(circleShader1->ID,"specNum"),8.0f);
        circle1.Draw(circleShader1);
        
        std::vector<Vertex> F;
        if((changeNumber%2) == 1){
            frameNum = update(35);
            F = modelist[0].meshes[0].vertices;
            for (int j  = 0; j < 24; j++) { //F = f0 + B*w
                for (int i = 0; i < B[j].size(); i++) {
                    if (i % 3 == 0) {
                        F[i/3].Position.x += B[j][i]*weight_animation[frameNum][j+1];
                    }
                    else if (i % 3 == 1) {
                        F[i/3].Position.y += B[j][i]*weight_animation[frameNum][j+1];
                    }else{
                        F[i/3].Position.z += B[j][i]*weight_animation[frameNum][j+1];
                    }
                }
            }
        }
        else{
            F = modelist[0].meshes[0].vertices;
            for (int j  = 0; j < 24; j++) { //F = f0 + B*w
                for (int i = 0; i < B[j].size(); i++) {
                    if (i % 3 == 0) {
                        F[i/3].Position.x += B[j][i]*weight[j+1];
                    }
                    else if (i % 3 == 1) {
                        F[i/3].Position.y += B[j][i]*weight[j+1];
                    }else{
                        F[i/3].Position.z += B[j][i]*weight[j+1];
                    }
                }
            }
        }
        
        Mesh  mesh1(F,modelist[0].meshes[0].indices);
//        pixel = vertexPicker(clickPointX, clickPointY, VM, projMat, mesh1);
//        pixel = CreateRay(clickPointX, clickPointY,View,projMat,mesh1);
        pixel = FindVertex(xOffset, yOffset, invVP, projMat, modelist[0]);
    
        modelShader -> use();
        ModelMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,-1.8f,-2.0f));
//        Model = glm::rotate(Model,(float)glfwGetTime(),glm::vec3(0.0f,1.0f,0.0f));
        ModelMat = glm::scale(ModelMat, glm::vec3(0.1,0.1,0.1));

        glUniformMatrix4fv(glGetUniformLocation(modelShader->ID,"modelMat"),1,GL_FALSE,value_ptr(ModelMat));
        glUniformMatrix4fv(glGetUniformLocation(modelShader->ID,"viewMat"),1,GL_FALSE,value_ptr(View));
        glUniformMatrix4fv(glGetUniformLocation(modelShader->ID,"projMat"),1,GL_FALSE,value_ptr(projMat));
        glUniform3f(glGetUniformLocation(modelShader->ID,"cameraPos"),radius,0,radius);
        glUniform3f(glGetUniformLocation(modelShader->ID,"ambientColor"),0.5f,0.5f,0.5f);//环境光
        glUniform3f(glGetUniformLocation(modelShader->ID,"lightPos"), -2.0f,5.5f, 2.0f);
        glUniform3f(glGetUniformLocation(modelShader->ID,"lightColor"),0.6f,0.6f,0.6f);
        glUniform1f(glGetUniformLocation(modelShader->ID,"specNum"),8.0f);
        
        if(model.expression == Model::neutral){
//            model1.loadModel(dirList[1]);
            mesh1.Draw(modelShader);
        }
        else if (model.expression == Model::l_n_w) {
//            model.loadModel(dirList[0]);
            modelist[1].Draw(modelShader);
        }
        else if(model.expression == Model::kiss){
//            model1.loadModel(dirList[1]);
            modelist[2].Draw(modelShader);
        }else if(model.expression == Model::l_b_r){
//            model1.loadModel(dirList[1]);
            modelist[3].Draw(modelShader);
        }
        else if(model.expression == Model::j_o){
//            model1.loadModel(dirList[1]);
            modelist[4].Draw(modelShader);
        }
        else if(model.expression == Model::r_e_u_o){
//            model1.loadModel(dirList[1]);
            modelist[5].Draw(modelShader);
        }
        else if(model.expression == Model::r_e_c){
//            model1.loadModel(dirList[1]);
            modelist[6].Draw(modelShader);
        }
        else if(model.expression == Model::r_s){
//            model1.loadModel(dirList[1]);
            modelist[7].Draw(modelShader);
        }
        else if(model.expression == Model::r_b_l){
//            model1.loadModel(dirList[1]);
            modelist[8].Draw(modelShader);
        }
        else if(model.expression == Model::l_b_n){
//            model1.loadModel(dirList[1]);
            modelist[9].Draw(modelShader);
        }
        else if(model.expression == Model::r_n_w){
//            model1.loadModel(dirList[1]);
            modelist[10].Draw(modelShader);
        }
        else if(model.expression == Model::l_s){
//            model1.loadModel(dirList[1]);
            modelist[11].Draw(modelShader);
        }
        else if(model.expression == Model::r_e_l_o){
//            model1.loadModel(dirList[1]);
            modelist[12].Draw(modelShader);
        }
        else if(model.expression == Model::r_b_r){
//            model1.loadModel(dirList[1]);
            modelist[13].Draw(modelShader);
        }
        else if(model.expression == Model::l_sad){
//            model1.loadModel(dirList[1]);
            modelist[14].Draw(modelShader);
        }
        else if(model.expression == Model::l_p){
//            model1.loadModel(dirList[1]);
            modelist[15].Draw(modelShader);
        }
        else if(model.expression == Model::l_e_u_o){
//            model1.loadModel(dirList[1]);
            modelist[16].Draw(modelShader);
        }
        else if(model.expression == Model::r_p){
//            model1.loadModel(dirList[1]);
            modelist[17].Draw(modelShader);
        }
        else if(model.expression == Model::l_e_c){
//            model1.loadModel(dirList[1]);
            modelist[18].Draw(modelShader);
        }
        else if(model.expression == Model::l_b_l){
//            model1.loadModel(dirList[1]);
            modelist[19].Draw(modelShader);
        }
        else if(model.expression == Model::l_e_l_o){
//            model1.loadModel(dirList[1]);
            modelist[20].Draw(modelShader);
        }
        else if(model.expression == Model::r_b_n){
//            model1.loadModel(dirList[1]);
            modelist[21].Draw(modelShader);
        }
        else if(model.expression == Model::r_smile){
//            model1.loadModel(dirList[1]);
            modelist[22].Draw(modelShader);
        }
        else if(model.expression == Model::l_smile){
//            model1.loadModel(dirList[1]);
            modelist[23].Draw(modelShader);
        }
        else{
//            model1.loadModel(dirList[1]);
            modelist[24].Draw(modelShader);
        }
        
        TwDraw();

        glfwSwapBuffers(window); //切换前后buffer
        glfwPollEvents();

    }
    //Exit Program
    TwTerminate();
    glfwTerminate();
    return 0;
}

