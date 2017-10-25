#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}


Object::~Object()
{
}

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
}


Collider Object::getObjectCollider() { 
	m_objectCollider.minX = m_objectPosition2D.x - m_objectSize / 2;
	m_objectCollider.minY = m_objectPosition2D.y - m_objectSize / 2;
	m_objectCollider.maxX = m_objectPosition2D.x + m_objectSize / 2;
	m_objectCollider.maxY = m_objectPosition2D.y + m_objectSize / 2;
	return m_objectCollider;
}

void Object::WallCollision() {
	if (m_objectPosition2D.x + m_objectSize / 2 >= 250 || m_objectPosition2D.x - m_objectSize / 2 <= -250) m_objectVelocity.x = -m_objectVelocity.x;
	if (m_objectPosition2D.y + m_objectSize / 2 >= 250 || m_objectPosition2D.y - m_objectSize / 2 <= -250) m_objectVelocity.y = -m_objectVelocity.y;
}

void Object::update() {
	Move(1);
	WallCollision();
}