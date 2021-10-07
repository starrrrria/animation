// bone.cpp: implementation of the bone class.
//
//////////////////////////////////////////////////////////////////////

#include "Bone.h"
#include "string.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

bone::bone(int ID,char *name,int PID)
{
	this->ID =ID;
	strcpy (this->name,name);
	this->PID = PID;
	this->x = 0;	
	this->y = 0;
	this->r_x = 0;
	this->r_y = 0;
	this->r_z = 0;
	this->rotated_X = 0;
	this->rotated_Y = 0;
	this->is_marked = 0;
	this->start_arc_x = 0;
	this->start_arc_y = 0;
	this->start_arc_z = 0;
	this->end_arc_x = 0;
	this->end_arc_y = 0;
	this->end_arc_z = 0;
	this->CID = 0;
	strcpy(this->file_name_3ds,"");
	bone_init_x = 0;
	bone_init_y = -1;  //方向缺省向下
	bone_init_z = 0;
}

bone::~bone()
{

}
