#include "stdafx.h"
#include "SceneMgr.h"

// ��������
random_device randomDevice;
default_random_engine dre(randomDevice());
uniform_real_distribution<> ur_randomVelocityX(-1.0f, 1.0f);
uniform_real_distribution<> ur_randomT1VelocityY(-1.0f, 0.0f);
uniform_real_distribution<> ur_randomT2VelocityY(0.0f, 1.0f);
uniform_real_distribution<> ur_randomBullet_VelocityX(-0.5f, 0.5f);

uniform_real_distribution<> ur_randomPosX(-WINDOWSIZE_WIDTH / 2.0f + 10.0f, WINDOWSIZE_WIDTH / 2.0f - 10.0f);
uniform_real_distribution<> ur_randomPosY(0.0f, WINDOWSIZE_HEIGHT / 2.0f - 10.0f);

// ���� ���� ����
uniform_real_distribution<> ur_randomUnit(0.0f, 1.0f);

// �������� ������Ʈ�� ����
SceneMgr::SceneMgr()
{
	m_p_Renderer = new Renderer(WINDOWSIZE_WIDTH, WINDOWSIZE_HEIGHT);
	m_BackgroundTextureID = m_p_Renderer->CreatePngTexture("./Resource/Background.png");
	m_Climate_Rain_TextureID = m_p_Renderer->CreatePngTexture("./Resource/Climate_Rain.png");
	//m_Climate_Star_TextureID = m_p_Renderer->CreatePngTexture("./Resource/Climate_Star.png");


	m_Team1_Bullet_TextureID = m_p_Renderer->CreatePngTexture("./Resource/Team1_Bullet.png");
	m_Team2_Bullet_TextureID = m_p_Renderer->CreatePngTexture("./Resource/Team2_Bullet.png");

	m_Team1_Arrow_TextureID = m_p_Renderer->CreatePngTexture("./Resource/Team1_Normal_Arrow.png");
	m_Team2_Arrow_TextureID = m_p_Renderer->CreatePngTexture("./Resource/Team2_Normal_Arrow.png");
	m_Team1_S_Arrow_TextureID = m_p_Renderer->CreatePngTexture("./Resource/Team1_Siege_Arrow.png");
	m_Team2_S_Arrow_TextureID = m_p_Renderer->CreatePngTexture("./Resource/Team2_Siege_Arrow.png");
	m_Team1_D_Arrow_TextureID = m_p_Renderer->CreatePngTexture("./Resource/Team1_Dragon_Flame.png");
	m_Team2_D_Arrow_TextureID = m_p_Renderer->CreatePngTexture("./Resource/Team2_Dragon_Flame.png");
		

	m_Team1_NormalUnit_TextureID = m_p_Renderer->CreatePngTexture("./Resource/Team1_NormalUnit.png");
	m_Team2_NormalUnit_TextureID = m_p_Renderer->CreatePngTexture("./Resource/Team2_NormalUnit.png");
	m_Team1_SiegeUnit_TextureID = m_p_Renderer->CreatePngTexture("./Resource/Team1_SiegeUnit.png");
	m_Team2_SiegeUnit_TextureID = m_p_Renderer->CreatePngTexture("./Resource/Team2_SiegeUnit.png");
	m_Team1_Dragon_TextureID = m_p_Renderer->CreatePngTexture("./Resource/Team1_Dragon.png");
	m_Team2_Dragon_TextureID = m_p_Renderer->CreatePngTexture("./Resource/Team2_Dragon.png");


	m_Team1_MasterBuilding_TextureID = m_p_Renderer->CreatePngTexture("./Resource/Team1_MasterBuilding.png");
	m_Team2_MasterBuilding_TextureID = m_p_Renderer->CreatePngTexture("./Resource/Team2_MasterBuilding.png");
	m_Team1_SubBuilding_TextureID = m_p_Renderer->CreatePngTexture("./Resource/Team1_SubBuilding.png");
	m_Team2_SubBuilding_TextureID = m_p_Renderer->CreatePngTexture("./Resource/Team2_SubBuilding.png");

	m_pSound_BGM = new Sound();
	m_Resource_BGM = m_pSound_BGM->CreateSound("./Resource/BGM.wav");
	m_pSound_BGM->PlaySound(m_Resource_BGM, true, 0.5f);


	m_pSound_BulletShot = new Sound();
	m_Resource_BulletShot = m_pSound_BulletShot->CreateSound("./Resource/Bullet_Shot.wav");
	m_pSound_BulletCrash = new Sound();
	m_Resource_BulletCrash = m_pSound_BulletCrash->CreateSound("./Resource/Bullet_Crash.wav");

	m_pSound_NormalArrowShot = new Sound();
	m_Resource_NormalArrowShot = m_pSound_NormalArrowShot->CreateSound("./Resource/Normal_Arrow_Shot.mp3");
	m_pSound_SiegeArrowShot = new Sound();
	m_Resource_SiegeArrowShot = m_pSound_SiegeArrowShot->CreateSound("./Resource/Siege_Arrow_Shot.wav");
	m_pSound_DragonArrowShot = new Sound();
	m_Resource_DragonArrowShot = m_pSound_DragonArrowShot->CreateSound("./Resource/Dragon_Arrow_Shot.wav");
	m_pSound_DragonArrowBlast = new Sound();
	m_Resource_DragonArrowBlast = m_pSound_DragonArrowBlast->CreateSound("./Resource/Dragon_Arrow_Blast.wav");

	m_pSound_Roar = new Sound();
	m_Resource_Roar = m_pSound_Roar->CreateSound("./Resource/Roar.wav");

	m_pSound_CharDead = new Sound();
	m_Resource_CharDead = m_pSound_CharDead->CreateSound("./Resource/Char_Dead.wav");


	// default �ǹ� ����
	BuildObjects(-150.0f, 300.0f, OBJECT_TEAM_1, OBJECT_BUILDING, 0);
	BuildObjects(-150.0f, -300.0f, OBJECT_TEAM_2, OBJECT_BUILDING, 0);
}


