
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <sstream>
//#include <GL/glew.h>
//#include <GL/glut.h>
//#include <GL/gl.h>
//#include <GLFW/glfw3.h> //目录下的档案
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtc/quaternion.hpp>
//#include <glm/gtx/quaternion.hpp>
//#include <ft2build.h>
//#include <freetype/freetype.h>
//#include <assert.h>
//#include <AntTweakBar.h>
//#include "stdio.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//#include <math.h>
//#define GLUT_DISABLE_ATEXIT_HACK
//#include "Shader.hpp"
//#include "Material.hpp"
//#include "Camera.hpp"
//#include "mesh.h"
//#include "ogldev_util.h"
//#include "boneh.hpp"
//using namespace::glm;
//#include "3dLoad.hpp"
#include <GL/GLTools.h>
#include <glut/glut.h>
#define FREEGLUT_STATIC
#include <GL/glut.h>
#include <cstdio>
#include <cassert>
#include <cmath>

//#include "3dx.hpp"
#include "boneh.hpp"
#include "matrix.hpp"
#include "vector.hpp"
//#include "buffer.hpp"
//#include "util.h"

GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
float PI = 3.1415926;
float locx = 0,locy = 0;

float pyzy = 0, pyqh = 0, pysx = 0;
float times = 1;
float anglezy = 0, anglesx = 0;
float py_speed = 10;

float xx = 4, yy = 5, zz = 20;
float angle1 = 1.0, angle2 = 1.0, angle3 = 1.0;
float xOffset = 0, yOffset = 0;
float xPre = 0, yPre = 6;

