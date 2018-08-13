#include "Screen.h"

Vector3f ScreenColorBuffer[WIN_HIGH][WIN_WIDTH] = {};

void swap(Vector3f& a, Vector3f& b) {
	Vector3f temp = a;
	a = b;
	b = a;
}

void InitScreen() {
	for (int i = 0; i < WIN_HIGH; i++) {
		for (int j = 0; j < WIN_WIDTH ; j++)
			ScreenColorBuffer[i][j] = Vector3f(0.62, 0.47, 0.93);
	}
}

void Buffer2RealScreen() {					//win api 绘制的坐标和buffer不一致
	for (int i = 0; i < WIN_WIDTH; i++) {
		for (int j = 0; j < WIN_HIGH / 2; j++)
			swap(ScreenColorBuffer[j][i], ScreenColorBuffer[WIN_HIGH - j][i]);
	}
}