SceneMgr::~SceneMgr()
{
	DestroyObjects();
}


void SceneMgr::BuildObjects(float x, float y, int id, int type, int objType)
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
			m_p_Object_Building->setObjectSpeed(0.0f);
			m_p_Object_Building->setObjectID(id);
			m_p_Object_Building->setObjcetDamage(30.0f);

			if (i == 1)
			{
				m_p_Object_Building->setObjcetLife(1000.0f);
				m_p_Object_Building->SetObjectType(BUILDINGTYPE_MASTER);
				if (id == OBJECT_TEAM_1)
				{
					m_p_Object_Building->setObjectPosition_Y(y + 20.0f);
					m_p_Object_Building->setTextureID(m_Team1_MasterBuilding_TextureID);
				}
				else if (id == OBJECT_TEAM_2)
				{
					m_p_Object_Building->setObjectPosition_Y(y - 20.0f);
					m_p_Object_Building->setTextureID(m_Team2_MasterBuilding_TextureID);
				}
			}

			else
			{
				m_p_Object_Building->setObjcetLife(500.0f);
				m_p_Object_Building->setObjectSize(70.0f);
				m_p_Object_Building->SetObjectType(BUILDINGTYPE_SUB);
				if (id == OBJECT_TEAM_1)
					m_p_Object_Building->setTextureID(m_Team1_SubBuilding_TextureID);
				else if (id == OBJECT_TEAM_2)
					m_p_Object_Building->setTextureID(m_Team2_SubBuilding_TextureID);
			}
			m_BuildingObj_List.push_back(*m_p_Object_Building);
		}

		break;

	case OBJECT_CHARACTER:
		if (id == OBJECT_TEAM_1 && m_curT1CharCount < MAX_CHARACTER_COUNT)
		{
			++m_curT1CharCount;
			m_p_Object_Char = new Object();
			m_p_Object_Char->setObjectVelocityX(ur_randomVelocityX(dre));
			m_p_Object_Char->setObjectVelocityY(ur_randomT1VelocityY(dre));
			if (m_p_Object_Char->getObjectVelocity().x == 0.0f && m_p_Object_Char->getObjectVelocity().y == 0.0f) {
				m_p_Object_Char->setObjectVelocityX(ur_randomVelocityX(dre));
				m_p_Object_Char->setObjectVelocityY(-1.0f);
			}
			m_p_Object_Char->setObjectID(id);
			m_p_Object_Char->setAniCountX(0);
			m_p_Object_Char->setAniCountY(0);

			if (objType == UNITTYPE_DRAGON)
			{
				m_pSound_Roar->PlaySound(m_Resource_Roar, false, 1.0f);
				m_p_Object_Char->setObjectInfo(x, y, 0.0f, 100.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.2f);
				m_p_Object_Char->SetObjectType(UNITTYPE_DRAGON); // Ư�� ����
				m_p_Object_Char->setObjectSpeed(50.0f);
				m_p_Object_Char->setMaxAniSizeX(4);
				m_p_Object_Char->setMaxAniSizeY(1);
				m_p_Object_Char->setObjcetLife(DRAGON_MAX_LIFE);
				m_p_Object_Char->setObjcetDamage(10.0f);
				m_p_Object_Char->setTextureID(m_Team1_Dragon_TextureID);
			}

			else
			{
				m_p_Object_Char->setObjectInfo(x, y, 0.0f, 50.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.2f);

				if (ur_randomUnit(dre) > 0.4f)
				{
					m_p_Object_Char->SetObjectType(UNITTYPE_NORMAL); // �Ϲ� ����
					m_p_Object_Char->setObjectSpeed(100.0f);
					m_p_Object_Char->setMaxAniSizeX(10);
					m_p_Object_Char->setMaxAniSizeY(1);
					m_p_Object_Char->setObjcetLife(NORMAL_UNIT_MAX_LIFE);
					m_p_Object_Char->setObjcetDamage(NORMAL_UNIT_MAX_LIFE);
					m_p_Object_Char->setTextureID(m_Team1_NormalUnit_TextureID);
				}
				else
				{
					m_p_Object_Char->SetObjectType(UNITTYPE_SIEGE); // ���� ����
					m_p_Object_Char->setObjectSpeed(70.0f);
					m_p_Object_Char->setMaxAniSizeX(1);
					m_p_Object_Char->setMaxAniSizeY(1);
					m_p_Object_Char->setObjcetLife(SIEGE_UNIT_MAX_LIFE);
					m_p_Object_Char->setObjcetDamage(SIEGE_UNIT_MAX_LIFE);
					m_p_Object_Char->setTextureID(m_Team1_SiegeUnit_TextureID);
				}
			}

			m_CharObj_List.push_back(*m_p_Object_Char);
		}

		else if (id == OBJECT_TEAM_2 && m_curT2CharCount < MAX_CHARACTER_COUNT)
		{
			++m_curT2CharCount;
			m_p_Object_Char = new Object();
			m_p_Object_Char->setObjectVelocityX(ur_randomVelocityX(dre));
			m_p_Object_Char->setObjectVelocityY(ur_randomT2VelocityY(dre));
			if (m_p_Object_Char->getObjectVelocity().x == 0.0f && m_p_Object_Char->getObjectVelocity().y == 0.0f)
			{
				m_p_Object_Char->setObjectVelocityX(ur_randomVelocityX(dre));
				m_p_Object_Char->setObjectVelocityY(1.0f);
			}
			m_p_Object_Char->setObjectID(id);


			m_p_Object_Char->setAniCountX(0);
			m_p_Object_Char->setAniCountY(0);

			if (objType == UNITTYPE_DRAGON)
			{
				m_pSound_Roar->PlaySound(m_Resource_Roar, false, 1.0f);
				m_p_Object_Char->setObjectInfo(x, y, 0.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.2f);
				m_p_Object_Char->SetObjectType(UNITTYPE_DRAGON); // Ư�� ����
				m_p_Object_Char->setObjectSpeed(50.0f);
				m_p_Object_Char->setMaxAniSizeX(4);
				m_p_Object_Char->setMaxAniSizeY(1);
				m_p_Object_Char->setObjcetLife(DRAGON_MAX_LIFE);
				m_p_Object_Char->setObjcetDamage(10.0f);
				m_p_Object_Char->setTextureID(m_Team2_Dragon_TextureID);
			}

			else
			{
				m_p_Object_Char->setObjectInfo(x, y, 0.0f, 50.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.2f);
				
				if (ur_randomUnit(dre) > 0.4f)
				{
					m_p_Object_Char->SetObjectType(UNITTYPE_NORMAL); // �Ϲ� ����
					m_p_Object_Char->setObjectSpeed(100.0f);
					m_p_Object_Char->setMaxAniSizeX(10);
					m_p_Object_Char->setMaxAniSizeY(1);
					m_p_Object_Char->setObjcetLife(NORMAL_UNIT_MAX_LIFE);
					m_p_Object_Char->setObjcetDamage(NORMAL_UNIT_MAX_LIFE);
					m_p_Object_Char->setTextureID(m_Team2_NormalUnit_TextureID);
				}
				else
				{
					m_p_Object_Char->SetObjectType(UNITTYPE_SIEGE); // ���� ����
					m_p_Object_Char->setObjectSpeed(70.0f);
					m_p_Object_Char->setMaxAniSizeX(1);
					m_p_Object_Char->setMaxAniSizeY(1);
					m_p_Object_Char->setObjcetLife(SIEGE_UNIT_MAX_LIFE);
					m_p_Object_Char->setObjcetDamage(SIEGE_UNIT_MAX_LIFE);
					m_p_Object_Char->setTextureID(m_Team2_SiegeUnit_TextureID);
				}
			}
			m_CharObj_List.push_back(*m_p_Object_Char);
		}
		
		break;

	case OBJECT_BULLET:
		if (m_curBulletCount < MAX_BULLET_COUNT)
		{
			++m_curBulletCount;
			m_p_Object_Bullets = new Object();

			m_p_Object_Bullets->setObjectInfo(x, y, 0.0f, 20.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.3f);
			m_p_Object_Bullets->setObjcetLife(1.0f);
			m_p_Object_Bullets->setObjcetDamage(30.0f);
			m_p_Object_Bullets->setObjectSpeed(600.0f);
			m_p_Object_Bullets->setObjectID(id);
			m_p_Object_Bullets->SetTarget(&m_BuildingObj_List);
			m_p_Object_Bullets->SetDir_ToTarget();
			m_p_Object_Bullets->SetParticleTimer(0);

			if (id == OBJECT_TEAM_1)
			{
				if (!m_p_Object_Bullets->GetIsTargetting())
				{
					m_p_Object_Bullets->setObjectVelocityX(ur_randomBullet_VelocityX(dre));
					m_p_Object_Bullets->setObjectVelocityY(ur_randomT1VelocityY(dre));
					if (m_p_Object_Bullets->getObjectVelocity().x == 0.0f && m_p_Object_Bullets->getObjectVelocity().y == 0.0f) {
						m_p_Object_Bullets->setObjectVelocityX(ur_randomVelocityX(dre));
						m_p_Object_Bullets->setObjectVelocityY(-1.0f);
					}
				}
				
				m_p_Object_Bullets->setTextureID(m_Team1_Bullet_TextureID);
				m_p_Object_Bullets->setParticleDirY(1.0f); // ��ƼŬ ���� ����
			}

			else if (id == OBJECT_TEAM_2)
			{
				if (!m_p_Object_Bullets->GetIsTargetting())
				{
					m_p_Object_Bullets->setObjectVelocityX(ur_randomBullet_VelocityX(dre));
					m_p_Object_Bullets->setObjectVelocityY(ur_randomT2VelocityY(dre));
					if (m_p_Object_Bullets->getObjectVelocity().x == 0.0f && m_p_Object_Bullets->getObjectVelocity().y == 0.0f) {
						m_p_Object_Bullets->setObjectVelocityX(ur_randomVelocityX(dre));
						m_p_Object_Bullets->setObjectVelocityY(1.0f);
					}
				}

				m_p_Object_Bullets->setTextureID(m_Team2_Bullet_TextureID);
				m_p_Object_Bullets->setParticleDirY(-1.0f); // ��ƼŬ ���� ����
			}

			m_pSound_BulletShot->PlaySound(m_Resource_BulletShot, false, 0.3f);
			m_BulletObj_List.push_back(*m_p_Object_Bullets);
		}
		break;

	case OBJECT_ARROW:
		if (m_curArrowCount < MAX_ARROW_COUNT)
		{
			++m_curArrowCount;
			m_p_Object_Arrows = new Object();
			m_p_Object_Arrows->setObjectInfo(x, y, 0.0f, 30.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.3f);
			m_p_Object_Arrows->setObjcetLife(1.0f);
			m_p_Object_Arrows->setObjectSpeed(200.0f);
			m_p_Object_Arrows->setObjectID(id);
			m_p_Object_Arrows->SetObjectType(objType);

			if (id == OBJECT_TEAM_1)
			{
				switch (objType)
				{
				case UNITTYPE_NORMAL:
					m_pSound_NormalArrowShot->PlaySound(m_Resource_NormalArrowShot, false, 0.5f);
					m_p_Object_Arrows->setObjcetDamage(10.0f);
					m_p_Object_Arrows->setTextureID(m_Team1_Arrow_TextureID);
					break;
				case UNITTYPE_SIEGE:
					m_pSound_SiegeArrowShot->PlaySound(m_Resource_SiegeArrowShot, false, 0.7f);
					m_p_Object_Arrows->setObjcetDamage(20.0f);
					m_p_Object_Arrows->setTextureID(m_Team1_S_Arrow_TextureID);
					break;
				case UNITTYPE_DRAGON:
					m_pSound_DragonArrowShot->PlaySound(m_Resource_DragonArrowShot, false, 0.7f);
					m_p_Object_Arrows->setObjectSize(60.0f);
					m_p_Object_Arrows->setObjectSpeed(300.0f);
					m_p_Object_Arrows->setObjcetDamage(100.0f);
					m_p_Object_Arrows->setAniCountX(0);
					m_p_Object_Arrows->setAniCountY(0);
					m_p_Object_Arrows->setMaxAniSizeX(1);
					m_p_Object_Arrows->setMaxAniSizeY(6);
					m_p_Object_Arrows->setTextureID(m_Team1_D_Arrow_TextureID);
					break;
				}
			}
			else if (id == OBJECT_TEAM_2)
			{
				switch (objType)
				{
				case UNITTYPE_NORMAL:
					m_pSound_NormalArrowShot->PlaySound(m_Resource_NormalArrowShot, false, 0.5f);
					m_p_Object_Arrows->setObjcetDamage(10.0f);
					m_p_Object_Arrows->setTextureID(m_Team2_Arrow_TextureID);
					break;
				case UNITTYPE_SIEGE:
					m_pSound_SiegeArrowShot->PlaySound(m_Resource_SiegeArrowShot, false, 0.7f);
					m_p_Object_Arrows->setObjcetDamage(20.0f);
					m_p_Object_Arrows->setTextureID(m_Team2_S_Arrow_TextureID);
					break;
				case UNITTYPE_DRAGON:
					m_pSound_DragonArrowShot->PlaySound(m_Resource_DragonArrowShot, false, 0.7f);
					m_p_Object_Arrows->setObjectSize(60.0f);
					m_p_Object_Arrows->setObjectSpeed(300.0f);
					m_p_Object_Arrows->setObjcetDamage(100.0f);
					m_p_Object_Arrows->setAniCountX(0);
					m_p_Object_Arrows->setAniCountY(0);
					m_p_Object_Arrows->setMaxAniSizeX(1);
					m_p_Object_Arrows->setMaxAniSizeY(6);
					m_p_Object_Arrows->setTextureID(m_Team2_D_Arrow_TextureID);
					break;
				}
			}
			

			m_ArrowObj_List.push_back(*m_p_Object_Arrows);
		}
		break;
	}
};


