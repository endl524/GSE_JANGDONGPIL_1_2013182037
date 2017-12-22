#include "stdafx.h"
#include "Object.h"

// 오브젝트 정보 setting
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

// 오브젝트 움직임
void Object::Move(float time) {
	float elapsedTime = time / 1000.f;
	m_objectPosition2D.x += m_objectVelocity.x * elapsedTime * m_objectSpeed;
	m_objectPosition2D.y += m_objectVelocity.y * elapsedTime * m_objectSpeed;
}

// 오브젝트 충돌체 getting
Collider Object::getObjectCollider() { 
	m_objectCollider.minX = m_objectPosition2D.x - m_objectSize / 2.0f;
	m_objectCollider.minY = m_objectPosition2D.y - m_objectSize / 2.0f;
	m_objectCollider.maxX = m_objectPosition2D.x + m_objectSize / 2.0f;
	m_objectCollider.maxY = m_objectPosition2D.y + m_objectSize / 2.0f;
	return m_objectCollider;
}

// 벽 충돌검사
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

// 오브젝트를 향한 정규화된 방향벡터 구하기
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



// 타겟(위치) 받기
void Object::SetTarget(list<Object>* pTargetlist)
{
	float distance;
	float minDistance = 10000000.0f;
	list<Object>::iterator temp_iter;
	bool is_found = false;

	// 리스트 안의 오브젝트들을 살펴본다.
	list<Object>::iterator iter;
	for (iter = pTargetlist->begin(); iter != pTargetlist->end(); ++iter)
	{
		// 서로 다른 팀이면
		if (iter->getObjectID() != this->getObjectID())
		{
			// 둘 사이의 거리를 구한다.
			distance = sqrt
			(
				((getObjectPosition_X() - iter->getObjectPosition_X()) * (getObjectPosition_X() - iter->getObjectPosition_X()))
				+
				((getObjectPosition_Y() - iter->getObjectPosition_Y()) * (getObjectPosition_Y() - iter->getObjectPosition_Y()))
			);

			// 그 중 가장 짧은 거리를 가진 오브젝트를 찾는다.
			if (minDistance > distance)
			{
				minDistance = distance;
				temp_iter = iter;
				is_found = true;
			}
		}
	}

	// 찾았으면
	if (is_found)
	{
		// 좌표를 받아온다.
		m_IsTargetting = true;
		m_TargetPos.x = temp_iter->getObjectPosition_X();
		m_TargetPos.y = temp_iter->getObjectPosition_Y();
	}
};



// 타겟(위치)으로 이동하기
void Object::SetDir_ToTarget()
{
	if (m_IsTargetting)
	{
		m_objectVelocity = GetDirectionVector(m_TargetPos);
	}
};


// 타겟에 도착했다면
void Object::IsArrived()
{
	if (m_IsTargetting)
	{
		// 캐릭터가 타겟에 도달했다면 타겟팅을 취소.
		// = 새로운 타겟을 받아오도록 한다.
		// 타겟 위치는 오차범위 +-20.
		if (m_objectPosition2D.x >= m_TargetPos.x - 20 && m_objectPosition2D.x <= m_TargetPos.x + 20
			&&
			m_objectPosition2D.y >= m_TargetPos.y - 20 && m_objectPosition2D.y <= m_TargetPos.y + 20)
		{
			m_IsTargetting = false;
		}
	}
};


// 업데이트 함수
void Object::update(float elapsedTime)
{
	SetDir_ToTarget();
	Move(elapsedTime);
};