
#include "stdafx.h"
#include "OpenGL.h"
//////////////////////////////////////////////////////////////////////
extern HWND	hWnd;

const float pi = 3.1415926f;
GLUquadricObj* quadric=NULL;

//////////////////////////////////////////////////////////////////////
OpenGL::OpenGL()
{
	x_arc = 0;
	y_arc = 0;
	z_arc = 0;

}
OpenGL::~OpenGL()
{	CleanUp();
}
BOOL OpenGL::SetupPixelFormat(HDC hDC0)//��ⰲװOpenGL
{	int nPixelFormat;					  // ���ص��ʽ
	hDC=hDC0;
	PIXELFORMATDESCRIPTOR pfd = { 
	    sizeof(PIXELFORMATDESCRIPTOR),    // pfd�ṹ�Ĵ�С 
	    1,                                // �汾�� 
	    PFD_DRAW_TO_WINDOW |              // ֧���ڴ����л�ͼ 
	    PFD_SUPPORT_OPENGL |              // ֧�� OpenGL 
	    PFD_DOUBLEBUFFER,                 // ˫����ģʽ 
	    PFD_TYPE_RGBA,                    // RGBA ��ɫģʽ 
	    16,                               // 24 λ��ɫ��� 
	    0, 0, 0, 0, 0, 0,                 // ������ɫλ 
	    0,                                // û�з�͸���Ȼ��� 
	    0,                                // ������λλ 
	    0,                                // ���ۼӻ��� 
	    0, 0, 0, 0,                       // �����ۼ�λ 
	    16,                               // 32 λ��Ȼ���     
	    0,                                // ��ģ�建�� 
	    0,                                // �޸������� 
	    PFD_MAIN_PLANE,                   // ���� 
	    0,                                // ���� 
	    0, 0, 0                           // ���Բ�,�ɼ��Ժ������ģ 
	}; 
	if (!(nPixelFormat = ChoosePixelFormat(hDC, &pfd)))
		{ MessageBox(NULL,"û�ҵ����ʵ���ʾģʽ","Error",MB_OK|MB_ICONEXCLAMATION);
	      return FALSE;
		}
	SetPixelFormat(hDC,nPixelFormat,&pfd);//���õ�ǰ�豸�����ص��ʽ
	hRC = wglCreateContext(hDC);          //��ȡ��Ⱦ�������
	wglMakeCurrent(hDC, hRC);             //������Ⱦ�������
	return TRUE;
}

void OpenGL::init(int Width, int Height)
{	glViewport(0,0,Width,Height);			// ����OpenGL�ӿڴ�С��	
	glMatrixMode(GL_PROJECTION);			// ���õ�ǰ����ΪͶӰ����
	glLoadIdentity();						// ���õ�ǰָ���ľ���Ϊ��λ����
	int view_winsize= 60;
	glOrtho(-view_winsize, view_winsize, -view_winsize, view_winsize,-view_winsize,view_winsize); 
	glMatrixMode(GL_MODELVIEW);				// ���õ�ǰ����Ϊģ����ͼ����
	glLoadIdentity();						// ���õ�ǰָ���ľ���Ϊ��λ����
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_ambient[] = { 0.24725f, 0.1995f, 0.0745f, 1.0f };
	GLfloat mat_ambient_color[] = { 0.9f,0.9f,0.3f, 1.0f };
	GLfloat mat_diffuse[] = { 0.75164f, 0.60648f, 0.22648f, 1.0f };
	GLfloat mat_specular[] = { 0.628281f, 0.555802f, 0.366065f, 1.0f };
	GLfloat no_shininess[] = { 0.0f };
	GLfloat low_shininess[] = { 5.0f };
	GLfloat high_shininess[] = { 51.2f };
	GLfloat mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};


	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_mat);

	m_3ds=new CLoad3DS();

}

void OpenGL::Render()//OpenGLͼ�δ���
{	

	

	for(int i=1;i<14;i++)
	{
		m_3ds->show3ds(i,0,0,0,2);	
	}



}

void OpenGL::CleanUp()//���OpenGL
{
	 if(m_3ds!=NULL) delete m_3ds;
	 wglMakeCurrent(hDC, NULL);                       //���OpenGL
	 wglDeleteContext(hRC);                           //���OpenGL

}


int OpenGL::Init()
{return 0;}


void OpenGL::display()
{	
	glFlush();
	SwapBuffers(hDC);								 // �л�������
}

void OpenGL::draw2point(Vector3f vVector1, Vector3f vVector2)
{

	float Zoom = 200;

	//printf("before unproject: %f,%f,%f \n",vVector1.x,vVector1.y,vVector1.z);
	//printf("before unproject: %f,%f,%f \n",vVector2.x,vVector2.y,vVector2.z);
	//printf("after  unproject: %f,%f,%f \n\n",xx,yy,zz);
	

	//��Ҫ����float Խ������
	Vector3f *vt1 = new Vector3f(vVector1.x/Zoom,vVector1.y/Zoom,vVector1.z/Zoom);
	Vector3f *vt2 = new Vector3f(vVector2.x/Zoom,vVector2.y/Zoom,vVector2.z/Zoom);
	Vector3f vt4 = *vt2-*vt1;
	Vector3f *vty = new Vector3f(0,0,1);
	
	double arc12 = AngleBetweenVectors(*vty,vt4);
	double rarc12 = 180 + 180*arc12/pi;
	float len= Distance(*vt1,*vt2);
	Vector3f vt3 = Cross(*vty,vt4);

	glPushMatrix();	
	glTranslatef (vt1->x,vt1->y,vt1->z);
	glColor3f(1.0f,0.5f,0.7f); 
	auxSolidSphere(0.09);
	glTranslatef (vt4.x,vt4.y,vt4.z);
	auxSolidSphere(0.09);	
	glColor3f(1.0f,1.0f,0.7f);
	glRotatef ((float)rarc12,vt3.x,vt3.y,vt3.z);
	gluCylinder(quadric,0.06,0.06,len,35,35);
	glPopMatrix();

	delete vt1;
	delete vt2;
	delete vty;

}

