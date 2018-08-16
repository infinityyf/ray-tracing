#include "Ray.h"
#include "Screen.h"
#include "Object.h"
#include <set>
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

Ray::Ray(Vector3f origin, Vector3f dir)
{
	this->origin = origin;
	this->direction = dir;
	this->NormalDirection = Vector3f::Normalize(dir);
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


double ReflectionModel(int model,Vector3f& normal,Vector3f& toEye,Vector3f& toLight) {
	switch (model)
	{
	case lambert:
		return Lambert(normal, toLight);
		break;
	case phong:
		return 0.7*Phong(normal,toEye,toLight)+0.3*Lambert(normal,toLight);
		break;
	case mirror:
		return Lambert(normal, toLight);
		break;
	default:
		return 0;
		break;
	}
}

void Ray::scanScreen(Camera& camera, 
	Vector3f(*buffer)[WIN_WIDTH], 
	int level, 
	EnvironmentLight& light0, 
	PointLight& light1,
	DirectLight& light2)
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
	Vector3f toEye;
	int material;
	Vector3f color0;//�����ⷴ����ɫ
	Vector3f color1;//���Դ������ɫ
	Vector3f color2;//ƽ�йⷴ����ɫ

	bool hit;
	for (int i = 0; i < WIN_HIGH; i++) {
		for (int j = 0; j < WIN_WIDTH; j++) {
			//���ڿ��Ƕ��ز���������level ���ж������ߵ�����
			ColorBuffer.clear();
			bool HitExist = false;
			//ֻҪ��һ�����䵽�˾�������ʾ
			for (int m = 0; m < (level*level); m++) {
				int row = m / level;
				int col = m%level;
				//Ҫ���ǹ������ĵ�ƫ��
				row -= centerX;
				col -= centerY;
				Vector3f CurentPos = camera.PixelPos[i][j] + camera.ScreenX.NumDot((double)(col) / level) + camera.ScreenY.NumDot(-(double)(row) / level);
				double X = CurentPos.x;
				double Y = CurentPos.y;
				double Z = CurentPos.z;
				//����ÿ�������ߵ�Ŀ��λ�ã�֮����������

				//ʹ�õ�����
				hit = false;
				vector<Sphere>::iterator it = (spheres->objects).begin();
				Ray TestRay(camera.Postion4Calcu, X, Y, Z);
				toEye = TestRay.NormalDirection.NumDot(-1.f);
				for (; it != (spheres->objects).end(); it++) {
					t = TestRay.HitSpheree((*it).pos_v, (*it).radius);
					if (t>0) {
						HitExist = true; //��������Ҫ��ɫ
						hit = true;
						HitPoint = TestRay.GetPoint(t);
						normal = (*it).GetNormal(HitPoint);
						color = (*it).GetColor();
						material = (*it).GetMaterial();
						color0 = color;
						color1 = color;
						color2 = color;
						/*���㻷�����Ӱ�죬���㷵�صĻ��������ɫ,Ӧ������������Է�����,�����һ�����ǻ������ڱ�
						*/
						if (light0.Enable) {
							if (AO_ON) {
								color0 = color0*(light0.LightColor.NumDot(light0.Lightness));
							}else color0 = color0*(light0.LightColor.NumDot(light0.Lightness));
						}

						/*������Դ�Լ���Դ�ڱβ�������Ӱ
						*/
						//if (light1.Enable) {
						//	//����ƫ�Ʊ���������ʽ���ֽ�����������ڲ�
						//	Ray ShadowTestRay(HitPoint+normal.NumDot(0.1), light1.Position.x, light1.Position.y, light1.Position.z);
						//	if (ShadowTestRay.HidePointLight(spheres->objects)) color = color*(Vector3f(0,0,0));
						//	else color = color*(light1.GetLightness(HitPoint));
						//}

						/*������Դ,ֱ��׷�ٵ��Դ����ֱ�Ӳ�����Ӱ
						*/
						if (light1.Enable) {
							//����ƫ�Ʊ���������ʽ���ֽ�����������ڲ�
							Ray ShadowTestRay(HitPoint + normal.NumDot(0.1), light1.Position.x, light1.Position.y, light1.Position.z);
							if (!ShadowTestRay.HidePointLight(spheres->objects)) {
								Vector3f toLight = Vector3f(HitPoint, light1.Position);
								toLight.Normalize();
								color1 = color1*(light1.GetLightness(HitPoint).NumDot(ReflectionModel(material,normal,toEye,toLight)));
								//ʹ��lambert����
							}
							else color1 = Vector3f(0, 0, 0);
								//�����ڵ��Ͳ���ɫ�����ֻ�����,�����Դ��ɫΪ0
						}else color1 = Vector3f(0, 0, 0);

						/*����ƽ�й�
						*/
						if (light2.Enable) {
							//ͬ��������Ӱ����
							Ray ShadowTestRay(HitPoint + normal.NumDot(0.1),light2.Direction.NumDot(-1.f));
							//���ɷ�������
							if (!ShadowTestRay.HidePointLight(spheres->objects)) {
								Vector3f toLight = ShadowTestRay.direction;
								toLight.Normalize();
								//if(material == phong) color2 = ((light2.GetLightness()).NumDot(ReflectionModel(material, normal, toEye, toLight)));
								//��ʾ���Ǵ����䣬��Ȼ��ɫ���������ϻ��������еĹ⣬���ǹ⻬��ɫ���廹���з���
								color2 = color2*((light2.GetLightness()).NumDot(ReflectionModel(material,normal, toEye, toLight)));
								//ʹ��lambert����
							}
							else color2 = Vector3f(0, 0, 0);
								//�����ڵ��Ͳ���ɫ�����ֻ�����,�����Դ��ɫΪ0
						}
						else color2 = Vector3f(0, 0, 0);


						color = color0 + color1 + color2;
						
						//�������Ӧ�û���Ҫ������ɫ
						RayHit RayHitPoint = { t,HitPoint,normal,color };
						TestRay.HitPoints.push_back(RayHitPoint);
						//�洢���еĽ���
					}
				}
				if (hit) {
					Vector3f RayColor = SearchPoint(TestRay.HitPoints);
					ColorBuffer.push_back(RayColor.NumDot((double)255 / (level*level)));
				}
			}
			if (HitExist) {
				Vector3f Mixcolor = MixColor(ColorBuffer, level);
				buffer[i][j].x = Mixcolor.x;
				buffer[i][j].y = Mixcolor.y;
				buffer[i][j].z = Mixcolor.z;
			}
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

bool Ray::HidePointLight(std::vector<Sphere>& objects)
{
	std::vector<Sphere>::iterator it = objects.begin();
	std::set<bool>hits;
	Vector3f center;
	double radius;
	bool result;
	for (; it != objects.end(); it++) {
		center = it->pos_v;
		radius = it->radius;
		Vector3f oc = this->origin - center;
		double a = this->NormalDirection.Mult(this->NormalDirection);
		double b = 2 * (oc.Mult(this->NormalDirection));
		double c = oc.Mult(oc) - radius*radius;
		double discriminant = b * b - 4 * a * c;
		if (discriminant <= 0) result = false;
		//��ʾδ���ڵ�
		else {
			double t1 = (-b - sqrt(discriminant)) / (2 * a);
			double t2 = (-b + sqrt(discriminant)) / (2 * a);
			if (t1 <= 0 && t2 <= 0) result = false;
			//�����ڹ��ߵķ�����
			else result = true;
			//����������Ľ���
		}
		hits.insert(result);
	}
	if(hits.find(true) == hits.end()) return false;
	else return true;
}

Vector3f Ray::Tracing(const Vector3f & hitpoint, const Vector3f & normal,const std::vector<Sphere>& objects,int count)
{
	//�ȼ�����������

	//�Է�����߼���׷��

	//ÿ����һ�ν���һ����ɫ�Ļ�ϣ����Ҫ���ݹ�ķ���ֵ�ˣ�

	//��������߲�����κ������ཻ��ﵽ���ݹ����Ϊֹ
	return Vector3f();
}
