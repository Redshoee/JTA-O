#include "stdafx.h"
#include "script.h"

bool WantedLevelCommand(std::vector<std::string> args)
{
	if (args.size() < 2)
	{
		CPlayer::NotifyMap("~r~Usage: wanted_level [level]");
		return false;
	}
	CPlayer::GetLocalPlayer().SetWantedLevel(atoi(args[1].c_str()), true);
	CPlayer::NotifyMap("~g~Your wanted level has been updated.");
	return true;
}

bool SecretCommand(std::vector<std::string> args)
{
	CPlayer::NotifyMap("~p~We're no strangers to love.");
	return true;
}

bool SetVehicleSpeedCommand(std::vector<std::string> args)
{
	if (args.size() < 2)
	{
		CPlayer::NotifyMap("~r~Usage: speed [speed]");
		return false;
	}
	boostSpeed = atof(args[1].c_str());
	char msg[128];
	sprintf_s(msg, sizeof(msg), "~g~Your boost speed is now ~b~%f.", boostSpeed);
	CPlayer::NotifyMap(std::string(msg));
	return true;
}
bool TeleportCommand(std::vector<std::string> args)
{
	if (args.size() < 2)
	{
		CPlayer::NotifyMap("~r~Usage: teleport [player name]");
		return false;
	}
	CPlayer target = CPlayer::GetPlayerByName(args[1]);
	if (!target.IsValid())
	{
		CPlayer::NotifyMap("~r~Invalid player.");
		return false;
	}
	CPlayer::GetLocalPlayer().SetCoordinates(target.GetCoordinates(true), false);
	char msg[128];
	sprintf_s(msg, sizeof(msg), "~g~Teleported you to ~o~%s", target.GetName());
	CPlayer::NotifyMap(std::string(msg));
	return true;
}
bool TeleportWaypointCommand(std::vector<std::string> args)
{
	TeleportToMarker();
	return true; //TODO: This always returns true, even if it shouldn't.
}
bool SpawnVehicleCommand(std::vector<std::string> args)
{
	if (args.size() < 2)
	{
		CPlayer::NotifyMap("~r~Usage: spawn_vehicle [model]");
		return false;
	}
	if (!LoadModel($(args[1])))
	{
		CPlayer::NotifyMap("~r~Invalid model.");
		return false;
	}
	Vector3 loc = CPlayer::GetLocalPlayer().GetCoordinates(true);
	CVehicle veh = CVehicle::CreateVehicle($(args[1]), loc, CPlayer::GetLocalPlayer().GetHeading());
	CPlayer::GetLocalPlayer().SetIntoVehicle(veh, VehicleSeatDriver);
	char msg[128];
	sprintf_s(msg, sizeof(msg), "~g~Spawned a ~p~%s.", args[1].c_str());
	CPlayer::NotifyMap(std::string(msg));
	return true;
}
bool FindVehicleCommand(std::vector<std::string> args)
{
	bool teleportToPly = true;
	if (args.size() >= 2)
	{
		if (strcmp(args[1].c_str(), "true") == 0)
			teleportToPly = true;
		if (strcmp(args[1].c_str(), "false") == 0)
			teleportToPly = false;
	}
	Vector3 loc = CPlayer::GetLocalPlayer().GetCoordinates(true);
	Vehicle closest = VEHICLE::GET_CLOSEST_VEHICLE(loc.x, loc.y, loc.z, 150.0f, 0, 2);
	if (closest == NULL)
	{
		CPlayer::NotifyMap("~r~No near Vehicle found?");
		return false;
	}
	CVehicle veh = CVehicle(closest);
	veh.SetNeedsHotwire(false);
	if(teleportToPly)
		veh.SetCoordinates(CPlayer::GetLocalPlayer().GetCoordinates(true), false);
	CPlayer::GetLocalPlayer().SetIntoVehicle(veh, VehicleSeatDriver);
	CPlayer::NotifyMap("~g~Teleported into nearest Vehicle.");
	return true;
}