void OpenGL::clear()
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);			 // ����ˢ�±���ɫ
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);// ˢ�±���
	glLoadIdentity();

	if(!quadric)
	{
		quadric=gluNewQuadric();
		gluQuadricNormals(quadric,GLU_SMOOTH);
		gluQuadricTexture(quadric,GL_TRUE);
	}

	//gluCylinder(quadric,0.06,0.06,0.9,35,35);
	glRotatef (15.0,1.0,1.0,0.0);
	glRotatef ((float)x_arc,1.0,0.0,0.0);
	glRotatef ((float)y_arc,0.0,1.0,0.0);
	glRotatef ((float)z_arc,0.0,0.0,1.0);


	glTranslatef(0,-40,0);
	
	draw_ground();
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	glColor3f(1.0f,0.5f,0.7f);
	//������
	glBegin(GL_LINE_LOOP); //
		glVertex3f( 0.0f, -50.0f,0.0f);
		glVertex3f(0.0f,  100.0f, 0.0f);
	glEnd();
	glColor3f(1.0f,1.0f,0.7f);
	glBegin(GL_LINE_LOOP); //
		glVertex3f( 0.0f, 00.0f,-100.0f);
		glVertex3f(0.0f,  0.0f, 100.0f);
	glEnd();

	glColor3f(0.1f,0.5f,0.7f);
	glBegin(GL_LINE_LOOP); //
		glVertex3f( -100.0f, 0.0f,0.0f);
		glVertex3f(100.0f,  0.0f, 0.0f);
	glEnd();

	glColor3f(0.9f,0.9f,0.3f);
}

//���Ǽ���ת��y������
int OpenGL::Correct_3D_Layout(Vector3f vVector1, Vector3f vVector2)
{
	Vector3f vt4 = vVector2-vVector1;
	Vector3f *vty = new Vector3f(0,1,0);	
	double arc12 = AngleBetweenVectors(*vty,vt4);
	double rarc12 = 180*arc12/pi;
	Vector3f vt3 = Cross(*vty,vt4);
	glRotatef ((float)rarc12,vt3.x,vt3.y,vt3.z);
	delete vty;
	return 0;
}

void OpenGL::draw_ground()
{
  glPushAttrib(GL_CURRENT_BIT);
  glEnable(GL_BLEND);
  glPushMatrix();
  glColor3f(0.5f, 0.7f, 1.0f);
  glTranslatef(0,0.0f,0);
  float size0=50;
  glBegin(GL_LINES);
	for (float x = -size0; x < size0;x+=size0/4)
		{glVertex3f(x, -1.5, -size0); glVertex3f(x, -1.5,  size0);}
	for (float z = -size0; z < size0;z+=size0/5)
		{glVertex3f(-size0, -1.5, z); glVertex3f( size0, -1.5, z);}
  glEnd();
  glPopMatrix();
  glDisable(GL_BLEND);
  glPopAttrib();

}

int OpenGL::Load3DS(int ID, char *filename)
{
	if(m_3ds!=NULL) m_3ds->Init(filename,ID);
	return 0;
}

int OpenGL::show3ds(int ID)
{
	m_3ds->show3ds(ID,0,0,0,2);	
	return 0;
}

int OpenGL::push()
{
	 glPushMatrix();
	 return 0;
}

int OpenGL::pop()
{
	glPopMatrix();
	return 0;
}


int OpenGL::rotate_bone(Vector3f vVector1, Vector3f vVector2, Vector3f vVectorOrgin)
{
	Vector3f vt1 =  Vector3f(vVector1.x,vVector1.y,vVector1.z);
	Vector3f vt2 =  Vector3f(vVector2.x,vVector2.y,vVector2.z);
	Vector3f vt4 = vt2-vt1;

	double arc12 = AngleBetweenVectors(vVectorOrgin,vt4);
	double rarc12 = 180*arc12/pi;
	float len= Distance(vt1,vt2);
	Vector3f vt3 = Cross(vVectorOrgin,vt4);
	glRotatef ((float)rarc12,vt3.x,vt3.y,vt3.z);

	//glRotatef(20,0,0,1);
	return 0;


}

Vector3f OpenGL::get_joint_point(int ID)
{
	Vector3f vect = m_3ds->get_joint_point(ID);
	return vect;
}

int OpenGL::translate(float x, float y, float z)
{
	glTranslatef(x,y,z);
	return 0;
}

int OpenGL::rotate(float arc, float x, float y, float z)
{	
	glRotatef(arc,x,y,z);
	return 0;
}
