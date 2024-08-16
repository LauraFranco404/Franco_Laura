#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "glApplication.h"
#include "glutWindow.h"
#include "glsl.h"
#include <time.h>
#include <iostream>

#define PLAYER_SPEED 10
#define Z_POS 0

class Player
{

private:
	float posX, posY;
public:
	Player() {
		posX = 0;
		posY = 0;
		printPos();
	}

	void Move(float amount_x, float amount_y);
	void Dibujar();

	void printPos();
};

