// skelecton.cpp: implementation of the skelecton class.
//
//////////////////////////////////////////////////////////////////////


#include "skelecton.h"
#include "kalman.h"
#include <string.h>
#include <math.h>
#include "vector3f.h"
#include <assert.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int coordinator_X,coordinator_Y=0; //ͼ����������
const double MaxMinZero=0.0000001;  //С�����ֵ��Ϊ��0
const double f=200;  //pin-hole����Ч����
const double StardardLength=500;  //��Ӧ��ʵ���������ĸ߶ȣ�ʵ�����Ƕ�Ӧ������
const double StardardLengthNoiseRatio = 0.3 ; //�������ռ���������ı���
double arc_y= 0;//y����ת15��
double arc_z= 0;//z����ת15��
char *FilePath3DS="data/3ds/skeleton/";

float cccc=-1 ;


skelecton::skelecton()
{
	float fy = 0.56f ;
	float ftx = 0.19f;
	float ffx = 0.08f;
	bone obone = bone (1,"neck",0);
	bonevec.push_back (obone);	

	obone =  bone (2,"head",1);	
	strcpy(obone.file_name_3ds,"head.3DS");
	obone.bone_init_x = 0; 
	obone.bone_init_y = 1; 
	obone.bone_init_z = 0; 
	bonevec.push_back (obone);	

	obone = bone (3,"rShoulder",1);	
	bonevec.push_back (obone);	

	obone = bone (4,"lShoulder",1);	
	bonevec.push_back (obone);	

	obone = bone (5,"rElbow",3);
	strcpy(obone.file_name_3ds,"rShoulder.3DS");
	obone.bone_init_x = fy; 
	obone.bone_init_y = -1; 
	obone.bone_init_z = 0; 
	obone.CID = 7;
	bonevec.push_back (obone);	

	obone = bone  (6,"lElbow",4);	
	strcpy(obone.file_name_3ds,"lShoulder.3DS");
	obone.bone_init_x = -fy; 
	obone.bone_init_y = -1; 
	obone.bone_init_z = 0; 
	obone.CID = 8;
	bonevec.push_back (obone);	

	obone = bone (7,"rWrist",5);
	strcpy(obone.file_name_3ds,"rElbow.3DS");
	obone.bone_init_x = fy; 
	obone.bone_init_y = -1; 
	obone.bone_init_z = 0; 
	bonevec.push_back (obone);	

	obone = bone (8,"lWrist",6);
	strcpy(obone.file_name_3ds,"lElbow.3DS");
	obone.bone_init_x = -fy; 
	obone.bone_init_y = -1; 
	obone.bone_init_z = 0; 
	bonevec.push_back (obone);	

	obone = bone (9,"Waist",1);
	strcpy(obone.file_name_3ds,"body.3DS");
	bonevec.push_back (obone);	

	obone = bone (10,"rKnee",9);	
	strcpy(obone.file_name_3ds,"rthigh.3DS");
	obone.bone_init_x = ftx; 
	obone.bone_init_y = -1; 
	obone.bone_init_z = 0; 
	obone.CID = 12;
	bonevec.push_back (obone);	

	obone = bone(11,"lKnee",9);	
	strcpy(obone.file_name_3ds,"lthigh.3DS");
	obone.bone_init_x = -ftx; 
	obone.bone_init_y = -1; 
	obone.bone_init_z = 0; 
	obone.CID = 13;
	bonevec.push_back (obone);	

	obone = bone (12,"rAnkle",10);
	strcpy(obone.file_name_3ds,"rfeet.3DS");
	obone.bone_init_x = ffx; 
	obone.bone_init_y = -1; 
	obone.bone_init_z = 0; 
	bonevec.push_back (obone);	

	obone = bone (13,"lAnkle",11);
	strcpy(obone.file_name_3ds,"lfeet.3DS");
	obone.bone_init_x = -ffx; 
	obone.bone_init_y = -1; 
	obone.bone_init_z = 0; 
	bonevec.push_back (obone);	


	pre_ske=NULL;

	//pgl = m_OpenGL;
	//pgl->Init();
	
}

