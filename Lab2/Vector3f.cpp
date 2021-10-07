/***************************************************************************
                          vector3f.cpp  -  description
                             -------------------
    begin                : Thu Apr 10 2003
    copyright            : (C) 2003 by junglesong
    email                : junglesong@etang.com
 ***************************************************************************/

#include "vector3f.h"
#include <math.h>

//�õ��������Ĳ��
/*	�йز�˵�˵��(���ֳ���:http://www.gameres.com/Articles/Program/Visual/Other/shiliang.htm)
���:Vector1(x1,y1,z1),Vector2(x2,y2,z2):
�����Ǹ�ʸ��.
������Vector1,Vector2���ɵ�ƽ�淨��.��ʹ�����ֶ���
������Length(Vector1)*Length(Vector2)*sin(theta)
theta��Vector1 & Vector2�ļн�.
����,ƽ�е�ʸ����˽��Ϊ0ʸ��(��Ϊ0,��������)
������ʸ��:(ox,oy,oz)
ox = (y1 * z2) - (y2 * z1)
oy = (z1 * x2) - (z2 * x1)
oz = (x1 * y2) - (x2 * y1)
��;:���㷨����
*/
Vector3f Cross(Vector3f vVector1, Vector3f vVector2)
{
	//����һ�����ɲ�˽��������
	Vector3f vNormal;

	//�õ���������X���ϵ�ͶӰֵ
	vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));

	//�õ���������Y���ϵ�ͶӰֵ
	vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));

	//�õ���������Z���ϵ�ͶӰֵ
	vNormal.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

	//���ش�����
	return vNormal;
}

//�õ�һ�������ľ��Գ���
float Magnitude(Vector3f vNormal)
{
	return (float)sqrt( (vNormal.x * vNormal.x) + (vNormal.y * vNormal.y) + (vNormal.z * vNormal.z) );
}

//��һ��������λ��
Vector3f Normalize(Vector3f vNormal)
{
	//�õ��������ľ��Գ���
	float magnitude = Magnitude(vNormal);

	//��ÿ�������ֱ���Դ˳���
	vNormal.x /= magnitude;	
	vNormal.y /= magnitude;	
	vNormal.z /= magnitude;	

	//���ش�����
	return vNormal;	
}

//�õ�һ�����������ƽ��Ĵ�ֱ����(������λ��)
Vector3f Normal(Vector3f vPolygon[])
{
	//�õ������ߵ�����
	Vector3f vVector1 = vPolygon[2] - vPolygon[0];
	Vector3f vVector2 = vPolygon[1] - vPolygon[0];

	//�õ����������Ĳ��
	Vector3f vNormal = Cross(vVector1, vVector2);

	//��λ��
	vNormal.x = Normalize(vNormal).x;		
	vNormal.y = Normalize(vNormal).y;
	vNormal.z = Normalize(vNormal).z;
	
	//���ش˱���
	return vNormal;	
}

//�õ������ľ���
float Distance(Vector3f vPoint1, Vector3f vPoint2)
{
	double distance = sqrt( (vPoint2.x - vPoint1.x) * (vPoint2.x - vPoint1.x) +
						    (vPoint2.y - vPoint1.y) * (vPoint2.y - vPoint1.y) +
						    (vPoint2.z - vPoint1.z) * (vPoint2.z - vPoint1.z) );

	return (float)distance;
}

//�õ��������ĵ��
/*�йص����˵��(���ֳ���:http://www.gameres.com/Articles/Program/Visual/Other/shiliang.htm)
����ʸ���ĵ���Ǹ�����.
��ѧ���������������ʸ�����������:W=|F|.|S|.cos(theta)

��ʸ�����:
Vector1:(x1,y1,z1) Vector2(x2,y2,z2)
DotProduct=x1*x2+y1*y2+z1*z2

����Ҫ��Ӧ��:
1.���ʸ������:
����������Ϥ��������:
cos(theta)=F.S/(|F|.|S|)
�����ж϶�ʸ���ķ������: cos=1ͬ��,cos=-1�෴,cos=0ֱ��
��������(Cull face)ʱ�ж���������Ƿ�ɼ�:(���ߺ�����ʸ���ķ�������)cos>0���ɼ�,cos<0�ɼ�
OpenGL������ô���ġ�

2.Lambert���������ǿ��Ҳ�õ��:
Light=K.I.cos(theta)
K,IΪ����,theta��ƽ�淨����������߼н�
*/
float Dot(Vector3f vVector1, Vector3f vVector2)
{
	return ( (vVector1.x * vVector2.x) + (vVector1.y * vVector2.y) + (vVector1.z * vVector2.z) );
}

//�õ��������ļн�
double AngleBetweenVectors(Vector3f Vector1, Vector3f Vector2)
{
	//�õ��������ĵ��
	float dotProduct = Dot(Vector1, Vector2);

	//�õ����������ȵĳ˻�
	float vectorsMagnitude = Magnitude(Vector1) * Magnitude(Vector2) ;

	//�õ��������н�
	double angle = acos( dotProduct / vectorsMagnitude );

	//���ؽǶ�ֵ
	return( angle );
}