void SceneMgr::DrawStatusUI(float charcooltime, float dragoncooltime)
{
	// UI â
	m_p_Renderer->DrawSolidRect(0.0f, 0.0f, 0.0f, 300.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.15f);

	// �ؽ�Ʈ
	m_p_Renderer->DrawText(-20.0f, 140.0f, GLUT_STROKE_ROMAN, 1.0f, 1.0f, 1.0f, "This is UI.");

	// �ؽ�Ʈ
	m_p_Renderer->DrawText(-80.0f, 120.0f, GLUT_STROKE_ROMAN, 1.0f, 1.0f, 1.0f, "Game Software Engineering Class");

	// ���� ���
	sprintf_s(m_text, sizeof(m_text), "Current Team1 Characters Count: %d", m_curT1CharCount);
	m_p_Renderer->DrawText(-80.0f, 100.0f, GLUT_STROKE_ROMAN, 1.0f, 1.0f, 1.0f, m_text);

	sprintf_s(m_text, sizeof(m_text), "Current Team2 Characters Count: %d", m_curT2CharCount);
	m_p_Renderer->DrawText(-80.0f, 80.0f, GLUT_STROKE_ROMAN, 1.0f, 1.0f, 1.0f, m_text);

	sprintf_s(m_text, sizeof(m_text), "Left Team1 Buildings Count: %d", m_Left_Team1_Building);
	m_p_Renderer->DrawText(-80.0f, 60.0f, GLUT_STROKE_ROMAN, 1.0f, 1.0f, 1.0f, m_text);

	sprintf_s(m_text, sizeof(m_text), "Left Team2 Buildings Count: %d", m_Left_Team2_Building);
	m_p_Renderer->DrawText(-80.0f, 40.0f, GLUT_STROKE_ROMAN, 1.0f, 1.0f, 1.0f, m_text);

	sprintf_s(m_text, sizeof(m_text), "Team1 Character Summon CoolTime: %.3f / %.3f", getElapsedTime(), TEAM1_UNIT_COOLTIME);
	m_p_Renderer->DrawText(-110.0f, -20.0f, GLUT_STROKE_ROMAN, 1.0f, 1.0f, 1.0f, m_text);
	sprintf_s(m_text, sizeof(m_text), "Team1 Dragon Summon CoolTime: %.3f / %.3f", getElapsedTime(), TEAM1_DRAGON_COOLTIME);
	m_p_Renderer->DrawText(-110.0f, -40.0f, GLUT_STROKE_ROMAN, 1.0f, 1.0f, 1.0f, m_text);

	sprintf_s(m_text, sizeof(m_text), "Team2 Character Summon CoolTime: %.3f / %.3f", charcooltime, TEAM2_UNIT_COOLTIME);
	m_p_Renderer->DrawText(-110.0f, -60.0f, GLUT_STROKE_ROMAN, 1.0f, 1.0f, 1.0f, m_text);
	sprintf_s(m_text, sizeof(m_text), "Team2 Dragon Summon CoolTime: %.3f / %.3f", dragoncooltime, TEAM2_DRAGON_COOLTIME);
	m_p_Renderer->DrawText(-110.0f, -80.0f, GLUT_STROKE_ROMAN, 1.0f, 1.0f, 1.0f, m_text);
};