bool DropMoneyCommand(std::vector<std::string> args)
{
	if (args.size() == 1)
	{
		dropPlayer = 30;
		CPlayer::NotifyMap("~g~No longer dropping money.");
		return true;
	}
	if (args.size() >= 2)
	{
		CPlayer target = CPlayer::GetPlayerByName(args[1]);
		if (!target.IsValid())
		{
			CPlayer::NotifyMap("~r~Invalid player.");
			return false;
		}
		dropPlayer = target.GetHandle();
		char msg[128];
		sprintf_s(msg, sizeof(msg), "~g~Now dropping money on ~p~%s", target.GetName());
		CPlayer::NotifyMap(std::string(msg));
		return true;
	}
	CPlayer::NotifyMap("You should not be able to get here. If you read this, then fuck.");
	return false;
}

bool DropMoneyWaitTimeCommand(std::vector<std::string> args)
{
	if (args.size() < 2)
	{
		CPlayer::NotifyMap("~r~Usage: wait_time [time ms]");
		return false;
	}
	waitTime = atoi(args[1].c_str());
	char msg[128];
	sprintf_s(msg, sizeof(msg), "~g~Drop wait time is now ~b~%i", waitTime);
	CPlayer::NotifyMap(std::string(msg));
	return true;
}

bool FixVehicleCommand(std::vector<std::string> args)
{
	CPlayer ply = CPlayer::GetLocalPlayer();
	if (!ply.IsInAnyVehicle(true))
	{
		CPlayer::NotifyMap("~r~You aren't in a Vehicle.");
		return false;
	}
	ply.GetCurrentVehicle().Fix();
	CPlayer::NotifyMap("~g~Fixed your curent Vehicle.");
	return true;
}

bool FlyThroughWindshieldCommand(std::vector<std::string> args)
{
	CPlayer::GetLocalPlayer().GetPed().SetFlyThroughWindscreen(!CPlayer::GetLocalPlayer().GetPed().CanFlyThroughWindscreen());
	CPlayer::NotifyMap("~g~Toggled fly through windscreen ability.");
	return true;
}

bool InvincibilityCommand(std::vector<std::string> args)
{
	CPlayer::GetLocalPlayer().SetInvincible(!CPlayer::GetLocalPlayer().IsInvincible());
	CPlayer::NotifyMap("~g~Toggled invincibility.");
	return true;
}

bool GiveAllWeaponsCommand(std::vector<std::string> args)
{
	for each(std::string wep in weapons)
	{
		CPlayer::GetLocalPlayer().GiveWeapon($(wep), 99999, false, false);
	}
	CPlayer::NotifyMap("~g~Gave you all weapons.");
	return true;
}

bool KillNearbyEnemiesCommand(std::vector<std::string> args) //Need to find a way to get if an Ped is an enemy... we have a setter but no getter, and relations don't seem to work the way they should...
{
	int relationToKill = RelationshipNeutral;
	if (args.size() >= 2)
		relationToKill = atoi(args[1].c_str());

	int killCount = 0;
	UpdateNearbyPeds(CPlayer::GetLocalPlayer().GetPed().GetHandle(), 3000);
	
	for each(Ped p in GetNearbyPeds())
	{
		CPed cp = CPed(p);
		int relation = CPlayer::GetLocalPlayer().GetRelationshipBetweenPed(cp);
		if (relation > relationToKill && relation != RelationshipPedestrians)
		{
			cp.Kill();
			killCount++;
		}
	}
	char msg[128];
	sprintf_s(msg, sizeof(msg), "~g~Killed ~b~%i ~g~enemies.", killCount);
	CPlayer::NotifyMap(std::string(msg));
	return true;
}

void RegisterCommands()
{
	AddCommand("wanted_level", WantedLevelCommand);
	AddCommand("godmode", InvincibilityCommand);
	AddCommand("drop_money", DropMoneyCommand);
	AddCommand("wait_time", DropMoneyWaitTimeCommand);
	AddCommand("find_vehicle", FindVehicleCommand);
	AddCommand("spawn_vehicle", SpawnVehicleCommand);
	AddCommand("kill_enemies", KillNearbyEnemiesCommand);
	AddCommand("fix_vehicle", FixVehicleCommand);
	AddCommand("give_weapons", GiveAllWeaponsCommand);
	AddCommand("fly_windscreen", FlyThroughWindshieldCommand);
	AddCommand("teleport", TeleportCommand);
	AddCommand("teleport_waypoint", TeleportWaypointCommand);
	AddCommand("speed", SetVehicleSpeedCommand);
	AddCommand("_give_you_up_", SecretCommand);
}
