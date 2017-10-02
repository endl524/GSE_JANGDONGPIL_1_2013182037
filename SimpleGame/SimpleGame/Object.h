#pragma once
class Object
{
public:
	Object();
	~Object();

	// setRectAngle..
	void setRectInfo(int x, int y, int z, int size, int r, int g, int b, int a);
	//
	int getRectLocation_X() { return m_rectLocation_X; };
	void setRectLocation_X(int x) { m_rectLocation_X = x; };
	int getRectLocation_Y() { return m_rectLocation_Y; };
	void setRectLocation_Y(int y) { m_rectLocation_Y = y; };
	int getRectLocation_Z() { return m_rectLocation_Z; };
	void setRectLocation_Z(int z) { m_rectLocation_Z = z; };
	//
	int getRectSize() { return m_rectSize; };
	void setRectSize(int size) { m_rectSize = size; };
	//
	int getRectColor_R() { return m_rectColor_R; };
	void setRectColor_R(int r) { m_rectColor_R = r; };
	int getRectColor_G() { return m_rectColor_G; };
	void setRectColor_G(int g) { m_rectColor_G = g; };
	int getRectColor_B() { return m_rectColor_B; };
	void setRectColor_B(int b) { m_rectColor_B = b; };
	int getRectColor_A() { return m_rectColor_A; };
	void setRectColor_A(int a) { m_rectColor_A = a; };
	//

private:
	int m_rectLocation_X, m_rectLocation_Y, m_rectLocation_Z;
	int m_rectSize;
	int m_rectColor_R, m_rectColor_G, m_rectColor_B, m_rectColor_A;
	
};