void SceneMgr::DrawObjects(float elapsedTime, float coolTime, float dragoncooltime) {
	// ���ȭ��
	m_p_Renderer->DrawTexturedRect(0.0f, 0.0f, 0.0f, 800.0f, 1.0f, 1.0f, 1.0f, 0.8f, m_BackgroundTextureID, 0.99f);


	// �߾Ӽ�
	for (int i = -WINDOWSIZE_WIDTH / 2; i < WINDOWSIZE_WIDTH / 2; ++i)
		m_p_Renderer->DrawSolidRect(i, 0, 0, 1, 1, 1, 1, 1, 0.98f);

	if (!m_BulletObj_List.empty()) // �Ѿ�
	{
		for (m_iter_bullet = m_BulletObj_List.begin(); m_iter_bullet != m_BulletObj_List.end(); ++m_iter_bullet)
		{
			m_p_Renderer->DrawParticle
			(
				m_iter_bullet->getObjectPosition_X(), m_iter_bullet->getObjectPosition_Y(), m_iter_bullet->getObjectPosition_Z(),
				m_iter_bullet->getObjectSize(),
				m_iter_bullet->getObjectColor_R(), m_iter_bullet->getObjectColor_G(), m_iter_bullet->getObjectColor_B(), m_iter_bullet->getObjectColor_A(),
				0.0f, m_iter_bullet->getParticleDirY(),
				m_iter_bullet->getTextureID(), m_iter_bullet->GetParticleTimer(),
				m_iter_bullet->getRenderLevel()
			);
			m_iter_bullet->SetParticleTimer(m_iter_bullet->GetParticleTimer() + m_Bullet_Timer);
		}
	}

	if (!m_ArrowObj_List.empty()) // ȭ��
	{
		for (m_iter_arrow = m_ArrowObj_List.begin(); m_iter_arrow != m_ArrowObj_List.end(); ++m_iter_arrow)
		{
			if (m_iter_arrow->GetObjectType() == UNITTYPE_DRAGON)
			{
				// �巡�� �ַο� animation
				m_p_Renderer->DrawTexturedRectSeq
				(
					m_iter_arrow->getObjectPosition_X(), m_iter_arrow->getObjectPosition_Y(), m_iter_arrow->getObjectPosition_Z(),
					m_iter_arrow->getObjectSize(),
					m_iter_arrow->getObjectColor_R(), m_iter_arrow->getObjectColor_G(), m_iter_arrow->getObjectColor_B(), m_iter_arrow->getObjectColor_A(),
					m_iter_arrow->getTextureID(), m_iter_arrow->getAniCountX(), m_iter_arrow->getAniCountY(), m_iter_arrow->getMaxAniSizeX(), m_iter_arrow->getMaxAniSizeY(),
					m_iter_arrow->getRenderLevel()
				);

				// animation ����
				m_iter_arrow->plusAniCountX(1.0f);
				// animation �ִ� �� ���� �� �ʱ�ȭ
				if (m_iter_arrow->getAniCountX() > m_iter_arrow->getMaxAniSizeX()) m_iter_arrow->setAniCountX(0);
			}

			else 
			{
				m_p_Renderer->DrawTexturedRect
				(
					m_iter_arrow->getObjectPosition_X(), m_iter_arrow->getObjectPosition_Y(), m_iter_arrow->getObjectPosition_Z(),
					m_iter_arrow->getObjectSize(),
					m_iter_arrow->getObjectColor_R(), m_iter_arrow->getObjectColor_G(), m_iter_arrow->getObjectColor_B(), m_iter_arrow->getObjectColor_A(),
					m_iter_arrow->getTextureID(),
					m_iter_arrow->getRenderLevel()
				);
			}
		}
	}

	if (!m_CharObj_List.empty()) // ĳ����
	{
		for (m_iter_char = m_CharObj_List.begin(); m_iter_char != m_CharObj_List.end(); ++m_iter_char)
		{
			// ĳ���� animation
			m_p_Renderer->DrawTexturedRectSeq
			(
				m_iter_char->getObjectPosition_X(), m_iter_char->getObjectPosition_Y(), m_iter_char->getObjectPosition_Z(),
				m_iter_char->getObjectSize(),
				m_iter_char->getObjectColor_R(), m_iter_char->getObjectColor_G(), m_iter_char->getObjectColor_B(), m_iter_char->getObjectColor_A(),
				m_iter_char->getTextureID(), m_iter_char->getAniCountX(), m_iter_char->getAniCountY(), m_iter_char->getMaxAniSizeX(), m_iter_char->getMaxAniSizeY(),
				m_iter_char->getRenderLevel()
			);

			// animation ����
			m_iter_char->plusAniCountX(0.1f * m_iter_char->getMaxAniSizeX());
			// animation �ִ� �� ���� �� �ʱ�ȭ
			if (m_iter_char->getAniCountX() > m_iter_char->getMaxAniSizeX()) m_iter_char->setAniCountX(0);

			float max_life;
			switch (m_iter_char->GetObjectType())
			{
			case UNITTYPE_NORMAL:
				max_life = NORMAL_UNIT_MAX_LIFE;
				break;
			case UNITTYPE_SIEGE:
				max_life = SIEGE_UNIT_MAX_LIFE;
				break;
			case UNITTYPE_DRAGON:
				max_life = DRAGON_MAX_LIFE;
				break;
			}
			// ������ ������
			m_p_Renderer->DrawSolidRectGauge(
				m_iter_char->getObjectPosition_X(), m_iter_char->getObjectPosition_Y() + m_iter_char->getObjectSize(), m_iter_char->getObjectPosition_Z(),
				m_iter_char->getObjectSize(), 10.0f,
				m_iter_char->getObjectColor_R(), m_iter_char->getObjectColor_G(), m_iter_char->getObjectColor_B(), m_iter_char->getObjectColor_A(),
				m_iter_char->getObjectLife() / max_life,
				m_iter_char->getRenderLevel()
			);
		}
	}

	if (!m_BuildingObj_List.empty()) // �ǹ�
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
			float max_life;
			switch (m_iter_building->GetObjectType())
			{
			case BUILDINGTYPE_MASTER:
				max_life = MASTER_BUILDING_MAX_LIFE;
				break;
			case BUILDINGTYPE_SUB:
				max_life = SUB_BUILDING_MAX_LIFE;
				break;
			}
			if (m_iter_building->getObjectID() == OBJECT_TEAM_1)
			{
				m_p_Renderer->DrawSolidRectGauge(
					m_iter_building->getObjectPosition_X(), m_iter_building->getObjectPosition_Y() + m_iter_building->getObjectSize() - 30.0f, m_iter_building->getObjectPosition_Z(),
					m_iter_building->getObjectSize(), 10.0f,
					1.0f, 0.0f, 0.0f, m_iter_building->getObjectColor_A(),
					m_iter_building->getObjectLife() / max_life,
					m_iter_building->getRenderLevel()
				);
			}
			else if (m_iter_building->getObjectID() == OBJECT_TEAM_2)
			{

				m_p_Renderer->DrawSolidRectGauge(
					m_iter_building->getObjectPosition_X() + 5.0f, m_iter_building->getObjectPosition_Y() + m_iter_building->getObjectSize() - 30.0f, m_iter_building->getObjectPosition_Z(),
					m_iter_building->getObjectSize(), 10.0f,
					0.0f, 0.0f, 1.0f, m_iter_building->getObjectColor_A(),
					m_iter_building->getObjectLife() / max_life,
					m_iter_building->getRenderLevel()
				);
			}
		}
	}

	// ���� ����â UI
	if (GetIsStatusUI())
		DrawStatusUI(coolTime, dragoncooltime);
	else
	{
		m_p_Renderer->DrawText(0.0f, 0.0f, GLUT_STROKE_ROMAN, 1.0f, 1.0f, 1.0f, "If you push CTRL Key, UI will POP UP!");
		if (!m_isTeam1_Alive)
			m_p_Renderer->DrawText(-20.0f, 50.0f, GLUT_STROKE_ROMAN, 1.0f, 1.0f, 1.0f, "YOU WIN!");
		if (!m_isTeam2_Alive)
			m_p_Renderer->DrawText(-20.0f, 50.0f, GLUT_STROKE_ROMAN, 1.0f, 1.0f, 1.0f, "YOU LOSE!");
		if (!m_isTeam1_Alive && !m_isTeam2_Alive)
			m_p_Renderer->DrawText(-20.0f, 50.0f, GLUT_STROKE_ROMAN, 1.0f, 1.0f, 1.0f, "DRAW!");
	}

	

	// ����ȿ��
	m_p_Renderer->DrawParticleClimate(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -0.1f, -0.1f, m_Climate_Rain_TextureID, m_Climate_Timer, 0.01);
	m_Climate_Timer += elapsedTime / 1000.0f;
	if (m_Climate_Timer > 30.0f)
		m_Climate_Timer = 0.0f;
}


