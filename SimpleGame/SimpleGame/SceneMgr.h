#pragma once
#include "Object.h"
#include "Renderer.h"
#include <vector>
#include <Windows.h>
#include <mmsystem.h>

#define MAX_OBJECTS_COUNT 10
#define MAX_BULLETS_COUNT 100

#define OBJECT_BUILDING 0
#define OBJECT_CHARACTER 1
#define OBJECT_BULLET 2
#define OBJECT_ARROW 3

class SceneMgr
{
private:
	int m_curObjectCount = -1;
	int m_curBulletCount = -1;

	Object* m_p_Object_RectAngleS[MAX_OBJECTS_COUNT];
	Object* m_p_Object_Bullets[MAX_BULLETS_COUNT];
	Object* m_p_Object_Building;
	Renderer* m_p_Renderer;
	
	
public:
	SceneMgr();
	~SceneMgr();

	int getMaxObjectCount() { return MAX_OBJECTS_COUNT; };
	Object** getObject() { return m_p_Object_RectAngleS; };

	int getCurBulletCount() { return m_curBulletCount; };
	bool IsBullet() { if (m_p_Object_Bullets != NULL) return true; };

	void BuildObjects(float x, float y, int type);
	void DrawObjects();
	void ObjectsCollisionCheck();
	void UpdateObjects(DWORD elapsedTime);
	void CheckDeadObject();

	void DestroyObjects();
};