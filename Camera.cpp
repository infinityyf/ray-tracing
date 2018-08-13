#include "Camera.h"
#include "Screen.h"

Camera::Camera() {}
Camera::~Camera() {}
Camera::Camera(Point pos) {
	this->CameraPosition = pos;
	this->Postion4Calcu = Vector3f(pos.x,pos.y,pos.z);
}

void Camera::lookat(double tarx, double tary, double tarz, double headx, double heady, double headz) {
	Point target(tarx,tary,tarz);
	Vector3f view_z(target, this->CameraPosition);//z轴反向
	view_z.Normalize();
	Vector3f view_y(headx,heady,headz);
	view_y.Normalize();
	Vector3f view_x = Vector3f::CrossMult(view_y, view_z, 1);//Z X Y
	this->N = view_z;
	this->V = view_x;
	this->U = view_y;
}

void Camera::SetProjection(double near, double far, double width_left, double width_right, double height_top, double height_buttom) {
	this->D = near;
	this->F = far;
	this->width_left = width_left;//x
	this->width_right = width_right;
	this->height_top = height_top;//y
	this->height_buttom =height_buttom;
}


//传入一个指针数组
void Camera::GetPixelPos(int level) {
	//在这里实现
	Vector3f CenterPos = this->Postion4Calcu - this->N.NumDot(this->D);
	for (int i = -(WIN_HIGH/2); i < WIN_HIGH/2; i++) {
		for (int j = -(WIN_WIDTH / 2); j < WIN_WIDTH/2; j++) {
			this->PixelPos[i + (WIN_HIGH / 2)][j + (WIN_WIDTH / 2)] = CenterPos + this->V.NumDot(j) + this->U.NumDot(i);
		}
	}
}