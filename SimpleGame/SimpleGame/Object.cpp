#include "stdafx.h"
#include "Object.h"

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
	if (m_objectCollider.maxX > WINDOWSIZE_WIDTH / 2 - 1 || m_objectCollider.minX < -WINDOWSIZE_WIDTH / 2 + 1 )
	{
		m_objectVelocity.x = -m_objectVelocity.x;
	}
	if (m_objectCollider.maxY > WINDOWSIZE_HEIGHT / 2 - 1 || m_objectCollider.minY < -WINDOWSIZE_HEIGHT / 2 + 1) 
	{
		m_objectVelocity.y = -m_objectVelocity.y;
	}
}

// ������Ʈ�� ���� ����ȭ�� ���⺤�� ���ϱ�
Vector2D Object::GetDirectionVector(Vector2D pObjectPos)
{
	Vector2D NormalizedDir;
	float x = pObjectPos.x - m_objectPosition2D.x;
	float y = pObjectPos.y - m_objectPosition2D.y;
	float size = sqrt(x*x + y*y);

	NormalizedDir.x = x / size;
	NormalizedDir.y = y / size;

	return NormalizedDir;
};



// Ÿ��(��ġ) �ޱ�
void Object::SetTarget(list<Object>* pTargetlist)
{
	float distance;
	float minDistance = 10000000.0f;
	list<Object>::iterator temp_iter;
	bool is_found = false;

	// ����Ʈ ���� ������Ʈ���� ���캻��.
	list<Object>::iterator iter;
	for (iter = pTargetlist->begin(); iter != pTargetlist->end(); ++iter)
	{
		// ���� �ٸ� ���̸�
		if (iter->getObjectID() != this->getObjectID())
		{
			// �� ������ �Ÿ��� ���Ѵ�.
			distance = sqrt
			(
				((getObjectPosition_X() - iter->getObjectPosition_X()) * (getObjectPosition_X() - iter->getObjectPosition_X()))
				+
				((getObjectPosition_Y() - iter->getObjectPosition_Y()) * (getObjectPosition_Y() - iter->getObjectPosition_Y()))
			);

			// �� �� ���� ª�� �Ÿ��� ���� ������Ʈ�� ã�´�.
			if (minDistance > distance)
			{
				minDistance = distance;
				temp_iter = iter;
				is_found = true;
			}
		}
	}

	// ã������
	if (is_found)
	{
		// ��ǥ�� �޾ƿ´�.
		m_IsTargetting = true;
		m_TargetPos.x = temp_iter->getObjectPosition_X();
		m_TargetPos.y = temp_iter->getObjectPosition_Y();
	}
};



// Ÿ��(��ġ)���� �̵��ϱ�
void Object::SetDir_ToTarget()
{
	if (m_IsTargetting)
	{
		m_objectVelocity = GetDirectionVector(m_TargetPos);
	}
};


// Ÿ�ٿ� �����ߴٸ�
void Object::IsArrived()
{
	if (m_IsTargetting)
	{
		// ĳ���Ͱ� Ÿ�ٿ� �����ߴٸ� Ÿ������ ���.
		// = ���ο� Ÿ���� �޾ƿ����� �Ѵ�.
		// Ÿ�� ��ġ�� �������� +-20.
		if (m_objectPosition2D.x >= m_TargetPos.x - 20 && m_objectPosition2D.x <= m_TargetPos.x + 20
			&&
			m_objectPosition2D.y >= m_TargetPos.y - 20 && m_objectPosition2D.y <= m_TargetPos.y + 20)
		{
			m_IsTargetting = false;
		}
	}
};


// ������Ʈ �Լ�
void Object::update(float elapsedTime)
{
	SetDir_ToTarget();
	Move(elapsedTime);
};