skelecton::~skelecton()
{	
  //�����ͷų�����Ҫ�ٴμ���Ƿ���ѭ������
	/*
	if(pre_ske!=NULL) 
	{
		delete pre_ske;
		pre_ske = NULL;
	}

	if(pgl!=NULL) 
	{
		delete pgl;
		pgl = NULL;
	}
*/
	bonevec.empty(); 

}

int skelecton::draw2D(CvArr* motion_track_img)
{
	bone_vector::iterator theIterator;
	bone *pbone = 0;
	bone *ppbone = 0;
		
    for (theIterator = bonevec.begin(); theIterator != bonevec.end();
         theIterator++)
    {
		  pbone = theIterator;		   
		  cvCircle( motion_track_img, cvPoint(pbone->x,pbone->y),10, CV_RGB(0,255,0),3, CV_AA, 0 );
		  if ( 0 != pbone->PID )  
		  {
			  ppbone = get_bone_by_ID(pbone->PID); 
			  cvLine( motion_track_img, cvPoint(pbone->x,pbone->y),cvPoint(ppbone->x,ppbone->y),CV_RGB(0,255,0),2,CV_AA, 0 );
		  }

	} 
	return 0;
}

bone* skelecton::get_bone_by_name(char *name)
{
	bone_vector::iterator theIterator;
	bone_vector::iterator theIterator2;
	theIterator2  = 0;
	
	
    for (theIterator = bonevec.begin(); theIterator != bonevec.end();
         theIterator++)
    {
			 if (0 == strncmp(theIterator->name, name , 4 ))
			 {
				 theIterator2=theIterator;
				 break;
			 }                                         
	} 
	return (theIterator2);
}

bone* skelecton::get_bone_by_ID(int ID)
{

	return (&bonevec[ID-1]);	
}

int skelecton::reset()
{
	bone_vector::iterator theIterator;
	bone *pbone = 0;
	
		
    for (theIterator = bonevec.begin(); theIterator != bonevec.end();
         theIterator++)
    {
		  pbone = theIterator;		   
		  pbone->x =0 ;
		  pbone->y =0 ;	
		  pbone->is_marked = 0;
		 
	} 
	return 0;
}

