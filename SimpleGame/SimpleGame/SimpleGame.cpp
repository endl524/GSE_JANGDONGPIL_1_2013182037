/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "SceneMgr.h"

using namespace std;

DWORD g_prevTime = 0;
SceneMgr* g_SceneMgr = NULL;

void RenderScene(void)
{
	// background setting
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - g_prevTime;
	g_prevTime = currTime;

	g_SceneMgr->UpdateObjects(elapsedTime);
	g_SceneMgr->DrawObjects();

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	/*
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		g_Object_rectAngle->setRectPosition_X(x - 250);
		g_Object_rectAngle->setRectPosition_Y(y - 300); // 수정 필요
		
					// 새 오브젝트 생성
			++rectCount;
		g_Object_rectAngleS[rectCount] = new Object();
		g_Object_rectAngleS[rectCount]->setRectInfo(0, 0, 0, 10, 1.0f, 0.0f, 1.0f, 1.0f);
		g_Object_rectAngleS[rectCount]->setRectVelocity(2, 3);
		
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		
			
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		if (rectCount >= 0) {
			delete g_Object_rectAngleS[rectCount];
			--rectCount;
			
		}
		
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		
			
	}*/
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
	g_SceneMgr->BuildObjects();

	//-------------------------------
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	//-------------------------------

	glutMainLoop();

	g_SceneMgr->DestroyObjects();
	cout << "\nScene Manager deleted" << endl;
	delete g_SceneMgr;

    return 0;
}

