#include "MyHelper.h"

RECT MyHelper::ToRect(int left, int right, int top, int bottom) {
	RECT r;
	r.left = left;
	r.right = right;
	r.top = top;
	r.bottom = bottom;
	return r;
}

float MyHelper::Clamp(float x, float a, float z) {
	if (x <= a)
		x = a;
	else
		if (x >= z)
			x = z;
	return x;
}
