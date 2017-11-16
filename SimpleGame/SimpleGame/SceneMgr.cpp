#include "stdafx.h"
#include "SceneMgr.h"

// 랜덤엔진
random_device randomDevice;
default_random_engine dre(randomDevice());
uniform_int_distribution<> ui_randomVelocityX(-1.0f, 1.0f);
uniform_int_distribution<> ui_randomVelocityY(-1.0f, 1.0f);


// 렌더러와 오브젝트들 생성
SceneMgr::SceneMgr()
{
	m_p_Renderer = new Renderer(WINDOWSIZE_WIDTH, WINDOWSIZE_HEIGHT);

	for (int i = 0; i < MAX_T1_BUILDING_COUNT; ++i)
		m_p_Object_T1_Building[i] = NULL;

	for (int i = 0; i < MAX_T2_BUILDING_COUNT; ++i)
		m_p_Object_T2_Building[i] = NULL;

	for (int i = 0; i < MAX_T1_CHAR_COUNT; ++i)
		m_p_Object_T1_Char[i] = NULL;

	for (int i = 0; i < MAX_T2_CHAR_COUNT; ++i)
		m_p_Object_T2_Char[i] = NULL;

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
	case OBJECT_BUILDING:
		if (id == OBJECT_TEAM_1)
		{
			for (int i = 0; i < MAX_T1_BUILDING_COUNT; ++i)
			{
				++m_curT1BuildingCount;
				m_p_Object_T1_Building[i] = new Object();
				m_p_Object_T1_Building[i]->setObjectInfo(x + i * 150.0f, y, 0.0f, 50.0f, 1.0f, 1.0f, 0.0f, 1.0f);
				m_p_Object_T1_Building[i]->setObjectVelocityX(0);
				m_p_Object_T1_Building[i]->setObjectVelocityY(0);
				m_p_Object_T1_Building[i]->setObjcetLife(500.0f);
				m_p_Object_T1_Building[i]->setObjectSpeed(0.0f);
				m_p_Object_T1_Building[i]->setObjectID(OBJECT_TEAM_1);
				m_p_Object_T1_Building[i]->setTextureID(m_p_Renderer->CreatePngTexture("./Resource/Pig.png"));
			}
		}

		else if (id == OBJECT_TEAM_2)
		{
			for (int i = 0; i < MAX_T2_BUILDING_COUNT; ++i)
			{
				++m_curT2BuildingCount;
				m_p_Object_T2_Building[i] = new Object();
				m_p_Object_T2_Building[i]->setObjectInfo(x + i * 150.0f, y, 0.0f, 50.0f, 1.0f, 1.0f, 0.0f, 1.0f);
				m_p_Object_T2_Building[i]->setObjectVelocityX(0);
				m_p_Object_T2_Building[i]->setObjectVelocityY(0);
				m_p_Object_T2_Building[i]->setObjcetLife(500.0f);
				m_p_Object_T2_Building[i]->setObjectSpeed(0.0f);
				m_p_Object_T2_Building[i]->setObjectID(OBJECT_TEAM_2);
				m_p_Object_T2_Building[i]->setTextureID(m_p_Renderer->CreatePngTexture("./Resource/AngryBird.png"));
			}
		}

		break;

	case OBJECT_CHARACTER:
		if (id == OBJECT_TEAM_1)
		{
			if (m_curT1CharCount < MAX_T1_CHAR_COUNT - 1)
			{
				++m_curT1CharCount;
				m_p_Object_T1_Char[m_curT1CharCount] = new Object();
				m_p_Object_T1_Char[m_curT1CharCount]->setObjectInfo(x, y, 0.0f, 10.0f, 1.0f, 0.0f, 0.0f, 1.0f);
				m_p_Object_T1_Char[m_curT1CharCount]->setObjectVelocityX(ui_randomVelocityX(dre));
				m_p_Object_T1_Char[m_curT1CharCount]->setObjectVelocityY(ui_randomVelocityY(dre));
				if (m_p_Object_T1_Char[m_curT1CharCount]->getObjectVelocity().x == 0.0f && m_p_Object_T1_Char[m_curT1CharCount]->getObjectVelocity().y == 0.0f) {
					m_p_Object_T1_Char[m_curT1CharCount]->setObjectVelocityX(1.0f);
					m_p_Object_T1_Char[m_curT1CharCount]->setObjectVelocityY(1.0f);
				}
				m_p_Object_T1_Char[m_curT1CharCount]->setObjcetLife(10.0f);
				m_p_Object_T1_Char[m_curT1CharCount]->setObjectSpeed(150.0f);
				m_p_Object_T1_Char[m_curT1CharCount]->setObjectID(OBJECT_TEAM_1);
			}
		}

		else if (id == OBJECT_TEAM_2)
		{
			if (m_curT2CharCount < MAX_T2_CHAR_COUNT - 1)
			{
				++m_curT2CharCount;
				m_p_Object_T2_Char[m_curT2CharCount] = new Object();
				m_p_Object_T2_Char[m_curT2CharCount]->setObjectInfo(x, y, 0.0f, 10.0f, 0.0f, 0.0f, 1.0f, 1.0f);
				m_p_Object_T2_Char[m_curT2CharCount]->setObjectVelocityX(ui_randomVelocityX(dre));
				m_p_Object_T2_Char[m_curT2CharCount]->setObjectVelocityY(ui_randomVelocityY(dre));
				if (m_p_Object_T2_Char[m_curT2CharCount]->getObjectVelocity().x == 0.0f && m_p_Object_T2_Char[m_curT2CharCount]->getObjectVelocity().y == 0.0f) {
					m_p_Object_T2_Char[m_curT2CharCount]->setObjectVelocityX(1.0f);
					m_p_Object_T2_Char[m_curT2CharCount]->setObjectVelocityY(1.0f);
				}
				m_p_Object_T2_Char[m_curT2CharCount]->setObjcetLife(10.0f);
				m_p_Object_T2_Char[m_curT2CharCount]->setObjectSpeed(150.0f);
				m_p_Object_T2_Char[m_curT2CharCount]->setObjectID(OBJECT_TEAM_2);
			}
		}

		break;

	case OBJECT_BULLET:
		if (m_curBulletCount < MAX_BULLETS_COUNT - 1)
		{
			++m_curBulletCount;
			m_p_Object_Bullets[m_curBulletCount] = new Object();
			if (id == OBJECT_TEAM_1)
				m_p_Object_Bullets[m_curBulletCount]->setObjectInfo(x, y, 0.0f, 2.0f, 1.0f, 0.0f, 0.0f, 1.0f);
			else if (id == OBJECT_TEAM_2)
				m_p_Object_Bullets[m_curBulletCount]->setObjectInfo(x, y, 0.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f);
			m_p_Object_Bullets[m_curBulletCount]->setObjectVelocityX(ui_randomVelocityX(dre));
			m_p_Object_Bullets[m_curBulletCount]->setObjectVelocityY(ui_randomVelocityY(dre));
			if (m_p_Object_Bullets[m_curBulletCount]->getObjectVelocity().x == 0.0f && m_p_Object_Bullets[m_curBulletCount]->getObjectVelocity().y == 0.0f) {
				m_p_Object_Bullets[m_curBulletCount]->setObjectVelocityX(1.0f);
				m_p_Object_Bullets[m_curBulletCount]->setObjectVelocityY(1.0f);
			}
			m_p_Object_Bullets[m_curBulletCount]->setObjcetLife(20.0f);
			m_p_Object_Bullets[m_curBulletCount]->setObjectSpeed(300.0f);
			m_p_Object_Bullets[m_curBulletCount]->setObjectID(id);
		}

		break;

	case OBJECT_ARROW:
		if (m_curArrowCount < MAX_ARROWS_COUNT - 1)
		{
			++m_curArrowCount;
			m_p_Object_Arrows[m_curArrowCount] = new Object();
			m_p_Object_Arrows[m_curArrowCount]->setObjectInfo(x, y, 0.0f, 2.0f, 0.0f, 1.0f, 0.0f, 1.0f);
			m_p_Object_Arrows[m_curArrowCount]->setObjcetLife(10.0f);
			m_p_Object_Arrows[m_curArrowCount]->setObjectSpeed(100.0f);
			m_p_Object_Arrows[m_curArrowCount]->setObjectID(id);
		}
		break;
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

	if (m_p_Object_T1_Char != NULL)
	{
		for (int i = 0; i <= m_curT1CharCount; ++i)
		{
			m_p_Renderer->DrawSolidRect(
				m_p_Object_T1_Char[i]->getObjectPosition_X(), m_p_Object_T1_Char[i]->getObjectPosition_Y(), m_p_Object_T1_Char[i]->getObjectPosition_Z(),
				m_p_Object_T1_Char[i]->getObjectSize(),
				m_p_Object_T1_Char[i]->getObjectColor_R(), m_p_Object_T1_Char[i]->getObjectColor_G(), m_p_Object_T1_Char[i]->getObjectColor_B(), m_p_Object_T1_Char[i]->getObjectColor_A());
		}
	}
	if (m_p_Object_T2_Char != NULL)
	{
		for (int i = 0; i <= m_curT2CharCount; ++i)
		{
			cout << "d" << endl;
			m_p_Renderer->DrawSolidRect(
				m_p_Object_T2_Char[i]->getObjectPosition_X(), m_p_Object_T2_Char[i]->getObjectPosition_Y(), m_p_Object_T2_Char[i]->getObjectPosition_Z(),
				m_p_Object_T2_Char[i]->getObjectSize(),
				m_p_Object_T2_Char[i]->getObjectColor_R(), m_p_Object_T2_Char[i]->getObjectColor_G(), m_p_Object_T2_Char[i]->getObjectColor_B(), m_p_Object_T2_Char[i]->getObjectColor_A());
		}
	}

	if (m_p_Object_T1_Building != NULL)
	{
		for (int i = 0; i < MAX_T1_BUILDING_COUNT; ++i)
		{
			m_p_Renderer->DrawTexturedRect
			(
				m_p_Object_T1_Building[i]->getObjectPosition_X(), m_p_Object_T1_Building[i]->getObjectPosition_Y(), m_p_Object_T1_Building[i]->getObjectPosition_Z(),
				m_p_Object_T1_Building[i]->getObjectSize(),
				m_p_Object_T1_Building[i]->getObjectColor_R(), m_p_Object_T1_Building[i]->getObjectColor_G(), m_p_Object_T1_Building[i]->getObjectColor_B(), m_p_Object_T1_Building[i]->getObjectColor_A(),
				m_p_Object_T1_Building[i]->getTextureID()
			);
		}
	}
	if (m_p_Object_T2_Building != NULL)
	{
		for (int i = 0; i < MAX_T2_BUILDING_COUNT; ++i)
		{
			m_p_Renderer->DrawTexturedRect
			(
				m_p_Object_T2_Building[i]->getObjectPosition_X(), m_p_Object_T2_Building[i]->getObjectPosition_Y(), m_p_Object_T2_Building[i]->getObjectPosition_Z(),
				m_p_Object_T2_Building[i]->getObjectSize(),
				m_p_Object_T2_Building[i]->getObjectColor_R(), m_p_Object_T2_Building[i]->getObjectColor_G(), m_p_Object_T2_Building[i]->getObjectColor_B(), m_p_Object_T2_Building[i]->getObjectColor_A(),
				m_p_Object_T2_Building[i]->getTextureID()
			);
		}
	}
}


