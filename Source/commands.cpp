#include "stdafx.h"

bool WantedLevelCommand(std::vector<std::string> args)
{
	if (args.size() < 2)
	{
		CPlayer::NotifyMap("Usage: wanted_level [level]", FALSE);
		return false;
	}
	CPlayer::GetLocalPlayer().SetWantedLevel(atoi(args[1].c_str()), true);
	CPlayer::NotifyMap("~r~Your wanted level has been updated.", FALSE);
	return true;
}

bool SecretCommand(std::vector<std::string> args)
{
	CPlayer::NotifyMap("We're no strangers to love.", FALSE);
	return true;
}

void RegisterCommands()
{
	AddCommand("wanted_level", WantedLevelCommand);
	AddCommand("give_you_up", SecretCommand);
}
