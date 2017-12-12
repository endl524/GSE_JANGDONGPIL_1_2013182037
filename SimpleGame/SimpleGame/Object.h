#pragma once
#include "stdafx.h"
#include "Renderer.h"

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
	float m_objectColor_R, m_objectColor_G, m_objectColor_B, m_objectColor_A; // 색상
	Vector2D m_objectVelocity; // 방향벡터
	Collider m_objectCollider;

	float m_objectSpeed;

	float m_objectLife;
	bool m_objectIsDead = false;

	float m_renderLevel;

	float m_objectCoolTime = 0.0f;

	int m_objectID;


	GLuint m_textureID;
	float m_aniCountX;
	float m_aniCountY;
	int m_maxAniSizeX;
	int m_maxAniSizeY;

	int m_ParticleDir;


	int m_ObjectType;
	bool m_IsTargetting = false;
	Vector2D m_TargetPos;

public:
	Object() {};
	~Object() {};

	// setRectAngle
	void setObjectInfo(float x, float y, float z, float size, float r, float g, float b, float a, float l);

	// position
	float getObjectPosition_X() const { return m_objectPosition2D.x; };
	void setObjectPosition_X(float x) { m_objectPosition2D.x = x; };
	float getObjectPosition_Y() const { return m_objectPosition2D.y; };
	void setObjectPosition_Y(float y) { m_objectPosition2D.y = y; };
	float getObjectPosition_Z() const { return m_objectPosition_Z; };
	void setObjectPosition_Z(float z) { m_objectPosition_Z = z; };

	// size
	float getObjectSize() const { return m_objectSize; };
	void setObjectSize(float size) { m_objectSize = size; };

	// color
	float getObjectColor_R() const { return m_objectColor_R; };
	void setObjectColor_R(float r) { m_objectColor_R = r; };
	float getObjectColor_G() const { return m_objectColor_G; };
	void setObjectColor_G(float g) { m_objectColor_G = g; };
	float getObjectColor_B() const { return m_objectColor_B; };
	void setObjectColor_B(float b) { m_objectColor_B = b; };
	float getObjectColor_A() const { return m_objectColor_A; };
	void setObjectColor_A(float a) { m_objectColor_A = a; };

	// Velocity
	Vector2D getObjectVelocity() { return m_objectVelocity; };
	void setObjectVelocityX(float x) { m_objectVelocity.x = x; };
	void setObjectVelocityY(float y) { m_objectVelocity.y = y; };
	void Move(float elapsedTime);
	void setObjectSpeed(float s) { m_objectSpeed = s; };
	float getObjectSpeed() const { return m_objectSpeed; };

	// Collision
	Collider getObjectCollider();
	bool IsCollide(Collider other)
	{
		if (getObjectCollider().minX <= other.maxX	&&	getObjectCollider().maxX >= other.minX	&&	getObjectCollider().minY <= other.maxY	&&	getObjectCollider().maxY >= other.minY)
			return true;
		else return false;
	}
	void WallCollision();

	void damageObjcetLife(float l) { m_objectLife += l; if (m_objectLife <= 0.0f) m_objectIsDead = true; };

	void setObjcetLife(float l) { m_objectLife = l;};
	float getObjectLife() const { return m_objectLife; };
	bool getObjectIsDead() const { return m_objectIsDead; };
	void setObjectIsDead(bool d) { m_objectIsDead = d; };


	// CoolTime
	void setObjectCoolTime(float ct) { m_objectCoolTime = ct; };
	void plusObjectCoolTime(float ct) { m_objectCoolTime += ct; };
	float getObjectCoolTime() const { return m_objectCoolTime; };

	// render level
	void setRenderLevel(float l) { m_renderLevel = l; };
	float getRenderLevel() const { return m_renderLevel; };

	// ID
	void setObjectID(int id) { m_objectID = id; };
	int getObjectID() const { return m_objectID; };


	// Texture
	void setTextureID(int id) { m_textureID = id; };
	int getTextureID() const { return m_textureID; };

	void setAniCountX(int x) { m_aniCountX = x; };
	void plusAniCountX(float x) { m_aniCountX += x; };
	int getAniCountX() const { return m_aniCountX; };

	void setAniCountY(int y) { m_aniCountY = y; };
	void plusAniCountY(float y) { m_aniCountY += y; };
	int getAniCountY() const { return m_aniCountY; };

	void setMaxAniSizeX(int x) { m_maxAniSizeX = x; };
	int getMaxAniSizeX() const { return m_maxAniSizeX; };

	void setMaxAniSizeY(int y) { m_maxAniSizeY = y; };
	int getMaxAniSizeY() const { return m_maxAniSizeY; };

	void setParticleDirY(int y) { m_ParticleDir = y; };
	int getParticleDirY() const { return m_ParticleDir; };



	// AI ======
	int GetObjectType() const { return m_ObjectType; };
	void SetObjectType(int type) { m_ObjectType = type; };

	bool GetIsTargetting() const { return m_IsTargetting; };

	Vector2D GetTargetPos() { return m_TargetPos; };

	// 오브젝트를 향한 정규화된 방향벡터 구하기
	Vector2D GetDirectionVector(Vector2D pObjectPos);

	// 타겟(위치) 받기
	void SetTarget(list<Object>* pTargetlist);

	// 타겟(위치)으로 이동하기
	void SetDir_ToTarget();

	// 타겟에 도착했다면
	void IsArrived();

	// ========


	// update()
	void update(float elapsedTime);
};
