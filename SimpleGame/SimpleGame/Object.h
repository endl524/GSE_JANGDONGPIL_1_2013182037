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

<<<<<<< HEAD
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
=======
	// setRectAngle..
	void setRectInfo(int x, int y, int z, int size, float r, float g, float b, float a);
	// position
	int getRectPosition_X() { return m_rectPosition2D.x; };
	void setRectPosition_X(int x) { m_rectPosition2D.x = x; };
	int getRectPosition_Y() { return m_rectPosition2D.y; };
	void setRectPosition_Y(int y) { m_rectPosition2D.y = y; };
	int getRectPosition_Z() { return m_rectPosition_Z; };
	void setRectPosition_Z(int z) { m_rectPosition_Z = z; };
	// size
	int getRectSize() { return m_rectSize; };
	void setRectSize(int size) { m_rectSize = size; };
	// color
	float getRectColor_R() { return m_rectColor_R; };
	void setRectColor_R(float r) { m_rectColor_R = r; };
	float getRectColor_G() { return m_rectColor_G; };
	void setRectColor_G(float g) { m_rectColor_G = g; };
	float getRectColor_B() { return m_rectColor_B; };
	void setRectColor_B(float b) { m_rectColor_B = b; };
	float getRectColor_A() { return m_rectColor_A; };
	void setRectColor_A(float a) { m_rectColor_A = a; };
	// Velocity
	Vector2D getRectVelocity() { return m_rectVelocity; }
	void setRectVelocity(int x, int y) { m_rectVelocity.x = x; m_rectVelocity.y = y; }
	void rectMove(int time) { 
		m_rectPosition2D.x += m_rectVelocity.x * time;
		m_rectPosition2D.y += m_rectVelocity.y * time;
		if (m_rectPosition2D.x >= 250 || m_rectPosition2D.x <= -250) m_rectVelocity.x = -m_rectVelocity.x;
		if (m_rectPosition2D.y >= 250 || m_rectPosition2D.y <= -250) m_rectVelocity.y = -m_rectVelocity.y;
	}
	// 


	// update()
	void update();


private:

	// m_rectInfo
	Vector2D m_rectPosition2D;
	int m_rectPosition_Z;
	int m_rectSize;
	float m_rectColor_R, m_rectColor_G, m_rectColor_B, m_rectColor_A; // 사각형색상
	Vector2D m_rectVelocity; // 속도벡터
	
>>>>>>> 778b8e48c3e6a3471fbbb9b862441ae9da03a292
};

