#pragma once
#include "Object.h"
#include "Renderer.h"
#include <vector>
#include <Windows.h>
#include <mmsystem.h>

#define MAX_OBJECTS_COUNT 50;

// add update get

class SceneMgr
{
private:
	int m_maxObjectCount = MAX_OBJECTS_COUNT;
	Object* m_p_Object_RectAngleS[50];
	Renderer* m_p_Renderer;
	
	
public:
	SceneMgr();
	~SceneMgr();

	int getMaxObjectCount() { return m_maxObjectCount; };
	Object** getObject() { return m_p_Object_RectAngleS; };

	void BuildObjects();
	void DrawObjects();
	void ObjectsCollisionCheck();
	void UpdateObjects(DWORD elapsedTime);
	void CheckDeadObject();

	void DestroyObjects();
};