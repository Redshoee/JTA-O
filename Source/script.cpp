#include "stdafx.h"
#include "script.h"
#include "entity.h"
#include "ped.h"
#include "player.h"
#include "vehicle.h"
#include "commands.h"

float boostSpeed = 50.0f;
uint dropPlayer = 30;
int waitTime = 20;

bool Script::IsInit()
{
	RegisterCommands();
	return true;
}

void Script::OnTick()
{
	if (dropPlayer != 30)
	{
		Vector3 loc = CPlayer(dropPlayer).GetCoordinates(true);
		DropMoney(loc.x, loc.y, loc.z);
		WAIT(waitTime);
	}

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
		if (CPlayer::GetLocalPlayer().IsInAnyVehicle(true))
			CPlayer::GetLocalPlayer().GetCurrentVehicle().SetForwardSpeed(boostSpeed);
	}
}
