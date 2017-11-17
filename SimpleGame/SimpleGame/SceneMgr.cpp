#include "stdafx.h"
#include "SceneMgr.h"

// 랜덤엔진
random_device randomDevice;
default_random_engine dre(randomDevice());
uniform_real_distribution<> ur_randomVelocityX(-1.0f, 1.0f);
uniform_real_distribution<> ur_randomT1VelocityY(-1.0f, 0.0f);
uniform_real_distribution<> ur_randomT2VelocityY(0.0f, 1.0f);

uniform_real_distribution<> ur_randomPosX(-WINDOWSIZE_WIDTH / 2.0f + 10.0f, WINDOWSIZE_WIDTH / 2.0f - 10.0f);
uniform_real_distribution<> ur_randomPosY(0.0f, WINDOWSIZE_HEIGHT / 2.0f - 10.0f);

// 렌더러와 오브젝트들 생성
SceneMgr::SceneMgr()
{
	m_p_Renderer = new Renderer(WINDOWSIZE_WIDTH, WINDOWSIZE_HEIGHT);
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
		for (int i = 0; i < 3; ++i)
		{
			m_p_Object_Building = new Object();
			m_p_Object_Building->setObjectInfo(x + i * 150.0f, y, 0.0f, 100.0f, 1.0f, 1.0f, 0.0f, 1.0f);
			m_p_Object_Building->setObjectVelocityX(0);
			m_p_Object_Building->setObjectVelocityY(0);
			m_p_Object_Building->setObjcetLife(500.0f);
			m_p_Object_Building->setObjectSpeed(0.0f);
			m_p_Object_Building->setObjectID(id);
			if (id == OBJECT_TEAM_1)
				m_p_Object_Building->setTextureID(m_p_Renderer->CreatePngTexture("./Resource/Pig.png"));
			else if (id == OBJECT_TEAM_2)
				m_p_Object_Building->setTextureID(m_p_Renderer->CreatePngTexture("./Resource/AngryBird.png"));

			m_BuildingObj_List.push_back(*m_p_Object_Building);
		}

		break;

	case OBJECT_CHARACTER:
		if (id == OBJECT_TEAM_1 && m_curT1CharCount < MAX_CHARACTER_COUNT)
		{
			++m_curT1CharCount;
			m_p_Object_Char = new Object();
			m_p_Object_Char->setObjectInfo(x, y, 0.0f, 10.0f, 1.0f, 0.0f, 0.0f, 1.0f);
			m_p_Object_Char->setObjectVelocityX(ur_randomVelocityX(dre));
			m_p_Object_Char->setObjectVelocityY(ur_randomT1VelocityY(dre));
			if (m_p_Object_Char->getObjectVelocity().x == 0.0f && m_p_Object_Char->getObjectVelocity().y == 0.0f) {
				m_p_Object_Char->setObjectVelocityX(ur_randomVelocityX(dre));
				m_p_Object_Char->setObjectVelocityY(-1.0f);
			}
			m_p_Object_Char->setObjcetLife(10.0f);
			m_p_Object_Char->setObjectSpeed(300.0f);
			m_p_Object_Char->setObjectID(id);

			m_CharObj_List.push_back(*m_p_Object_Char);
		}

		else if (id == OBJECT_TEAM_2 && m_curT2CharCount < MAX_CHARACTER_COUNT)
		{
			++m_curT2CharCount;
			m_p_Object_Char = new Object();
			m_p_Object_Char->setObjectInfo(x, y, 0.0f, 10.0f, 0.0f, 0.0f, 1.0f, 1.0f);
			m_p_Object_Char->setObjectVelocityX(ur_randomVelocityX(dre));
			m_p_Object_Char->setObjectVelocityY(ur_randomT2VelocityY(dre));
			if (m_p_Object_Char->getObjectVelocity().x == 0.0f && m_p_Object_Char->getObjectVelocity().y == 0.0f) {
				m_p_Object_Char->setObjectVelocityX(ur_randomVelocityX(dre));
				m_p_Object_Char->setObjectVelocityY(1.0f);
			}
			m_p_Object_Char->setObjcetLife(10.0f);
			m_p_Object_Char->setObjectSpeed(300.0f);
			m_p_Object_Char->setObjectID(id);

			m_CharObj_List.push_back(*m_p_Object_Char);
		}

		break;

	case OBJECT_BULLET:
		if (m_curBulletCount < MAX_BULLET_COUNT)
		{
			++m_curBulletCount;
			m_p_Object_Bullets = new Object();
			if (id == OBJECT_TEAM_1)
			{
				m_p_Object_Bullets->setObjectInfo(x, y, 0.0f, 2.0f, 1.0f, 0.0f, 0.0f, 1.0f);
				m_p_Object_Bullets->setObjectVelocityX(ur_randomVelocityX(dre));
				m_p_Object_Bullets->setObjectVelocityY(ur_randomT1VelocityY(dre));
				if (m_p_Object_Bullets->getObjectVelocity().x == 0.0f && m_p_Object_Bullets->getObjectVelocity().y == 0.0f) {
					m_p_Object_Bullets->setObjectVelocityX(ur_randomVelocityX(dre));
					m_p_Object_Bullets->setObjectVelocityY(-1.0f);
				}
			}
			else if (id == OBJECT_TEAM_2)
			{
				m_p_Object_Bullets->setObjectInfo(x, y, 0.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f);
				m_p_Object_Bullets->setObjectVelocityX(ur_randomVelocityX(dre));
				m_p_Object_Bullets->setObjectVelocityY(ur_randomT2VelocityY(dre));
				if (m_p_Object_Bullets->getObjectVelocity().x == 0.0f && m_p_Object_Bullets->getObjectVelocity().y == 0.0f) {
					m_p_Object_Bullets->setObjectVelocityX(ur_randomVelocityX(dre));
					m_p_Object_Bullets->setObjectVelocityY(1.0f);
				}
			}
			m_p_Object_Bullets->setObjcetLife(20.0f);
			m_p_Object_Bullets->setObjectSpeed(600.0f);
			m_p_Object_Bullets->setObjectID(id);

			m_BulletObj_List.push_back(*m_p_Object_Bullets);
		}
		break;

	case OBJECT_ARROW:
		if (m_curArrowCount < MAX_ARROW_COUNT)
		{
			++m_curArrowCount;
			m_p_Object_Arrows = new Object();
			if (id == OBJECT_TEAM_1) m_p_Object_Arrows->setObjectInfo(x, y, 0.0f, 2.0f, 0.5f, 0.2f, 0.7f, 1.0f);
			else if (id == OBJECT_TEAM_2) m_p_Object_Arrows->setObjectInfo(x, y, 0.0f, 2.0f, 1.0f, 1.0f, 0.0f, 1.0f);
			m_p_Object_Arrows->setObjcetLife(10.0f);
			m_p_Object_Arrows->setObjectSpeed(100.0f);
			m_p_Object_Arrows->setObjectID(id);

			m_ArrowObj_List.push_back(*m_p_Object_Arrows);
		}
		break;
	}
};


