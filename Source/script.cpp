#include "stdafx.h"
#include "script.h"
#include "entity.h"
#include "ped.h"
#include "player.h"
#include "vehicle.h"
#include "commands.h"

bool Script::IsInit()
{
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
}
