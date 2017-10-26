#include "stdafx.h"
#include "SceneMgr.h"
#include <iostream>
#include <random>

using namespace std;

// ��������
random_device randomDevice;
default_random_engine dre(randomDevice());
uniform_int_distribution<> ui_randomPositionX(-240.0f, 240.0f);
uniform_int_distribution<> ui_randomPositionY(-240.0f, 240.0f);
uniform_int_distribution<> ui_randomVelocityX(-1.0f, 1.0f);
uniform_int_distribution<> ui_randomVelocityY(-1.0f, 1.0f);


// �������� ������Ʈ�� ����
SceneMgr::SceneMgr()
{
	m_p_Renderer = new Renderer(500, 500);
	for (int i = 0; i < m_maxObjectCount; ++i)
		m_p_Object_RectAngleS[i] = new Object();
}


SceneMgr::~SceneMgr()
{
}

// �簢�� 50�� set
void SceneMgr::BuildObjects() {
	for (int i = 0; i < m_maxObjectCount; ++i) {
		m_p_Object_RectAngleS[i]->setObjectInfo(ui_randomPositionX(dre), ui_randomPositionY(dre), 0.0f, 30.0f, 1.0f, 1.0f, 1.0f, 1.0f);
		m_p_Object_RectAngleS[i]->setObjectVelocityX(ui_randomVelocityX(dre));
		m_p_Object_RectAngleS[i]->setObjectVelocityY(ui_randomVelocityY(dre));
		if (m_p_Object_RectAngleS[i]->getObjectVelocity().x == 0.0f)
			m_p_Object_RectAngleS[i]->setObjectVelocityX(1);
		if (m_p_Object_RectAngleS[i]->getObjectVelocity().y == 0.0f)
			m_p_Object_RectAngleS[i]->setObjectVelocityY(1);
	}
};

// �簢�� 50�� draw
void SceneMgr::DrawObjects() {
	for (int i = 0; i < m_maxObjectCount; ++i) {
		m_p_Renderer->DrawSolidRect(
			m_p_Object_RectAngleS[i]->getObjectPosition_X(), m_p_Object_RectAngleS[i]->getObjectPosition_Y(), m_p_Object_RectAngleS[i]->getObjectPosition_Z(),
			m_p_Object_RectAngleS[i]->getObjectSize(),
			m_p_Object_RectAngleS[i]->getObjectColor_R(), m_p_Object_RectAngleS[i]->getObjectColor_G(), m_p_Object_RectAngleS[i]->getObjectColor_B(), m_p_Object_RectAngleS[i]->getObjectColor_A());
	}
}


void SceneMgr::ObjectsCollisionCheck() {
	// �⺻�� (������� �ʱ�ȭ)
	for (int i = 0; i < m_maxObjectCount; ++i) {
		m_p_Object_RectAngleS[i]->setObjectColor_G(1.0f);
		m_p_Object_RectAngleS[i]->setObjectColor_B(1.0f);
	}

	// �浹�� ����ȭ (������)
	for (int i = 0; i < m_maxObjectCount; ++i) {
		for (int j = 0; j < m_maxObjectCount; ++j) {
			if (i != j) {	// �ڽŰ� �浹�˻縦 ��������.
				if (m_p_Object_RectAngleS[i]->getObjectCollider().minX <= m_p_Object_RectAngleS[j]->getObjectCollider().maxX
					&&
					m_p_Object_RectAngleS[j]->getObjectCollider().minX <= m_p_Object_RectAngleS[i]->getObjectCollider().maxX
					&&
					m_p_Object_RectAngleS[i]->getObjectCollider().minY <= m_p_Object_RectAngleS[j]->getObjectCollider().maxY
					&&
					m_p_Object_RectAngleS[j]->getObjectCollider().minY <= m_p_Object_RectAngleS[i]->getObjectCollider().maxY)
				{
					m_p_Object_RectAngleS[i]->setObjcetLife(-1.0f);
					m_p_Object_RectAngleS[i]->setObjectColor_G(0.0f);
					m_p_Object_RectAngleS[i]->setObjectColor_B(0.0f);
				}
			}
			
		}
	}
}


// �簢�� 50�� Update
void SceneMgr::UpdateObjects(DWORD elapsedTime) {
	for (int i = 0; i < m_maxObjectCount; ++i) {
		m_p_Object_RectAngleS[i]->update(elapsedTime);
	}
	ObjectsCollisionCheck();
	CheckDeadObject();
}


void SceneMgr::CheckDeadObject() {
	for (int i = 0; i < m_maxObjectCount; ++i) {
		if (m_p_Object_RectAngleS[i]->getObjectIsDead()) {
			m_p_Object_RectAngleS[i] = nullptr;
			for (int j = i; j < m_maxObjectCount; ++j) {
				m_p_Object_RectAngleS[i] = m_p_Object_RectAngleS[j];
			}
			--m_maxObjectCount;
			--i;
		}
	}
	if (m_maxObjectCount <= 0) {
		m_maxObjectCount = MAX_OBJECTS_COUNT;
		BuildObjects();
	}
};

// �簢�� 50�� Destroy
void SceneMgr::DestroyObjects() {
	if (m_p_Object_RectAngleS)
		delete m_p_Object_RectAngleS;
}