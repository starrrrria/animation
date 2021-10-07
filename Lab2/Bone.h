// bone.h: interface for the bone class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BONE_H__94B356FA_3743_435A_B470_BC668997DEA5__INCLUDED_)
#define AFX_BONE_H__94B356FA_3743_435A_B470_BC668997DEA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class bone
{
public:
	int y;
	int x;
	int r_z;  //现实世界z坐标
	int r_y;
	int r_x;
	int rotated_X; //旋转后的坐标
	int rotated_Y;
	int is_marked; //是否已经标记
	int PID;   //父节点
	int CID;   //子节点，目前针对轴关节和膝盖有效
	float start_arc_x,end_arc_x; //相对父节点的x 左右方向转动角度限制
	float start_arc_y,end_arc_y; //相对父节点的y 上下方向转动角度限制
	float start_arc_z,end_arc_z; //相对父节点的z 前后方向转动角度限制
	double LengthRatio; 
	char name[80]; //名称
	char file_name_3ds[180]; //名称
	int ID;      
	bone(int ID,char *name,int PID);
	virtual ~bone();
	float bone_init_x,bone_init_y,bone_init_z; //初始化骨骼的矢量方向,3d max 模型
};

#endif // !defined(AFX_BONE_H__94B356FA_3743_435A_B470_BC668997DEA5__INCLUDED_)
