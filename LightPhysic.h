#pragma once

#ifndef _LIGHT_H
#define _LIGHT_H
#define LAMBERT 1.f
#define PHONG_W 0.2f
#define PHONG_N 50
#define AO_ON  true
//打开环境光遮蔽

//把RGB 理解成分别对不同维度的发射度，白色则表示每个维度都进行反射，黑色表示全部吸收
//注意灰度的特征RGB三个分量是一致的
//同一颜色三个分量同时变化就是其亮度变化
#include "math_tool.h"

//注意这里将环境光计算为物体的自发光

class Light
{
public:
	Light();
	~Light();
	Light(Vector3f color);
	Vector3f LightColor = Vector3f(1.f,1.f,1.f);
	bool Enable = false;
	//记录光的颜色
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