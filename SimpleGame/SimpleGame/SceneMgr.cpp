#include "stdafx.h"
#include "SceneMgr.h"

// 랜덤엔진
random_device randomDevice;
default_random_engine dre(randomDevice());
uniform_real_distribution<> ur_randomVelocityX(-1.0f, 1.0f);
uniform_real_distribution<> ur_randomT1VelocityY(-1.0f, 0.0f);
uniform_real_distribution<> ur_randomT2VelocityY(0.0f, 1.0f);
uniform_real_distribution<> ur_randomBullet_VelocityX(-0.5f, 0.5f);

uniform_real_distribution<> ur_randomPosX(-WINDOWSIZE_WIDTH / 2.0f + 10.0f, WINDOWSIZE_WIDTH / 2.0f - 10.0f);
uniform_real_distribution<> ur_randomPosY(0.0f, WINDOWSIZE_HEIGHT / 2.0f - 10.0f);

// 렌더러와 오브젝트들 생성
SceneMgr::SceneMgr()
{
	m_p_Renderer = new Renderer(WINDOWSIZE_WIDTH, WINDOWSIZE_HEIGHT);
	m_BackgroundTextureID = m_p_Renderer->CreatePngTexture("./Resource/Background.png");
	m_pSound = new Sound();
	m_BackgroundSound = m_pSound->CreateSound("./Dependencies/SoundSamples/MF-W-90.XM");
	m_pSound->PlaySound(m_BackgroundSound, true, 0.2f);
	// default 건물 생성
	BuildObjects(-150.0f, 300.0f, OBJECT_TEAM_1, OBJECT_BUILDING);
	BuildObjects(-150.0f, -300.0f, OBJECT_TEAM_2, OBJECT_BUILDING);
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
			m_p_Object_Building->setObjectInfo(x + i * 150.0f, y, 0.0f, 100.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.1f);
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
			m_p_Object_Char->setObjectInfo(x, y, 0.0f, 50.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.2f);
			m_p_Object_Char->setObjectVelocityX(ur_randomVelocityX(dre));
			m_p_Object_Char->setObjectVelocityY(ur_randomT1VelocityY(dre));
			if (m_p_Object_Char->getObjectVelocity().x == 0.0f && m_p_Object_Char->getObjectVelocity().y == 0.0f) {
				m_p_Object_Char->setObjectVelocityX(ur_randomVelocityX(dre));
				m_p_Object_Char->setObjectVelocityY(-1.0f);
			}
			m_p_Object_Char->setObjcetLife(10.0f);
			m_p_Object_Char->setObjectSpeed(300.0f);
			m_p_Object_Char->setObjectID(id);

			m_p_Object_Char->setTextureID(m_p_Renderer->CreatePngTexture("./Resource/Team1_Char.png"));

			m_p_Object_Char->setAniCountX(0);
			m_p_Object_Char->setAniCountY(0);

			m_p_Object_Char->setMaxAniSizeX(10);
			m_p_Object_Char->setMaxAniSizeY(1);

			m_CharObj_List.push_back(*m_p_Object_Char);
		}

		else if (id == OBJECT_TEAM_2 && m_curT2CharCount < MAX_CHARACTER_COUNT)
		{
			++m_curT2CharCount;
			m_p_Object_Char = new Object();
			m_p_Object_Char->setObjectInfo(x, y, 0.0f, 50.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.2f);
			m_p_Object_Char->setObjectVelocityX(ur_randomVelocityX(dre));
			m_p_Object_Char->setObjectVelocityY(ur_randomT2VelocityY(dre));
			if (m_p_Object_Char->getObjectVelocity().x == 0.0f && m_p_Object_Char->getObjectVelocity().y == 0.0f) {
				m_p_Object_Char->setObjectVelocityX(ur_randomVelocityX(dre));
				m_p_Object_Char->setObjectVelocityY(1.0f);
			}
			m_p_Object_Char->setObjcetLife(10.0f);
			m_p_Object_Char->setObjectSpeed(300.0f);
			m_p_Object_Char->setObjectID(id);

			m_p_Object_Char->setTextureID(m_p_Renderer->CreatePngTexture("./Resource/Team2_Char.png"));

			m_p_Object_Char->setAniCountX(0);
			m_p_Object_Char->setAniCountY(0);

			m_p_Object_Char->setMaxAniSizeX(10);
			m_p_Object_Char->setMaxAniSizeY(1);

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
				m_p_Object_Bullets->setObjectInfo(x, y, 0.0f, 20.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.3f);
				m_p_Object_Bullets->setObjectVelocityX(ur_randomBullet_VelocityX(dre));
				m_p_Object_Bullets->setObjectVelocityY(ur_randomT1VelocityY(dre));
				if (m_p_Object_Bullets->getObjectVelocity().x == 0.0f && m_p_Object_Bullets->getObjectVelocity().y == 0.0f) {
					m_p_Object_Bullets->setObjectVelocityX(ur_randomVelocityX(dre));
					m_p_Object_Bullets->setObjectVelocityY(-1.0f);
				}
				m_p_Object_Bullets->setTextureID(m_p_Renderer->CreatePngTexture("./Resource/Team1_Bullet.png"));
				m_p_Object_Bullets->setParticleDirY(1); // 파티클 방향 설정
			}

			else if (id == OBJECT_TEAM_2)
			{
				m_p_Object_Bullets->setObjectInfo(x, y, 0.0f, 20.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.3f);
				m_p_Object_Bullets->setObjectVelocityX(ur_randomBullet_VelocityX(dre));
				m_p_Object_Bullets->setObjectVelocityY(ur_randomT2VelocityY(dre));
				if (m_p_Object_Bullets->getObjectVelocity().x == 0.0f && m_p_Object_Bullets->getObjectVelocity().y == 0.0f) {
					m_p_Object_Bullets->setObjectVelocityX(ur_randomVelocityX(dre));
					m_p_Object_Bullets->setObjectVelocityY(1.0f);
				}
				m_p_Object_Bullets->setTextureID(m_p_Renderer->CreatePngTexture("./Resource/Team2_Bullet.png"));
				m_p_Object_Bullets->setParticleDirY(-1); // 파티클 방향 설정
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
			if (id == OBJECT_TEAM_1) m_p_Object_Arrows->setObjectInfo(x, y, 0.0f, 2.0f, 0.5f, 0.2f, 0.7f, 1.0f, 0.3f);
			else if (id == OBJECT_TEAM_2) m_p_Object_Arrows->setObjectInfo(x, y, 0.0f, 2.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.3f);
			m_p_Object_Arrows->setObjcetLife(10.0f);
			m_p_Object_Arrows->setObjectSpeed(100.0f);
			m_p_Object_Arrows->setObjectID(id);

			m_ArrowObj_List.push_back(*m_p_Object_Arrows);
		}
		break;
	}
};


