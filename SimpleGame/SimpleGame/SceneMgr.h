#pragma once
#include "Object.h"
#include "Renderer.h"


// add update get

class SceneMgr
{
private:
	int MAX_OBJECTS_COUNT = 50;
	//Object* m_pp_Object_RectAngleS[50];
	
public:
	SceneMgr();
	~SceneMgr();
	void buildObjects();
	//void drawObjects();
	int getMaxObjectCount() { return MAX_OBJECTS_COUNT; };
	Object** getObject() { return m_pp_Object_RectAngleS; };
	void updateObjects();
	void destroyObjects();
	Object* m_pp_Object_RectAngleS[50];
};

 