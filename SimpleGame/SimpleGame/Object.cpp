#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}


Object::~Object()
{
}

// ������Ʈ ���� setting
void Object::setObjectInfo(float x, float y, float z, float size, float r, float g, float b, float a, float l) {
	m_objectPosition2D.x = x;
	m_objectPosition2D.y = y;
	m_objectPosition_Z = z;
	m_objectSize = size;
	m_objectColor_R = r;
	m_objectColor_G = g;
	m_objectColor_B = b;
	m_objectColor_A = a;
	m_renderLevel = l;
}

// ������Ʈ ������
void Object::Move(float time) {
	float elapsedTime = time / 1000.f;
	m_objectPosition2D.x += m_objectVelocity.x * elapsedTime * m_objectSpeed;
	m_objectPosition2D.y += m_objectVelocity.y * elapsedTime * m_objectSpeed;
}

// ������Ʈ �浹ü getting
Collider Object::getObjectCollider() { 
	m_objectCollider.minX = m_objectPosition2D.x - m_objectSize / 2.0f;
	m_objectCollider.minY = m_objectPosition2D.y - m_objectSize / 2.0f;
	m_objectCollider.maxX = m_objectPosition2D.x + m_objectSize / 2.0f;
	m_objectCollider.maxY = m_objectPosition2D.y + m_objectSize / 2.0f;
	return m_objectCollider;
}

// �� �浹�˻�
void Object::WallCollision() {
	getObjectCollider();
	if (m_objectCollider.maxX > WINDOWSIZE_WIDTH / 2 || m_objectCollider.minX < -WINDOWSIZE_WIDTH / 2)
	{
		m_objectVelocity.x = -m_objectVelocity.x;
	}
	if (m_objectCollider.maxY > WINDOWSIZE_HEIGHT/2 || m_objectCollider.minY < -WINDOWSIZE_HEIGHT/2) 
	{
		m_objectVelocity.y = -m_objectVelocity.y;
	}
}

// ������Ʈ �Լ�
void Object::update(float elapsedTime) {
	Move(elapsedTime);
}