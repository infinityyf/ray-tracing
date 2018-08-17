#include "Ray.h"
#include "Screen.h"
#include "Object.h"
#include <set>
#include <iterator>
#include <math.h>
#include <climits>//使用内置的最大值

using namespace std;

Ray::Ray(){}

Ray::~Ray(){}

Vector3f SearchPoint(std::vector<RayHit>& HitList, 
	Vector3f& hitpoint, 
	Vector3f& normal,
	int& material) {
	double result = (std::numeric_limits<double>::max)();//这是一个函数
	Vector3f color;
	std::vector<RayHit>::iterator it = HitList.begin();
	for (; it != HitList.end();it++) {
		if ((*it).t <= result) {
			result = (*it).t;
			color = (*it).Color;
			hitpoint = (*it).Hitpoint;
			normal = (*it).Normal;
			material = (*it).material;

		}
	}
	return color;
}

Vector3f MixColor(std::vector<Vector3f>& ColorList,int level) {

	//int/int 结果还是int 这么浅显的问题还折腾这么久
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


//void Ray::scanScreen(Camera& camera , Vector3f (*buffer)[WIN_WIDTH],int level)
//{
//	std::vector<Vector3f>ColorBuffer;
//	int centerX = level / 2;
//	int centerY = level / 2;
//	//多重采样的结果缓存
//	//以上均是为多重采样服务
//	ObjectList* spheres = ObjectList::getInstance();
//	double t;
//	Vector3f HitPoint;
//	Vector3f normal;
//	Vector3f color;
//	bool hit;
//	for (int i = 0; i < WIN_HIGH; i++) {
//		for (int j = 0; j < WIN_WIDTH; j++) {
//			//现在考虑多重采样，根据level 进行多条射线的生成
//			ColorBuffer.clear();
//			bool HitExist = false;
//			//只要有一条线射到了就予以显示
//			for (int m = 0; m < (level*level);m++) {
//				int row = m/level;
//				int col = m%level;
//				//要考虑光线中心的偏移
//				row -= centerX;
//				col -= centerY;
//				Vector3f CurentPos = camera.PixelPos[i][j] + camera.ScreenX.NumDot((double)(col)/level)+ camera.ScreenY.NumDot(-(double)(row)/level);
//				double X = CurentPos.x;
//				double Y = CurentPos.y;
//				double Z = CurentPos.z;
//				//计算每条子射线的目标位置，之后生成射线
//
//				//使用迭代器
//				hit = false;
//				vector<Sphere>::iterator it = (spheres->objects).begin();
//				Ray TestRay(camera.Postion4Calcu, X, Y, Z);
//				for (; it != (spheres->objects).end(); it++) {
//					t = TestRay.HitSpheree((*it).pos_v, (*it).radius);
//					if (t>0) {
//						HitExist = true; //该像素需要上色
//						hit = true;
//						HitPoint = TestRay.GetPoint(t);
//						normal = (*it).GetNormal(HitPoint);
//						color = (*it).GetColor();
//						//
//						//这里后期应该还需要加上颜色
//						RayHit RayHitPoint = { t,HitPoint,normal,color };
//						TestRay.HitPoints.push_back(RayHitPoint);
//						//存储所有的交点
//					}
//				}
//				if (hit) {
//					Vector3f RayColor = SearchPoint(TestRay.HitPoints,HitPoint,normal);
//					ColorBuffer.push_back(RayColor.NumDot((double)255/(level*level)));
//				}
//			}
//			if (HitExist) {
//				Vector3f Mixcolor = MixColor(ColorBuffer,level);
//				buffer[i][j].x = Mixcolor.x;
//				buffer[i][j].y = Mixcolor.y;
//				buffer[i][j].z = Mixcolor.z;
//			}
//
//			////使用迭代器
//			//hit = false;
//			//vector<Sphere>::iterator it = (spheres->objects).begin();
//			//double X = camera.PixelPos[i][j].x;
//			//double Y = camera.PixelPos[i][j].y;
//			//double Z = camera.PixelPos[i][j].z;
//			//Ray TestRay(camera.Postion4Calcu,X,Y,Z);
//			//for (;it!= (spheres->objects).end();it++) {
//			//	t = TestRay.HitSpheree((*it).pos_v, (*it).radius);
//			//	if (t>0) {
//			//		hit = true;
//			//		HitPoint = TestRay.GetPoint(t);
//			//		normal = (*it).GetNormal(HitPoint);
//			//		color = (*it).GetColor();
//			//		RayHit RayHitPoint = { t,HitPoint,normal,color};
//			//		TestRay.HitPoints.push_back(RayHitPoint);
//			//		//存储所有的交点
//			//	}
//			//	if (hit) {
//			//		color = SearchPoint(TestRay.HitPoints);
//			//		buffer[i][j].x = color.x;
//			//		buffer[i][j].y = color.y;
//			//		buffer[i][j].z = color.z;
//			//	}
//			//}
//		}
//	}
//}


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
		return 0.5+0.5*Lambert(normal, toLight);
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
	//多重采样的结果缓存
	//以上均是为多重采样服务
	ObjectList* spheres = ObjectList::getInstance();
	double t;
	double fade = 0;
	Vector3f HitPoint;
	Vector3f normal;
	Vector3f color;
	Vector3f toEye;
	int material;
	Vector3f color0;//环境光反射颜色
	Vector3f color1;//点光源反射颜色
	Vector3f color2;//平行光反射颜色

	bool hit;
	for (int i = 0; i < WIN_HIGH; i++) {
		for (int j = 0; j < WIN_WIDTH; j++) {
			//现在考虑多重采样，根据level 进行多条射线的生成
			ColorBuffer.clear();
			bool HitExist = false;
			//只要有一条线射到了就予以显示
			for (int m = 0; m < (level*level); m++) {
				int row = m / level;
				int col = m%level;
				//要考虑光线中心的偏移
				row -= centerX;
				col -= centerY;
				Vector3f CurentPos = camera.PixelPos[i][j] + camera.ScreenX.NumDot((double)(col) / level) + camera.ScreenY.NumDot(-(double)(row) / level);
				double X = CurentPos.x;
				double Y = CurentPos.y;
				double Z = CurentPos.z;
				//计算每条子射线的目标位置，之后生成射线

				//使用迭代器
				hit = false;
				vector<Sphere>::iterator it = (spheres->objects).begin();
				Ray TestRay(camera.Postion4Calcu, X, Y, Z);
				toEye = TestRay.NormalDirection.NumDot(-1.f);
				for (; it != (spheres->objects).end(); it++) {
					t = TestRay.HitSpheree((*it).pos_v, (*it).radius);
					if (t>0) {
						HitExist = true; //该像素需要上色
						hit = true;
						HitPoint = TestRay.GetPoint(t);
						normal = (*it).GetNormal(HitPoint);
						color = (*it).GetColor();
						material = (*it).GetMaterial();
						
						
						RayHit RayHitPoint = { t,HitPoint,normal,color,material };
						TestRay.HitPoints.push_back(RayHitPoint);
						//存储所有的交点
					}
				}
				if (hit) {
					Vector3f RayColor = SearchPoint(TestRay.HitPoints,HitPoint,normal,material);
					//计算得到最近交点的颜色，坐标，法线的信息
					color0 = RayColor;
					color1 = RayColor;
					color2 = RayColor;
					
					/*计算环境光的影响，计算返回的环境光的颜色,应该算是物体的自发光了,这里进一步考虑环境光遮蔽
					*/
					if (light0.Enable) {
						if (AO_ON) {
							color0 = color0*(light0.LightColor.NumDot(light0.Lightness));
						}
						else color0 = color0*(light0.LightColor.NumDot(light0.Lightness));
					}

					/*计算点光源,直接追踪点光源，不直接产生阴影
					*/
					if (light1.Enable) {
						//设置偏移避免计算误差式部分交点进入球体内部
						Ray ShadowTestRay(HitPoint + normal.NumDot(0.1), light1.Position.x, light1.Position.y, light1.Position.z);
						if (!ShadowTestRay.HidePointLight(spheres->objects)) {
							Vector3f toLight = Vector3f(HitPoint, light1.Position);
							toLight.Normalize();
							color1 = color1*(light1.GetLightness(HitPoint).NumDot(ReflectionModel(material, normal, toEye, toLight)));
						}
						else color1 = Vector3f(0, 0, 0);
						//若被遮挡就不着色，保持环境光,即点光源颜色为0
					}
					else color1 = Vector3f(0, 0, 0);

					/*计算平行光
					*/
					if (light2.Enable) {
						//同样进行阴影测试
						Ray ShadowTestRay(HitPoint + normal.NumDot(0.1), light2.Direction.NumDot(-1.f));
						//生成反向检测线
						if (!ShadowTestRay.HidePointLight(spheres->objects)) {
							Vector3f toLight = ShadowTestRay.direction;
							toLight.Normalize();
							color2 = color2*((light2.GetLightness()).NumDot(ReflectionModel(material, normal, toEye, toLight)));
						}
						else color2 = Vector3f(0, 0, 0);
					}
					else color2 = Vector3f(0, 0, 0);
					color = color0 + color1 + color2;
					//计算第一次反射的基本色
					if (material == lambert) fade = LAMBERT_FADE;
					else if (material == phong) fade = PHONG_FADE;
					else fade = MIRROR_FADE;
					color = color + TestRay.Tracing(HitPoint,normal, spheres->objects,1,light0,light1,light2).NumDot(fade);

					ColorBuffer.push_back(color.NumDot((double)255 / (level*level)));
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

	////实际上是判断这个方程有没有根，如果有2个根就是击中
	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0) return -1;
	else
	{
		//返回距离最近的那个根
		return (-b - sqrt(discriminant)) / (2 * a);

		//也可以返回两个根，计算完法向量之后找和视线夹角为锐角的点为结果
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
		//表示未被遮挡
		else {
			double t1 = (-b - sqrt(discriminant)) / (2 * a);
			double t2 = (-b + sqrt(discriminant)) / (2 * a);
			if (t1 <= 0 && t2 <= 0) result = false;
			//交点在光线的反方向
			else result = true;
			//存在正方向的交点
		}
		hits.insert(result);
	}
	if(hits.find(true) == hits.end()) return false;
	else return true;
}

Vector3f Ray::Tracing(Vector3f & hitpoint, 
	Vector3f & normal,
	std::vector<Sphere>& objects,
	int count,
	EnvironmentLight& light0,
	PointLight& light1,
	DirectLight& light2)
{
	if (count == TRACING_MAX) return Vector3f(0,0,0);
	//当反射光线不会和任何物体相交或达到最大递归深度为止，本次反射作废


	//一些临时变量
	double t;
	double fade;   //光线的衰减
	Vector3f HitPoint;
	Vector3f Normal;
	Vector3f color;
	Vector3f toEye;
	int material;
	Vector3f color0;//环境光反射颜色
	Vector3f color1;//点光源反射颜色
	Vector3f color2;//平行光反射颜色
	bool hit = false;

	//记录射线返回的颜色
	Vector3f RayColor;

	//记录最后的混合结果
	Vector3f FinalColor;

	//先计算出反射光线
	toEye = this->NormalDirection.NumDot(-1.f);
	//这里toEye的意义并没有发生变化

	Vector3f R = normal.NumDot(2.f).NumDot(normal.Mult(toEye)) - toEye;
	//反射光的方向
	Ray ReflectionRay = Ray(hitpoint,R);
	//反射光

	//对反射光线继续追踪
	vector<Sphere>::iterator it = objects.begin();
	for (; it != objects.end(); it++) {
		t = ReflectionRay.HitSpheree((*it).pos_v, (*it).radius);
		if (t > 0) {
			//在计算第一次相交的时候就已经判断过时候需要上色了，这里确认是一定要上色的
			hit = true;
			HitPoint = ReflectionRay.GetPoint(t);
			Normal = (*it).GetNormal(HitPoint);
			color = (*it).GetColor();
			material = (*it).GetMaterial();
			RayHit RayHitPoint = { t,HitPoint,Normal,color ,material};
			ReflectionRay.HitPoints.push_back(RayHitPoint);
			//存储所有的交点
		}
	}
	if (hit) {
		RayColor = SearchPoint(ReflectionRay.HitPoints, HitPoint, Normal, material);
		color0 = RayColor;
		color1 = RayColor;
		color2 = RayColor;
		//这里首先要计算基础色
		/*计算环境光的影响，计算返回的环境光的颜色,应该算是物体的自发光了,这里进一步考虑环境光遮蔽
		*/
		if (light0.Enable) {
			if (AO_ON) {
				color0 = color0*(light0.LightColor.NumDot(light0.Lightness));
			}
			else color0 = color0*(light0.LightColor.NumDot(light0.Lightness));
		}

		/*计算点光源,直接追踪点光源，不直接产生阴影
		*/
		if (light1.Enable) {
			//设置偏移避免计算误差式部分交点进入球体内部
			Ray ShadowTestRay(HitPoint + Normal.NumDot(0.1), light1.Position.x, light1.Position.y, light1.Position.z);
			if (!ShadowTestRay.HidePointLight(objects)) {
				Vector3f toLight = Vector3f(HitPoint, light1.Position);
				toLight.Normalize();
				color1 = color1*(light1.GetLightness(HitPoint).NumDot(ReflectionModel(material, Normal, toEye, toLight)));
				//使用lambert材质
			}
			else color1 = Vector3f(0, 0, 0);
			//若被遮挡就不着色，保持环境光,即点光源颜色为0
		}
		else color1 = Vector3f(0, 0, 0);

		/*计算平行光
		*/
		if (light2.Enable) {
			//同样进行阴影测试
			Ray ShadowTestRay(HitPoint + Normal.NumDot(0.1), light2.Direction.NumDot(-1.f));
			//生成反向检测线
			if (!ShadowTestRay.HidePointLight(objects)) {
				Vector3f toLight = ShadowTestRay.direction;
				toLight.Normalize();
				color2 = color2*((light2.GetLightness()).NumDot(ReflectionModel(material, Normal, toEye, toLight)));
				//使用lambert材质
			}
			else color2 = Vector3f(0, 0, 0);
			//若被遮挡就不着色，保持环境光,即点光源颜色为0
		}
		else color2 = Vector3f(0, 0, 0);
		color = color0 + color1 + color2;
		//计算local colro

		//这里跟踪的是每条射线因此不需要对超采样进行处理


	}
	//得到反射线相交物体的颜色
	else return Vector3f(0,0,0);
	//如果没有相交则返回0 结束递归

	//每反射一次进行一次颜色的混合（这个要看递归的返回值了）
	if (material == lambert) fade = LAMBERT_FADE;
	else if (material == phong) fade = PHONG_FADE;
	else fade = MIRROR_FADE;
	FinalColor = color + (ReflectionRay.Tracing(HitPoint,Normal,objects,count+1,light0,light1,light2)).NumDot(fade);
	//local color + tracing color
	//进一步考虑光线强度的衰减
	
	return FinalColor;
}
