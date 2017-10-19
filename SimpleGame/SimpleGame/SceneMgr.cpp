#include "stdafx.h"
#include "SceneMgr.h"
#include "Object.h"
#include "Renderer.h"

//Renderer* g_Renderer = new Renderer(500,500);

//Object* m_pp_Object_RectAngleS[50];

SceneMgr::SceneMgr()
{
}


SceneMgr::~SceneMgr()
{
}


void SceneMgr::buildObjects() {
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
		m_pp_Object_RectAngleS[i] = new Object();
		m_pp_Object_RectAngleS[i]->setRectInfo(i * 2 + 10, i * 2 + 10, 0, 4, 1, 1, 1, 1);
		m_pp_Object_RectAngleS[i]->setObjectVelocity(2, 3);
	}
};

/*
void SceneMgr::drawObjects() {
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
		g_Renderer->DrawSolidRect(
			m_pp_Object_RectAngleS[i]->getObjectPosition_X(), m_pp_Object_RectAngleS[i]->getObjectPosition_Y(), m_pp_Object_RectAngleS[i]->getObjectPosition_Z(),
			m_pp_Object_RectAngleS[i]->getObjectSize(),
			m_pp_Object_RectAngleS[i]->getObjectColor_R(), m_pp_Object_RectAngleS[i]->getObjectColor_G(), m_pp_Object_RectAngleS[i]->getObjectColor_B(), m_pp_Object_RectAngleS[i]->getObjectColor_A());
	}
}
*/

void SceneMgr::updateObjects() {
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
		m_pp_Object_RectAngleS[i]->update();
	}
}

void SceneMgr::destroyObjects() {
	if (m_pp_Object_RectAngleS)
		delete m_pp_Object_RectAngleS;
}