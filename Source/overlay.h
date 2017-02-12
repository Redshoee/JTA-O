#pragma once
#include "stdafx.h"

class Overlay
{
private:
	std::string name;
	virtual void InternalDraw();
public:
	Overlay(std::string name)
	{
		this->name = name;
	}
	void Draw();
	static bool overlaysEnabled;
	std::string GetName();
};