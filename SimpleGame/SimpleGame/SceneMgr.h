#pragma once
#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"
#include "Sound.h"


// object type
#define OBJECT_BUILDING 0
#define OBJECT_CHARACTER 1
#define OBJECT_BULLET 2
#define OBJECT_ARROW 3

#define OBJECT_TEAM_1 4
#define OBJECT_TEAM_2 5

// unit type
#define UNITTYPE_NORMAL 101
#define UNITTYPE_SIEGE 102
#define UNITTYPE_DRAGON 103

#define BUILDINGTYPE_MASTER 201
#define BUILDINGTYPE_SUB 202

// count
#define MAX_BULLET_COUNT 20
#define MAX_ARROW_COUNT 50
#define MAX_CHARACTER_COUNT 10

// cooltime
#define BULLET_COOLTIME 3.0f
#define ARROW_COOLTIME 1.5f
#define DRAGON_ARROW_COOLTIME 2.0f

#define TEAM1_UNIT_COOLTIME 1.0f
#define TEAM1_DRAGON_COOLTIME 10.0f
#define TEAM2_UNIT_COOLTIME 1.0f
#define TEAM2_DRAGON_COOLTIME 10.0f

// objects info
#define MASTER_BUILDING_MAX_LIFE 1000.0f
#define SUB_BUILDING_MAX_LIFE 500.0f
#define NORMAL_UNIT_MAX_LIFE 10.0f
#define SIEGE_UNIT_MAX_LIFE 20.0f
#define DRAGON_MAX_LIFE 350.0f

class SceneMgr
{
private:

	int m_curBulletCount = 0;
	int m_curArrowCount = 0;
	int m_curT1CharCount = 0;
	int m_curT2CharCount = 0;

	int m_Left_Team1_Building = 0;
	int m_Left_Team2_Building = 0;

	bool m_isTeam1_Alive = true;
	bool m_isTeam2_Alive = true;

	Object* m_p_Object_Bullets;
	list<Object> m_BulletObj_List;
	list<Object>::iterator m_iter_bullet;

	Object* m_p_Object_Building;
	list<Object> m_BuildingObj_List;
	list<Object>::iterator m_iter_building;

	Object* m_p_Object_Arrows;
	list<Object> m_ArrowObj_List;
	list<Object>::iterator m_iter_arrow;

	Object* m_p_Object_Char;
	list<Object> m_CharObj_List;
	list<Object>::iterator m_iter_char;
	list<Object>::iterator m_iter_char_temp;


	Renderer* m_p_Renderer;


	Sound* m_pSound_BGM;
	GLuint m_Resource_BGM;

	Sound* m_pSound_BulletShot;
	GLuint m_Resource_BulletShot;
	Sound* m_pSound_BulletCrash;
	GLuint m_Resource_BulletCrash;

	Sound* m_pSound_NormalArrowShot;
	GLuint m_Resource_NormalArrowShot;
	Sound* m_pSound_SiegeArrowShot;
	GLuint m_Resource_SiegeArrowShot;
	Sound* m_pSound_DragonArrowShot;
	GLuint m_Resource_DragonArrowShot;

	Sound* m_pSound_DragonArrowBlast;
	GLuint m_Resource_DragonArrowBlast;

	Sound* m_pSound_CharDead;
	GLuint m_Resource_CharDead;

	Sound* m_pSound_Roar;
	GLuint m_Resource_Roar;

	


	GLuint m_BackgroundTextureID;
	GLuint m_Climate_Rain_TextureID;
	GLuint m_Climate_Star_TextureID;

	GLuint m_Team1_Bullet_TextureID;
	GLuint m_Team2_Bullet_TextureID;
	GLuint m_Team1_Arrow_TextureID;
	GLuint m_Team2_Arrow_TextureID;
	GLuint m_Team1_S_Arrow_TextureID;
	GLuint m_Team2_S_Arrow_TextureID;
	GLuint m_Team1_D_Arrow_TextureID;
	GLuint m_Team2_D_Arrow_TextureID;

	GLuint m_Team1_NormalUnit_TextureID;
	GLuint m_Team2_NormalUnit_TextureID;
	GLuint m_Team1_SiegeUnit_TextureID;
	GLuint m_Team2_SiegeUnit_TextureID;
	GLuint m_Team1_Dragon_TextureID;
	GLuint m_Team2_Dragon_TextureID;


	GLuint m_Team1_MasterBuilding_TextureID;
	GLuint m_Team2_MasterBuilding_TextureID;
	GLuint m_Team1_SubBuilding_TextureID;
	GLuint m_Team2_SubBuilding_TextureID;

	float m_Climate_Timer = 0.0f;
	float m_Bullet_Timer = 0.0f;
	float m_Team1_Dragon_Timer = 0.0f;


	bool m_is_StatusUI;
	float m_time = 5.0f;
	
	char m_text[100];

public:
	SceneMgr();
	~SceneMgr();

	void BuildObjects(float x, float y, int id, int type, int objType);
	void DrawObjects(float elapsedTime, float coolTime, float dragoncooltime);
	void ObjectsCollisionCheck();
	void UpdateObjects(float elapsedTime);
	void CheckDeadObject();

	bool GetIsStatusUI() { return m_is_StatusUI; };
	void SetIsStatusUI(bool b) { m_is_StatusUI = b; };

	void setElapsedTime(float t) { m_time = t; };
	void plusElapsedTime(float t) { m_time += t; };
	float getElapsedTime() { return m_time; };

	void DrawStatusUI(float cooltime, float dragoncooltime);

	void DestroyObjects();
};