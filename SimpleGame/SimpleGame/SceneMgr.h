#pragma once
#include "stdafx.h"
#include "Object.h"
#include "Renderer.h"
#include "Sound.h"


#define OBJECT_BUILDING 0
#define OBJECT_CHARACTER 1
#define OBJECT_BULLET 2
#define OBJECT_ARROW 3
#define OBJECT_TEAM_1 4
#define OBJECT_TEAM_2 5

#define UNITTYPE_NORMAL 101
#define UNITTYPE_SIEGE 102
#define UNITTYPE_FLYING 103

#define MAX_BULLET_COUNT 20
#define MAX_ARROW_COUNT 50
#define MAX_CHARACTER_COUNT 10

class SceneMgr
{
private:

	int m_curBulletCount = 0;
	int m_curArrowCount = 0;
	int m_curT1CharCount = 0;
	int m_curT2CharCount = 0;

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

	Renderer* m_p_Renderer;
	Sound* m_pSound;

	GLuint m_BackgroundSound;

	GLuint m_BackgroundTextureID;
	GLuint m_Climate_Rain_TextureID;
	GLuint m_Team1_Bullet_TextureID;
	GLuint m_Team2_Bullet_TextureID;
	GLuint m_Team1_Arrow_TextureID;
	GLuint m_Team2_Arrow_TextureID;
	GLuint m_Team1_NormalUnit_TextureID;
	GLuint m_Team2_NormalUnit_TextureID;
	GLuint m_Team1_SiegeUnit_TextureID;
	GLuint m_Team2_SiegeUnit_TextureID;
	GLuint m_Team1_MasterBuilding_TextureID;
	GLuint m_Team2_MasterBuilding_TextureID;
	GLuint m_Team1_SubBuilding_TextureID;
	GLuint m_Team2_SubBuilding_TextureID;

	float m_Climate_Timer = 0.0f;

	bool m_is_StatusUI;
	float m_time = 5.0f;
	
public:
	SceneMgr();
	~SceneMgr();

	void BuildObjects(float x, float y, int id, int type);
	void DrawObjects(float elapsedTime);
	void ObjectsCollisionCheck();
	void UpdateObjects(float elapsedTime);
	void CheckDeadObject();

	bool GetIsStatusUI() { return m_is_StatusUI; };
	void SetIsStatusUI(bool b) { m_is_StatusUI = b; };

	void setElapsedTime(float t) { m_time = t; };
	void plusElapsedTime(float t) { m_time += t; };
	float getElapsedTime() { return m_time; };

	void DrawStatusUI();

	void DestroyObjects();
};