#pragma once

extern float boostSpeed;
extern bool drop;
extern bool selfdrop;

class Script
{
public:
	static bool IsInit();
	static void OnTick();
}; 