void SceneMgr::DrawObjects() {
	
	// 중앙선
	for (int i = -WINDOWSIZE_WIDTH / 2; i < WINDOWSIZE_WIDTH / 2; ++i)
		m_p_Renderer->DrawSolidRect(i, 0, 0, 1, 1, 1, 1, 1);

	if (!m_BulletObj_List.empty()) // 총알
	{
		for (m_iter_bullet = m_BulletObj_List.begin(); m_iter_bullet != m_BulletObj_List.end(); ++m_iter_bullet)
		{
			m_p_Renderer->DrawSolidRect(
				m_iter_bullet->getObjectPosition_X(), m_iter_bullet->getObjectPosition_Y(), m_iter_bullet->getObjectPosition_Z(),
				m_iter_bullet->getObjectSize(),
				m_iter_bullet->getObjectColor_R(), m_iter_bullet->getObjectColor_G(), m_iter_bullet->getObjectColor_B(), m_iter_bullet->getObjectColor_A());
		}
	}

	if (!m_ArrowObj_List.empty()) // 화살
	{
		for (m_iter_arrow = m_ArrowObj_List.begin(); m_iter_arrow != m_ArrowObj_List.end(); ++m_iter_arrow)
		{
			m_p_Renderer->DrawSolidRect(
				m_iter_arrow->getObjectPosition_X(), m_iter_arrow->getObjectPosition_Y(), m_iter_arrow->getObjectPosition_Z(),
				m_iter_arrow->getObjectSize(),
				m_iter_arrow->getObjectColor_R(), m_iter_arrow->getObjectColor_G(), m_iter_arrow->getObjectColor_B(), m_iter_arrow->getObjectColor_A());
		}
	}

	if (!m_CharObj_List.empty()) // 캐릭터
	{
		for (m_iter_char = m_CharObj_List.begin(); m_iter_char != m_CharObj_List.end(); ++m_iter_char)
		{
			m_p_Renderer->DrawSolidRect(
				m_iter_char->getObjectPosition_X(), m_iter_char->getObjectPosition_Y(), m_iter_char->getObjectPosition_Z(),
				m_iter_char->getObjectSize(),
				m_iter_char->getObjectColor_R(), m_iter_char->getObjectColor_G(), m_iter_char->getObjectColor_B(), m_iter_char->getObjectColor_A());
		}
	}

	if (!m_BuildingObj_List.empty()) // 건물
	{
		for (m_iter_building = m_BuildingObj_List.begin(); m_iter_building != m_BuildingObj_List.end(); ++m_iter_building)
		{
			m_p_Renderer->DrawTexturedRect
			(
				m_iter_building->getObjectPosition_X(), m_iter_building->getObjectPosition_Y(), m_iter_building->getObjectPosition_Z(),
				m_iter_building->getObjectSize(),
				m_iter_building->getObjectColor_R(), m_iter_building->getObjectColor_G(), m_iter_building->getObjectColor_B(), m_iter_building->getObjectColor_A(),
				m_iter_building->getTextureID()
			);
		}
	}
}