float theta1 = 1.0, theta2 = 1.0, betla = 1.0, omega = 1.0;
bool elbowUp = false;
float l1 = 4.25f, l2 = 4.25f;
//Model3ds Model3;
//vector <ModelObj *> OBvec;
//glm::vec3 **V_array;
//glm::vec2 **prjV_array;
//Buffer Buff;
//glm::vec3 lamp_p(4.0, 3.0, 2.0);
//float lamp_intsty = 1.0;
//glm::vec3 view_p(2.0, 3.0, 4.0);
//glm::vec3 model_p(0.0, 0.0, 0.0);
void init(const char *model_f)
{
//    glm::mat4 trans = lookAt(view_p, model_p, glm::vec3(0.0, 0.0, 1.0));
//    Model3.Load(model_f);
//    int m_num = Model3.GetObjNum();
//    OBvec = Model3.GetOB();
//    V_array = new glm::vec3 *[m_num];      // A Obj has a vertex array
//    prjV_array = new glm::vec2 *[m_num];
//    for (int i = 0; i < m_num; ++i) {
//            ModelObj *MObj = OBvec.at(i);
//            float *vb = MObj->GetVB();
//            int v_num = MObj->GetVertexNum();
//            V_array[i] = new glm::vec3 [v_num];
//            prjV_array[i] = new glm::vec2 [v_num];
//            for (int j = 0; j < v_num; ++j) {
//                glm::vec4 tmp = glm::vec4(1.0f);
//                tmp.x = vb[j * 3];
//                tmp.y = vb[j * 3 + 1];
//                tmp.z = vb[j * 3 + 2];
//                tmp.w = 1.0;
//                tmp = trans * tmp;
//                glm::vec3 v_vec = glm::vec3(tmp.x,tmp.y,tmp.z) / tmp.w;
//                V_array[i][j] = v_vec;
//                prjV_array[i][j] = glm::vec2(- v_vec.x,-v_vec.y) / v_vec.z;
//            }
//        }
    glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    GLfloat ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //环境光参数，半亮白色
    GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //漫射光参数，
    GLfloat position[] = { -10.0f, 10.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

}


GLint xRotation = 0;
GLint yRotation = 0;
float xp = 0;
float yp = 0;
int oldx = 0;
int oldy = 0;
void draw_ball() {
    glPushMatrix();
    glColor3f(0.0, 0.7, 0.7);
//    glTranslatef(0, bones[0].length , 0);
    glTranslatef(xp, yp , 0);
    glutWireSphere(0.5, 200, 500);
    glPopMatrix();

}
void draw_move(void) {
    if ((xp*xp + yp * yp )>= (l1+l2)*(l1+l2)) {
        theta1 = atan(yp/xp);
        theta1 = theta1 * 180/3.14;
        if(xp<= 0){
            theta1 = theta1+90;
        }else{
            theta1 = theta1-90;
        }
        
        theta2 = 0;
//        printf("out,%f\n",theta1);
    }
    else{
//        if (xp > 0) {
//            yp = -1 * yp;
//        }
        
        float summ = yp * yp + xp * xp;
        
        float alph1 = acos((l1*l1 - l2 * l2 - summ) / (-2 * l1*sqrt(summ)));
        float alph2 = atan2(yp , xp);
        alph1 = alph1 * 180 / 3.14;
        alph2 = alph2 * 180 / 3.14;
        
        if(elbowUp){
            float alph3 = acos((summ - l1 * l1 - l2 * l2) / (2 * l1*l2));
            alph3 = alph3 * 180 / 3.14;
            theta2 = alph3;
            if(theta2<0){
                theta1 = -alph1 - alph2;
            }else{
                theta1 = alph2 - alph1-90;
            }
        }else{
            float alph3 = acos((summ - l1 * l1 - l2 * l2) / (-2 * l1*l2));
            alph3 = alph3 * 180 / 3.14;
            theta2 = alph3;
            theta2 = -180 + theta2;
            if(theta2<0){
                theta1 =  alph1 + alph2-90 ;
            }else{
                theta1 =  -alph2 + alph1;
            }
        }
            
//other
        if (xp >= 0) {
            if(elbowUp){
//                theta2 = 180 + theta2;
//                theta1 = -theta1-60;
            }else{
//                theta1 = -theta1-90;
            }
            
//
//            yp = -1 * yp;
        }else{
            if(elbowUp){
//                theta2 = 180 + theta2;
//                theta1 = theta1+60;
            }
        }
    }
    
//    bool elbow_up = true;
//    bool elbow_down = false;
//    float s2 = 0;
//    float c2 = (summ -l1 * l1 - l2 * l2)/2 * l1*l2;
//    if (elbow_up) {
//        s2 = -sqrt(1-c2*c2);
//    }else if (elbow_down){
//        s2 = sqrt(1-c2*c2);
//    }
//    angle2 = atan(s2/ c2)* 180 / 3.14;
//    angle2 = 180 - angle2;
//    angle1 = (atan(yp/ xp) - atan(l2*s2/ l1+l2*c2))* 180 / 3.14;
    printf("pos,%f, %f \n", xp, yp);
    printf("angle,%f,%f \n", theta1, theta2);
}

/** 骨骼更新，即计算出每个骨骼的新变换矩阵，用displayBones数组保存 */

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'z':
                draw_move();
                glutPostRedisplay();
                break;
        case 'a':
                elbowUp = true;
                glutPostRedisplay();
                break;
        case 'd':
                elbowUp = false;
                glutPostRedisplay();
                break;

    }
}
void display(void)
{
    /** 用户自定义的绘制过程 */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
//    glTranslatef(0.0f, 1.0f, -25.0f);
    gluLookAt (0.0, 1.0, 25.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(25.0, 1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0, -1, -3);
    glScaled(2.0, 3, 2);
    glutSolidCube(2);
    glPopMatrix();
    glRotatef(theta1, 0, 0, 1);
    glColor3f(0.0, 0.5, 0.2);
    glTranslatef(0, 1, 0);
    glutSolidCube(1);
    glColor3f(0.5, 0.2, 0.3);
    glTranslatef(0, 1, 0);
    glRotatef(theta2, 0, 0, 1);
    glutWireSphere(0.8, 200, 500);
    glColor3f(0.4, 0.8, 0.3);
    glTranslatef(0, 3, 0);
    glScaled(0.5, 3, 1);

    glutSolidCube(2);

    glPopMatrix();
    
    /** 强制执行所有的OpenGL命令 */
    glFlush();
}
 
 void ChangeSize(int width, int height)
{
    glViewport(0, 0, width, height);                                    /**< 重新设置视口 */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1700.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
 
void motion(int x, int y)
{
    xRotation = xRotation - (x - oldx);
    yRotation = yRotation - (y - oldy);
    
    xOffset = x -400;
    yOffset = 300 - y;
    xp = xOffset*4.5/130;
    yp = yOffset*4.5/130;
//
//    if ((xp*xp+yp*yp)<=(l1+l2)*(l1+l2)) {
//        float theta2_cos,omega_cos;
//        theta2_cos = (xp*xp + yp*yp - l1*l1 - l2*l2)/2*l1*l2;
//        theta2 = acos(theta2_cos);
//        theta2 = theta2*180/PI;
//
//        betla = atan2(yp, xp);
//        omega_cos = (xp*xp + yp*yp + l1*l1 - l2*l2)/2*l1*sqrt(xp*xp + yp*yp);
//        omega = acos(omega_cos);
//        omega = omega*180/PI;
//
//        if (theta2 > 0) {
//            theta1 = betla-omega;
//        }else{
//            theta1 = betla+omega;
//        }
        
//        printf("%.3f",l1*l1+l2*l2);
//    }
    oldx = x;
    oldy = y;
 
    glutPostRedisplay();
}
 
void processMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        xOffset = x -400;
        yOffset = 300 - y;
        xp = xOffset*4.5/130;
        yp = yOffset*4.5/130;
    }
    printf("%.3f,%.3f",xp,yp);
}
int main(int argc, char** argv)
{
//    const char *model_f = argv[1];
//        init(model_f);
//
//        int m_num = Model3.GetObjNum();
//
//        for (int i = 0; i < m_num; ++i) {
//            LOG("Object:", i, m_num)
//
//            ModelObj *MObj = OBvec.at(i);
//
//            int f_num = MObj->GetFaceNum();
//            unsigned short *ib = MObj->GetIB();
//            // float z_min = 1000.0, z_max = -1000.0;
//            for (int j = 0; j < f_num; ++j) {
//                LOG("Face:", j, f_num)
//                // get face' 3 vertex by index j
//                glm::vec3 V0, V1, V2;
//                get_from_index<glm::vec3>(
//                    V0, V1, V2, V_array, i, ib, j);
//                glm::vec2 prjV0, prjV1, prjV2;
//                get_from_index<glm::vec2>(
//                    prjV0, prjV1, prjV2, prjV_array, i, ib, j);
//
//                // find the quation of face-plane
//                // A*x + B*y + C*z = 1.0
//                glm::mat3 XYZ3 = glm::mat3(V0, V1, V2);
//                XYZ3 = glm::inverse(XYZ3);
//                glm::vec3 ABC = glm::vec3(1.0, 1.0, 1.0) * XYZ3;
//
//                // find bounding box
//                // glm::vec2 proj_V0
//                unsigned i_min, i_max, j_min, j_max;
//                get_bound_box(prjV0, prjV1, prjV2, i_min, i_max, j_min, j_max);
//
//                // for (int ii = 0; ii < WIDTH; ++ii) {
//                // for (int jj = 0; jj < HEIGHT; ++jj) {
//                for (int ii = i_min - 2; ii < i_max + 2; ++ii) {
//                    for (int jj = j_min - 2; jj < j_max + 2; ++jj) {
//                        float x = ((float)(ii - (WIDTH / 2))) / (WIDTH / 2);
//                        float y = ((float)((HEIGHT / 2) - jj)) / (WIDTH / 2);
//                        glm::vec2 D(x, y);
//                        glm::vec3 P;
//                        screen_to_face(D, ABC, P);
//
//                        if (in_tri(V0, V1, V2, D)) {
//                            float z_v = z_value(P);
//                            // z_min = min(z_min, z_v); z_max = max(z_max, z_v);
//                            if (z_v > Buff.z_buff(ii, jj)) {
//                            #ifdef PHONG
//                                float f_v = f_value (
//                                    lamp_intsty,
//                                    255.0,
//                                    lamp_p,
//                                    view_p,
//                                    P,
//                                    ABC
//                                );
//                            #else
//                                float f_v = f_value(z_v);
//                            #endif
//                                Buff.update(ii, jj, (unsigned char)f_v, z_v);
//                            }
//                        }
//                    }
//                }
//            }
//            // cout << z_max << " " << z_min << endl;
//        }
//
//        if (argc == 4 && strcmp(argv[2], "-o") == 0)
//            Buff.svimg(argv[3]);
//        else
//            Buff.svimg("out.png");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB );
    glutInitWindowSize (800, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Lab2");
    init("/Users/buxin/Downloads/HumanMotionTrack_skeleton/data/3ds/skeleton/LTHIGH.3DS");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(display);
    glutMouseFunc(processMouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
//
//#define MAX_BONES                4   /**骨骼数*/
//#define MAX_MESHES              3   /**网格数，即基本图元数(纹理贴图后的皮肤)*/
//#define MAX_MESH_POINTS    4   /**一个网格顶点数，即四边形*/
//
//CVector4         trans;                       /**< 用于平移骨骼模型 */
//CBone             bones[MAX_BONES];            /**< 保存骨骼结构 */
//CMatrix4x4     displayBones[MAX_BONES];     /**< 用于绘制骨骼 */
//CBoneVertex   modelPoints[MAX_MESHES * MAX_MESH_POINTS]; /**< 模型顶点数据，即皮肤顶点 */
//GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
//float PI = 3.1415926;
//float locx = 0,locy = 0;
//
//float pyzy = 0, pyqh = 0, pysx = 0;
//float times = 1;
//float anglezy = 0, anglesx = 0;
//float py_speed = 10;
//
//float xx = 4, yy = 5, zz = 20;
//float angle1 = 1.0, angle2 = 1.0, angle3 = 1.0;
//float xOffset = 0, yOffset = 0;
//float xPre = 0, yPre = 6;
//
//float theta1 = 1.0, theta2 = 1.0, betla = 1.0, omega = 1.0;
//
//float l1 = 4.5f, l2 = 4.5f;
//
//
//void init(void)
//{
//    glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
//    glShadeModel(GL_SMOOTH);
//    glEnable(GL_DEPTH_TEST);
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//    GLfloat ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f }; //环境光参数，半亮白色
//    GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //漫射光参数，
//    GLfloat position[] = { -10.0f, 10.0f, 0.0f, 1.0f };
//    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
//    glLightfv(GL_LIGHT0, GL_POSITION, position);
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
////    m_mesh.LoadMesh("/Users/buxin/Downloads/ogldev-master/Content/boblampclean.md5mesh");
//    /** 构造骨骼 */
//    bones[0].SetBone(-1, l1);/**根关节(骨骼索引与长度)*/
//    bones[1].SetBone(0, 0);/**子关节*/
//    bones[2].SetBone(1, l2);
//    bones[3].SetBone(2, 0);
//
//    /** 绑定到骨骼上的皮肤顶点数据 */
//    modelPoints[0].SetVertex(CVector4(-1.0f, 0.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
//                             0, 0, 0, 0,
//                             1.0f, 0.0f, 0.0f, 0.0f,
//                             0.0f, 0.0f, 1.0f, 1.0f,
//                             1);
//    modelPoints[1].SetVertex(CVector4(1.0f, 0.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
//                             0, 0, 0, 0,
//                             1.0f, 0.0f, 0.0f, 0.0f,
//                             0.0f, 0.0f, 1.0f, 1.0f,
//                             1);
//    modelPoints[2].SetVertex(CVector4(1.0f, 3.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
//                             0, 1, 0, 0,
//                             0.50f, 0.50f, 0.0f, 0.0f,
//                             0.0f, 0.0f, 1.0f, 1.0f,
//                             2);
//    modelPoints[3].SetVertex(CVector4(-1.0f, 3.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
//                             0, 1, 0, 0,
//                             0.50f, 0.50f, 0.0f, 0.0f,
//                             0.0f, 0.0f, 1.0f, 1.0f,
//                             2);
//     modelPoints[4].SetVertex(CVector4(-1.0f, 3.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
//                             0, 1, 0, 0,
//                              0.50f, 0.50f, 0.0f, 0.0f,
//                              0.0f, 1.0f, 0.0f, 1.0f,
//                              2);
//    modelPoints[5].SetVertex(CVector4(1.0f, 3.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
//                             0, 1, 0, 0,
//                             0.50f, 0.50f, 0.0f, 0.0f,
//                             0.0f, 1.0f, 0.0f, 1.0f,
//                             2);
//    modelPoints[6].SetVertex(CVector4(1.0f, 6.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
//                             0, 1, 0, 0,
//                             0.35f, 0.65f, 0.0f, 0.0f,
//                             0.0f, 1.0f, 0.0f, 1.0f,
//                             2);
//    modelPoints[7].SetVertex(CVector4(-1.0f, 6.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
//                             0, 1, 0, 0,
//                             0.35f, 0.65f, 0.0f, 0.0f,
//                             0.0f, 1.0f, 0.0f, 1.0f,
//                             2);
//    modelPoints[8].SetVertex(CVector4(-1.0f, 6.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
//                             0, 1, 0, 0,
//                             0.35f, 0.65f, 0.0f, 0.0f,
//                             1.0f, 0.0f, 0.0f, 1.0f,
//                             2);
//    modelPoints[9].SetVertex(CVector4(1.0f, 6.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
//                             0, 1, 0, 0,
//                             0.35f, 0.65f, 0.0f, 0.0f,
//                             1.0f, 0.0f, 0.0f, 1.0f,
//                             2);
//    modelPoints[10].SetVertex(CVector4(1.0f, 9.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
//                              1, 0, 0, 0,
//                              1.0f, 0.0f, 0.0f, 0.0f,
//                              1.0f, 0.0f, 0.0f, 1.0f,
//                              1);
//    modelPoints[11].SetVertex(CVector4(-1.0f, 9.0f, 0.0f), CVector4(0.0f, 0.0f, 1.0),
//                              1, 0, 0, 0,
//                              1.0f, 0.0f, 0.0f, 0.0f,
//                              1.0, 0.0f, 0.0f, 1.0f,
//                              1);
//
//}
//
//
//GLint xRotation = 0;
//GLint yRotation = 0;
//float xp = 0;
//float yp = 0;
//int oldx = 0;
//int oldy = 0;
//void draw_ball() {
//    glPushMatrix();
//    glColor3f(0.0, 0.7, 0.7);
////    glTranslatef(0, bones[0].length , 0);
//    glTranslatef(xp, yp , 0);
//    glutWireSphere(0.5, 200, 500);
//    glPopMatrix();
//
//}
//void draw_move(void) {
//    if ((xp*xp + yp * yp )>= (l1+l2)*(l1+l2)) {
//        printf("Wrong\n");
//        return;
//    }
//
//    if (xp > 0) {
//        yp = -1 * yp;
//    }
//
//    float summ = yp * yp + xp * xp;
//    float alph3 = acos((summ - l1 * l1 - l2 * l2) / (-2 * l1*l2));
//    alph3 = alph3 * 180 / 3.14;
//    angle2 = 180 - alph3;
//
//
//    float alph1 = acos((l1*l1 - l2 * l2 - summ) / (-2 * l1*sqrt(summ)));
//    float alph2 = atan(yp / xp);
//    alph1 = alph1 * 180 / 3.14;
//    alph2 = alph2 * 180 / 3.14;
//    angle1 = 90 - alph1 + alph2;
//
//    if (xp >= 0) {
//        angle1 = 360 - angle1;
//        angle2 = 360 - angle2;
//        yp = -1 * yp;
//    }
//
////    bool elbow_up = true;
////    bool elbow_down = false;
////    float s2 = 0;
////    float c2 = (summ -l1 * l1 - l2 * l2)/2 * l1*l2;
////    if (elbow_up) {
////        s2 = -sqrt(1-c2*c2);
////    }else if (elbow_down){
////        s2 = sqrt(1-c2*c2);
////    }
////    angle2 = atan(s2/ c2)* 180 / 3.14;
////    angle2 = 180 - angle2;
////    angle1 = (atan(yp/ xp) - atan(l2*s2/ l1+l2*c2))* 180 / 3.14;
//    printf("%f, %f \n", xp, yp);
//    printf("%f,%f \n", angle1, angle2);
//}
//
///** 骨骼更新，即计算出每个骨骼的新变换矩阵，用displayBones数组保存 */
//void updateBones()
//{
//    /** 用于保存旋转和平移矩阵 */
//    CMatrix4x4 transpose, rot,rot2, rotTemp1, rotTemp2, tempRelative;
//
//    /** 循环更新骨骼 */
//    for(int i = 0; i < MAX_BONES; i++)
//    {
//        ///检查是否是根骨骼
//        if(bones[i].parent == -1)
//        {
//            /** 设置变换矩阵 */
////            printf("%f,%f,%f",trans.x,trans.y,trans.z);
//            rot.Rotate(angle1, 0,0,1);
//            bones[i].relative.Translate(trans.x,trans.y, trans.z);
//            displayBones[i] = bones[i].relative *(rot);
//            bones[i].relative = bones[i].relative * rot;
//            bones[i].absolute = bones[i].relative;
//
//            /** 赋值，为了显示骨骼 */
//            displayBones[i] = bones[i].relative;
//        }
//        else if(bones[i].parent == 1)
//        {
//            bones[i].relative.Clear();
////            printf("%d,%d,%d,%d,%d,%d",xRotation,yRotation,oldx,oldy,xp,yp);
//            /** 移动该骨骼到父结点骨骼(绕父骨骼转) */
//            bones[i].relative.Translate((0)/30, (0)/30+bones[bones[i].parent].length * i, 0);
//
//            /** 根据鼠标旋转 */
//            rotTemp1.Rotate(xRotation, 0, 1, 0);
//            rotTemp2.Rotate(angle2, 0, 0, 1);
//
//            /** 保存相对变换矩阵，并反转 */
//            tempRelative = bones[i].relative;
//            tempRelative.inverseTranslate();
//
//            /** 保存变换，为了显示骨骼 */
//            displayBones[i] = bones[bones[i].parent].absolute * bones[i].relative;
//
//            /** 计算相对变换矩阵 */
//            bones[i].relative = bones[i].relative *tempRelative;
//
//            /** 计算绝对变换矩阵 */
//            bones[i].absolute = bones[bones[i].parent].absolute * bones[i].relative;
//        }
//        else if(bones[i].parent == 0){
//            bones[i].relative.Clear();
//            bones[i].relative.Translate((0)/30, (0)/30+bones[bones[i].parent].length*i, 0);
//            rotTemp2.Rotate(angle2, 0, 0, 1);
//            displayBones[i] = bones[bones[i].parent].absolute * bones[i].relative* (rotTemp2);
//            bones[i].relative = bones[i].relative * (rotTemp2) * tempRelative;
//            bones[i].absolute = bones[bones[i].parent].absolute * bones[i].relative;
//        }
//        else {
//            bones[i].relative.Clear();
//            bones[i].relative.Translate((0)/30, (0)/30+bones[bones[i].parent].length, 0);
//            displayBones[i] = bones[bones[i].parent].absolute * bones[i].relative;
//            bones[i].absolute = bones[bones[i].parent].absolute * bones[i].relative;
//        }
//    }
//}
//void keyboard(unsigned char key, int x, int y) {
//    switch (key) {
//        case 'z':
//                draw_move();
//                updateBones();
//                glutPostRedisplay();
//                break;
//    }
//}
//void display(void)
//{
//    /** 用户自定义的绘制过程 */
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//    glLoadIdentity();
////    glTranslatef(0.0f, 1.0f, -25.0f);
//    gluLookAt (0.0, 1.0, 25.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//    glRotatef(25.0, 1.0, 0.0, 0.0);
//    glPushMatrix();
//    glTranslatef(0, -1, -3);
//    glScaled(2.0, 3, 2);
//    glutSolidCube(2);
//    glPopMatrix();
//    glRotatef(angle1, 0, 0, 1);
//    glColor3f(0.0, 0.5, 0.2);
//    glTranslatef(0, 1, 0);
//    glutSolidCube(1);
//    glColor3f(0.5, 0.2, 0.3);
//    glTranslatef(0, 1, 0);
//    glRotatef(angle2, 0, 0, 1);
//    glutWireSphere(1, 200, 500);
//    glColor3f(0.4, 0.8, 0.3);
//    glTranslatef(0, 3, 0);
//    glScaled(0.5, 3, 1);
//
//    glutSolidCube(2);
//
//    draw_ball();
//
//    glPopMatrix();
//
//    /** 更新骨骼列表 */
//    updateBones();
//
//    CMatrix4x4 mat;
//
//    /** 渲染网格中的顶点，即绘制皮肤 */
//    for(int j = 0; j < MAX_MESHES; j++)
//    {
//        glBegin(GL_QUADS);
//
//        for(int i = 0; i < MAX_MESH_POINTS; i++)
//        {
//            ///获得顶点指针
//            CBoneVertex *thisVertex = &modelPoints[i + j * MAX_MESH_POINTS];
//
//            ///根据权值计算顶点
//            CVector4 pos = CVector4(0.0, 0.0, 0.0, 0.0);
//            CVector4 normal = CVector4(0.0, 0.0, 0.0);
//
//            for(int i2 = 0; i2 < thisVertex->numBones; i2++)
//            {
//                mat = bones[thisVertex->boneIndex[i2]].absolute;
//
//                ///加权骨骼对顶点位置和法线的影响
//                pos += (mat.VectorMatrixMultiply(thisVertex->pos) * thisVertex->weights[i2]);
//                normal += (mat.VectorMatrixMultiply3x3(thisVertex->normal) *
//                           thisVertex->weights[i2]);
//            }
//
//            ///渲染该顶点
//            glColor4f(thisVertex->r, thisVertex->g, thisVertex->b, thisVertex->a);
//            glNormal3f(normal.x, normal.y, normal.z);
//            glVertex3f(pos.x, pos.y, pos.z);
//        }
//
//        glEnd();
//    }
////    draw_ball();
//    //绘制骨骼
//    for(int i = 0; i < MAX_BONES; i++)
//    {
//        glPushMatrix();
//
//        glMultMatrixf(displayBones[i].matrix);
////        glScalef(0.5,0.5,0.5);
//        glColor3f(1.0f, 1.0f, 1.0f);
//
//        if (i == 2) {
//            glBegin(GL_LINES);
//
//            glVertex3f(-0.4f, 0.0f, -0.4f);
//            glVertex3f(0.4f, 0.0f, -0.4f);
//            glVertex3f(0.4f, 0.0f, -0.4f);
//            glVertex3f(0.4f, 0.0f, 0.4f);
//            glVertex3f(0.4f, 0.0f, 0.4f);
//            glVertex3f(-0.4f, 0.0f, 0.4f);
//            glVertex3f(-0.4f, 0.0f, 0.4f);
//            glVertex3f(-0.4f, 0.0f, -0.4f);
//
//            glVertex3f(-0.4f, 0.0f, -0.4f);
//            glVertex3f(0.0f, bones[i].length, 0.0f);
//            glVertex3f(0.4f, 0.0f, -0.4f);
//            glVertex3f(0.0f, bones[i].length, 0.0f);
//            glVertex3f(0.4f, 0.0f, 0.4f);
//            glVertex3f(0.0f, bones[i].length, 0.0f);
//            glVertex3f(-0.4f, 0.0f, 0.4f);
//            glVertex3f(0.0f, bones[i].length, 0.0f);
//
//            glEnd();
//
//            glPopMatrix();
//        }else if (i == 0){
//
//        glBegin(GL_LINES);
//
//
//        ///绘制线段
//        glVertex3f(-0.4f, 0.0f, -0.4f);
//        glVertex3f(0.4f, 0.0f, -0.4f);
//        glVertex3f(0.4f, 0.0f, -0.4f);
//        glVertex3f(0.4f, 0.0f, 0.4f);
//        glVertex3f(0.4f, 0.0f, 0.4f);
//        glVertex3f(-0.4f, 0.0f, 0.4f);
//        glVertex3f(-0.4f, 0.0f, 0.4f);
//        glVertex3f(-0.4f, 0.0f, -0.4f);
//
//        glVertex3f(-0.4f, 0.0f, -0.4f);
//        glVertex3f(0.0f, bones[i].length, 0.0f);
//        glVertex3f(0.4f, 0.0f, -0.4f);
//        glVertex3f(0.0f, bones[i].length, 0.0f);
//        glVertex3f(0.4f, 0.0f, 0.4f);
//        glVertex3f(0.0f, bones[i].length, 0.0f);
//        glVertex3f(-0.4f, 0.0f, 0.4f);
//        glVertex3f(0.0f, bones[i].length, 0.0f);
//
//        glEnd();
//
//        glPopMatrix();
//        }else if (i == 1) {
//            glBegin(GL_LINES);
//            draw_ball();
//            glVertex3f(-0.4f, 0.0f, -0.4f);
//            glVertex3f(0.4f, 0.0f, -0.4f);
//            glVertex3f(0.4f, 0.0f, -0.4f);
//            glVertex3f(0.4f, 0.0f, 0.4f);
//            glVertex3f(0.4f, 0.0f, 0.4f);
//            glVertex3f(-0.4f, 0.0f, 0.4f);
//            glVertex3f(-0.4f, 0.0f, 0.4f);
//            glVertex3f(-0.4f, 0.0f, -0.4f);
//
//            glVertex3f(-0.4f, 0.0f, -0.4f);
//            glVertex3f(0.0f, bones[i].length, 0.0f);
//            glVertex3f(0.4f, 0.0f, -0.4f);
//            glVertex3f(0.0f, bones[i].length, 0.0f);
//            glVertex3f(0.4f, 0.0f, 0.4f);
//            glVertex3f(0.0f, bones[i].length, 0.0f);
//            glVertex3f(-0.4f, 0.0f, 0.4f);
//            glVertex3f(0.0f, bones[i].length, 0.0f);
//
//            glEnd();
//
//            glPopMatrix();
//        }else{
//            glBegin(GL_LINES);
//            draw_ball();
//            glVertex3f(-0.4f, 0.0f, -0.4f);
//            glVertex3f(0.4f, 0.0f, -0.4f);
//            glVertex3f(0.4f, 0.0f, -0.4f);
//            glVertex3f(0.4f, 0.0f, 0.4f);
//            glVertex3f(0.4f, 0.0f, 0.4f);
//            glVertex3f(-0.4f, 0.0f, 0.4f);
//            glVertex3f(-0.4f, 0.0f, 0.4f);
//            glVertex3f(-0.4f, 0.0f, -0.4f);
//
//            glVertex3f(-0.4f, 0.0f, -0.4f);
//            glVertex3f(0.0f, bones[i].length, 0.0f);
//            glVertex3f(0.4f, 0.0f, -0.4f);
//            glVertex3f(0.0f, bones[i].length, 0.0f);
//            glVertex3f(0.4f, 0.0f, 0.4f);
//            glVertex3f(0.0f, bones[i].length, 0.0f);
//            glVertex3f(-0.4f, 0.0f, 0.4f);
//            glVertex3f(0.0f, bones[i].length, 0.0f);
//
//            glEnd();
//
//            glPopMatrix();
//        }
//    }
//
//    /** 强制执行所有的OpenGL命令 */
//    glFlush();
//}
//
//
//void ChangeSize(int width, int height)
//{
//    glViewport(0, 0, width, height);                                    /**< 重新设置视口 */
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1700.0f);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//}
//
//
//
//void motion(int x, int y)
//{
//    xRotation = xRotation - (x - oldx);
//    yRotation = yRotation - (y - oldy);
//
//    xOffset = x -400;
//    yOffset = 300 - y;
//    xp = xOffset*4.5/130;
//    yp = yOffset*4.5/130;
//    locx = xOffset/30;
//    locy = yOffset/30+bones[0].length*2;
//    if ((xp*xp+yp*yp)<=(l1+l2)*(l1+l2)) {
//        float theta2_cos,omega_cos;
//        theta2_cos = (xp*xp + yp*yp - l1*l1 - l2*l2)/2*l1*l2;
//        theta2 = acos(theta2_cos);
//        theta2 = theta2*180/PI;
//
//        betla = atan2(yp, xp);
//        omega_cos = (xp*xp + yp*yp + l1*l1 - l2*l2)/2*l1*sqrt(xp*xp + yp*yp);
//        omega = acos(omega_cos);
//        omega = omega*180/PI;
//
//        if (theta2 > 0) {
//            theta1 = betla-omega;
//        }else{
//            theta1 = betla+omega;
//        }
//
////        printf("%.3f",l1*l1+l2*l2);
//    }
//    oldx = x;
//    oldy = y;
//
//    glutPostRedisplay();
//}
//
//void processMouse(int button, int state, int x, int y) {
//    if (button == GLUT_LEFT_BUTTON) {
//        xOffset = x -400;
//        yOffset = 300 - y;
//        xp = xOffset*4.5/130;
//        yp = yOffset*4.5/130;
//    }
//    printf("%.3f,%.3f",xp,yp);
//}
//int main(int argc, char** argv)
//{
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB );
//    glutInitWindowSize (800, 600);
//    glutInitWindowPosition (100, 100);
//    glutCreateWindow("骨骼动画");
//    init();
//    glutReshapeFunc(ChangeSize);
//    glutDisplayFunc(display);
//    glutMouseFunc(processMouse);
//    glutMotionFunc(motion);
//    glutKeyboardFunc(keyboard);
//    glutMainLoop();
//    return 0;
//}
////
//#define MAX_BONES                2   /**骨骼数*/
//#define MAX_MESHES              3   /**网格数，即基本图元数(纹理贴图后的皮肤)*/
//#define MAX_MESH_POINTS 4 /**一个网格顶点数，即四边形*/
//
//float g_quadVertices[] ={
//    //     r,   g,   b,    a,    x,   y,  z, weights[2], matrixIndices[2],numBones
//            1.0f,1.0f,0.0f,1.0f, -1.0f,0.0f,0.0f, 1.0f,0.0f, 0,0, 1, // 蓝色
//            1.0f,1.0f,0.0f,1.0f, 1.0f, 0.0f,0.0f, 1.0f,0.0f, 0,0, 1,
//            1.0f,1.0f,0.0f,1.0f, 1.0f, 2.0f,0.0f, 0.5f,0.5f, 0,1, 2,
//            1.0f,1.0f,0.0f,1.0f, -1.0f,2.0f,0.0f, 0.5f,0.5f, 0,1, 2,
//
//            0.0f,1.0f,0.0f,1.0f, -1.0f,2.0f,0.0f, 0.5f,0.5f, 0,1, 2, // 绿色
//            0.0f,1.0f,0.0f,1.0f, 1.0f, 2.0f,0.0f, 0.5f,0.5f, 0,1, 2,
//            0.0f,1.0f,0.0f,1.0f, 1.0f, 4.0f,0.0f, 0.5f,0.5f, 0,1, 2,
//            0.0f,1.0f,0.0f,1.0f, -1.0f,4.0f,0.0f, 0.5f,0.5f, 0,1, 2,
//
//            0.0f,0.0f,1.0f,1.0f, -1.0f,4.0f,0.0f, 0.5f,0.5f, 0,1, 2, // 黄色
//            0.0f,0.0f,1.0f,1.0f, 1.0f, 4.0f,0.0f, 0.5f,0.5f, 0,1, 2,
//            0.0f,0.0f,1.0f,1.0f, 1.0f, 6.0f,0.0f, 1.0f,0.0f, 1,0, 1,
//            0.0f,0.0f,1.0f,1.0f, -1.0f,6.0f,0.0f, 1.0f,0.0f, 1,0, 1
//};
//
//vec4         trans;                       /**< 用于平移骨骼模型 */
//CBone             bones[MAX_BONES];            /**< 保存骨骼结构 */
//mat4     displayBones[MAX_BONES];     /**< 用于绘制骨骼 */
//CBoneVertex   modelPoints[MAX_MESHES * MAX_MESH_POINTS]; /**< 模型顶点数据，即皮肤顶点 */
//
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//float arBone[] =
//{
//0.0f, 0.0f, 0.0f,
//-0.2f, 0.2f,-0.2f,
//0.2f, 0.2f,-0.2f,
//0.0f, 3.0f, 0.0f,
//-0.2f, 0.2f,-0.2f,
//-0.2f, 0.2f, 0.2f,
//0.0f, 0.0f, 0.0f,
//0.2f, 0.2f,-0.2f,
//0.2f, 0.2f, 0.2f,
//0.0f, 0.0f, 0.0f,
//-0.2f, 0.2f, 0.2f,
//0.0f, 3.0f, 0.0f,
//0.2f, 0.2f, 0.2f,
//-0.2f, 0.2f, 0.2f,
//};
//
//
//mat4 g_boneMatrix[2];
//mat4 g_matrixToRenderBone[2];
//
//GLint xRotation = 0;
//GLint yRotation = 0;
//
//float g_fSpinX_R = 0.0f;
//float g_fSpinY_R = 0.0f;
//Camera camera(vec3(0,0,3.0f),radians(15.0f),radians(180.0f),vec3(0,1.0f,0));
//
//float lastX;
//float lastY;
//float Angle = 0;
//void update(){
//    float lastTime = 0;
//    float currTime = (float)glfwGetTime();
//    float  delta = (currTime - lastTime) * 0.001f;
//    if (delta > 0.03f){
//        delta = 0.03f;
//        lastTime = currTime;
//        Angle += 0.2f;
//    }
//
//}
//bool firstMouse = true;
//
//unsigned int loadTexture(char const * path)
//{
//    unsigned int textureID;
//    glGenTextures(1, &textureID);
//
//    int width, height, nrComponents;
//    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
//    if (data)
//    {
//        GLenum format;
//        if (nrComponents == 1)
//            format = GL_RED;
//        else if (nrComponents == 3)
//            format = GL_RGB;
//        else if (nrComponents == 4)
//            format = GL_RGBA;
//
//        glBindTexture(GL_TEXTURE_2D, textureID);
//        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        stbi_image_free(data);
//    }
//    else
//    {
//        std::cout << "Texture failed to load at path: " << path << std::endl;
//        stbi_image_free(data);
//    }
//
//    return textureID;
//}
//
//void processInput(GLFWwindow *window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//        camera.speedZ = 1.0f;
//    }
//    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//        camera.speedZ = -1.0f;
//    }
//    else{
//        camera.speedZ = 0;
//    }
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//        camera.speedX = 1.0f;
//    }
//    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//        camera.speedX = -1.0f;
//    }
//    else{
//        camera.speedX = 0;
//    }
//    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
//        camera.speedY = -1.0f;
//    }
//    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
//        camera.speedY = 1.0f;
//    }
//    else{
//        camera.speedY = 0;
//    }
//}
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float deltaX,deltaY;
//    deltaX = xpos - lastX;
//    deltaY = ypos - lastY;
//
//    lastX = xpos;
//    lastY = ypos;
//
//    camera.ProcessMouseMovement(deltaX, deltaY);
//}
//
//unsigned int loadCubemap(std::vector<std::string> faces)
//{
//    unsigned int textureID;
//    glGenTextures(1, &textureID);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
//
//    int width, height, nrChannels;
//    for (unsigned int i = 0; i < faces.size(); i++)
//    {
//        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
//        if (data)
//        {
//            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//            stbi_image_free(data);
//        }
//        else
//        {
//            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
//            stbi_image_free(data);
//        }
//    }
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//
//    return textureID;
//}
//unsigned int LoadImageToGPU(const char* filename,GLint internalFormat, GLenum format,int textureSlot){
//    unsigned int TexBuffer;
//    glGenTextures(1, &TexBuffer); //产生buffer
//    glActiveTexture(GL_TEXTURE0 + textureSlot);
//    glBindTexture(GL_TEXTURE_2D, TexBuffer);
//
//    int width,height,nrChannel;
//    stbi_set_flip_vertically_on_load(true);
//    unsigned char *data = stbi_load(filename,&width,&height,&nrChannel,0);
//    if(data){
//        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    } //第几登记mipmap,不给边缘
//    else{
//        printf("load image failed.");
//    }
//    stbi_image_free(data);
//    return TexBuffer;
//}
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//int main(int argc, const char * argv[]) {
//    std::string exePath = argv[0];
//    //Open window
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lab4", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate(); //终止
//        return -1;
//    }
//    glfwMakeContextCurrent(window); //绑定使用
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//取消鼠标
//    glfwSetCursorPosCallback(window, mouse_callback);
//
////    glEnable(GL_CULL_FACE);
////    glEnable(GL_BLEND);
////    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
////    glCullFace(GL_BACK);
//
//    //Init GLEW
//    glewExperimental = true;
//    if (glewInit() != GLEW_OK) {
//        printf("Init GLEW fault");
//        glfwTerminate();
//        return -1;
//    }
//
//    glViewport(0, 0, 800, 600); //设置窗口大小起始坐标终止坐标
//    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
////    stbi_set_flip_vertically_on_load(true);
//    glShadeModel(GL_SMOOTH);
//    glEnable(GL_DEPTH_TEST);
//    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//
//    Shader* skyShader = new Shader("/Users/buxin/Documents/real-time-rendering/rendering/Lab3/skyBoxVertex.vert","/Users/buxin/Documents/real-time-rendering/rendering/Lab3/skyBoxFragment.frag");
////    Shader* normalMapShader = new Shader("/Users/buxin/Documents/real-time-rendering/rendering/Lab3/vertexSource.vert","/Users/buxin/Documents/real-time-rendering/rendering/Lab3/fragementSource.frag");
//    Shader* normalMapShader = new Shader("/Users/buxin/Documents/real-time-rendering/rendering/Lab3/normalVertex.vert","/Users/buxin/Documents/real-time-rendering/rendering/Lab3/normalFrag.frag");
////    unsigned int diffuseMap = loadTexture("/Users/buxin/Desktop/CS7GV6 2020/triangle/model/backpack/diffuse.jpg");
////    unsigned int normalMap  = loadTexture("/Users/buxin/Desktop/CS7GV6 2020/triangle/model/backpack/normal.png");
////    unsigned int diffuseMap = loadTexture("/Users/buxin/Documents/real-time-rendering/rendering/Lab3/brickwall.jpg");
////    unsigned int normalMap  = loadTexture("/Users/buxin/Documents/real-time-rendering/rendering/Lab3/brickwall_normal.jpg");
////    Material* myMaterial = new Material(normalMapShader,
////                                        LoadImageToGPU("/Users/buxin/Desktop/CS7GV6 2020/triangle/model/backpack/diffuse.jpg", GL_RGBA, GL_RGBA, Shader::DIFFUSE),
////                                        LoadImageToGPU("/Users/buxin/Desktop/CS7GV6 2020/triangle/model/backpack/specular.jpg", GL_RGBA, GL_RGBA, Shader::SPECULAR),
////                                        LoadImageToGPU("/Users/buxin/Desktop/CS7GV6 2020/triangle/model/backpack/normal.png", GL_RGBA, GL_RGBA, Shader::NORMAL),
////                                        vec3 (1.0f,1.0f,1.0f),
////                                        32.0f);
//    Mesh m_mesh;
//    m_mesh.LoadMesh("/Users/buxin/Downloads/ogldev-master/Content/boblampclean.md5mesh");
//
//    mat4 modelMat = mat4(1.0f);
//    mat4 viewMat = mat4(1.0f);
//    mat4 view = mat4(1.0f);
//    mat4 projMat = perspective(radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
//
//    /** 构造骨骼 */
//        bones[0].SetBone(-1, 4.5f);/**根关节(骨骼索引与长度)*/
//        bones[1].SetBone(0, 4.5f);/**子关节*/
//
//        /** 绑定到骨骼上的皮肤顶点数据 */
//        modelPoints[0].SetVertex( vec4(-1.0f, 0.0f, 0.0f, 1.0),  vec4(0.0f, 0.0f, 1.0, 1.0),
//                                 0, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1);
//        modelPoints[1].SetVertex( vec4(1.0f, 0.0f, 0.0f, 1.0),  vec4(0.0f, 0.0f, 1.0, 1.0),
//                                 0, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1);
//        modelPoints[2].SetVertex( vec4(1.0f, 3.0f, 0.0f, 1.0),  vec4(0.0f, 0.0f, 1.0, 1.0),
//                                 0, 1, 0, 0, 0.50f, 0.50f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 2);
//        modelPoints[3].SetVertex( vec4(-1.0f, 3.0f, 0.0f, 1.0),  vec4(0.0f, 0.0f, 1.0, 1.0),
//                                 0, 1, 0, 0, 0.50f, 0.50f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 2);
//
//        modelPoints[4].SetVertex( vec4(-1.0f, 3.0f, 0.0f, 1.0),  vec4(0.0f, 0.0f, 1.0, 1.0),
//                                 0, 1, 0, 0, 0.50f, 0.50f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 2);
//        modelPoints[5].SetVertex( vec4(1.0f, 3.0f, 0.0f, 1.0),  vec4(0.0f, 0.0f, 1.0, 1.0),
//                                 0, 1, 0, 0, 0.50f, 0.50f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 2);
//        modelPoints[6].SetVertex( vec4(1.0f, 6.0f, 0.0f, 1.0),  vec4(0.0f, 0.0f, 1.0, 1.0),
//                                 0, 1, 0, 0, 0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 2);
//        modelPoints[7].SetVertex( vec4(-1.0f, 6.0f, 0.0f, 1.0),  vec4(0.0f, 0.0f, 1.0, 1.0),
//                                 0, 1, 0, 0, 0.35f, 0.65f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 2);
//
//        modelPoints[8].SetVertex( vec4(-1.0f, 6.0f, 0.0f, 1.0),  vec4(0.0f, 0.0f, 1.0, 1.0),
//                                 0, 1, 0, 0, 0.35f, 0.65f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 2);
//        modelPoints[9].SetVertex( vec4(1.0f, 6.0f, 0.0f, 1.0),  vec4(0.0f, 0.0f, 1.0, 1.0),
//                                 0, 1, 0, 0, 0.35f, 0.65f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 2);
//        modelPoints[10].SetVertex( vec4(1.0f, 9.0f, 0.0f, 1.0),  vec4(0.0f, 0.0f, 1.0, 1.0),
//                                  1, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1);
//        modelPoints[11].SetVertex( vec4(-1.0f, 9.0f, 0.0f, 1.0),  vec4(0.0f, 0.0f, 1.0, 1.0),
//                                  1, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f, 1.0, 0.0f, 0.0f, 1.0f, 1);
//
//
//    // cube VAO
//    unsigned int cubeVAO, cubeVBO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &cubeVBO);
//    glBindVertexArray(cubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(g_quadVertices), &g_quadVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(4 * sizeof(float)));
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(7 * sizeof(float)));
//    glEnableVertexAttribArray(3);
//    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(9 * sizeof(float)));
//    glEnableVertexAttribArray(4);
//    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(11 * sizeof(float)));
//
//    while (!glfwWindowShouldClose(window)) {
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//        //Process input
//        processInput(window); //下一帧输入
//        //Clear screen
//        glClearColor(0.8f,0.8f,0.8f,1.0f); //r,g,b,
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glEnable(GL_DEPTH_TEST);
//
//        glMatrixMode( GL_MODELVIEW );
//        glLoadIdentity();
//        glTranslatef( 0.0f, 0.0f, -15 );
//
//        glEnableClientState(GL_VERTEX_ARRAY);
//        glEnableClientState(GL_COLOR_ARRAY);
//
//
//        g_boneMatrix[0] = mat4(1.0f);
//        g_matrixToRenderBone[0]= mat4(1.0f);
//
//        mat4 rotationMatrixY;
//        mat4 rotationMatrixZ;
//        mat4 boneRotationMatrix;
//
//
//        g_boneMatrix[1]= mat4(1.0f);
//        g_matrixToRenderBone[1]= mat4(1.0f);
//
//        mat4 offsetMatrix_toBoneEnd;
//        mat4 offsetMatrix_backFromBoneEnd;
//
//        offsetMatrix_toBoneEnd= translate(offsetMatrix_toBoneEnd, vec3(0,3.0f,0));
//        offsetMatrix_backFromBoneEnd=translate(offsetMatrix_backFromBoneEnd, vec3(0,-3.0f,0));
//
//        rotationMatrixY=rotate(rotationMatrixY,radians(g_fSpinY_R), vec3(0,1.0f,0));
//        rotationMatrixZ=rotate(rotationMatrixY,radians(-g_fSpinX_R), vec3(0,0.0f,1.0f));
//        boneRotationMatrix = rotationMatrixY * rotationMatrixZ;
//
//        g_boneMatrix[1] = g_boneMatrix[0] * offsetMatrix_toBoneEnd * boneRotationMatrix;
//        g_matrixToRenderBone[1] = g_boneMatrix[1];
//        g_boneMatrix[1] = g_boneMatrix[1] * offsetMatrix_backFromBoneEnd;
//
////        Vertex calQuadVertices[12];
////        memcpy(calQuadVertices,g_quadVertices,sizeof(g_quadVertices));
////        for (int i = 0 ;i < 12 ; ++ i )
////        {
////        vec3 vec(0,0,0);
////        vec3 vecSrc(g_quadVertices[i].x,g_quadVertices[i].y,g_quadVertices[i].z);
////        for (int x = 0 ; x < calQuadVertices[i].numBones ; ++ x)
////        {
////        //! 计算位置
////        vector3f temp = vecSrc* g_boneMatrix[g_quadVertices[i].matrixIndices[x]];
////        //! 计算权重位置
////        vec += temp * g_quadVertices[i].weights[x];
////        }
////        calQuadVertices[i].x = vec.x;
////        calQuadVertices[i].y = vec.y;
////        calQuadVertices[i].z = vec.z;
////        }
////        glColorPointer(4,GL_FLOAT,sizeof(Vertex),calQuadVertices);
////        glVertexPointer(3,GL_FLOAT,sizeof(Vertex),((float*)calQuadVertices) + 4);
//        for (int i = 0 ;i < 3 ; ++ i )
//        {
//            glDrawArrays(GL_LINE_LOOP,i * 4,4);
//        }
//        glDisableClientState(GL_COLOR_ARRAY);
//
//        viewMat = glm::mat4(glm::mat3(camera.GetfirstViewMatrix()));
//        view = camera.GetfirstViewMatrix();
//        modelMat = translate(mat4(1.0f), vec3(0.0f,-1.2f,-3.0f));
//        modelMat = rotate(modelMat, radians(-90.0f), vec3(1,0,0));
////        modelMat = glm::rotate(modelMat, glm::radians((float)glfwGetTime() * -10.0f), glm::normalize(glm::vec3(0.0, 1.0, 0.0)));
//        modelMat = scale(modelMat, vec3(0.03,0.03,0.03));
//        normalMapShader -> use();
//        vector<Matrix4f> Transforms;
//
////        m_mesh.BoneTransform(RunningTime, Transforms);
////        Matrix4f m = {
////            m[0][0] = 1.0f; m[0][1] = 1.0f; m[0][2] = 1.0f; m[0][3] = 1;
////            m[1][0] = 1.0f; m[1][1] = 1.0f; m[1][2] = 1.0f; m[1][3] = 1;
////            m[2][0] = 1.0f; m[2][1] = 1.0f; m[2][2] = 1.0f; m[2][3] = 1;
////            m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
////        }
//
//
//        glUniformMatrix4fv(glGetUniformLocation(normalMapShader->ID,"model"),1,GL_FALSE,value_ptr(modelMat));
//        glUniformMatrix4fv(glGetUniformLocation(normalMapShader->ID,"view"),1,GL_FALSE,value_ptr(view));
//        glUniformMatrix4fv(glGetUniformLocation(normalMapShader->ID,"projection"),1,GL_FALSE,value_ptr(projMat));
//        glUniform3f(glGetUniformLocation(normalMapShader->ID,"viewPos"),camera.Position.x,camera.Position.y,camera.Position.z);
//
//        m_mesh.Render();
//
////        myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
////        myMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
////        myMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
////        myMaterial->shader->SetUniform1i("material.normal", Shader::NORMAL);
////        myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);
//
//        glUniform3f(glGetUniformLocation(normalMapShader->ID,"lightPos"),0.5f,0.0f, -2.0f);
////        glUniform1i(glGetUniformLocation(normalMapShader->ID,"diffuseMap"),0);
////        glUniform1i(glGetUniformLocation(normalMapShader->ID,"normalMap"),1);
//
////        glBindVertexArray(quadVAO);
////        glActiveTexture(GL_TEXTURE0);
////        glBindTexture(GL_TEXTURE_2D, diffuseMap);
////        glActiveTexture(GL_TEXTURE1);
////        glBindTexture(GL_TEXTURE_2D, normalMap);
////        glDrawArrays(GL_TRIANGLES, 0, 36);
////        glBindVertexArray(0);
//
////        model.Draw(myMaterial->shader);
//
//        // cubes
////        glBindVertexArray(cubeVAO);
////        glActiveTexture(GL_TEXTURE0);
////        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
////        glDrawArrays(GL_TRIANGLES, 0, 36);
////        glBindVertexArray(0);
//
//        glVertexPointer(3,GL_FLOAT,0,arBone);
//        glPushMatrix();
//        {
//        //! 绿色骨头
//        glMultMatrixf( g_matrixToRenderBone[0] );
//        glColor3f( 1.0f, 1.0f, 0.0 );
//        glDrawArrays(GL_LINE_STRIP,0,sizeof(arBone)/12);
//        }
//        glPopMatrix();
//
//        //Clean up,prepare for next render loop
//        glfwSwapBuffers(window); //切换前后buffer
//        glfwPollEvents();
//        camera.UpdateCameraPos();
//    }
//    //Exit Program
//    glfwTerminate();
//    return 0;
//}
//
