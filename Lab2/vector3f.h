/***************************************************************************
                          vector3f.h  -  description
                             -------------------
    begin                : Thu Apr 10 2003
    copyright            : (C) 2003 by junglesong
    email                : junglesong@etang.com
 ***************************************************************************/
#ifndef VECTOR3F_H
#define VECTOR3F_H

//������ά�ռ�"����/��"��
class Vector3f {
public: 
	//�޲ι��캯��
	Vector3f()
	{
		x=y=z=0;
	};
	//�вι��캯��
	Vector3f(const float inx,const float iny,const float inz)
	{
		//�ֱ𽫲�����ֵ��������Ա����
		x=inx;
		y=iny;
		z=inz;	
	};
	//��������
	~Vector3f(){};
	
	//����=������,ʵ�������������ĸ�ֵ
	Vector3f& operator=(Vector3f& inVet)
	{
		x=inVet.x;
		y=inVet.y;
		z=inVet.z;
		return *this;
	};

	//����+������,ʵ�����������������
	Vector3f operator+(Vector3f vVector)
	{
		//������ӵĽ��
		return Vector3f(vVector.x + x, vVector.y + y, vVector.z + z);
	}

	//����-������,ʵ�����������������
	Vector3f operator-(Vector3f vVector)
	{
		//��������Ľ��
		return Vector3f(x - vVector.x, y - vVector.y, z - vVector.z);
	}

	//����*������,ʵ��һ������������һ���������ĳ˷�
	Vector3f operator*(float num)
	{
		//���������˵�����
		return Vector3f(x * num, y * num, z * num);
	}

	//����/������,ʵ��һ������������һ���������ĳ���
	Vector3f operator/(float num)
	{
		//���������˵�����
		return Vector3f(x / num, y / num, z / num);
	}
	
	//������x����ת,����sinthetaΪ��ת�Ƕȵ�����ֵ,����costhetaΪ��ת�Ƕȵ�����ֵ
	void RotateX(float sintheta,float costheta)
	{
		float sin_beta,cos_bata;
		sin_beta=z*costheta +y*sintheta;
		cos_bata=y* costheta- z*sintheta;
		z=sin_beta;
		y=cos_bata;
	};

	//������y����ת,����sinthetaΪ��ת�Ƕȵ�����ֵ,����costhetaΪ��ת�Ƕȵ�����ֵ
	void RotateY(float sintheta,float costheta)
	{
		float sin_beta,cos_bata;
		sin_beta=z*costheta +x*sintheta;
		cos_bata=x* costheta- z*sintheta;
		z=sin_beta;
		x=cos_bata;
	};

    //������z����ת,����sinthetaΪ��ת�Ƕȵ�����ֵ,����costhetaΪ��ת�Ƕȵ�����ֵ
	void RotateZ(float sintheta,float costheta)
	{
		float sin_beta,cos_bata;
		sin_beta=y*costheta +x*sintheta;
		cos_bata=x* costheta- y*sintheta;
		y=sin_beta;
		x=cos_bata;
	};
	
	//����һ������,����scaleΪ���ŵı���
	void Zoom(float scale)
	{
		x*=scale;
		y*=scale;
		z*=scale;
	};
	
	//ƽ��һ������
	void Move(Vector3f inVect)
	{
		x+=inVect.x;
		y+=inVect.y;
		z+=inVect.z;
	};
public:	
	float x;//��Ա����x,������x���ϵķ���
	float y;//��Ա����y,������y���ϵķ���
	float z;//��Ա����z,������z���ϵķ���
};

//�õ��������Ĳ��
Vector3f Cross(Vector3f vVector1, Vector3f vVector2);

//�õ�һ�������ľ��Գ���
float Magnitude(Vector3f vNormal);

//��һ��������λ��
Vector3f Normalize(Vector3f vNormal);

//�õ�һ�����������ƽ��Ĵ�ֱ����(������λ��)
Vector3f Normal(Vector3f vPolygon[]);

//�õ��ռ�������ľ���
float Distance(Vector3f vPoint1, Vector3f vPoint2);

//�õ��������ĵ��
float Dot(Vector3f vVector1, Vector3f vVector2);

//�õ��������ļн�
double AngleBetweenVectors(Vector3f Vector1, Vector3f Vector2);

#endif

