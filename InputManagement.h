#pragma once
#include <iostream>

class InputManagement
{


public:

	static void SetKey(char key, bool state);
	static bool GetKey(char key);
	static float GetAxisX();
	static float GetAxisY();

	InputManagement() = delete; // clase estatica 
private:

	static bool wKey, aKey, sKey, dKey;
	static float axisX, axisY;
};

