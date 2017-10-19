<<<<<<< HEAD
#include "stdafx.h"
#include "SceneMgr.h"
#include <iostream>
#include <random>

using namespace std;

// 랜덤엔진
random_device randomDevice;
default_random_engine dre(randomDevice());
uniform_int_distribution<> ui_randomPositionX(-250, 250);
uniform_int_distribution<> ui_randomPositionY(-250, 250);
uniform_int_distribution<> ui_randomVelocityX(-10, 10);
uniform_int_distribution<> ui_randomVelocityY(-10, 10);


// 렌더러와 오브젝트들 생성
SceneMgr::SceneMgr()
{
	m_p_Renderer = new Renderer(500, 500);
	for (int i = 0; i < m_maxObjectCount; ++i)
		m_pp_Object_RectAngleS[i] = new Object();
}


SceneMgr::~SceneMgr()
{
}

// 사각형 50개 set
void SceneMgr::BuildObjects() {
	for (int i = 0; i < m_maxObjectCount; ++i) {
		m_pp_Object_RectAngleS[i]->setObjectInfo(ui_randomPositionX(dre), ui_randomPositionY(dre), 0, 10, 1.0f, 1.0f, 1.0f, 1.0f);
		m_pp_Object_RectAngleS[i]->setObjectVelocity(ui_randomVelocityX(dre), ui_randomVelocityY(dre));
	}
};

// 사각형 50개 draw
void SceneMgr::DrawObjects() {
	for (int i = 0; i < m_maxObjectCount; ++i) {
		m_p_Renderer->DrawSolidRect(
			m_pp_Object_RectAngleS[i]->getObjectPosition_X(), m_pp_Object_RectAngleS[i]->getObjectPosition_Y(), m_pp_Object_RectAngleS[i]->getObjectPosition_Z(),
			m_pp_Object_RectAngleS[i]->getObjectSize(),
			m_pp_Object_RectAngleS[i]->getObjectColor_R(), m_pp_Object_RectAngleS[i]->getObjectColor_G(), m_pp_Object_RectAngleS[i]->getObjectColor_B(), m_pp_Object_RectAngleS[i]->getObjectColor_A());
	}
}

// 사각형 50개 update
void SceneMgr::UpdateObjects() {
	for (int i = 0; i < m_maxObjectCount; ++i) {
		m_pp_Object_RectAngleS[i]->update();
	}
}

// 사각형 50개 delete
void SceneMgr::DestroyObjects() {
	if (m_pp_Object_RectAngleS)
		delete m_pp_Object_RectAngleS;
=======
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
>>>>>>> 778b8e48c3e6a3471fbbb9b862441ae9da03a292
}