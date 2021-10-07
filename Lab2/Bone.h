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
	int r_z;  //��ʵ����z����
	int r_y;
	int r_x;
	int rotated_X; //��ת�������
	int rotated_Y;
	int is_marked; //�Ƿ��Ѿ����
	int PID;   //���ڵ�
	int CID;   //�ӽڵ㣬Ŀǰ�����ؽں�ϥ����Ч
	float start_arc_x,end_arc_x; //��Ը��ڵ��x ���ҷ���ת���Ƕ�����
	float start_arc_y,end_arc_y; //��Ը��ڵ��y ���·���ת���Ƕ�����
	float start_arc_z,end_arc_z; //��Ը��ڵ��z ǰ����ת���Ƕ�����
	double LengthRatio; 
	char name[80]; //����
	char file_name_3ds[180]; //����
	int ID;      
	bone(int ID,char *name,int PID);
	virtual ~bone();
	float bone_init_x,bone_init_y,bone_init_z; //��ʼ��������ʸ������,3d max ģ��
};

#endif // !defined(AFX_BONE_H__94B356FA_3743_435A_B470_BC668997DEA5__INCLUDED_)
