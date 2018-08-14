#include "Ray.h"
#include "Screen.h"
#include "Object.h"
#include <iterator>
#include <math.h>
#include <climits>//ʹ�����õ����ֵ

using namespace std;

Ray::Ray(){}

Ray::~Ray(){}

Vector3f SearchPoint(std::vector<RayHit>& HitList) {
	double result = (std::numeric_limits<double>::max)();//����һ������
	Vector3f color;
	std::vector<RayHit>::iterator it = HitList.begin();
	for (; it != HitList.end();it++) {
		if ((*it).t <= result) {
			result = (*it).t;
			color = (*it).Color;
		}
	}
	return color;
}

Vector3f MixColor(std::vector<Vector3f>& ColorList,int level) {

	//int/int �������int ��ôǳ�Ե����⻹������ô��
	std::vector<Vector3f>::iterator it = ColorList.begin();
	Vector3f MixUp(0,0,0);
	int i = 1;
	for (; i <= (level*level) && it != ColorList.end(); i++, it++) {
		MixUp = MixUp + (*it);
	}
	for (; i <= (level*level); i++) {
		MixUp = MixUp + BACKGROUND_COLOR.NumDot((double)255/(level*level));
	}
	MixUp = MixUp.NumDot((double)1/255);
	return MixUp;
}



Ray::Ray(Vector3f origin,double x, double y, double z) {
	Vector3f temp_dir(x,y,z);
	//Vector3f temp_origin(0,0,0);
	this->origin = origin;
	this->direction = Vector3f(this->origin, temp_dir);
	this->NormalDirection =Vector3f::Normalize(this->direction);
}


void Ray::scanScreen(Camera& camera , Vector3f (*buffer)[WIN_WIDTH],int level)
{
	std::vector<Vector3f>ColorBuffer;
	int centerX = level / 2;
	int centerY = level / 2;
	//���ز����Ľ������
	//���Ͼ���Ϊ���ز�������
	ObjectList* spheres = ObjectList::getInstance();
	double t;
	Vector3f HitPoint;
	Vector3f normal;
	Vector3f color;
	bool hit;
	for (int i = 0; i < WIN_HIGH; i++) {
		for (int j = 0; j < WIN_WIDTH; j++) {
			//���ڿ��Ƕ��ز���������level ���ж������ߵ�����
			ColorBuffer.clear();
			bool HitExist = false;
			//ֻҪ��һ�����䵽�˾�������ʾ
			for (int m = 0; m < (level*level);m++) {
				int row = m/level;
				int col = m%level;
				//Ҫ���ǹ������ĵ�ƫ��
				row -= centerX;
				col -= centerY;
				Vector3f CurentPos = camera.PixelPos[i][j] + camera.ScreenX.NumDot((double)(col)/level)+ camera.ScreenY.NumDot(-(double)(row)/level);
				double X = CurentPos.x;
				double Y = CurentPos.y;
				double Z = CurentPos.z;
				//����ÿ�������ߵ�Ŀ��λ�ã�֮����������

				//ʹ�õ�����
				hit = false;
				vector<Sphere>::iterator it = (spheres->objects).begin();
				Ray TestRay(camera.Postion4Calcu, X, Y, Z);
				for (; it != (spheres->objects).end(); it++) {
					t = TestRay.HitSpheree((*it).pos_v, (*it).radius);
					if (t>0) {
						HitExist = true; //��������Ҫ��ɫ
						hit = true;
						HitPoint = TestRay.GetPoint(t);
						normal = (*it).GetNormal(HitPoint);
						color = (*it).GetColor();
						//
						//�������Ӧ�û���Ҫ������ɫ
						RayHit RayHitPoint = { t,HitPoint,normal,color };
						TestRay.HitPoints.push_back(RayHitPoint);
						//�洢���еĽ���
					}
				}
				if (hit) {
					Vector3f RayColor = SearchPoint(TestRay.HitPoints);
					ColorBuffer.push_back(RayColor.NumDot((double)255/(level*level)));
				}
			}
			if (HitExist) {
				Vector3f Mixcolor = MixColor(ColorBuffer,level);
				buffer[i][j].x = Mixcolor.x;
				buffer[i][j].y = Mixcolor.y;
				buffer[i][j].z = Mixcolor.z;
			}

			////ʹ�õ�����
			//hit = false;
			//vector<Sphere>::iterator it = (spheres->objects).begin();
			//double X = camera.PixelPos[i][j].x;
			//double Y = camera.PixelPos[i][j].y;
			//double Z = camera.PixelPos[i][j].z;
			//Ray TestRay(camera.Postion4Calcu,X,Y,Z);
			//for (;it!= (spheres->objects).end();it++) {
			//	t = TestRay.HitSpheree((*it).pos_v, (*it).radius);
			//	if (t>0) {
			//		hit = true;
			//		HitPoint = TestRay.GetPoint(t);
			//		normal = (*it).GetNormal(HitPoint);
			//		color = (*it).GetColor();
			//		RayHit RayHitPoint = { t,HitPoint,normal,color};
			//		TestRay.HitPoints.push_back(RayHitPoint);
			//		//�洢���еĽ���
			//	}
			//	if (hit) {
			//		color = SearchPoint(TestRay.HitPoints);
			//		buffer[i][j].x = color.x;
			//		buffer[i][j].y = color.y;
			//		buffer[i][j].z = color.z;
			//	}
			//}
		}
	}
}

Vector3f Ray::GetPoint(double t)
{
	Vector3f t_times_normal = this->NormalDirection.NumDot(t);
	Vector3f hit_point= this->origin + t_times_normal;
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