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
			ScreenColorBuffer[i][j] = BACKGROUND_COLOR;
	}
}

void Buffer2RealScreen() {					//win api ���Ƶ������buffer��һ��
	for (int i = 0; i < WIN_WIDTH; i++) {
		for (int j = 0; j < WIN_HIGH / 2; j++)
			swap(ScreenColorBuffer[j][i], ScreenColorBuffer[WIN_HIGH - j][i]);
	}
}