void SceneMgr::ObjectsCollisionCheck()
{
	if (!m_BulletObj_List.empty()) // �Ѿ˰�
	{
		for (m_iter_bullet = m_BulletObj_List.begin(); m_iter_bullet != m_BulletObj_List.end(); ++m_iter_bullet)
		{
			if (!m_CharObj_List.empty()) // ĳ����
			{
				for (m_iter_char = m_CharObj_List.begin(); m_iter_char != m_CharObj_List.end(); ++m_iter_char)
				{
					if ((m_iter_bullet->getObjectID() != m_iter_char->getObjectID()) && m_iter_char->IsCollide(m_iter_bullet->getObjectCollider()))
					{
						m_iter_char->damageObjcetLife(m_iter_bullet->getObjectDamage());
						m_iter_bullet->setObjectIsDead(true);
					}
				}
			}

			if (!m_BuildingObj_List.empty()) // �ǹ�
			{
				for (m_iter_building = m_BuildingObj_List.begin(); m_iter_building != m_BuildingObj_List.end(); ++m_iter_building)
				{
					if ((m_iter_bullet->getObjectID() != m_iter_building->getObjectID()) && m_iter_building->IsCollide(m_iter_bullet->getObjectCollider()))
					{
						m_pSound_BulletCrash->PlaySound(m_Resource_BulletCrash, false, 0.7f);
						m_iter_building->damageObjcetLife(m_iter_bullet->getObjectDamage());
						m_iter_bullet->setObjectIsDead(true);
					}
				}
			}
		}
	}


	if (!m_ArrowObj_List.empty()) // ȭ���
	{
		for (m_iter_arrow = m_ArrowObj_List.begin(); m_iter_arrow != m_ArrowObj_List.end(); ++m_iter_arrow)
		{
			if (!m_CharObj_List.empty()) // ĳ����
			{
				for (m_iter_char = m_CharObj_List.begin(); m_iter_char != m_CharObj_List.end(); ++m_iter_char)
				{
					if ((m_iter_arrow->getObjectID() != m_iter_char->getObjectID()) && m_iter_char->IsCollide(m_iter_arrow->getObjectCollider()))
					{
						if (m_iter_arrow->GetObjectType() == UNITTYPE_DRAGON)
							m_pSound_DragonArrowBlast->PlaySound(m_Resource_DragonArrowBlast, false, 1.0f);
						m_iter_char->damageObjcetLife(m_iter_arrow->getObjectDamage());
						m_iter_arrow->setObjectIsDead(true);
					}
				}
			}
			if (!m_BuildingObj_List.empty()) // �ǹ�
			{
				for (m_iter_building = m_BuildingObj_List.begin(); m_iter_building != m_BuildingObj_List.end(); ++m_iter_building)
				{
					if ((m_iter_arrow->getObjectID() != m_iter_building->getObjectID()) && m_iter_building->IsCollide(m_iter_arrow->getObjectCollider()))
					{
						if (m_iter_arrow->GetObjectType() == UNITTYPE_DRAGON)
							m_pSound_DragonArrowBlast->PlaySound(m_Resource_DragonArrowBlast, false, 1.0f);
						m_iter_building->damageObjcetLife(m_iter_arrow->getObjectDamage());
						m_iter_arrow->setObjectIsDead(true);
					}
				}
			}
		}
	}

	if (!m_CharObj_List.empty()) // ĳ���Ϳ�
	{
		for (m_iter_char = m_CharObj_List.begin(); m_iter_char != m_CharObj_List.end(); ++m_iter_char)
		{
			if (!m_BuildingObj_List.empty()) // �ǹ�
			{
				for (m_iter_building = m_BuildingObj_List.begin(); m_iter_building != m_BuildingObj_List.end(); ++m_iter_building)
				{
					if ((m_iter_char->getObjectID() != m_iter_building->getObjectID()) && m_iter_building->IsCollide(m_iter_char->getObjectCollider()))
					{
						m_iter_building->damageObjcetLife(m_iter_char->getObjectDamage());
						m_iter_char->damageObjcetLife(m_iter_building->getObjectDamage());
					}
				}
			}
			for (m_iter_char_temp = m_CharObj_List.begin(); m_iter_char_temp != m_CharObj_List.end(); ++m_iter_char_temp) // ĳ����
			{
				if ((m_iter_char_temp->getObjectID() != m_iter_char->getObjectID()) && m_iter_char_temp->IsCollide(m_iter_char->getObjectCollider()))
				{
					m_iter_char_temp->damageObjcetLife(m_iter_char->getObjectDamage());
					m_iter_char->damageObjcetLife(m_iter_char_temp->getObjectDamage());
				}
			}
		}
	}
	
}


