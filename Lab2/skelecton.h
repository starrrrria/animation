// skelecton.h: interface for the skelecton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKELECTON_H__37F431BB_0C89_4757_AC1C_29A6DA471423__INCLUDED_)
#define AFX_SKELECTON_H__37F431BB_0C89_4757_AC1C_29A6DA471423__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bone.h"
#include "kalman.h"
#include <vector>
#include "cv.h"
#include "highgui.h"
#include "OpenGL.h"


using namespace std ;
typedef vector<bone> bone_vector;

class skelecton  
{
public:
	int draw_skeleton_3D(CvArr *motion_track_img);
	void view_right();
	void view_left();
	void view_down();
	void view_up();
	int drawOpenGL3D(CvArr *motion_track_img);
	void set_previous_skelecton(skelecton *pre_skelecton);	
	int ID;
	void CalcLengthRatio(int ID,CvPoint2D32f pt);
	void CorrectPosition(int ID,CvPoint2D32f &pt,kalman &bone_kalman,const CvArr* image);
	int draw3D(CvArr* motion_track_img);
	int reset ();
	bone* get_bone_by_ID(int ID);
	bone* get_bone_by_name(char *name);
	bool ske_pause;
	OpenGL *pgl; 
	
	int draw2D(CvArr* img);   //ªÊ÷∆Õº–Œ	
	skelecton();
	virtual ~skelecton();
	int Load3DS();


private:
	int Render_skeleton_3D(int ID);
	
	bone_vector bonevec;	
	int get_porper_Z(int x1,int x2,bone* pbone);
	int check_porper_Z(int x1,int x2,bone* pbone,bool IsLeft);
	void CalcBonePosition();
	int CalcBoneRealWorldPosition(char *pName,char *ppName,double LengthRatio);
	int CalcBoneRealWorldPosition_parallel(char *pName,char *ppName);
	skelecton *pre_ske;

	
};

#endif // !defined(AFX_SKELECTON_H__37F431BB_0C89_4757_AC1C_29A6DA471423__INCLUDED_)
