#pragma once
#include "stdafx.h"
#include "entity.h"

struct Color3
{
	Color3(int r, int g, int b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
	int r, g, b;
};

struct Color4
{
	Color4(int r, int g, int b, int a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	int r, g, b, a;
};

struct Raycast
{
	Raycast(Vector3 source, Vector3 hitpos, bool dithit, CEntity hitent)
	{
		this->source = source;
		this->hitpos = hitpos;
		this->dithit = dithit;
		this->hitent = hitent;
	}
	Vector3 source, hitpos;
	CEntity hitent = CEntity(-1);
	bool dithit;
};