int skelecton::draw3D(CvArr *motion_track_img)
{
	//2d����ת��Ϊ3d����
	bone_vector::iterator theIterator;
	bone *pbone = 0;
	bone *ppbone = 0;	
	
	ppbone = get_bone_by_name("head"); 
	ppbone->r_z =0;  //��ʼ��head������Ϊ0
	ppbone->r_x=ppbone->x - coordinator_X;
	ppbone->r_y=ppbone->y - coordinator_Y;

	
	CvSize ImageSize; 
	ImageSize = cvGetSize(motion_track_img);
	
	coordinator_X = (int)ImageSize.width/2;
	coordinator_Y = (int)ImageSize.height/2;
	
	CalcBonePosition();

	//����3d����ϵ
	if(ske_pause) arc_y+=5;
	const double pi = 3.1415926535;
	double cosx = cos(arc_y/90*pi);
	double sinx = sin(arc_y/90*pi);
	double cosx_z = cos(arc_z/90*pi);
	double sinx_z = sin(arc_z/90*pi);

	const float ZX[] = { 1, 0, 0, 0,
						0,cosx,sinx,0,					
						0,-sinx,cosx,0,
						0,0,0,1
						};

	const float ZY[] = { cosx,0,sinx,0,	
						 0,1,0,0,
						-sinx,0,cosx,0,
						0,0,0,1
						};

	const float ZZ[] = { cosx_z,sinx_z, 0, 0,
						-sinx_z,cosx_z,0,0,					
						0,0,1,0,
						0,0,0,1
						};

	const float Zoom[] = { 
						1,0,0,0,
						0,1,0,0,					
						0,0,1,0,
						coordinator_X,coordinator_Y,coordinator_X,1
						};  //���ű���,����ƽ��100
	CvMat* RotateMatrix = cvCreateMat( 4, 4, CV_32FC1 ); //��ת����
	memcpy( RotateMatrix->data.fl, ZY, sizeof(ZY));      
	CvMat* tempMatrix = cvCreateMat( 4, 4, CV_32FC1 );
	memcpy( tempMatrix->data.fl, ZZ, sizeof(ZZ));
	cvMatMul( RotateMatrix, tempMatrix, RotateMatrix);	
	memcpy( tempMatrix->data.fl, Zoom, sizeof(Zoom));
	cvMatMul( RotateMatrix, tempMatrix, RotateMatrix);  

	CvMat* PointVector = cvCreateMat( 1, 4, CV_32FC1 ); //��ʸ������
	float pt[] = { 0,0, 0, 1};
	int ox,oy=0; //ԭ��
	memcpy( PointVector->data.fl, pt, sizeof(pt));
	cvMatMul(PointVector,RotateMatrix,PointVector);	
	ox = PointVector->data.fl[0];
	oy = PointVector->data.fl[1];

	pt[0]=300 ;
	pt[1]=0 ;
	pt[2]=0;
	memcpy( PointVector->data.fl, pt, sizeof(pt));
	cvMatMul(PointVector,RotateMatrix,PointVector);	
	cvLine( motion_track_img, cvPoint(ox,oy),cvPoint(PointVector->data.fl[0],PointVector->data.fl[1]),CV_RGB(255,255,255),2,CV_AA, 0 );
	//printf( "PointVector->data.fl[0,1]: %f,%f \n",PointVector->data.fl[0],PointVector->data.fl[1]);
	
	pt[0]=0 ;
	pt[1]=300 ;
	pt[2]=0;
	memcpy( PointVector->data.fl, pt, sizeof(pt));
	cvMatMul(PointVector,RotateMatrix,PointVector);	
	cvLine( motion_track_img, cvPoint(ox,oy),cvPoint(PointVector->data.fl[0],PointVector->data.fl[1]),CV_RGB(0,255,255),2,CV_AA, 0 );
	//printf( "PointVector->data.fl[0,1]: %f,%f \n",PointVector->data.fl[0],PointVector->data.fl[1]);
	
	pt[0]=0 ;
	pt[1]=0 ;
	pt[2]=300;
	memcpy( PointVector->data.fl, pt, sizeof(pt));
	cvMatMul(PointVector,RotateMatrix,PointVector);
	cvLine( motion_track_img, cvPoint(ox,oy),cvPoint(PointVector->data.fl[0],PointVector->data.fl[1]),CV_RGB(255,255,0),2,CV_AA, 0 );
	//printf( "PointVector->data.fl[0,1]: %f,%f \n",PointVector->data.fl[0],PointVector->data.fl[1]);


		
    for (theIterator = bonevec.begin(); theIterator != bonevec.end();
         theIterator++)
    {
		  pbone = theIterator;	
		  
			pt[0]=pbone->r_x ;
			pt[1]=pbone->r_y ;
			pt[2]=pbone->r_z ;
			memcpy( PointVector->data.fl, pt, sizeof(pt));
			cvMatMul(PointVector,RotateMatrix,PointVector);
			pbone->rotated_X = PointVector->data.fl[0];
			pbone->rotated_Y = PointVector->data.fl[1];		
			
			if(pbone->is_marked==0)  continue; //δ����򲻻�
/*
			printf( "%s,r_x,r_y,r_z: %d,%d,%d \n",pbone->name,pbone->r_x,pbone->r_y,pbone->r_z);
			printf( "rotated_X,Y: %d,%d \n",pbone->rotated_X,pbone->rotated_Y);
			printf( "---------------------------------------------------\n");
*/
			cvCircle( motion_track_img, cvPoint(pbone->rotated_X,pbone->rotated_Y),5, CV_RGB(0,255,0),2, CV_AA, 0 );
			  if ( 0 != pbone->PID )  
			  {
				  ppbone = get_bone_by_ID(pbone->PID); 
				  cvLine( motion_track_img, cvPoint(pbone->rotated_X,pbone->rotated_Y),cvPoint(ppbone->rotated_X,ppbone->rotated_Y),CV_RGB(0,255,0),2,CV_AA, 0 );
		  
			  }

	} 
	
	pgl->display();
    return 0;
}

