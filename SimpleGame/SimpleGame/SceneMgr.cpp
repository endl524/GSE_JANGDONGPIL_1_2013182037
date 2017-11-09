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
uniform_int_distribution<> ui_randomVelocityX(-1.0f, 1.0f);
uniform_int_distribution<> ui_randomVelocityY(-1.0f, 1.0f);


// 렌더러와 오브젝트들 생성
SceneMgr::SceneMgr()
{
	m_p_Renderer = new Renderer(500, 500);

	m_p_Object_Building = NULL;

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_p_Object_RectAngleS[i] = NULL;

	for (int i = 0; i < MAX_BULLETS_COUNT; ++i)
		m_p_Object_Bullets[i] = NULL;

	for (int i = 0; i < MAX_ARROWS_COUNT; ++i)
		m_p_Object_Arrows[i] = NULL;
}


SceneMgr::~SceneMgr()
{
}


void SceneMgr::BuildObjects(float x, float y, int type)
{
	switch (type)
	{
	case 0:
		m_p_Object_Building = new Object();
		m_p_Object_Building->setObjectInfo(x, y, 0.0f, 50.0f, 1.0f, 1.0f, 0.0f, 1.0f);
		m_p_Object_Building->setObjectVelocityX(0);
		m_p_Object_Building->setObjectVelocityY(0);
		m_p_Object_Building->setObjcetLife(500.0f);
		m_p_Object_Building->setObjectSpeed(0.0f);

		BuildingTextureID = m_p_Renderer->CreatePngTexture("./Resource/Pig.png");
		break;
	case 1:
		if (m_curObjectCount < MAX_OBJECTS_COUNT - 1)
		{
			++m_curObjectCount;
			m_p_Object_RectAngleS[m_curObjectCount] = new Object();
			m_p_Object_RectAngleS[m_curObjectCount]->setObjectInfo(x, y, 0.0f, 10.0f, 1.0f, 1.0f, 1.0f, 1.0f);
			m_p_Object_RectAngleS[m_curObjectCount]->setObjectVelocityX(ui_randomVelocityX(dre));
			m_p_Object_RectAngleS[m_curObjectCount]->setObjectVelocityY(ui_randomVelocityY(dre));
			if (m_p_Object_RectAngleS[m_curObjectCount]->getObjectVelocity().x == 0.0f && m_p_Object_RectAngleS[m_curObjectCount]->getObjectVelocity().y == 0.0f) {
				m_p_Object_RectAngleS[m_curObjectCount]->setObjectVelocityX(1.0f);
				m_p_Object_RectAngleS[m_curObjectCount]->setObjectVelocityY(1.0f);
			}
			m_p_Object_RectAngleS[m_curObjectCount]->setObjcetLife(10.0f);
			m_p_Object_RectAngleS[m_curObjectCount]->setObjectSpeed(150.0f);
		}
		break;
	case 2:
		if (m_curBulletCount < MAX_BULLETS_COUNT - 1)
		{
			++m_curBulletCount;
			m_p_Object_Bullets[m_curBulletCount] = new Object();
			m_p_Object_Bullets[m_curBulletCount]->setObjectInfo(x, y, 0.0f, 2.0f, 1.0f, 0.0f, 1.0f, 1.0f);
			m_p_Object_Bullets[m_curBulletCount]->setObjectVelocityX(ui_randomVelocityX(dre));
			m_p_Object_Bullets[m_curBulletCount]->setObjectVelocityY(ui_randomVelocityY(dre));
			if (m_p_Object_Bullets[m_curBulletCount]->getObjectVelocity().x == 0.0f && m_p_Object_Bullets[m_curBulletCount]->getObjectVelocity().y == 0.0f) {
				m_p_Object_Bullets[m_curBulletCount]->setObjectVelocityX(1.0f);
				m_p_Object_Bullets[m_curBulletCount]->setObjectVelocityY(1.0f);
			}
			m_p_Object_Bullets[m_curBulletCount]->setObjcetLife(20.0f);
			m_p_Object_Bullets[m_curBulletCount]->setObjectSpeed(300.0f);
		}
		break;
	// 화살 생성시 방향 조정
	case 3:
		if (m_curArrowCount < MAX_ARROWS_COUNT - 1)
		{
			++m_curArrowCount;
			m_p_Object_Arrows[m_curArrowCount] = new Object();
			m_p_Object_Arrows[m_curArrowCount]->setObjectInfo(x, y, 0.0f, 2.0f, 0.0f, 1.0f, 0.0f, 1.0f);
			m_p_Object_Arrows[m_curArrowCount]->setObjectVelocityX(ui_randomVelocityX(dre));
			m_p_Object_Arrows[m_curArrowCount]->setObjectVelocityY(ui_randomVelocityY(dre));
			if (m_p_Object_Arrows[m_curArrowCount]->getObjectVelocity().x == 0.0f && m_p_Object_Arrows[m_curArrowCount]->getObjectVelocity().y == 0.0f) {
				m_p_Object_Arrows[m_curArrowCount]->setObjectVelocityX(1.0f);
				m_p_Object_Arrows[m_curArrowCount]->setObjectVelocityY(1.0f);
			}
			m_p_Object_Arrows[m_curArrowCount]->setObjcetLife(10.0f);
			m_p_Object_Arrows[m_curArrowCount]->setObjectSpeed(100.0f);
		}
	}
};