void SceneMgr::ObjectsCollisionCheck()
{
	// T1
	for (int i = 0; i <= m_curT1CharCount; ++i)
	{
		// 건물 & 캐릭터 충돌체크
		for (int j = 0; j < m_curT2BuildingCount; ++j)
		if (m_p_Object_T2_Building != NULL && m_p_Object_T1_Char != NULL)
		{
			if (m_p_Object_T1_Char[i]->IsCollide ( m_p_Object_T1_Char[i]->getObjectCollider() ) )
			{
				m_p_Object_T2_Building[j]->damageObjcetLife(-m_p_Object_T1_Char[i]->getObjectLife());
				m_p_Object_T1_Char[i]->damageObjcetLife(-10.0f);
			}
		}

		// 총알 & 캐릭터 충돌체크
		if (m_p_Object_T1_Char != NULL && m_p_Object_Bullets != NULL)
		{
			for (int j = 0; j <= m_curBulletCount; ++j)
			{
				if (m_p_Object_T1_Char[i]->getObjectID() != m_p_Object_Bullets[j]->getObjectID()
					&&
					m_p_Object_T1_Char[i]->IsCollide(m_p_Object_Bullets[j]->getObjectCollider()))
				{
					m_p_Object_T1_Char[i]->damageObjcetLife(-m_p_Object_Bullets[j]->getObjectLife());
					m_p_Object_Bullets[j]->damageObjcetLife(-20.0f);
				}
			}
		}

		// 화살 & 캐릭터 충돌체크
		if (m_p_Object_T1_Char != NULL && m_p_Object_Arrows != NULL)
		{
			for (int j = 0; j <= m_curArrowCount; ++j)
			{
				if (m_p_Object_T1_Char[i]->getObjectID() != m_p_Object_Arrows[j]->getObjectID()
					&& // id가 다른것만 충돌체크.
					m_p_Object_T1_Char[i]->IsCollide(m_p_Object_Arrows[j]->getObjectCollider()))
					{
						m_p_Object_T1_Char[i]->damageObjcetLife(-m_p_Object_Arrows[j]->getObjectLife());
						m_p_Object_Arrows[j]->damageObjcetLife(-10.0f);
					}
			}
		}
	}

	for (int i = 0; i < m_curT1BuildingCount; ++i)
	{
		if (m_p_Object_T1_Building != NULL && m_p_Object_Arrows != NULL)
		{
			for (int j = 0; j <= m_curArrowCount; ++j)
			{
				// 화살 & 건물 충돌체크
				if (m_p_Object_T1_Building[i]->getObjectID() != m_p_Object_Arrows[j]->getObjectID()
					&&
					m_p_Object_T1_Building[i]->IsCollide(m_p_Object_Arrows[j]->getObjectCollider()))
				{
					m_p_Object_T1_Building[i]->damageObjcetLife(-m_p_Object_Arrows[j]->getObjectLife());
					m_p_Object_Arrows[j]->damageObjcetLife(-10.0f);
				}
			}
		}
	}


	// T2
	for (int i = 0; i <= m_curT2CharCount; ++i)
	{
		// 건물 & 캐릭터 충돌체크
		for (int j = 0; j < m_curT1BuildingCount; ++j)
			if (m_p_Object_T1_Building != NULL && m_p_Object_T2_Char != NULL)
			{
				if (m_p_Object_T2_Char[i]->IsCollide(m_p_Object_T2_Char[i]->getObjectCollider()))
				{
					m_p_Object_T1_Building[j]->damageObjcetLife(-m_p_Object_T2_Char[i]->getObjectLife());
					m_p_Object_T2_Char[i]->damageObjcetLife(-10.0f);
				}
			}

		// 총알 & 캐릭터 충돌체크
		if (m_p_Object_T2_Char != NULL && m_p_Object_Bullets != NULL)
		{
			for (int j = 0; j <= m_curBulletCount; ++j)
			{
				if (m_p_Object_T2_Char[i]->getObjectID() != m_p_Object_Bullets[j]->getObjectID()
					&&
					m_p_Object_T2_Char[i]->IsCollide(m_p_Object_Bullets[j]->getObjectCollider()))
				{
					m_p_Object_T2_Char[i]->damageObjcetLife(-m_p_Object_Bullets[j]->getObjectLife());
					m_p_Object_Bullets[j]->damageObjcetLife(-20.0f);
				}
			}
		}

		// 화살 & 캐릭터 충돌체크
		if (m_p_Object_T2_Char != NULL && m_p_Object_Arrows != NULL)
		{
			for (int j = 0; j <= m_curArrowCount; ++j)
			{
				if (m_p_Object_T2_Char[i]->getObjectID() != m_p_Object_Arrows[j]->getObjectID()
					&& // id가 다른것만 충돌체크.
					m_p_Object_T2_Char[i]->IsCollide(m_p_Object_Arrows[j]->getObjectCollider()))
				{
					m_p_Object_T2_Char[i]->damageObjcetLife(-m_p_Object_Arrows[j]->getObjectLife());
					m_p_Object_Arrows[j]->damageObjcetLife(-10.0f);
				}
			}
		}
	}

	for (int i = 0; i < m_curT2BuildingCount; ++i)
	{
		if (m_p_Object_T2_Building != NULL && m_p_Object_Arrows != NULL)
		{
			for (int j = 0; j <= m_curArrowCount; ++j)
			{
				// 화살 & 건물 충돌체크
				if (m_p_Object_T2_Building[i]->getObjectID() != m_p_Object_Arrows[j]->getObjectID()
					&&
					m_p_Object_T2_Building[i]->IsCollide(m_p_Object_Arrows[j]->getObjectCollider()))
				{
					m_p_Object_T2_Building[i]->damageObjcetLife(-m_p_Object_Arrows[j]->getObjectLife());
					m_p_Object_Arrows[j]->damageObjcetLife(-10.0f);
				}
			}
		}
	}
}


