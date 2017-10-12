#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}


Object::~Object()
{
}


void Object::setRectInfo(int x, int y, int z, int size, float r, float g, float b, float a) {
	m_rectPosition2D.x = x;
	m_rectPosition2D.y = y;
	m_rectPosition_Z = z;
	m_rectSize = size;
	m_rectColor_R = r;
	m_rectColor_G = g;
	m_rectColor_B = b;
	m_rectColor_A = a;
}

void Object::update() {
	rectMove(1);

}