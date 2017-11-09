#pragma once
#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"


#define MAX_OBJECTS_COUNT 10
#define MAX_BULLETS_COUNT 100
#define MAX_ARROWS_COUNT 100

#define OBJECT_BUILDING 0
#define OBJECT_CHARACTER 1
#define OBJECT_BULLET 2
#define OBJECT_ARROW 3

class SceneMgr
{
private:
	int m_curObjectCount = -1;
	int m_curBulletCount = -1;
	int m_curArrowCount = -1;

	Object* m_p_Object_RectAngleS[MAX_OBJECTS_COUNT];
	Object* m_p_Object_Bullets[MAX_BULLETS_COUNT];
	Object* m_p_Object_Building;
	Object* m_p_Object_Arrows[MAX_ARROWS_COUNT];

	Renderer* m_p_Renderer;
	
	GLuint BuildingTextureID;

	float elapsedTime;
	
public:
	SceneMgr();
	~SceneMgr();

	void BuildObjects(float x, float y, int id, int type);
	void DrawObjects();
	void ObjectsCollisionCheck();
	void UpdateObjects(float elapsedTime);
	void CheckDeadObject();


	void setElapsedTime(float t) { elapsedTime = t; };
	float getElapsedTime() { return elapsedTime; };

	void DestroyObjects();
};