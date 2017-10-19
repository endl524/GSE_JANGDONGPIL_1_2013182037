#include "stdafx.h"
#include "SceneMgr.h"
#include <iostream>
#include <random>

using namespace std;

// ��������
random_device randomDevice;
default_random_engine dre(randomDevice());
uniform_int_distribution<> ui_randomPositionX(-250, 250);
uniform_int_distribution<> ui_randomPositionY(-250, 250);
uniform_int_distribution<> ui_randomVelocityX(-10, 10);
uniform_int_distribution<> ui_randomVelocityY(-10, 10);


// �������� ������Ʈ�� ����
SceneMgr::SceneMgr()
{
	m_p_Renderer = new Renderer(500, 500);
	for (int i = 0; i < m_maxObjectCount; ++i)
		m_pp_Object_RectAngleS[i] = new Object();
}


SceneMgr::~SceneMgr()
{
}

// �簢�� 50�� set
void SceneMgr::BuildObjects() {
	for (int i = 0; i < m_maxObjectCount; ++i) {
		m_pp_Object_RectAngleS[i]->setObjectInfo(ui_randomPositionX(dre), ui_randomPositionY(dre), 0, 10, 1.0f, 1.0f, 1.0f, 1.0f);
		m_pp_Object_RectAngleS[i]->setObjectVelocity(ui_randomVelocityX(dre), ui_randomVelocityY(dre));
	}
};

// �簢�� 50�� draw
void SceneMgr::DrawObjects() {
	for (int i = 0; i < m_maxObjectCount; ++i) {
		m_p_Renderer->DrawSolidRect(
			m_pp_Object_RectAngleS[i]->getObjectPosition_X(), m_pp_Object_RectAngleS[i]->getObjectPosition_Y(), m_pp_Object_RectAngleS[i]->getObjectPosition_Z(),
			m_pp_Object_RectAngleS[i]->getObjectSize(),
			m_pp_Object_RectAngleS[i]->getObjectColor_R(), m_pp_Object_RectAngleS[i]->getObjectColor_G(), m_pp_Object_RectAngleS[i]->getObjectColor_B(), m_pp_Object_RectAngleS[i]->getObjectColor_A());
	}
}

// �簢�� 50�� update
void SceneMgr::UpdateObjects() {
	for (int i = 0; i < m_maxObjectCount; ++i) {
		m_pp_Object_RectAngleS[i]->update();
	}
}

// �簢�� 50�� delete
void SceneMgr::DestroyObjects() {
	if (m_pp_Object_RectAngleS)
		delete m_pp_Object_RectAngleS;
}