#pragma once

#ifndef _SCREEN_H
#define _SCREEN_H

#define WIN_WIDTH	601
#define WIN_HIGH	601

#include "math_tool.h"

void swap(Vector3f& a, Vector3f& b);

void Buffer2RealScreen();

extern Vector3f ScreenColorBuffer[WIN_HIGH][WIN_WIDTH];


void InitScreen();


#endif