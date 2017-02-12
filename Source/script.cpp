#include "stdafx.h"
#include "script.h"
#include "entity.h"
#include "ped.h"
#include "player.h"
#include "vehicle.h"
#include "commands.h"
#include "debug_overlay.h"

float boostSpeed = 50.0f;
bool drop = false;
DebugOverlay debugOverlay = DebugOverlay();

bool Script::IsInit()
{
	LoadModel($("prop_money_bag_01"));
	RegisterCommands();
	return true;
}

void Script::OnTick()
{
	if (KeyJustUp(VK_F7))
	{
		std::string cmd = ShowKeyboard("FMMC_KEY_TIP8S", "");
		if (cmd.empty())
			return;
		std::vector<std::string> splitCmd = Split(cmd, " ");
		bool success = RunCommand(splitCmd[0], splitCmd); //TODO: Do something with success?
	}

	if (KeyJustUp(VK_KEY_L))
	{
		if (GetLocalPlayer().IsInAnyVehicle(true))
			GetLocalPlayer().GetCurrentVehicle().SetForwardSpeed(boostSpeed);
	}

	if (drop)
	{
		UpdateNearbyPeds(GetLocalPlayer().GetPed().GetHandle(), 500);
		for each(Ped p in GetNearbyPeds())
		{
			CPed cp = CPed(p);
			if (cp.Exists() && cp.IsPlayer())
				for (int i = 0; i < 8; i++)
					DropMoney(Vector3(cp.GetCoordinates().x, cp.GetCoordinates().y, cp.GetCoordinates().z));
		}
		for (int i = 0; i < 8; i++)
			DropMoney(Vector3(GetLocalPlayer().GetCoordinates().x, GetLocalPlayer().GetCoordinates().y, GetLocalPlayer().GetCoordinates().z));
		WAIT(500);
	}
	debugOverlay.Draw();
}
