#include "stdafx.h"
#include "SceneMgr.h"
#include <iostream>
#include <random>

using namespace std;

// 랜덤엔진
random_device randomDevice;
default_random_engine dre(randomDevice());
uniform_int_distribution<> ui_randomPositionX(-240.0f, 240.0f);
uniform_int_distribution<> ui_randomPositionY(-240.0f, 240.0f);
uniform_int_distribution<> ui_randomVelocityX(-200.0f, 200.0f);
uniform_int_distribution<> ui_randomVelocityY(-200.0f, 200.0f);


// 렌더러와 오브젝트들 생성
SceneMgr::SceneMgr()
{
	m_p_Renderer = new Renderer(500, 500);
	for (int i = 0; i < m_maxObjectCount; ++i)
		m_p_Object_RectAngleS[i] = NULL;
}


SceneMgr::~SceneMgr()
{
}


void SceneMgr::BuildObjects(float x, float y) {
	if (m_curObjectCount < m_maxObjectCount-1) {
		++m_curObjectCount;
		m_p_Object_RectAngleS[m_curObjectCount] = new Object();
		m_p_Object_RectAngleS[m_curObjectCount]->setObjectInfo(x, y, 0.0f, 30.0f, 1.0f, 1.0f, 1.0f, 1.0f);
		m_p_Object_RectAngleS[m_curObjectCount]->setObjectVelocityX(ui_randomVelocityX(dre));
		m_p_Object_RectAngleS[m_curObjectCount]->setObjectVelocityY(ui_randomVelocityY(dre));
		if (m_p_Object_RectAngleS[m_curObjectCount]->getObjectVelocity().x == 0.0f)
			m_p_Object_RectAngleS[m_curObjectCount]->setObjectVelocityX(1);
		if (m_p_Object_RectAngleS[m_curObjectCount]->getObjectVelocity().y == 0.0f)
			m_p_Object_RectAngleS[m_curObjectCount]->setObjectVelocityY(1);
	}
};


void SceneMgr::DrawObjects() {
	for (int i = 0; i <= m_curObjectCount; ++i) {
		m_p_Renderer->DrawSolidRect(
			m_p_Object_RectAngleS[i]->getObjectPosition_X(), m_p_Object_RectAngleS[i]->getObjectPosition_Y(), m_p_Object_RectAngleS[i]->getObjectPosition_Z(),
			m_p_Object_RectAngleS[i]->getObjectSize(),
			m_p_Object_RectAngleS[i]->getObjectColor_R(), m_p_Object_RectAngleS[i]->getObjectColor_G(), m_p_Object_RectAngleS[i]->getObjectColor_B(), m_p_Object_RectAngleS[i]->getObjectColor_A());
	}
}


void SceneMgr::ObjectsCollisionCheck() {
	// 기본색 (흰색으로 초기화)
	for (int i = 0; i <= m_curObjectCount; ++i) {
		m_p_Object_RectAngleS[i]->setObjectColor_G(1.0f);
		m_p_Object_RectAngleS[i]->setObjectColor_B(1.0f);
	}

	// 충돌시 색변화 (빨간색)
	for (int i = 0; i <= m_curObjectCount; ++i) {
		for (int j = 0; j <= m_curObjectCount; ++j) {
			if (i != j) {	// 자신과 충돌검사를 하지않음.
				if (m_p_Object_RectAngleS[i]->getObjectCollider().minX <= m_p_Object_RectAngleS[j]->getObjectCollider().maxX
					&&
					m_p_Object_RectAngleS[j]->getObjectCollider().minX <= m_p_Object_RectAngleS[i]->getObjectCollider().maxX
					&&
					m_p_Object_RectAngleS[i]->getObjectCollider().minY <= m_p_Object_RectAngleS[j]->getObjectCollider().maxY
					&&
					m_p_Object_RectAngleS[j]->getObjectCollider().minY <= m_p_Object_RectAngleS[i]->getObjectCollider().maxY)
				{
					m_p_Object_RectAngleS[i]->setObjcetLife(-0.1f);
					m_p_Object_RectAngleS[i]->setObjectColor_G(0.0f);
					m_p_Object_RectAngleS[i]->setObjectColor_B(0.0f);
				}
			}
			
		}
	}
}


void SceneMgr::UpdateObjects(DWORD elapsedTime) {
	for (int i = 0; i <= m_curObjectCount; ++i) {
		m_p_Object_RectAngleS[i]->update(elapsedTime);
		m_p_Object_RectAngleS[i]->setObjcetLife(-0.1f);
	}
	ObjectsCollisionCheck();
	CheckDeadObject();
}


void SceneMgr::CheckDeadObject() {
	for (int i = 0; i <= m_curObjectCount; ++i) {
		if (m_p_Object_RectAngleS[i]->getObjectIsDead()) {
			delete m_p_Object_RectAngleS[i];
			m_p_Object_RectAngleS[i] = nullptr;
			for (int j = i; j <= m_curObjectCount; ++j) {
				m_p_Object_RectAngleS[i] = m_p_Object_RectAngleS[j];
			}
			--m_curObjectCount;
			--i;
		}
	}
};


void SceneMgr::DestroyObjects() {
	if (m_p_Object_RectAngleS)
		delete m_p_Object_RectAngleS;
}