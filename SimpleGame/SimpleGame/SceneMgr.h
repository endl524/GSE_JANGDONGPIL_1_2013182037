#pragma once
#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"

#define MAX_T1_CHAR_COUNT 10
#define MAX_T2_CHAR_COUNT 10
#define MAX_BULLETS_COUNT 100
#define MAX_ARROWS_COUNT 100
#define MAX_T1_BUILDING_COUNT 3
#define MAX_T2_BUILDING_COUNT 3

#define OBJECT_BUILDING 0
#define OBJECT_CHARACTER 1
#define OBJECT_BULLET 2
#define OBJECT_ARROW 3
#define OBJECT_TEAM_1 4
#define OBJECT_TEAM_2 5

class SceneMgr
{
private:
	int m_curT1CharCount = -1;
	int m_curT2CharCount = -1;
	int m_curT1BuildingCount = -1;
	int m_curT2BuildingCount = -1;
	int m_curBulletCount = -1;
	int m_curArrowCount = -1;

	
	Object* m_p_Object_Bullets[MAX_BULLETS_COUNT];
	Object* m_p_Object_T1_Building[MAX_T1_BUILDING_COUNT];
	Object* m_p_Object_T2_Building[MAX_T2_BUILDING_COUNT];

	Object* m_p_Object_Arrows[MAX_ARROWS_COUNT];
	Object* m_p_Object_T1_Char[MAX_T1_CHAR_COUNT];
	Object* m_p_Object_T2_Char[MAX_T2_CHAR_COUNT];

	Renderer* m_p_Renderer;
	
	

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