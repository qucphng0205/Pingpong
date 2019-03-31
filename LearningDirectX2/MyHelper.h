#pragma once
#include <Windows.h>
class MyHelper {
public:
	static RECT ToRect(int left, int right, int top, int bottom);
	static float Clamp(float x, float a, float z);
};