//\����pin holeģ��
int skelecton::CalcBoneRealWorldPosition(char *pname, char *ppName,double LengthRatio)
{

	bone *ppbone = 0;
	bone *pbone = 0;
	int cx0,cy0=0; //У���������
	int cx,cy=0; //У���������
	double A,B,C,det,sqdet,x1,x2=0;

	ppbone = get_bone_by_name(pname); 
	pbone = get_bone_by_name(ppName); 
	cx0= ppbone->r_x;
	cy0= ppbone->r_y;	
	cx= pbone->x - coordinator_X ;
	cy= pbone->y - coordinator_Y ;
	
	//'����Ԫһ�η���

	A = pow(cx/f,2)  + pow(cy/f,2) + 1;
	B = -2*(cx/f)*ppbone ->r_x -2*(cy/f)*ppbone ->r_y - 2*ppbone->r_z;
	C = pow(ppbone->r_x,2) + pow(ppbone->r_y,2) + pow(ppbone->r_z,2) - pow(LengthRatio*StardardLength,2);
		//'B^2-4AC
		det = pow(B,2) - 4*A*C;
		//'det>0 ������
		if (det>MaxMinZero)
		{
			//��Ҫ����һ��������Ľ�
			sqdet = sqrt(det);
			x1=(-B+sqdet)/(2*A);
			x2=(-B-sqdet)/(2*A);
		}
		//'det==0 ����
		else if (det<MaxMinZero && det>0)
		{
			x1=x2=(-B)/(2*A);
		} 
		//'det<0 �޽�
		else if (det<0)
		{
			//��Ҫ�ٴ�̽��
			x1=x2=0;
		}	
	pbone->r_z =x1;
	pbone ->r_x = pbone->x * pbone->r_z / f;
	pbone ->r_y = pbone->y * pbone->r_z / f;

	/*
	printf( "A: %f \n",A);
	printf( "B: %f \n",B);
	printf( "C: %f \n",C);	
	
	*/
	
	return 0;

}

//\����ƽ�й�ģ��
int skelecton::CalcBoneRealWorldPosition_parallel(char *pname, char *ppName)
{

	bone *ppbone = 0;
	bone *pbone = 0;
	int cx0,cy0=0; //У���������
	ppbone = get_bone_by_name(pname); 
	pbone = get_bone_by_name(ppName); 
	if(pbone!=NULL && pbone->is_marked)
	{
		cx0= ppbone->x - coordinator_X ;
		cy0= ppbone->y - coordinator_Y ;

		ppbone ->r_x = cx0;
		ppbone ->r_y = cy0;
		double A,B,C,det,sqdet,x1,x2=0;

		int cx,cy=0; //У���������
		
		cx= pbone->x - coordinator_X ;
		cy= pbone->y - coordinator_Y ;

		//'����Ԫһ�η���
		A = 1;
		B = - 2*ppbone->r_z;
		C = pow(cx-cx0,2) + pow(cy-cy0,2) + pow(ppbone->r_z,2) - pow(pbone->LengthRatio*StardardLength,2);
			//'B^2-4ACy
			det = pow(B,2) - 4*A*C;
			//'det>0 ������
			if (det>MaxMinZero)
			{
				//��Ҫ����һ��������Ľ�
				sqdet = sqrt(det);
				x1=(-B+sqdet)/(2*A);
				x2=(-B-sqdet)/(2*A);
				x1=get_porper_Z(x1,x2,pbone);
			}
			//'det==0 ����
			else if (det<MaxMinZero && det>0)
			{
				x1=x2=(-B)/(2*A);
			} 
			//'det<0 �޽�
			else if (det<0)
			{
				//��Ҫ�ٴ�̽��
				x1=x2=0;
			}	
		pbone->r_z =x1;
		pbone ->r_x = cx ;
		pbone ->r_y = cy ;


		/*
		printf( "A: %f \n",A);
		printf( "B: %f \n",B);
		printf( "C: %f \n",C);	
		
		*/
	}
	return 0;

}

