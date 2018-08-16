#include "LightPhysic.h"
#include <math.h>

Light::Light(){}
Light::~Light(){}
EnvironmentLight::EnvironmentLight() {}
EnvironmentLight::~EnvironmentLight() {}
PointLight::PointLight() {}
PointLight::~PointLight() {}
DirectLight::DirectLight() {}
DirectLight::~DirectLight() {}

DirectLight::DirectLight(Vector3f color, Vector3f direction, double lightness):Light(color)
{
	this->Direction = direction;
	this->Lightness = lightness;
}

Vector3f DirectLight::GetLightness()
{
	Vector3f light = this->LightColor.NumDot(this->Lightness);
	return light;
}

Light::Light(Vector3f color) {
	this->LightColor = color;
}
EnvironmentLight::EnvironmentLight(Vector3f color,double lightness):Light(color)
{
	this->Lightness = lightness;
}

PointLight::PointLight(Vector3f pos,Vector3f color,double kl,double kq) :Light(color) {
	this->Position = pos;
	this->KL = kl;
	this->KQ = kq;
}

Vector3f PointLight::GetLightness(const Vector3f & target)
{
	double d = Vector3f::Distance(target,this->Position);
	double linear = (this->KL)*d;
	double nonlinear = (this->KQ)*pow(d, 2);
	Vector3f lightness = this->LightColor.NumDot((double)1 / (1 + linear + nonlinear));
	//点光源光强计算
	return lightness;
}



double Lambert(Vector3f& normal, Vector3f& toLight) {
	Vector3f color();
	double KD = LAMBERT;
	double cosine = Vector3f::GetCosine(normal, toLight);
	if (cosine < 0) return 0.0;
	else return cosine*KD;
}

double Phong(Vector3f & normal, Vector3f & toEye, Vector3f & toLight)
{
	double Wtheta = PHONG_W;
	double N = PHONG_N;
	Vector3f R = normal.NumDot(2.f).NumDot(normal.Mult(toLight))-toLight;
	double consine_n = Vector3f::GetCosine(R,toEye);
	if (consine_n < 0) return 0.0;
	consine_n = pow(consine_n, N);
	double I = Wtheta*consine_n;
	return I;
}
