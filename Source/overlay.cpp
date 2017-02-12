#include "stdafx.h"
#include "overlay.h"

bool Overlay::overlaysEnabled = false;

void Overlay::InternalDraw()
{}

void Overlay::Draw()
{
	if (Overlay::overlaysEnabled)
		InternalDraw();
}

std::string Overlay::GetName()
{
	return name;
}

bool Overlay::IsVisible()
{
	return visible;
}

void Overlay::SetVisible(bool toggle)
{
	visible = toggle;
}