void skelecton::CorrectPosition(int ID,CvPoint2D32f &pt,kalman &bone_kalman,const CvArr* grey)
{
		/*
			һЩ���裺1��neckΪ֧�㲻����
					  2��֧�������᲻ƫб��ʼ��y����,x����z����,�������˶���ֱ������λ�ã�
					  û�����ԵĲ����˶��ȡ������˶��������ơ�
					  head: L*-sinx2 < r_x < L*sinx1 ,   x^2 + y^2 <= L^2 ; 
					  shoulder: shoulder.x  <= neck.x + L ;
					  eblow: x^2 + y^2 <= L^2 ;
					  rWrist: x^2 + y^2 <= L^2 ; 
					  waist: waist.y = neck.y + L
					  keen:  x^2 + y^2 <= L^2 ; x<0;
					  ankle: x^2 + y^2 <= L^2 ;

		*/
		//������꣬���������ٺ��2D���꣬������ʽ
		//���λ�������˶���Χ��
			//
		//������������˶���Χ�ڣ��綪�������㣬���ڵ�������ʼ����kalman�˲���
			//���kalman�˲�λ�������˶���Χ��,��kalmanԤ��ĵ���ΧѰ���µ�������
			//���kalman�˲����������˶���Χ��,�������Բ�ֵ��һ��������

		bone *pbone;
		bone *ppbone;
		bool is_inarea=true;
		CvPoint2D32f predict_point;		
		double bone_length = 0; //��Ӧ�Ǽܵĳ���	
		
		pbone = get_bone_by_ID (ID);		
		pbone->is_marked =1;
		double x,y,x0,y0;
		x=pt.x;
		y=pt.y;
		if(0!=pbone->PID)
		{
			bone_length = (pbone->LengthRatio * (1+StardardLengthNoiseRatio)) * StardardLength;
			ppbone = get_bone_by_ID(pbone->PID); 
			x0=ppbone->x;
			y0=ppbone->y;
			if(pow(x-x0,2) + pow(y-y0,2) > pow(bone_length,2)) 
			is_inarea = false;	
		}

		//printf("before  : %f %f \n",x,y); 

		predict_point = bone_kalman.get_predict(x,y);

		//printf("predict : %f %f \n",predict_point.x,predict_point.y); 

		if(is_inarea) 
		{

			//����Ҽ磬���ӣ��������Ӹ���������Լ��
		}
		else
		{
			if(pow(predict_point.x-x0,2) + pow(predict_point.y-y0,2) > pow(bone_length,2)) 
			{
				//Ԥ���Ҳ���ڸ���Լ���ڣ������������㶪ʧ
				//�����㶪ʧ�������˶������ԣ���������֡������������������Բ�ֵ��Ԥ��һ����
				//to do list
				if (pre_ske!=NULL)
				{	
					bone* pre_pbone =NULL;
					//pre_pbone = pre_ske->get_bone_by_ID (pbone->ID);	
					//pt.x = pre_pbone->r_x;
					//pt.y = pre_pbone->r_y;

				}

			}
			else
			{		
				//Ԥ����ڸ���Լ���ڣ������ָ����ΧѰ��������
				//to do list
				pt.x = predict_point.x;
				pt.y = predict_point.y;
			}
/*
			cvFindCornerSubPix( grey, &pt, 1,
						        cvSize(10,10), cvSize(-1,-1),
							    cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03));
*/

		}
		pbone->x = (int)pt.x;
		pbone->y = (int)pt.y;

}

void skelecton::CalcLengthRatio(int ID,CvPoint2D32f pt)
{
		bone *pbone;
		bone *ppbone;
		double bone_length;
		double x,y,x0,y0;

		pbone = get_bone_by_ID(ID); 
		if(pbone!=NULL) 
		{
			if(0!=pbone->PID)
			{
				x=pt.x;
				y=pt.y;
				
				ppbone = get_bone_by_ID(pbone->PID); 
				x0=ppbone->x;
				y0=ppbone->y;
				bone_length = sqrt(pow(x-x0,2) + pow(y-y0,2));
				pbone->LengthRatio = bone_length/StardardLength ;

			}
			else
				pbone->LengthRatio = 0;
		}


}

//��������ģ��������z����Ķ�����
int skelecton::get_porper_Z(int x1, int x2, bone *pbone)
{
	
	//return x2;
	//������һ״̬���Ƶ�ǰ״̬,ȡ����һ״̬����ĵ�
	bone *pre_pbone=NULL;
	int result = 0;
	int pre_z = 0 ;

	if (pre_ske!=NULL)
	{
		pre_pbone = pre_ske->get_bone_by_ID (pbone->ID);	
		pre_z = pre_pbone->r_z ;
		if(abs(pre_z-x1)>abs(pre_z-x2)) 	
			result= x2;
		else
			result= x1;
	}
		result= x1;
	//֫�屾��Ķ�����
	if(pre_pbone!=NULL)
	{
		switch(pbone->ID)
		{
			case 5:	//rElbow �첲�ⲻ�������				
				result = check_porper_Z(x1,x2,pre_pbone,false);
				break;
			case 6: //lElbow �첲�ⲻ�������
				result = check_porper_Z(x1,x2,pre_pbone,true);
				break;
			case 10: //rKnee ϥ�ǲ�������
				result = check_porper_Z(x1,x2,pre_pbone,false);
				break;
			case 11: //lKnee ϥ�ǲ�������
				result = check_porper_Z(x1,x2,pre_pbone,true);
				break;
		}
	}
	return result;
}

