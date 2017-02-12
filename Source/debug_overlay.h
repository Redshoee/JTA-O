#pragma once
#include "stdafx.h"
#include "overlay.h"

class DebugOverlay : public Overlay
{
private:
	virtual void InternalDraw();
public:
	DebugOverlay() : Overlay("DebugOverlay") {};
};