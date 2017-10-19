<<<<<<< HEAD
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

=======
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

>>>>>>> 778b8e48c3e6a3471fbbb9b862441ae9da03a292
 