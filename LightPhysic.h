#pragma once

#ifndef _LIGHT_H
#define _LIGHT_H
#define LAMBERT 1.f
#define PHONG_W 0.2f
#define PHONG_N 50
#define AO_ON  true
//�򿪻������ڱ�

//��RGB ���ɷֱ�Բ�ͬά�ȵķ���ȣ���ɫ���ʾÿ��ά�ȶ����з��䣬��ɫ��ʾȫ������
//ע��Ҷȵ�����RGB����������һ�µ�
//ͬһ��ɫ��������ͬʱ�仯���������ȱ仯
#include "math_tool.h"

//ע�����ｫ���������Ϊ������Է���

class Light
{
public:
	Light();
	~Light();
	Light(Vector3f color);
	Vector3f LightColor = Vector3f(1.f,1.f,1.f);
	bool Enable = false;
	//��¼�����ɫ
private:
};



class EnvironmentLight :public Light
{
public:
	EnvironmentLight();
	~EnvironmentLight();
	EnvironmentLight(Vector3f color, double lightness);
	double Lightness;
private:
};

class PointLight : public Light
{
public:
	PointLight();
	~PointLight();
	PointLight(Vector3f pos,Vector3f color,double kl,double kq);
	Vector3f GetLightness(const Vector3f& target);
	Vector3f Position;
	double KL;
	double KQ;

private:

};

class DirectLight : public Light
{
public:
	DirectLight();
	~DirectLight();
	DirectLight(Vector3f color,Vector3f direction,double lightness);
	Vector3f GetLightness();
	Vector3f Direction;
	double Lightness;

private:

};



double Lambert(Vector3f& normal, Vector3f& toLight);
double Phong(Vector3f& normal,Vector3f& toEye ,Vector3f& toLight);




#endif