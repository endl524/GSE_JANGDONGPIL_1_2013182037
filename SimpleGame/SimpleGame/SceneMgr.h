#pragma once
#include "Object.h"
#include "Renderer.h"

#define MAX_OBJECTS_COUNT 50;

// add update get

class SceneMgr
{
private:
	int m_maxObjectCount = MAX_OBJECTS_COUNT;
	Object* m_pp_Object_RectAngleS[50];
	Renderer* m_p_Renderer;
	
	
public:
	SceneMgr();
	~SceneMgr();

	int getMaxObjectCount() { return m_maxObjectCount; };
	Object** getObject() { return m_pp_Object_RectAngleS; };

	void BuildObjects();
	void DrawObjects();
	void UpdateObjects();
	void DestroyObjects();
};