void skelecton::CalcBonePosition()
{
	CalcBoneRealWorldPosition_parallel("neck","head");
	CalcBoneRealWorldPosition_parallel("neck","rShoulder");
	CalcBoneRealWorldPosition_parallel("neck","lShoulder");
	CalcBoneRealWorldPosition_parallel("rShoulder","rElbow");
	CalcBoneRealWorldPosition_parallel("lShoulder","lElbow");
	CalcBoneRealWorldPosition_parallel("rElbow","rWrist");
	CalcBoneRealWorldPosition_parallel("lElbow","lWrist");
	CalcBoneRealWorldPosition_parallel("neck","Waist");
	CalcBoneRealWorldPosition_parallel("Waist","rKnee");
	CalcBoneRealWorldPosition_parallel("Waist","lKnee");
	CalcBoneRealWorldPosition_parallel("rKnee","rAnkle");
	CalcBoneRealWorldPosition_parallel("lKnee","lAnkle");

}


void skelecton::set_previous_skelecton(skelecton *pre_skelecton)
{
	pre_ske = pre_skelecton;
}

//��������ת�����������������ϣ���õ����ֵ�Ƿ��������Ϸ�
int skelecton::check_porper_Z(int x1, int x2, bone *pbone,bool IsLeft)
{
	int xx0,zz0,xx1,xx2,zz1,zz2,result=0;
	float sinx,cosx,radiolen;
	float zz,zzz;
	bone *ppbone,*cpbone;
	ppbone = pre_ske->get_bone_by_ID (pbone->PID);
	cpbone = pre_ske->get_bone_by_ID (pbone->CID);
	if (ppbone!=NULL && cpbone!=NULL)
	{
		xx1 = ppbone->r_x;
		zz1 = ppbone->r_z;
		xx2 = cpbone->r_x;
		zz2 = cpbone->r_z;
		xx0=xx2-xx1;
		zz0=zz2-zz1;
		radiolen = sqrt(xx0*xx0 + zz0*zz0);
		sinx=xx0/radiolen;
		cosx=zz0/radiolen;
		zz=(x1-zz1)*sinx+(x1-zz1)*cosx;  
		zzz=(x2-zz1)*sinx+(x2-zz1)*cosx;
		if(IsLeft)
		{
			if(zz<0) 
				result = x1;
			if(zzz<0)
				result = x2;
		}
		else
		{
			if(zz>0) 
				result = x1;
			if(zzz>0)
				result = x2;
		}

	}
	return result;
	
}

int skelecton::drawOpenGL3D(CvArr *motion_track_img)
{

	bone_vector::iterator theIterator;
	bone *pbone = 0;
	bone *ppbone = 0;	
	Vector3f  vt1,vt2;
	
	ppbone = get_bone_by_name("neck"); 
	ppbone->r_z =0;  //��ʼ��head������Ϊ0

	
	CvSize ImageSize; 
	ImageSize = cvGetSize(motion_track_img);	
	coordinator_X = (int)ImageSize.width/2;
	coordinator_Y = (int)ImageSize.height/2;

	CalcBonePosition();

	assert(pgl!=NULL);
	if(pgl!=NULL) 	pgl->clear();


    for (theIterator = bonevec.begin(); theIterator != bonevec.end();
         theIterator++)
    {
		  pbone = theIterator;	

			if(pbone->is_marked==0)  continue; //δ����򲻻�
			  if ( 0 != pbone->PID )  
			  {
				  ppbone = get_bone_by_ID(pbone->PID); 				  
				  vt1.x = pbone->r_x;
				  vt1.y = pbone->r_y;
				  vt1.z = pbone->r_z;
				  vt2.x = ppbone->r_x;
				  vt2.y = ppbone->r_y;
				  vt2.z = ppbone->r_z;
				  if(pgl!=NULL)  pgl->draw2point(vt1,vt2);				  
			  }

	} 
	


	if(pgl!=NULL) 
	{
		//pgl->Correct_3D_Layout(vt1,vt2);
		pgl->display();
	}
    return 0;
}

