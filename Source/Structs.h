#pragma once

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