void SceneMgr::ObjectsCollisionCheck()
{
	if (!m_BulletObj_List.empty()) // 총알과
	{
		for (m_iter_bullet = m_BulletObj_List.begin(); m_iter_bullet != m_BulletObj_List.end(); ++m_iter_bullet)
		{
			if (!m_CharObj_List.empty()) // 캐릭터
			{
				for (m_iter_char = m_CharObj_List.begin(); m_iter_char != m_CharObj_List.end(); ++m_iter_char)
				{
					if ((m_iter_bullet->getObjectID() != m_iter_char->getObjectID()) && m_iter_char->IsCollide(m_iter_bullet->getObjectCollider()))
					{
						m_iter_char->damageObjcetLife(-m_iter_bullet->getObjectLife());
						m_iter_bullet->damageObjcetLife(-20.0f);
					}
				}
			}

			if (!m_BuildingObj_List.empty()) // 건물
			{
				for (m_iter_building = m_BuildingObj_List.begin(); m_iter_building != m_BuildingObj_List.end(); ++m_iter_building)
				{
					if ((m_iter_bullet->getObjectID() != m_iter_building->getObjectID()) && m_iter_building->IsCollide(m_iter_bullet->getObjectCollider()))
					{
						m_iter_building->damageObjcetLife(-m_iter_bullet->getObjectLife());
						m_iter_bullet->damageObjcetLife(-20.0f);
					}
				}
			}
		}
	}


	if (!m_ArrowObj_List.empty()) // 화살과
	{
		for (m_iter_arrow = m_ArrowObj_List.begin(); m_iter_arrow != m_ArrowObj_List.end(); ++m_iter_arrow)
		{
			if (!m_CharObj_List.empty()) // 캐릭터
			{
				for (m_iter_char = m_CharObj_List.begin(); m_iter_char != m_CharObj_List.end(); ++m_iter_char)
				{
					if ((m_iter_arrow->getObjectID() != m_iter_char->getObjectID()) && m_iter_char->IsCollide(m_iter_arrow->getObjectCollider()))
					{
						m_iter_char->damageObjcetLife(-m_iter_arrow->getObjectLife());
						m_iter_arrow->damageObjcetLife(-20.0f);
					}
				}
			}
			if (!m_BuildingObj_List.empty()) // 건물
			{
				for (m_iter_building = m_BuildingObj_List.begin(); m_iter_building != m_BuildingObj_List.end(); ++m_iter_building)
				{
					if ((m_iter_arrow->getObjectID() != m_iter_building->getObjectID()) && m_iter_building->IsCollide(m_iter_arrow->getObjectCollider()))
					{
						m_iter_building->damageObjcetLife(-m_iter_arrow->getObjectLife());
						m_iter_arrow->damageObjcetLife(-20.0f);
					}
				}
			}
		}
	}

	if (!m_CharObj_List.empty()) // 캐릭터와
	{
		for (m_iter_char = m_CharObj_List.begin(); m_iter_char != m_CharObj_List.end(); ++m_iter_char)
		{
			if (!m_BuildingObj_List.empty()) // 건물
			{
				for (m_iter_building = m_BuildingObj_List.begin(); m_iter_building != m_BuildingObj_List.end(); ++m_iter_building)
				{
					if ((m_iter_char->getObjectID() != m_iter_building->getObjectID()) && m_iter_building->IsCollide(m_iter_char->getObjectCollider()))
					{
						m_iter_building->damageObjcetLife(-m_iter_char->getObjectLife());
						m_iter_char->damageObjcetLife(-10.0f);
					}
				}
			}
		}
	}
	
}


