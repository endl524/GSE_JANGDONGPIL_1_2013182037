#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}


Object::~Object()
{
}


void Object::setRectInfo(int x, int y, int z, int size, int r, int g, int b, int a) {
	m_rectLocation_X = x;
	m_rectLocation_Y = y;
	m_rectLocation_Z = z;
	m_rectSize = size;
	m_rectColor_R = r;
	m_rectColor_G = g;
	m_rectColor_B = b;
	m_rectColor_A = a;
}