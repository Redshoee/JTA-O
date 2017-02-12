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