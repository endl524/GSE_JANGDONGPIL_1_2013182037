#pragma once


struct Vector2D {
	int x;
	int y;
};

class Object
{
public:
	Object();
	~Object();

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
	
};

