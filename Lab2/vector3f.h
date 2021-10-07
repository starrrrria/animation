/***************************************************************************
                          vector3f.h  -  description
                             -------------------
    begin                : Thu Apr 10 2003
    copyright            : (C) 2003 by junglesong
    email                : junglesong@etang.com
 ***************************************************************************/
#ifndef VECTOR3F_H
#define VECTOR3F_H

//基本三维空间"向量/点"类
class Vector3f {
public: 
	//无参构造函数
	Vector3f()
	{
		x=y=z=0;
	};
	//有参构造函数
	Vector3f(const float inx,const float iny,const float inz)
	{
		//分别将参数赋值给三个成员变量
		x=inx;
		y=iny;
		z=inz;	
	};
	//析构函数
	~Vector3f(){};
	
	//重载=操作符,实现两向量变量的赋值
	Vector3f& operator=(Vector3f& inVet)
	{
		x=inVet.x;
		y=inVet.y;
		z=inVet.z;
		return *this;
	};

	//重载+操作符,实现两向量变量的相加
	Vector3f operator+(Vector3f vVector)
	{
		//返回相加的结果
		return Vector3f(vVector.x + x, vVector.y + y, vVector.z + z);
	}

	//重载-操作符,实现两向量变量的相减
	Vector3f operator-(Vector3f vVector)
	{
		//返回相减的结果
		return Vector3f(x - vVector.x, y - vVector.y, z - vVector.z);
	}

	//重载*操作符,实现一个向量变量和一个浮点数的乘法
	Vector3f operator*(float num)
	{
		//返回缩放了的向量
		return Vector3f(x * num, y * num, z * num);
	}

	//重载/操作符,实现一个向量变量和一个浮点数的除法
	Vector3f operator/(float num)
	{
		//返回缩放了的向量
		return Vector3f(x / num, y / num, z / num);
	}
	
	//向量绕x轴旋转,参数sintheta为旋转角度的正弦值,参数costheta为旋转角度的余弦值
	void RotateX(float sintheta,float costheta)
	{
		float sin_beta,cos_bata;
		sin_beta=z*costheta +y*sintheta;
		cos_bata=y* costheta- z*sintheta;
		z=sin_beta;
		y=cos_bata;
	};

	//向量绕y轴旋转,参数sintheta为旋转角度的正弦值,参数costheta为旋转角度的余弦值
	void RotateY(float sintheta,float costheta)
	{
		float sin_beta,cos_bata;
		sin_beta=z*costheta +x*sintheta;
		cos_bata=x* costheta- z*sintheta;
		z=sin_beta;
		x=cos_bata;
	};

    //向量绕z轴旋转,参数sintheta为旋转角度的正弦值,参数costheta为旋转角度的余弦值
	void RotateZ(float sintheta,float costheta)
	{
		float sin_beta,cos_bata;
		sin_beta=y*costheta +x*sintheta;
		cos_bata=x* costheta- y*sintheta;
		y=sin_beta;
		x=cos_bata;
	};
	
	//缩放一个向量,参数scale为缩放的比例
	void Zoom(float scale)
	{
		x*=scale;
		y*=scale;
		z*=scale;
	};
	
	//平移一个向量
	void Move(Vector3f inVect)
	{
		x+=inVect.x;
		y+=inVect.y;
		z+=inVect.z;
	};
public:	
	float x;//成员变量x,向量在x轴上的分量
	float y;//成员变量y,向量在y轴上的分量
	float z;//成员变量z,向量在z轴上的分量
};

//得到两向量的叉乘
Vector3f Cross(Vector3f vVector1, Vector3f vVector2);

//得到一个向量的绝对长度
float Magnitude(Vector3f vNormal);

//将一个向量单位化
Vector3f Normalize(Vector3f vNormal);

//得到一个三点决定的平面的垂直向量(经过单位化)
Vector3f Normal(Vector3f vPolygon[]);

//得到空间中两点的距离
float Distance(Vector3f vPoint1, Vector3f vPoint2);

//得到两向量的点积
float Dot(Vector3f vVector1, Vector3f vVector2);

//得到两向量的夹角
double AngleBetweenVectors(Vector3f Vector1, Vector3f Vector2);

#endif

