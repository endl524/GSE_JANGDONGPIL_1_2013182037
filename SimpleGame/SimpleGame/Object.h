#pragma once


struct Vector2D {
	int x;
	int y;
};

class Object
{
private:
	Vector2D m_objectPosition2D;
	int m_objectPosition_Z;
	int m_objectSize;
	float m_objectColor_R, m_objectColor_G, m_objectColor_B, m_objectColor_A; // 색상
	Vector2D m_objectVelocity; // 속도벡터

public:
	Object();
	~Object();

	// setRectAngle
	void setObjectInfo(int x, int y, int z, int size, float r, float g, float b, float a);

	// position
	int getObjectPosition_X() { return m_objectPosition2D.x; };
	void setObjectPosition_X(int x) { m_objectPosition2D.x = x; };
	int getObjectPosition_Y() { return m_objectPosition2D.y; };
	void setObjectPosition_Y(int y) { m_objectPosition2D.y = y; };
	int getObjectPosition_Z() { return m_objectPosition_Z; };
	void setObjectPosition_Z(int z) { m_objectPosition_Z = z; };

	// size
	int getObjectSize() { return m_objectSize; };
	void setObjectSize(int size) { m_objectSize = size; };

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
	Vector2D getObjectVelocity() { return m_objectVelocity; }
	void setObjectVelocity(int x, int y) { m_objectVelocity.x = x; m_objectVelocity.y = y; }
	void Move(int time);


	// update()
	void update();
};

