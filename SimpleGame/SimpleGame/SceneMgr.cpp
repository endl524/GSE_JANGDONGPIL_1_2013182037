#include "stdafx.h"
#include "SceneMgr.h"

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
	DestroyObjects();
}


void SceneMgr::BuildObjects(float x, float y, int id, int type)
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
			m_p_Object_RectAngleS[m_curObjectCount]->setObjectID(m_curObjectCount);
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
	
	case 3:
		if (m_curArrowCount < MAX_ARROWS_COUNT - 1)
		{
			++m_curArrowCount;
			m_p_Object_Arrows[m_curArrowCount] = new Object();
			m_p_Object_Arrows[m_curArrowCount]->setObjectInfo(x, y, 0.0f, 2.0f, 0.0f, 1.0f, 0.0f, 1.0f);
			m_p_Object_Arrows[m_curArrowCount]->setObjcetLife(10.0f);
			m_p_Object_Arrows[m_curArrowCount]->setObjectSpeed(100.0f);
			m_p_Object_Arrows[m_curArrowCount]->setObjectID(id);
		}
	}
};


void SceneMgr::DrawObjects() {
	if (m_p_Object_Bullets != NULL)
	{
		for (int i = 0; i <= m_curBulletCount; ++i)
		{
			m_p_Renderer->DrawSolidRect(
				m_p_Object_Bullets[i]->getObjectPosition_X(), m_p_Object_Bullets[i]->getObjectPosition_Y(), m_p_Object_Bullets[i]->getObjectPosition_Z(),
				m_p_Object_Bullets[i]->getObjectSize(),
				m_p_Object_Bullets[i]->getObjectColor_R(), m_p_Object_Bullets[i]->getObjectColor_G(), m_p_Object_Bullets[i]->getObjectColor_B(), m_p_Object_Bullets[i]->getObjectColor_A());
		}
	}

	if (m_p_Object_Arrows != NULL)
	{
		for (int i = 0; i <= m_curArrowCount; ++i)
		{
			m_p_Renderer->DrawSolidRect(
				m_p_Object_Arrows[i]->getObjectPosition_X(), m_p_Object_Arrows[i]->getObjectPosition_Y(), m_p_Object_Arrows[i]->getObjectPosition_Z(),
				m_p_Object_Arrows[i]->getObjectSize(),
				m_p_Object_Arrows[i]->getObjectColor_R(), m_p_Object_Arrows[i]->getObjectColor_G(), m_p_Object_Arrows[i]->getObjectColor_B(), m_p_Object_Arrows[i]->getObjectColor_A());
		}
	}

	if (m_p_Object_RectAngleS != NULL)
	{
		for (int i = 0; i <= m_curObjectCount; ++i)
		{
			m_p_Renderer->DrawSolidRect(
				m_p_Object_RectAngleS[i]->getObjectPosition_X(), m_p_Object_RectAngleS[i]->getObjectPosition_Y(), m_p_Object_RectAngleS[i]->getObjectPosition_Z(),
				m_p_Object_RectAngleS[i]->getObjectSize(),
				m_p_Object_RectAngleS[i]->getObjectColor_R(), m_p_Object_RectAngleS[i]->getObjectColor_G(), m_p_Object_RectAngleS[i]->getObjectColor_B(), m_p_Object_RectAngleS[i]->getObjectColor_A());
		}
	}

	if (m_p_Object_Building != NULL)
	{
		m_p_Renderer->DrawTexturedRect
		(
			m_p_Object_Building->getObjectPosition_X(), m_p_Object_Building->getObjectPosition_Y(), m_p_Object_Building->getObjectPosition_Z(),
			m_p_Object_Building->getObjectSize(),
			m_p_Object_Building->getObjectColor_R(), m_p_Object_Building->getObjectColor_G(), m_p_Object_Building->getObjectColor_B(), m_p_Object_Building->getObjectColor_A(),
			BuildingTextureID
		);
	}
}


