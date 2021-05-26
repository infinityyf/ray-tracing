#include "Ray.h"
#include "Screen.h"
#include "Object.h"
#include <iterator>
#include <math.h>

using namespace std;

Ray::Ray(){}

Ray::~Ray(){}

Ray::Ray(Vector3f origin,double x, double y, double z) {
	Vector3f temp_dir(x,y,z);
	//Vector3f temp_origin(0,0,0);
	this->origin = origin;
	this->direction = Vector3f(this->origin, temp_dir);
	this->NormalDirection =Vector3f::Normalize(this->direction);
}


void Ray::scanScreen(Camera& camera , Vector3f (*buffer)[WIN_WIDTH])
{
	ObjectList* spheres = ObjectList::getInstance();
	double t;
	Vector3f HitPoint;
	Vector3f normal;

	for (int i = 0; i < WIN_HIGH; i++) {
		for (int j = 0; j < WIN_WIDTH; j++) {
			//ʹ�õ�����
			vector<Sphere>::iterator it = (spheres->objects).begin();
			Ray TestRay(camera.Postion4Calcu,camera.PixelPos[i][j].x, camera.PixelPos[i][j].y, camera.PixelPos[i][j].z);
			for (;it!= (spheres->objects).end();it++) {
				t = TestRay.HitSpheree((*it).pos_v, (*it).radius);
				if (t>0) {
					HitPoint = TestRay.GetPoint(t);
					normal = (*it).GetNormal(HitPoint);
					buffer[i][j].x = (normal.x/2)+0.5;
					buffer[i][j].y = (normal.y/2)+0.5;
					buffer[i][j].z = (normal.z/2)+0.5;
				}
			}

		}
	}
}

Vector3f Ray::GetPoint(double t)
{
	Vector3f t_times_normal = this->NormalDirection.NumDot(t);
	Vector3f hit_point= this->origin + t_times_normal;
	//rest
	return hit_point;
}




double Ray::HitSpheree(Vector3f center, double radius)
{
	Vector3f oc = this->origin - center;
	double a = this->NormalDirection.Mult(this->NormalDirection);
	double b = 2 * (oc.Mult(this->NormalDirection));
	double c = oc.Mult(oc) - radius*radius;

	////ʵ�������ж����������û�и��������2�������ǻ���
	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0) return -1;
	else
	{
		//���ؾ���������Ǹ���
		return (-b - sqrt(discriminant)) / (2 * a);

		//Ҳ���Է����������������귨����֮���Һ����߼н�Ϊ��ǵĵ�Ϊ���
	}
	
}