void skelecton::view_up()
{
	if(pgl!=NULL) 
	 pgl->x_arc = (pgl ->x_arc + 5) % 360;
}

void skelecton::view_down()
{
	if(pgl!=NULL) 
	pgl->x_arc = (pgl ->x_arc - 5) % 360;
}

void skelecton::view_left()
{
	if(pgl!=NULL) 
	pgl->y_arc = (pgl ->y_arc + 5) % 360;
}

void skelecton::view_right()
{
	if(pgl!=NULL) 
	pgl->y_arc = (pgl ->y_arc - 5) % 360;
}

int skelecton::draw_skeleton_3D(CvArr *motion_track_img)
{
	bone *pbone = 0;
	bone *ppbone = 0;	

	
	ppbone = get_bone_by_name("neck"); 
	ppbone->r_z =0;  //��ʼ��head��z����Ϊ0

	
	CvSize ImageSize; 
	ImageSize = cvGetSize(motion_track_img);	
	coordinator_X = (int)ImageSize.width/2;
	coordinator_Y = (int)ImageSize.height/2;

	CalcBonePosition();

	assert(pgl!=NULL);
	if(pgl!=NULL) 	pgl->clear();
	
	Render_skeleton_3D(ppbone->ID);


	if(pgl!=NULL) 
	{
		pgl->display();
	}
    return 0;
}

int skelecton::Load3DS()
{
	bone_vector::iterator theIterator;
	bone *pbone = 0;
	bone *ppbone = 0;

	for (theIterator = bonevec.begin(); theIterator != bonevec.end();
         theIterator++)
    {
		  pbone = theIterator;	
		  char *pathname = pbone->file_name_3ds;
		  char temp[100]="";

			if(strlen(pathname)!=0)  
			{
				strcat(temp,FilePath3DS);
				strcat(temp,pathname);
				pgl->Load3DS (pbone->ID,temp );
			}

	} 
	return 0;
}

//�ݹ�ʵ��3d��ʵ
int skelecton::Render_skeleton_3D(int ID)
{
	
	bone_vector::iterator theIterator;
	bone *pbone = 0;
	bone *ppbone = 0;
	Vector3f  vt1,vt2,vto;
	Vector3f joint_point;

	

	pbone = get_bone_by_ID(ID); 

	if(pbone->is_marked && strlen(pbone->file_name_3ds)!=0)
	{

		if( (0 != pbone->PID)  )  //����ע�����Ҳ���neck�ڵ�
		{
			ppbone = get_bone_by_ID(pbone->PID); 				  
			vt1.x = ppbone->r_x;
			vt1.y = ppbone->r_y;
			vt1.z = ppbone->r_z;
			vt2.x = pbone->r_x;
			vt2.y = pbone->r_y;
			vt2.z = pbone->r_z;
		}
		else //������Ϊ�ǲ���ת
		{
			vt1.x = 0;
			vt1.y = 0;
			vt1.z = 0;
			vt2.x = pbone->bone_init_x;
			vt2.y = pbone->bone_init_y;
			vt2.z = pbone->bone_init_z;
		}

		vto.x = pbone->bone_init_x ;
		vto.y = pbone->bone_init_y ;
		vto.z = pbone->bone_init_z ;

		pgl->push ();	
		joint_point = pgl->get_joint_point(ID);
		pgl->translate(joint_point.x,joint_point.y,joint_point.z);
		pgl->rotate_bone (vt1,vt2,vto);
		pgl->translate(-joint_point.x,-joint_point.y,-joint_point.z);
		pgl->show3ds(ID);
		//if((ID == 9) || (ID == 2)) 
		
	}

	
	for (theIterator = bonevec.begin(); theIterator != bonevec.end();
         theIterator++)
    {
		  pbone = theIterator;	
		  if((pbone->PID == ID) ) 
		  {
			  Render_skeleton_3D(pbone->ID);
		  }
	} 

	if(pbone->is_marked && strlen(pbone->file_name_3ds)!=0)
	pgl->pop();
	

	return 0;

}