void SceneMgr::UpdateObjects(float elapsedTime)
{

	// 캐릭터 업데이트
	for (int i = 0; i <= m_curT1CharCount; ++i)
	{
		m_p_Object_T1_Char[i]->plusObjectCoolTime(elapsedTime/1000.0f);
		m_p_Object_T1_Char[i]->update(elapsedTime);
		if (m_p_Object_T1_Char[i]->getObjectCoolTime() >= 0.5f) // 0.5초 마다 화살 생성
		{
			m_p_Object_T1_Char[i]->setObjectCoolTime(0.0f);
			BuildObjects
			(
				m_p_Object_T1_Char[i]->getObjectPosition_X() + m_p_Object_T1_Char[i]->getObjectVelocity().x * 20.0f,
				m_p_Object_T1_Char[i]->getObjectPosition_Y() + m_p_Object_T1_Char[i]->getObjectVelocity().y * 20.0f,
				m_p_Object_T1_Char[i]->getObjectID(),
				OBJECT_ARROW
			);
			m_p_Object_Arrows[m_curArrowCount]->setObjectVelocityX(m_p_Object_T1_Char[i]->getObjectVelocity().x);
			m_p_Object_Arrows[m_curArrowCount]->setObjectVelocityY(m_p_Object_T1_Char[i]->getObjectVelocity().y);
		}
	}

	for (int i = 0; i <= m_curT2CharCount; ++i)
	{
		m_p_Object_T2_Char[i]->plusObjectCoolTime(elapsedTime / 1000.0f);
		m_p_Object_T2_Char[i]->update(elapsedTime);
		if (m_p_Object_T2_Char[i]->getObjectCoolTime() >= 0.5f) // 0.5초 마다 화살 생성
		{
			m_p_Object_T2_Char[i]->setObjectCoolTime(0.0f);
			BuildObjects
			(
				m_p_Object_T2_Char[i]->getObjectPosition_X() + m_p_Object_T2_Char[i]->getObjectVelocity().x * 20.0f,
				m_p_Object_T2_Char[i]->getObjectPosition_Y() + m_p_Object_T2_Char[i]->getObjectVelocity().y * 20.0f,
				m_p_Object_T2_Char[i]->getObjectID(),
				OBJECT_ARROW
			);
			m_p_Object_Arrows[m_curArrowCount]->setObjectVelocityX(m_p_Object_T2_Char[i]->getObjectVelocity().x);
			m_p_Object_Arrows[m_curArrowCount]->setObjectVelocityY(m_p_Object_T2_Char[i]->getObjectVelocity().y);
		}
	}

	// 건물 업데이트
	for (int i = 0; i < m_curT1BuildingCount; ++i)
	{
		if (m_p_Object_T1_Building != NULL)
		{
			m_p_Object_T1_Building[i]->plusObjectCoolTime(elapsedTime / 1000.0f);
			if (m_p_Object_T1_Building[i]->getObjectCoolTime() >= 0.5f) // 0.5초 마다 총알 생성
			{
				m_p_Object_T1_Building[i]->setObjectCoolTime(0.0f);
				BuildObjects(m_p_Object_T1_Building[i]->getObjectPosition_X(), m_p_Object_T1_Building[i]->getObjectPosition_Y(), m_p_Object_T1_Building[i]->getObjectID(), OBJECT_BULLET);
			}
		}
	}
	for (int i = 0; i < m_curT2BuildingCount; ++i)
	{
		if (m_p_Object_T2_Building != NULL)
		{
			m_p_Object_T2_Building[i]->plusObjectCoolTime(elapsedTime / 1000.0f);
			if (m_p_Object_T2_Building[i]->getObjectCoolTime() >= 0.5f) // 0.5초 마다 총알 생성
			{
				m_p_Object_T2_Building[i]->setObjectCoolTime(0.0f);
				BuildObjects(m_p_Object_T2_Building[i]->getObjectPosition_X(), m_p_Object_T2_Building[i]->getObjectPosition_Y(), m_p_Object_T2_Building[i]->getObjectID(), OBJECT_BULLET);
			}
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
	if (m_p_Object_T1_Char != nullptr)
	{
		for (int i = 0; i <= m_curT1CharCount; ++i)
		{
			if (m_p_Object_T1_Char[i]->getObjectIsDead())
			{
				delete m_p_Object_T1_Char[i];
				m_p_Object_T1_Char[i] = nullptr;
				for (int j = i; j <= m_curT1CharCount; ++j)
				{
					m_p_Object_T1_Char[i] = m_p_Object_T1_Char[j];
				}
				--m_curT1CharCount;
				--i;
			}
		}
	}
	if (m_p_Object_T2_Char != nullptr)
	{
		for (int i = 0; i <= m_curT2CharCount; ++i)
		{
			if (m_p_Object_T2_Char[i]->getObjectIsDead())
			{
				delete m_p_Object_T2_Char[i];
				m_p_Object_T2_Char[i] = nullptr;
				for (int j = i; j <= m_curT2CharCount; ++j)
				{
					m_p_Object_T2_Char[i] = m_p_Object_T2_Char[j];
				}
				--m_curT2CharCount;
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

	if (m_p_Object_T1_Building != nullptr)
	{
		for (int i = 0; i < m_curT1BuildingCount; ++i)
		{
			if (m_p_Object_T1_Building[i]->getObjectIsDead())
			{
				delete m_p_Object_T1_Building[i];
				m_p_Object_T1_Building[i] = nullptr;
				for (int j = i; j <= m_curT1BuildingCount; ++j)
				{
					m_p_Object_T1_Building[i] = m_p_Object_T1_Building[j];
				}
				--m_curT1BuildingCount;
				--i;
			}
		}
	}
	if (m_p_Object_T2_Building != nullptr)
	{
		for (int i = 0; i < m_curT2BuildingCount; ++i)
		{
			if (m_p_Object_T2_Building[i]->getObjectIsDead())
			{
				delete m_p_Object_T2_Building[i];
				m_p_Object_T2_Building[i] = nullptr;
				for (int j = i; j <= m_curT2BuildingCount; ++j)
				{
					m_p_Object_T2_Building[i] = m_p_Object_T2_Building[j];
				}
				--m_curT2BuildingCount;
				--i;
			}
		}
	}
};


void SceneMgr::DestroyObjects()
{
	if (m_p_Object_T1_Char != NULL)
	{
		for (int i = 0; i < MAX_T1_CHAR_COUNT; ++i)
		{
			if (m_p_Object_T1_Char[i])
			{
				delete m_p_Object_T1_Char[i];
			}
		}
	}
	if (m_p_Object_T2_Char != NULL)
	{
		for (int i = 0; i < MAX_T2_CHAR_COUNT; ++i)
		{
			if (m_p_Object_T2_Char[i])
			{
				delete m_p_Object_T2_Char[i];
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

	if (m_p_Object_T1_Building != NULL)
	{
		for (int i = 0; i < MAX_T1_BUILDING_COUNT; ++i)
		{
			if (m_p_Object_T1_Building[i])
			{
				delete m_p_Object_T1_Building[i];
			}
		}
	}

	if (m_p_Object_T2_Building != NULL)
	{
		for (int i = 0; i < MAX_T2_BUILDING_COUNT; ++i)
		{
			if (m_p_Object_T2_Building[i])
			{
				delete m_p_Object_T2_Building[i];
			}
		}
	}
}