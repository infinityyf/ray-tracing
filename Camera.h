#pragma once


#ifndef _CAMERA_H
#define _CAMERA_H
#include "math_tool.h"
#include "Screen.h"

//ÿ�����صĲ�����
#define ONE_SAMPLE		1
#define THREE_SAMPLE	3
#define FOUR_SAMPLE		4

class Camera
{
public:
	Camera();
	~Camera();
	Camera(Point pos);
	void lookat(double tarx, double tary, double tarz, double headx, double heady, double headz);
	Point CameraPosition;
	Vector3f Postion4Calcu;
	Vector3f N;//view_z
	Vector3f V;//view_x
	Vector3f U;//view_y

	void SetProjection(double near,double far,double width_left,double width_right,double height_top,double height_buttom);

	//����ÿ�����ص����꣬����һ��ָ������
	void GetPixelPos(int level);


	//Ĭ�ϳ߶�
	double D = 300;
	double F = 900;
	double width_left = -300;//x
	double width_right = 300;
	double height_top = 300;//y
	double height_buttom = -300;

	//��¼ÿ������ͨ�������ص�����Ŀǰ��һ������һ������
	Vector3f PixelPos[WIN_HIGH][WIN_WIDTH];

	//--------|---------0--------|
	//	300	  |---300---0---300--|

};


#endif