void SceneMgr::UpdateObjects(float elapsedTime)
{
	// ���� ���� ĳ���� ����
	plusElapsedTime(elapsedTime / 1000.0f);
	m_Bullet_Timer += elapsedTime / 1000.0f;
	m_Team1_Dragon_Timer += elapsedTime / 1000.0f;

	if (m_Bullet_Timer >= 30.0f)
		m_Bullet_Timer = 0.0f;

	if (m_isTeam1_Alive && getElapsedTime() >= TEAM1_UNIT_COOLTIME) // Team1 ĳ���� ����
	{
		setElapsedTime(0.0f);
		BuildObjects
		(
			ur_randomPosX(dre),
			ur_randomPosY(dre),
			OBJECT_TEAM_1,
			OBJECT_CHARACTER,
			0
		);
	}
	if (m_isTeam1_Alive && m_Team1_Dragon_Timer >= TEAM1_DRAGON_COOLTIME) // Team1 �巡�� ����
	{
		m_Team1_Dragon_Timer = 0.0f;
		BuildObjects
		(
			ur_randomPosX(dre),
			ur_randomPosY(dre),
			OBJECT_TEAM_1,
			OBJECT_CHARACTER,
			UNITTYPE_DRAGON
		);
	}

	// ĳ���� ������Ʈ
	if (!m_CharObj_List.empty())
	{
		for (m_iter_char = m_CharObj_List.begin(); m_iter_char != m_CharObj_List.end(); ++m_iter_char)
		{
			m_iter_char->plusObjectCoolTime(elapsedTime / 1000.0f);

			if (m_iter_char->GetObjectType() == UNITTYPE_NORMAL || m_iter_char->GetObjectType() == UNITTYPE_DRAGON)
			{
				// �Ϲ� ���� / Ư�� ������ ��� ������ ���� Ÿ������ �Ѵ�.
				m_iter_char->SetTarget(&m_CharObj_List);

				// ��� ������ ã�� ���ߴٸ� �������� �ǹ��� Ÿ������ �Ѵ�.
				if (!m_iter_char->GetIsTargetting())
					m_iter_char->SetTarget(&m_BuildingObj_List);
			}

			else if (m_iter_char->GetObjectType() == UNITTYPE_SIEGE)
			{
				// ���������� �ǹ��� Ÿ�������Ѵ�.
				if (!m_iter_char->GetIsTargetting())
					m_iter_char->SetTarget(&m_BuildingObj_List);
			}
			

			m_iter_char->IsArrived();
			m_iter_char->update(elapsedTime);
			m_iter_char->WallCollision();


			if (m_iter_char->GetObjectType() != UNITTYPE_DRAGON && m_iter_char->getObjectCoolTime() >= ARROW_COOLTIME) // �ַο� ����
			{
				m_iter_char->setObjectCoolTime(0.0f);
				BuildObjects
				(
					m_iter_char->getObjectPosition_X() + m_iter_char->getObjectVelocity().x * 20.0f,
					m_iter_char->getObjectPosition_Y() + m_iter_char->getObjectVelocity().y * 20.0f,
					m_iter_char->getObjectID(),
					OBJECT_ARROW,
					m_iter_char->GetObjectType()
				);
				m_ArrowObj_List.back().setObjectVelocityX(m_iter_char->getObjectVelocity().x);
				m_ArrowObj_List.back().setObjectVelocityY(m_iter_char->getObjectVelocity().y);
			}

			if (m_iter_char->GetObjectType() == UNITTYPE_DRAGON && m_iter_char->getObjectCoolTime() >= DRAGON_ARROW_COOLTIME) // �巡�� �ַο� ����
			{
				m_iter_char->setObjectCoolTime(0.0f);
				BuildObjects
				(
					m_iter_char->getObjectPosition_X() + m_iter_char->getObjectVelocity().x * 20.0f,
					m_iter_char->getObjectPosition_Y() + m_iter_char->getObjectVelocity().y * 20.0f,
					m_iter_char->getObjectID(),
					OBJECT_ARROW,
					m_iter_char->GetObjectType()
				);
				m_ArrowObj_List.back().setObjectVelocityX(m_iter_char->getObjectVelocity().x);
				m_ArrowObj_List.back().setObjectVelocityY(m_iter_char->getObjectVelocity().y);
			}
		}
	}

	// �ǹ� ������Ʈ
	if (!m_BuildingObj_List.empty())
	{
		m_Left_Team1_Building = 0;
		m_Left_Team2_Building = 0;
		for (m_iter_building = m_BuildingObj_List.begin(); m_iter_building != m_BuildingObj_List.end(); ++m_iter_building)
		{
			m_iter_building->plusObjectCoolTime(elapsedTime / 1000.0f);
			if (m_isTeam1_Alive && m_isTeam2_Alive && m_iter_building->getObjectCoolTime() >= BULLET_COOLTIME) // �Ѿ� ����
			{
				m_iter_building->setObjectCoolTime(0.0f);
				BuildObjects(m_iter_building->getObjectPosition_X(), m_iter_building->getObjectPosition_Y(), m_iter_building->getObjectID(), OBJECT_BULLET, 0);
			}
			if (m_iter_building->getObjectID() == OBJECT_TEAM_1)
				++m_Left_Team1_Building;
			else
				++m_Left_Team2_Building;
		}
		if (m_Left_Team1_Building <= 0)
			m_isTeam1_Alive = false;
		if (m_Left_Team2_Building <= 0)
			m_isTeam2_Alive = false;
	}

	// �Ѿ� ������Ʈ
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

	// ȭ�� ������Ʈ
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

	ObjectsCollisionCheck(); // �浹 �˻�
	CheckDeadObject(); // ���� ������Ʈ �˻�
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
				m_pSound_CharDead->PlaySound(m_Resource_CharDead, false, 1.0f);
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