void SceneMgr::DrawObjects() {
	for (int i = 0; i <= m_curObjectCount; ++i)
	{
		m_p_Renderer->DrawSolidRect(
			m_p_Object_RectAngleS[i]->getObjectPosition_X(), m_p_Object_RectAngleS[i]->getObjectPosition_Y(), m_p_Object_RectAngleS[i]->getObjectPosition_Z(),
			m_p_Object_RectAngleS[i]->getObjectSize(),
			m_p_Object_RectAngleS[i]->getObjectColor_R(), m_p_Object_RectAngleS[i]->getObjectColor_G(), m_p_Object_RectAngleS[i]->getObjectColor_B(), m_p_Object_RectAngleS[i]->getObjectColor_A());
	}

	for (int i = 0; i <= m_curBulletCount; ++i)
	{
		m_p_Renderer->DrawSolidRect(
			m_p_Object_Bullets[i]->getObjectPosition_X(), m_p_Object_Bullets[i]->getObjectPosition_Y(), m_p_Object_Bullets[i]->getObjectPosition_Z(),
			m_p_Object_Bullets[i]->getObjectSize(),
			m_p_Object_Bullets[i]->getObjectColor_R(), m_p_Object_Bullets[i]->getObjectColor_G(), m_p_Object_Bullets[i]->getObjectColor_B(), m_p_Object_Bullets[i]->getObjectColor_A());
	}

	if (m_p_Object_Building != nullptr) 
	{
		m_p_Renderer->DrawTexturedRect
		(
			m_p_Object_Building->getObjectPosition_X(), m_p_Object_Building->getObjectPosition_Y(), m_p_Object_Building->getObjectPosition_Z(),
			m_p_Object_Building->getObjectSize(),
			m_p_Object_Building->getObjectColor_R(), m_p_Object_Building->getObjectColor_G(), m_p_Object_Building->getObjectColor_B(), m_p_Object_Building->getObjectColor_A(),
			BuildingTextureID
		);
	}

	for (int i = 0; i <= m_curArrowCount; ++i)
	{
		m_p_Renderer->DrawSolidRect(
			m_p_Object_Arrows[i]->getObjectPosition_X(), m_p_Object_Arrows[i]->getObjectPosition_Y(), m_p_Object_Arrows[i]->getObjectPosition_Z(),
			m_p_Object_Arrows[i]->getObjectSize(),
			m_p_Object_Arrows[i]->getObjectColor_R(), m_p_Object_Arrows[i]->getObjectColor_G(), m_p_Object_Arrows[i]->getObjectColor_B(), m_p_Object_Arrows[i]->getObjectColor_A());
	}
}


