#pragma once
#include <Windows.h>

struct Vector2D {
	float x;
	float y;
};

struct Collider {
	float minX;
	float minY;
	float maxX;
	float maxY;
};

class Object
{
private:
	Vector2D m_objectPosition2D;
	float m_objectPosition_Z;
	float m_objectSize;
	float m_objectColor_R, m_objectColor_G, m_objectColor_B, m_objectColor_A; // ����
	Vector2D m_objectVelocity; // �ӵ�����
	Collider m_objectCollider;

	float m_objectLife = 10.0f;
	bool m_objectIsDead = false;

public:
	Object();
	~Object();

	// setRectAngle
	void setObjectInfo(float x, float y, float z, float size, float r, float g, float b, float a);

	// position
	float getObjectPosition_X() { return m_objectPosition2D.x; };
	void setObjectPosition_X(float x) { m_objectPosition2D.x = x; };
	float getObjectPosition_Y() { return m_objectPosition2D.y; };
	void setObjectPosition_Y(float y) { m_objectPosition2D.y = y; };
	float getObjectPosition_Z() { return m_objectPosition_Z; };
	void setObjectPosition_Z(float z) { m_objectPosition_Z = z; };

	// size
	float getObjectSize() { return m_objectSize; };
	void setObjectSize(float size) { m_objectSize = size; };

	// color
	float getObjectColor_R() { return m_objectColor_R; };
	void setObjectColor_R(float r) { m_objectColor_R = r; };
	float getObjectColor_G() { return m_objectColor_G; };
	void setObjectColor_G(float g) { m_objectColor_G = g; };
	float getObjectColor_B() { return m_objectColor_B; };
	void setObjectColor_B(float b) { m_objectColor_B = b; };
	float getObjectColor_A() { return m_objectColor_A; };
	void setObjectColor_A(float a) { m_objectColor_A = a; };

	// Velocity
	Vector2D getObjectVelocity() { return m_objectVelocity; };
	void setObjectVelocityX(float x) { if (x > 10.0f) x = 10.0f; m_objectVelocity.x = x; };
	void setObjectVelocityY(float y) { if (y > 10.0f) y = 10.0f; m_objectVelocity.y = y; };
	void Move(DWORD elapsedTime);

	// Collision
	Collider getObjectCollider();
	void WallCollision();
	void setObjcetLife(float l) { m_objectLife += l; if (m_objectLife <= 0.0f) m_objectIsDead = true; };
	float getObjectLife() { return m_objectLife; };
	bool getObjectIsDead() { return m_objectIsDead; };

	// update()
	void update(DWORD elapsedTime);
};

