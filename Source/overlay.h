#pragma once
#include "stdafx.h"

class Overlay
{
private:
	std::string name;
	bool visible;
	virtual void InternalDraw();
public:
	Overlay(std::string name)
	{
		this->name = name;
	}
	bool Overlay::IsVisible();
	std::string GetName();
	void Draw();
	void Overlay::SetVisible(bool toggle);
	static bool overlaysEnabled;
};