void SceneMgr::DrawStatusUI()
{
	// UI 창
	m_p_Renderer->DrawSolidRect(0.0f, 0.0f, 0.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.15f);

	// 텍스트
	m_p_Renderer->DrawText(-20.0f, 140.0f, GLUT_STROKE_ROMAN, 1.0f, 1.0f, 1.0f, "This is UI.");

	// 텍스트
	m_p_Renderer->DrawText(-80.0f, 120.0f, GLUT_STROKE_ROMAN, 1.0f, 1.0f, 1.0f, "Game Software Engineering Class");
};


void SceneMgr::DrawObjects(float elapsedTime) {
	// 배경화면
	m_p_Renderer->DrawTexturedRect(0.0f, 0.0f, 0.0f, 800.0f, 1.0f, 1.0f, 1.0f, 0.8f, m_BackgroundTextureID, 0.99f);

	

	// 중앙선
	for (int i = -WINDOWSIZE_WIDTH / 2; i < WINDOWSIZE_WIDTH / 2; ++i)
		m_p_Renderer->DrawSolidRect(i, 0, 0, 1, 1, 1, 1, 1, 0.98f);

	if (!m_BulletObj_List.empty()) // 총알
	{
		for (m_iter_bullet = m_BulletObj_List.begin(); m_iter_bullet != m_BulletObj_List.end(); ++m_iter_bullet)
		{
			m_p_Renderer->DrawParticle
			(
				m_iter_bullet->getObjectPosition_X(), m_iter_bullet->getObjectPosition_Y(), m_iter_bullet->getObjectPosition_Z(),
				m_iter_bullet->getObjectSize(),
				m_iter_bullet->getObjectColor_R(), m_iter_bullet->getObjectColor_G(), m_iter_bullet->getObjectColor_B(), m_iter_bullet->getObjectColor_A(),
				0.0f, m_iter_bullet->getParticleDirY(),
				m_iter_bullet->getTextureID(), getElapsedTime()
			);
		}
	}

	if (!m_ArrowObj_List.empty()) // 화살
	{
		for (m_iter_arrow = m_ArrowObj_List.begin(); m_iter_arrow != m_ArrowObj_List.end(); ++m_iter_arrow)
		{
			m_p_Renderer->DrawSolidRect(
				m_iter_arrow->getObjectPosition_X(), m_iter_arrow->getObjectPosition_Y(), m_iter_arrow->getObjectPosition_Z(),
				m_iter_arrow->getObjectSize(),
				m_iter_arrow->getObjectColor_R(), m_iter_arrow->getObjectColor_G(), m_iter_arrow->getObjectColor_B(), m_iter_arrow->getObjectColor_A(), m_iter_arrow->getRenderLevel());
		}
	}

	if (!m_CharObj_List.empty()) // 캐릭터
	{
		for (m_iter_char = m_CharObj_List.begin(); m_iter_char != m_CharObj_List.end(); ++m_iter_char)
		{
			// 캐릭터 animation
			m_p_Renderer->DrawTexturedRectSeq
			(
				m_iter_char->getObjectPosition_X(), m_iter_char->getObjectPosition_Y(), m_iter_char->getObjectPosition_Z(),
				m_iter_char->getObjectSize(),
				m_iter_char->getObjectColor_R(), m_iter_char->getObjectColor_G(), m_iter_char->getObjectColor_B(), m_iter_char->getObjectColor_A(),
				m_iter_char->getTextureID(), m_iter_char->getAniCountX(), m_iter_char->getAniCountY(), m_iter_char->getMaxAniSizeX(), m_iter_char->getMaxAniSizeY(),
				m_iter_char->getRenderLevel()
			);

			// animation 증가
			m_iter_char->plusAniCountX(0.5f);
			// animation 최대 수 도달 시 초기화
			if (m_iter_char->getAniCountX() > m_iter_char->getMaxAniSizeX()) m_iter_char->setAniCountX(0);

			// 라이프 게이지
			m_p_Renderer->DrawSolidRectGauge(
				m_iter_char->getObjectPosition_X(), m_iter_char->getObjectPosition_Y() + m_iter_char->getObjectSize() + 5.0f, m_iter_char->getObjectPosition_Z(),
				m_iter_char->getObjectSize() + 20.0f, 10.0f,
				m_iter_char->getObjectColor_R(), m_iter_char->getObjectColor_G(), m_iter_char->getObjectColor_B(), m_iter_char->getObjectColor_A(),
				m_iter_char->getObjectLife() / 10.0f,
				m_iter_char->getRenderLevel()
			);
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
				m_iter_building->getTextureID(), m_iter_building->getRenderLevel()
			);
			if (m_iter_building->getObjectID() == OBJECT_TEAM_1)
			{
				m_p_Renderer->DrawSolidRectGauge(
					m_iter_building->getObjectPosition_X(), m_iter_building->getObjectPosition_Y() + m_iter_building->getObjectSize() - 30.0f, m_iter_building->getObjectPosition_Z(),
					m_iter_building->getObjectSize(), 10.0f,
					1.0f, 0.0f, 0.0f, m_iter_building->getObjectColor_A(),
					m_iter_building->getObjectLife() / 500.0f,
					m_iter_building->getRenderLevel()
				);
			}
			else if (m_iter_building->getObjectID() == OBJECT_TEAM_2)
			{
				m_p_Renderer->DrawSolidRectGauge(
					m_iter_building->getObjectPosition_X()+5.0f, m_iter_building->getObjectPosition_Y() + m_iter_building->getObjectSize() - 30.0f, m_iter_building->getObjectPosition_Z(),
					m_iter_building->getObjectSize(), 10.0f,
					0.0f, 0.0f, 1.0f, m_iter_building->getObjectColor_A(),
					m_iter_building->getObjectLife() / 500.0f,
					m_iter_building->getRenderLevel()
				);
			}
		}
	}

	// 상태 정보창 UI
	if (GetIsStatusUI())
		DrawStatusUI();
	else m_p_Renderer->DrawText(0.0f, 0.0f, GLUT_STROKE_ROMAN, 1.0f, 1.0f, 1.0f, "If you push CTRL Key, UI will POP UP!");

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
	if (getElapsedTime() >= 2.0f) // 5.0초 마다 Team1 캐릭터 생성
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
			m_iter_char->WallCollision();
			if (m_iter_char->getObjectCoolTime() >= 1.0f) // 3.0초 마다 화살 생성
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
			if (m_iter_building->getObjectCoolTime() >= 2.0f) // 10.0초 마다 총알 생성
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
		{
			m_iter_bullet->update(elapsedTime);
			Collider bull = m_iter_bullet->getObjectCollider();
			if (bull.maxX > WINDOWSIZE_WIDTH / 2 || bull.minX < -WINDOWSIZE_WIDTH / 2
				|| bull.maxY > WINDOWSIZE_HEIGHT / 2 || bull.minY < -WINDOWSIZE_HEIGHT / 2)
			{
				m_iter_bullet->setObjectIsDead(true);
			}
		}
	}

	// 화살 업데이트
	if (!m_ArrowObj_List.empty())
	{
		for (m_iter_arrow = m_ArrowObj_List.begin(); m_iter_arrow != m_ArrowObj_List.end(); ++m_iter_arrow)
		{
			m_iter_arrow->update(elapsedTime);
			Collider arrow = m_iter_arrow->getObjectCollider();
			if (arrow.maxX > WINDOWSIZE_WIDTH / 2 || arrow.minX < -WINDOWSIZE_WIDTH / 2
				|| arrow.maxY > WINDOWSIZE_HEIGHT / 2 || arrow.minY < -WINDOWSIZE_HEIGHT / 2)
			{
				m_iter_arrow->setObjectIsDead(true);
			}
		}
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