void SceneMgr::ObjectsCollisionCheck() {
	if (m_p_Object_Building != nullptr) {
		m_p_Object_Building->setObjectColor_G(1.0f);
		m_p_Object_Building->setObjectColor_R(1.0f);

		for (int i = 0; i <= m_curObjectCount; ++i)
		{
			// 건물 & 캐릭터 충돌체크
			if (m_p_Object_Building != NULL)
			{
				if (m_p_Object_RectAngleS[i]->getObjectCollider().minX <= m_p_Object_Building->getObjectCollider().maxX
					&&
					m_p_Object_RectAngleS[i]->getObjectCollider().maxX >= m_p_Object_Building->getObjectCollider().minX
					&&
					m_p_Object_RectAngleS[i]->getObjectCollider().minY <= m_p_Object_Building->getObjectCollider().maxY
					&&
					m_p_Object_RectAngleS[i]->getObjectCollider().maxY >= m_p_Object_Building->getObjectCollider().minY)
				{
					m_p_Object_Building->damageObjcetLife(-m_p_Object_RectAngleS[i]->getObjectLife());
					m_p_Object_RectAngleS[i]->damageObjcetLife(-10.0f);
					m_p_Object_Building->setObjectColor_G(0.0f);
				}
			}

			for (int j = 0; j <= m_curBulletCount; ++j)
			{
				// 총알 & 캐릭터 충돌체크
				if (m_p_Object_RectAngleS[i]->getObjectCollider().minX <= m_p_Object_Bullets[j]->getObjectCollider().maxX
					&&
					m_p_Object_RectAngleS[i]->getObjectCollider().maxX >= m_p_Object_Bullets[j]->getObjectCollider().minX
					&&
					m_p_Object_RectAngleS[i]->getObjectCollider().minY <= m_p_Object_Bullets[j]->getObjectCollider().maxY
					&&
					m_p_Object_RectAngleS[i]->getObjectCollider().maxY >= m_p_Object_Bullets[j]->getObjectCollider().minY)
				{
					m_p_Object_RectAngleS[i]->damageObjcetLife(-m_p_Object_Bullets[j]->getObjectLife());
					m_p_Object_Bullets[j]->damageObjcetLife(-20.0f);
				}
			}
			for (int j = 0; j <= m_curArrowCount; ++j)
			{
				// 화살 & 캐릭터 충돌체크
				if (m_p_Object_RectAngleS[i]->getObjectCollider().minX <= m_p_Object_Arrows[j]->getObjectCollider().maxX
					&&
					m_p_Object_RectAngleS[i]->getObjectCollider().maxX >= m_p_Object_Arrows[j]->getObjectCollider().minX
					&&
					m_p_Object_RectAngleS[i]->getObjectCollider().minY <= m_p_Object_Arrows[j]->getObjectCollider().maxY
					&&
					m_p_Object_RectAngleS[i]->getObjectCollider().maxY >= m_p_Object_Arrows[j]->getObjectCollider().minY)
				{
					m_p_Object_RectAngleS[i]->damageObjcetLife(-m_p_Object_Arrows[j]->getObjectLife());
					m_p_Object_Arrows[j]->damageObjcetLife(-10.0f);
				}
			}
		}
		for (int j = 0; j <= m_curArrowCount; ++j)
		{
			// 화살 & 건물 충돌체크
			if (m_p_Object_Building->getObjectCollider().minX <= m_p_Object_Arrows[j]->getObjectCollider().maxX
				&&
				m_p_Object_Building->getObjectCollider().maxX >= m_p_Object_Arrows[j]->getObjectCollider().minX
				&&
				m_p_Object_Building->getObjectCollider().minY <= m_p_Object_Arrows[j]->getObjectCollider().maxY
				&&
				m_p_Object_Building->getObjectCollider().maxY >= m_p_Object_Arrows[j]->getObjectCollider().minY)
			{
				m_p_Object_Building->damageObjcetLife(-m_p_Object_Arrows[j]->getObjectLife());
				m_p_Object_Arrows[j]->damageObjcetLife(-10.0f);
			}
		}
	}
}


