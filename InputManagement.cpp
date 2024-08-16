#include "InputManagement.h"

//se deben declarar asi por ser estaticas
bool InputManagement::wKey = false;
bool InputManagement::aKey = false;
bool InputManagement::sKey = false;
bool InputManagement::dKey = false;
float InputManagement::axisX = 0;
float InputManagement::axisY = 0;

void InputManagement::SetKey(char key, bool state)
{
	switch (key) {
	case 'w': 
		wKey = state; 
		axisX = 0; axisY = 1*state;
		break;
	case 'a': 
		aKey = state; 
		axisX = -1*state; axisY = 0;
		break;
	case 's': 
		sKey = state; 
		axisX = 0; axisY = -1*state;
		break;
	case 'd': 
		dKey = state; 
		axisX = 1*state; axisY = 0;
		break;
	}
}

bool InputManagement::GetKey(char key)
{
	bool ans = false;
	switch (key) {
		case 'w': ans = wKey; break;
		case 'a': ans = aKey; break;
		case 's': ans = sKey; break;
		case 'd': ans = dKey; break;
		default: ans = false; break;
	}
		
	
	return ans;
}

float InputManagement::GetAxisX()
{
	//std::cout << "Axis X: " << axisX << std::endl;
	return axisX;
}

float InputManagement::GetAxisY()
{
	//std::cout << "Axis Y: " << axisY << std::endl;
	return axisY;
}
