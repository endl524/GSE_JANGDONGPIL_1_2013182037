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


DWORD g_prevTime = 0;
DWORD currTime = 0;
DWORD elapsedTime = 0;
SceneMgr* g_SceneMgr = NULL;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	currTime = timeGetTime();
	elapsedTime = currTime - g_prevTime;

	g_SceneMgr->setElapsedTime(elapsedTime);
	g_SceneMgr->UpdateObjects(elapsedTime);
	g_SceneMgr->DrawObjects();

	g_prevTime = currTime;

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	// Ŭ�� �� �ش� ��ġ�� ĳ���� ����
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		g_SceneMgr->BuildObjects(x - 250, 250 - y, 0, OBJECT_CHARACTER);
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
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

	// default �ǹ� ����
	g_SceneMgr->BuildObjects(0.0f, 0.0f, 0, OBJECT_BUILDING);

	//-------------------------------
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	//-------------------------------

	glutMainLoop();

	cout << "\nScene Manager deleted" << endl;
	delete g_SceneMgr;

    return 0;
}