void SceneMgr::ObjectsCollisionCheck()
{
	for (int i = 0; i <= m_curObjectCount; ++i)
	{
		// 건물 & 캐릭터 충돌체크
		if (m_p_Object_Building != NULL && m_p_Object_RectAngleS != NULL)
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

		// 총알 & 캐릭터 충돌체크
		if (m_p_Object_RectAngleS != NULL && m_p_Object_Bullets != NULL)
		{
			for (int j = 0; j <= m_curBulletCount; ++j)
			{
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
		}

		// 화살 & 캐릭터 충돌체크
		if (m_p_Object_RectAngleS != NULL && m_p_Object_Arrows != NULL)
		{
			for (int j = 0; j <= m_curArrowCount; ++j)
			{
				if (m_p_Object_RectAngleS[i]->getObjectID() != m_p_Object_Arrows[j]->getObjectID()) // id가 다른것만 충돌체크.
				{
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
		}
	}

	if (m_p_Object_Building != NULL && m_p_Object_Arrows != NULL)
	{
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


void SceneMgr::UpdateObjects(float elapsedTime)
{
	// 캐릭터 업데이트
	for (int i = 0; i <= m_curObjectCount; ++i)
	{
		m_p_Object_RectAngleS[i]->plusObjectCoolTime(elapsedTime/1000.0f);
		m_p_Object_RectAngleS[i]->update(elapsedTime);
		if (m_p_Object_RectAngleS[i]->getObjectCoolTime() >= 0.5f) // 0.5초 마다 화살 생성
		{
			m_p_Object_RectAngleS[i]->setObjectCoolTime(0.0f);
			BuildObjects
			(
				m_p_Object_RectAngleS[i]->getObjectPosition_X() + m_p_Object_RectAngleS[i]->getObjectVelocity().x * 20.0f, 
				m_p_Object_RectAngleS[i]->getObjectPosition_Y() + m_p_Object_RectAngleS[i]->getObjectVelocity().y * 20.0f, 
				m_p_Object_RectAngleS[i]->getObjectID(),
				OBJECT_ARROW
			);
			m_p_Object_Arrows[m_curArrowCount]->setObjectVelocityX(m_p_Object_RectAngleS[i]->getObjectVelocity().x);
			m_p_Object_Arrows[m_curArrowCount]->setObjectVelocityY(m_p_Object_RectAngleS[i]->getObjectVelocity().y);
		}
	}

	// 건물 업데이트
	if (m_p_Object_Building != NULL)
	{
		m_p_Object_Building->plusObjectCoolTime(elapsedTime / 1000.0f);
		if (m_p_Object_Building->getObjectCoolTime() >= 0.5f) // 0.5초 마다 총알 생성
		{
			m_p_Object_Building->setObjectCoolTime(0.0f);
			BuildObjects(m_p_Object_Building->getObjectPosition_X(), m_p_Object_Building->getObjectPosition_Y(), 0, OBJECT_BULLET);
		}
	}

	// 총알 업데이트
	if (m_p_Object_Bullets != NULL)
	{
		for (int i = 0; i <= m_curBulletCount; ++i)
			m_p_Object_Bullets[i]->update(elapsedTime);
	}

	// 화살 업데이트
	if (m_p_Object_Arrows != NULL)
	{
		for (int i = 0; i <= m_curArrowCount; ++i)
			m_p_Object_Arrows[i]->update(elapsedTime);
	}

	ObjectsCollisionCheck(); // 충돌 검사
	CheckDeadObject(); // 죽은 오브젝트 검사
}


void SceneMgr::CheckDeadObject()
{
	if (m_p_Object_RectAngleS != nullptr)
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
	}

	if (m_p_Object_Bullets != nullptr)
	{
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
	}

	if (m_p_Object_Arrows != nullptr)
	{
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
	if (m_p_Object_RectAngleS != NULL)
	{
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		{
			if (m_p_Object_RectAngleS[i])
			{
				delete m_p_Object_RectAngleS[i];
			}
		}
	}

	if (m_p_Object_Bullets != NULL)
	{
		for (int i = 0; i < MAX_BULLETS_COUNT; ++i)
		{
			if (m_p_Object_Bullets[i])
			{
				delete m_p_Object_Bullets[i];
			}
		}
	}

	if (m_p_Object_Arrows != NULL)
	{
		for (int i = 0; i < MAX_ARROWS_COUNT; ++i)
		{
			if (m_p_Object_Arrows[i])
			{
				delete m_p_Object_Arrows[i];
			}
		}
	}

	if (m_p_Object_Building != NULL)
	{
		delete m_p_Object_Building;
	}
}