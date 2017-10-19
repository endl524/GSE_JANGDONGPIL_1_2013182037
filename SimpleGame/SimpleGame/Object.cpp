#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}


Object::~Object()
{
}


<<<<<<< HEAD
void Object::setObjectInfo(int x, int y, int z, int size, float r, float g, float b, float a) {
	m_objectPosition2D.x = x;
	m_objectPosition2D.y = y;
	m_objectPosition_Z = z;
	m_objectSize = size;
	m_objectColor_R = r;
	m_objectColor_G = g;
	m_objectColor_B = b;
	m_objectColor_A = a;
}

void Object::Move(int time) {
	m_objectPosition2D.x += m_objectVelocity.x * time;
	m_objectPosition2D.y += m_objectVelocity.y * time;
	if (m_objectPosition2D.x >= 250 || m_objectPosition2D.x <= -250) m_objectVelocity.x = -m_objectVelocity.x;
	if (m_objectPosition2D.y >= 250 || m_objectPosition2D.y <= -250) m_objectVelocity.y = -m_objectVelocity.y;
}

void Object::update() {
	Move(1);
=======
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

>>>>>>> 778b8e48c3e6a3471fbbb9b862441ae9da03a292
}