// OpenGL.h: interface for the OpenGL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGL_H__17B7289C_7956_41C5_89B9_621E3C435389__INCLUDED_)
#define AFX_OPENGL_H__17B7289C_7956_41C5_89B9_621E3C435389__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "vector3f.h"
#include "3ds.h"

class OpenGL  
{	
public:	
	int rotate(float arc,float x,float y,float z);
	int translate(float x,float y,float z);
	Vector3f get_joint_point(int ID);
	int rotate_bone(Vector3f vVector1, Vector3f vVector2, Vector3f vVectorOrgin);
	int pop();
	int push();
	int show3ds(int ID);
	int Load3DS(int ID,char *filename);
	OpenGL();
	virtual ~OpenGL();
	HDC		hDC;			// GDI设备描述表
	HGLRC	hRC;		// 永久着色描述表
	BOOL	SetupPixelFormat(HDC hDC);
	void	init(int Width, int Height);
	void	Render();
	void	CleanUp();
	int x_arc; //旋转角度
	int y_arc;
	int z_arc;
	void clear();
	void draw2point(Vector3f vVector1, Vector3f vVector2);
	int Init();
	void display();
	int Correct_3D_Layout(Vector3f vVector1, Vector3f vVector2);
	CLoad3DS* m_3ds;
private:
	void draw_ground();
};

#endif // !defined(AFX_OPENGL_H__17B7289C_7956_41C5_89B9_621E3C435389__INCLUDED_)
