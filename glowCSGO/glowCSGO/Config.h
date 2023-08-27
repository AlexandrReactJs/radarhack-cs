#pragma once
#include <Windows.h> 

bool glowToggle = false;
bool radarHackToggle = false;


void checkTogglesFunc() 
{
	if (GetAsyncKeyState(VK_END) & 1)
	{
		glowToggle = !glowToggle;
	}

	if (GetAsyncKeyState(VK_DELETE) & 1)
	{
		radarHackToggle = !radarHackToggle;
	}

}