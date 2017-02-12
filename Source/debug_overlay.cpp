#include "stdafx.h"
#include "debug_overlay.h"

void DebugOverlay::InternalDraw()
{
	UpdateNearbyPeds(GetLocalPlayer().GetHandle(), 30);
	for each(Ped p in GetNearbyPeds())
	{
		CPed cp = CPed(p); 
		if (cp.Exists() && GetLocalPlayer().HasLineOfSightTo(cp.GetHandle()) && cp.IsPlayer())
		{
			char name[64];
			char health[64];
			char armor[64];
			char handle[64];
			CPlayer ply = GetPlayerByPed(cp);
			sprintf_s(name, sizeof(name), "Name %s", ply.GetName());
			sprintf_s(health, sizeof(health), "Health %i", cp.GetHealth());
			sprintf_s(armor, sizeof(armor), "Armor %i", cp.GetArmor());
			sprintf_s(handle, sizeof(handle), "Handle %i", cp.GetHandle());
			Vector2 screenCoords = WorldToScreen(cp.GetCoordinates());
			DrawUIText(name, screenCoords, Color4(255, 255, 255, 255), 0.5f, FontMonospace);
			DrawUIText(health, Vector2(screenCoords.x, screenCoords.y + .02f), Color4(255, 255, 255, 255), 0.5f, FontMonospace);
			DrawUIText(armor, Vector2(screenCoords.x, screenCoords.y + .04f), Color4(255, 255, 255, 255), 0.5f, FontMonospace);
			DrawUIText(handle, Vector2(screenCoords.x, screenCoords.y + .06f), Color4(255, 255, 255, 255), 0.5f, FontMonospace);
			DrawLine(GetLocalPlayer().GetCoordinates(), cp.GetCoordinates(), Color4(82, 51, 131, 255));
		}
	}
}
