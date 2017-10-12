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

#include "Renderer.h"
#include "Object.h"

#define rectsNUM 100
Renderer* g_Renderer = NULL;
Object* g_Object_rectAngle = NULL;
int rectCount = -1;
Object* g_Object_rectAngleS[rectsNUM];

void RenderScene(void)
{
	// background setting
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// rendering
	g_Renderer->DrawSolidRect(
		g_Object_rectAngle->getRectPosition_X(), g_Object_rectAngle->getRectPosition_Y(), g_Object_rectAngle->getRectPosition_Z(),
		g_Object_rectAngle->getRectSize(),
		g_Object_rectAngle->getRectColor_R(), g_Object_rectAngle->getRectColor_G(), g_Object_rectAngle->getRectColor_B(), g_Object_rectAngle->getRectColor_A()
	);

	for (int r = 0; r < rectCount; ++r) {
		g_Renderer->DrawSolidRect(
			g_Object_rectAngleS[r]->getRectPosition_X(), g_Object_rectAngleS[r]->getRectPosition_Y(), g_Object_rectAngleS[r]->getRectPosition_Z(),
			g_Object_rectAngleS[r]->getRectSize(),
			g_Object_rectAngleS[r]->getRectColor_R(), g_Object_rectAngleS[r]->getRectColor_G(), g_Object_rectAngleS[r]->getRectColor_B(), g_Object_rectAngleS[r]->getRectColor_A()
		);
	}



	// updating
	g_Object_rectAngle->update();

	for (int r = 0; r < rectCount; ++r) {
		g_Object_rectAngleS[r]->update();
	}

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		g_Object_rectAngle->setRectPosition_X(x-250);
		g_Object_rectAngle->setRectPosition_Y(y-300); // 수정 필요

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

	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		if (g_Object_rectAngle->getRectVelocity().y <= 100)
			g_Object_rectAngle->setRectVelocity(
				g_Object_rectAngle->getRectVelocity().x,
				g_Object_rectAngle->getRectVelocity().y + 1
			);
		break;
	case GLUT_KEY_DOWN:
		if (g_Object_rectAngle->getRectVelocity().y >= -100)
			g_Object_rectAngle->setRectVelocity(
				g_Object_rectAngle->getRectVelocity().x,
				g_Object_rectAngle->getRectVelocity().y - 1
			);
		break;
	case GLUT_KEY_RIGHT:
		if (g_Object_rectAngle->getRectVelocity().x <= 100)
			g_Object_rectAngle->setRectVelocity(
				g_Object_rectAngle->getRectVelocity().x + 1,
				g_Object_rectAngle->getRectVelocity().y
			);
		break;
	case GLUT_KEY_LEFT:
		if (g_Object_rectAngle->getRectVelocity().x >= -100)
			g_Object_rectAngle->setRectVelocity(
				g_Object_rectAngle->getRectVelocity().x - 1,
				g_Object_rectAngle->getRectVelocity().y
			);
		break;
	}
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
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	// Initialize Object
	g_Object_rectAngle = new Object();
	g_Object_rectAngle->setRectInfo(0, 0, 0, 10, 0.5f, 5.0f, 1.0f, 1.0f);
	g_Object_rectAngle->setRectVelocity(5, 3);

	//-------------------------------
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	//-------------------------------

	glutMainLoop();

	delete g_Object_rectAngle;
	delete g_Renderer;
	if (g_Object_rectAngleS) delete g_Object_rectAngleS;
    return 0;
}

