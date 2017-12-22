/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "SceneMgr.h"


float g_prevTime = 0.0f;
float currTime = 0.0f;
float elapsedTime = 0.0f;
float char_coolTime = TEAM2_UNIT_COOLTIME;
float dragon_coolTime = TEAM2_DRAGON_COOLTIME;
SceneMgr* g_SceneMgr = NULL;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	currTime = timeGetTime();
	elapsedTime = currTime - g_prevTime;

	if (char_coolTime <= TEAM2_UNIT_COOLTIME)
		char_coolTime += elapsedTime/1000.f;
	else char_coolTime = TEAM2_UNIT_COOLTIME;

	if (dragon_coolTime <= TEAM2_DRAGON_COOLTIME)
		dragon_coolTime += elapsedTime / 1000.f;
	else dragon_coolTime = TEAM2_DRAGON_COOLTIME;

	g_SceneMgr->UpdateObjects(elapsedTime);
	g_SceneMgr->DrawObjects(elapsedTime, char_coolTime, dragon_coolTime);
	g_prevTime = currTime;

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	// 좌클릭 시 해당 위치에 캐릭터 생성
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && char_coolTime >= TEAM2_UNIT_COOLTIME &&  WINDOWSIZE_HEIGHT / 2 - y < 0)
	{
		char_coolTime = 0.0f;
		g_SceneMgr->BuildObjects(x - WINDOWSIZE_WIDTH / 2, WINDOWSIZE_HEIGHT/ 2 - y, OBJECT_TEAM_2, OBJECT_CHARACTER, 0);
	}

	// 우클릭 시 해당 위치에 드래곤 생성
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && dragon_coolTime >= TEAM2_DRAGON_COOLTIME &&  WINDOWSIZE_HEIGHT / 2 - y < 0)
	{
		dragon_coolTime = 0.0f;
		g_SceneMgr->BuildObjects(x - WINDOWSIZE_WIDTH / 2, WINDOWSIZE_HEIGHT / 2 - y, OBJECT_TEAM_2, OBJECT_CHARACTER, UNITTYPE_DRAGON);
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_CTRL_L)
	{
		g_SceneMgr->SetIsStatusUI(true);
	}
	RenderScene();
}

void SpecialKeyUp(int key, int x, int y)
{
	if (key == GLUT_KEY_CTRL_L)
	{
		g_SceneMgr->SetIsStatusUI(false);
	}
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOWSIZE_WIDTH, WINDOWSIZE_HEIGHT);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize SceneMgr
	g_SceneMgr = new SceneMgr();
	g_prevTime = timeGetTime();
	cout << "\nScene Manager Loaded" << endl;

	//-------------------------------
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	glutSpecialUpFunc(SpecialKeyUp);
	//-------------------------------

	glutMainLoop();

	cout << "\nScene Manager deleted" << endl;
	delete g_SceneMgr;

    return 0;
}