void SceneMgr::UpdateObjects(float elapsedTime)
{
	// 북쪽 진영 캐릭터 생성
	plusElapsedTime(elapsedTime / 1000.0f);
	if (getElapsedTime() >= 5.0f) // 5.0초 마다 Team1 캐릭터 생성
	{
		setElapsedTime(0.0f);
		BuildObjects
		(
			ur_randomPosX(dre),
			ur_randomPosY(dre),
			OBJECT_TEAM_1,
			OBJECT_CHARACTER
		);
	}

	// 캐릭터 업데이트
	if (!m_CharObj_List.empty())
	{
		for (m_iter_char = m_CharObj_List.begin(); m_iter_char != m_CharObj_List.end(); ++m_iter_char)
		{
			m_iter_char->plusObjectCoolTime(elapsedTime / 1000.0f);
			m_iter_char->update(elapsedTime);
			if (m_iter_char->getObjectCoolTime() >= 3.0f) // 3.0초 마다 화살 생성
			{
				m_iter_char->setObjectCoolTime(0.0f);
				BuildObjects
				(
					m_iter_char->getObjectPosition_X() + m_iter_char->getObjectVelocity().x * 20.0f,
					m_iter_char->getObjectPosition_Y() + m_iter_char->getObjectVelocity().y * 20.0f,
					m_iter_char->getObjectID(),
					OBJECT_ARROW
				);
				m_ArrowObj_List.back().setObjectVelocityX(m_iter_char->getObjectVelocity().x);
				m_ArrowObj_List.back().setObjectVelocityY(m_iter_char->getObjectVelocity().y);
			}
		}
	}

	// 건물 업데이트
	if (!m_BuildingObj_List.empty())
	{
		for (m_iter_building = m_BuildingObj_List.begin(); m_iter_building != m_BuildingObj_List.end(); ++m_iter_building)
		{
			m_iter_building->plusObjectCoolTime(elapsedTime / 1000.0f);
			if (m_iter_building->getObjectCoolTime() >= 10.0f) // 10.0초 마다 총알 생성
			{
				m_iter_building->setObjectCoolTime(0.0f);
				BuildObjects(m_iter_building->getObjectPosition_X(), m_iter_building->getObjectPosition_Y(), m_iter_building->getObjectID(), OBJECT_BULLET);
			}
		}
	}

	// 총알 업데이트
	if (!m_BulletObj_List.empty())
	{
		for (m_iter_bullet = m_BulletObj_List.begin(); m_iter_bullet != m_BulletObj_List.end(); ++m_iter_bullet)
			m_iter_bullet->update(elapsedTime);
	}

	// 화살 업데이트
	if (!m_ArrowObj_List.empty())
	{
		for (m_iter_arrow = m_ArrowObj_List.begin(); m_iter_arrow != m_ArrowObj_List.end(); ++m_iter_arrow)
			m_iter_arrow->update(elapsedTime);
	}

	ObjectsCollisionCheck(); // 충돌 검사
	CheckDeadObject(); // 죽은 오브젝트 검사
}


void SceneMgr::CheckDeadObject()
{
	if (!m_CharObj_List.empty())
	{
		m_iter_char = m_CharObj_List.begin();
		while (m_iter_char != m_CharObj_List.end())
		{
			if (m_iter_char->getObjectIsDead())
			{
				if (m_iter_char->getObjectID() == OBJECT_TEAM_1) --m_curT1CharCount;
				else if (m_iter_char->getObjectID() == OBJECT_TEAM_2) --m_curT2CharCount;
				m_CharObj_List.erase(m_iter_char++);
			}
			else ++m_iter_char;
		}
	}

	if (!m_BuildingObj_List.empty())
	{
		m_iter_building = m_BuildingObj_List.begin();
		while (m_iter_building != m_BuildingObj_List.end())
		{
			if (m_iter_building->getObjectIsDead()) m_BuildingObj_List.erase(m_iter_building++);
			else ++m_iter_building;
		}
	}

	if (!m_ArrowObj_List.empty())
	{
		m_iter_arrow = m_ArrowObj_List.begin();
		while (m_iter_arrow != m_ArrowObj_List.end())
		{
			if (m_iter_arrow->getObjectIsDead())
			{
				--m_curArrowCount;
				m_ArrowObj_List.erase(m_iter_arrow++);
			}
			else ++m_iter_arrow;
		}
	}

	if (!m_BulletObj_List.empty())
	{
		m_iter_bullet = m_BulletObj_List.begin();
		while (m_iter_bullet != m_BulletObj_List.end())
		{
			if (m_iter_bullet->getObjectIsDead())
			{
				--m_curBulletCount;
				m_BulletObj_List.erase(m_iter_bullet++);
			}
			else ++m_iter_bullet;
		}
	}

};


void SceneMgr::DestroyObjects()
{
	if (!m_CharObj_List.empty())
	{
		m_CharObj_List.erase(m_CharObj_List.begin(), m_CharObj_List.end());
	}
	if (!m_ArrowObj_List.empty())
	{
		m_ArrowObj_List.erase(m_ArrowObj_List.begin(), m_ArrowObj_List.end());
	}
	if (!m_BuildingObj_List.empty())
	{
		m_BuildingObj_List.erase(m_BuildingObj_List.begin(), m_BuildingObj_List.end());
	}
	if (!m_BulletObj_List.empty())
	{
		m_BulletObj_List.erase(m_BulletObj_List.begin(), m_BulletObj_List.end());
	}
	
}