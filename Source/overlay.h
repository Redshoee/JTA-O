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
	std::string GetName();
	void Draw();
	static bool overlaysEnabled;
};