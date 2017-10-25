#include "stdafx.h"
#include "SceneMgr.h"
#include <iostream>
#include <random>

using namespace std;

// 랜덤엔진
random_device randomDevice;
default_random_engine dre(randomDevice());
uniform_int_distribution<> ui_randomPositionX(-240, 240);
uniform_int_distribution<> ui_randomPositionY(-240, 240);
uniform_int_distribution<> ui_randomVelocityX(-7, 7);
uniform_int_distribution<> ui_randomVelocityY(-7, 7);


// 렌더러와 오브젝트들 생성
SceneMgr::SceneMgr()
{
	m_p_Renderer = new Renderer(500, 500);
	for (int i = 0; i < m_maxObjectCount; ++i)
		m_p_Object_RectAngleS[i] = new Object();
}


SceneMgr::~SceneMgr()
{
}

// 사각형 50개 set
void SceneMgr::BuildObjects() {
	for (int i = 0; i < m_maxObjectCount; ++i) {
		m_p_Object_RectAngleS[i]->setObjectInfo(ui_randomPositionX(dre), ui_randomPositionY(dre), 0, 10, 1.0f, 1.0f, 1.0f, 1.0f);
		m_p_Object_RectAngleS[i]->setObjectVelocityX(ui_randomVelocityX(dre));
		m_p_Object_RectAngleS[i]->setObjectVelocityY(ui_randomVelocityY(dre));
	}
};

// 사각형 50개 draw
void SceneMgr::DrawObjects() {
	for (int i = 0; i < m_maxObjectCount; ++i) {
		m_p_Renderer->DrawSolidRect(
			m_p_Object_RectAngleS[i]->getObjectPosition_X(), m_p_Object_RectAngleS[i]->getObjectPosition_Y(), m_p_Object_RectAngleS[i]->getObjectPosition_Z(),
			m_p_Object_RectAngleS[i]->getObjectSize(),
			m_p_Object_RectAngleS[i]->getObjectColor_R(), m_p_Object_RectAngleS[i]->getObjectColor_G(), m_p_Object_RectAngleS[i]->getObjectColor_B(), m_p_Object_RectAngleS[i]->getObjectColor_A());
	}
}


void SceneMgr::ObjectsCollisionCheck() {
	for (int i = 0; i < m_maxObjectCount; ++i) {
		for (int j = 0; j < m_maxObjectCount; ++j) {
			if (i != j) {	// 자신과 충돌검사를 하지않음.
				if (m_p_Object_RectAngleS[i]->getObjectCollider().minX <= m_p_Object_RectAngleS[j]->getObjectCollider().maxX
					&&
					m_p_Object_RectAngleS[j]->getObjectCollider().minX <= m_p_Object_RectAngleS[i]->getObjectCollider().maxX
					&&
					m_p_Object_RectAngleS[i]->getObjectCollider().minY <= m_p_Object_RectAngleS[j]->getObjectCollider().maxY
					&&
					m_p_Object_RectAngleS[j]->getObjectCollider().minY <= m_p_Object_RectAngleS[i]->getObjectCollider().maxY)
				{
					//m_p_Object_RectAngleS[i]->setObjectVelocityX(m_p_Object_RectAngleS[j]->getObjectVelocity().x - m_p_Object_RectAngleS[i]->getObjectVelocity().x);
					//m_p_Object_RectAngleS[j]->setObjectVelocityX(m_p_Object_RectAngleS[i]->getObjectVelocity().x - m_p_Object_RectAngleS[j]->getObjectVelocity().x);
					//m_p_Object_RectAngleS[i]->setObjectVelocityY(m_p_Object_RectAngleS[j]->getObjectVelocity().y - m_p_Object_RectAngleS[i]->getObjectVelocity().y);
					//m_p_Object_RectAngleS[j]->setObjectVelocityY(m_p_Object_RectAngleS[i]->getObjectVelocity().y - m_p_Object_RectAngleS[j]->getObjectVelocity().y);
					m_p_Object_RectAngleS[j]->setObjectColor_G(0.0f);
					m_p_Object_RectAngleS[j]->setObjectColor_B(0.0f);
				}
			}
		}
	}
}


// 사각형 50개 update
void SceneMgr::UpdateObjects() {
	for (int i = 0; i < m_maxObjectCount; ++i) {
		m_p_Object_RectAngleS[i]->update();
	}
	ObjectsCollisionCheck();
}

// 사각형 50개 delete
void SceneMgr::DestroyObjects() {
	if (m_p_Object_RectAngleS)
		delete m_p_Object_RectAngleS;
}