void SceneMgr::UpdateObjects(DWORD elapsedTime)
{

	for (int i = 0; i <= m_curObjectCount; ++i)
	{
		m_p_Object_RectAngleS[i]->plusObjectCoolTime(elapsedTime/1000.0f);
		m_p_Object_RectAngleS[i]->update(elapsedTime);
		if (m_p_Object_RectAngleS[i]->getObjectCoolTime() >= 0.5f)
		{
			m_p_Object_RectAngleS[i]->setObjectCoolTime(0.0f);
			BuildObjects
			(
				m_p_Object_RectAngleS[i]->getObjectPosition_X() + m_p_Object_RectAngleS[i]->getObjectVelocity().x * 20.0f, 
				m_p_Object_RectAngleS[i]->getObjectPosition_Y() + m_p_Object_RectAngleS[i]->getObjectVelocity().y * 20.0f, 
				OBJECT_ARROW
			);
		}
	}

	if (m_p_Object_Building != NULL)
	{
		m_p_Object_Building->plusObjectCoolTime(elapsedTime / 1000.0f);
		if (m_p_Object_Building->getObjectCoolTime() >= 0.5f)
		{
			m_p_Object_Building->setObjectCoolTime(0.0f);
			BuildObjects(m_p_Object_Building->getObjectPosition_X(), m_p_Object_Building->getObjectPosition_Y(), OBJECT_BULLET);
		}
	}

	for (int i = 0; i <= m_curBulletCount; ++i)
		m_p_Object_Bullets[i]->update(elapsedTime);

	for (int i = 0; i <= m_curArrowCount; ++i) 
		m_p_Object_Arrows[i]->update(elapsedTime);
		

	ObjectsCollisionCheck();
	CheckDeadObject();
}


void SceneMgr::CheckDeadObject()
{
	for (int i = 0; i <= m_curObjectCount; ++i)
	{
		if (m_p_Object_RectAngleS[i]->getObjectIsDead())
		{
			delete m_p_Object_RectAngleS[i];
			m_p_Object_RectAngleS[i] = nullptr;
			for (int j = i; j <= m_curObjectCount; ++j)
			{
				m_p_Object_RectAngleS[i] = m_p_Object_RectAngleS[j];
			}
			--m_curObjectCount;
			--i;
		}
	}

	for (int i = 0; i <= m_curBulletCount; ++i)
	{
		if (m_p_Object_Bullets[i]->getObjectIsDead())
		{
			delete m_p_Object_Bullets[i];
			m_p_Object_Bullets[i] = nullptr;
			for (int j = i; j <= m_curBulletCount; ++j)
			{
				m_p_Object_Bullets[i] = m_p_Object_Bullets[j];
			}
			--m_curBulletCount;
			--i;
		}
	}

	for (int i = 0; i <= m_curArrowCount; ++i)
	{
		if (m_p_Object_Arrows[i]->getObjectIsDead())
		{
			delete m_p_Object_Arrows[i];
			m_p_Object_Arrows[i] = nullptr;
			for (int j = i; j <= m_curArrowCount; ++j)
			{
				m_p_Object_Arrows[i] = m_p_Object_Arrows[j];
			}
			--m_curArrowCount;
			--i;
		}
	}

	if (m_p_Object_Building != nullptr)
	{
		if (m_p_Object_Building->getObjectIsDead())
		{
			delete m_p_Object_Building;
			m_p_Object_Building = nullptr;
		}
	}
};


void SceneMgr::DestroyObjects()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_p_Object_RectAngleS[i])
		{
			delete m_p_Object_RectAngleS[i];
		}
	}
	for (int i = 0; i < MAX_BULLETS_COUNT; ++i)
	{
		if (m_p_Object_Bullets[i])
		{
			delete m_p_Object_Bullets[i];
		}
	}
	for (int i = 0; i < MAX_ARROWS_COUNT; ++i)
	{
		if (m_p_Object_Arrows[i])
		{
			delete m_p_Object_Arrows[i];
		}
	}
	if (m_p_Object_Building)
	{
		delete m_p_Object_Building;
	}
}