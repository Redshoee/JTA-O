#include "stdafx.h"
#include "script.h"
#include "overlay.h"

bool WantedLevelCommand(std::vector<std::string> args)
{
	if (args.size() < 2)
	{
		NotifyMap("~r~Usage: wanted_level [level]");
		return false;
	}
	GetLocalPlayer().SetWantedLevel(atoi(args[1].c_str()), true);
	NotifyMap("~g~Your wanted level has been updated.");
	return true;
}

bool SecretCommand(std::vector<std::string> args)
{
	NotifyMap("~p~We're no strangers to love.");
	return true;
}

bool SetVehicleSpeedCommand(std::vector<std::string> args)
{
	if (args.size() < 2)
	{
		NotifyMap("~r~Usage: speed [speed]");
		return false;
	}
	
	boostSpeed = atof(args[1].c_str());
	char msg[128];
	sprintf_s(msg, sizeof(msg), "~g~Your boost speed is now ~b~%f.", round(boostSpeed));
	NotifyMap(std::string(msg));
	return true;
}
bool TeleportCommand(std::vector<std::string> args)
{
	if (args.size() < 2)
	{
		NotifyMap("~r~Usage: teleport [player name]");
		return false;
	}
	CPlayer target = GetPlayerByName(args[1]);
	if (!target.Exists())
	{
		NotifyMap("~r~Invalid player.");
		return false;
	}
	if (GetLocalPlayer().IsInAnyVehicle(true))
		GetLocalPlayer().GetCurrentVehicle().SetCoordinates(target.GetCoordinates());
	else
		GetLocalPlayer().SetCoordinates(target.GetCoordinates(true));
	char msg[128];
	sprintf_s(msg, sizeof(msg), "~g~Teleported you to ~o~%s", target.GetName());
	NotifyMap(std::string(msg));
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
		NotifyMap("~r~Usage: spawn_vehicle [model]");
		return false;
	}
	if (!ValidModel($(args[1])))
	{
		NotifyMap("~r~Invalid model.");
		return false;
	}
	Vector3 loc = GetLocalPlayer().GetCoordinates(true);
	CVehicle veh = CreateVehicle($(args[1]), loc, GetLocalPlayer().GetHeading());
	if (!veh.Exists())
	{
		NotifyMap("~r~Vehicle did not spawn. Did disable model spawn check fail?");
		return true;
	}
	GetLocalPlayer().SetIntoVehicle(veh, VehicleSeatDriver);
	char msg[128];
	sprintf_s(msg, sizeof(msg), "~g~Spawned a ~p~%s.", args[1].c_str());
	NotifyMap(std::string(msg));
	return true;
}
bool FindVehicleCommand(std::vector<std::string> args)
{
	bool teleportToPly = true;
	if (args.size() >= 2)
		teleportToPly = strcmp(args[1].c_str(), "true") == 0;
	CVehicle veh = GetClosestVehicle(GetLocalPlayer().GetCoordinates(), 150.0f, );
	if (!veh.Exists())
	{
		NotifyMap("~r~No near Vehicle found?");
		return false;
	}
	veh.SetNeedsHotwire(false);
	if(teleportToPly)
		veh.SetCoordinates(GetLocalPlayer().GetCoordinates(true), false);
	GetLocalPlayer().SetIntoVehicle(veh, VehicleSeatDriver);
	NotifyMap("~g~Teleported into nearest Vehicle.");
	return true;
}

bool IntoPlayerVehicleCommand(std::vector<std::string> args)
{
	if (args.size() < 2)
	{
		NotifyMap("~r~Usage: teleport [player name]");
		return false;
	}
	CPlayer target = GetPlayerByName(args[1]);
	if (!target.Exists())
	{
		NotifyMap("~r~Invalid player.");
		return false;
	}
	if (target.GetHandle() == GetLocalPlayer().GetHandle())
	{
		NotifyMap("~r~You cannot set yourself into your own Vehicle!");
		return true;
	}
	if (!target.IsInAnyVehicle(true))
	{
		NotifyMap("~r~Player is not inside a Vehicle.");
		return true;
	}
	GetLocalPlayer().SetIntoVehicle(target.GetCurrentVehicle(), VehicleSeatPassenger);
	NotifyMap("~g~You are now a passenger inside that Player's Vehicle.");
	return true;
}

bool DropMoneyCommand(std::vector<std::string> args)
{
	drop = !drop;
	char msg[128];
	sprintf_s(msg, sizeof(msg), "~g~Money drop is now ~p~%s.", (drop ? "enabled" : "disabled"));
	NotifyMap(std::string(msg));
	return true;
}

bool FixVehicleCommand(std::vector<std::string> args)
{
	CPlayer ply = GetLocalPlayer();
	if (!ply.IsInAnyVehicle(true))
	{
		NotifyMap("~r~You aren't in a Vehicle.");
		return false;
	}
	ply.GetCurrentVehicle().Fix();
	NotifyMap("~g~Fixed your curent Vehicle.");
	return true;
}

bool FlyThroughWindshieldCommand(std::vector<std::string> args)
{
	GetLocalPlayer().GetPed().SetFlyThroughWindscreen(!GetLocalPlayer().GetPed().CanFlyThroughWindscreen());
	NotifyMap("~g~Toggled fly through windscreen ability.");
	return true;
}

bool InvincibilityVehicleCommand(std::vector<std::string> args)
{
	GetLocalPlayer().GetCurrentVehicle().SetInvincible(true);
	NotifyMap("~g~Your Vehicle is now invincible.");
}

bool InvincibilityCommand(std::vector<std::string> args)
{
	GetLocalPlayer().SetInvincible(!GetLocalPlayer().IsInvincible());
	NotifyMap("~g~Toggled invincibility.");
	return true;
}

bool GiveAllWeaponsCommand(std::vector<std::string> args)
{
	for each(std::string wep in weapons)
	{
		GetLocalPlayer().GiveWeapon($(wep), 99999, false, false);
	}
	NotifyMap("~g~Gave you all weapons.");
	return true;
}

bool KillNearbyEnemiesCommand(std::vector<std::string> args)
{
	int killCount = 0;
	UpdateNearbyPeds(GetLocalPlayer().GetPed().GetHandle(), 7500);
	
	for each(Ped p in GetNearbyPeds())
	{
		CPed cp = CPed(p);
		if (cp.IsPlayer())
			continue;
		if(cp.GetRelationshipBetweenPed(GetLocalPlayer().GetPed()) == RelationshipDislike || cp.GetRelationshipBetweenPed(GetLocalPlayer().GetPed()) == RelationshipHate)
		{
			cp.Kill();
			killCount++;
		}
	}
	char msg[128];
	sprintf_s(msg, sizeof(msg), "~g~Killed ~b~%i ~g~enemies.", killCount);
	NotifyMap(std::string(msg));
	return true;
}

bool OverlayCommand(std::vector<std::string>)
{
	Overlay::overlaysEnabled = !Overlay::overlaysEnabled;
	NotifyMap("~g~Toggled overlay.");
	return true;
}

bool ExplodeCommand(std::vector<std::string> args)
{
	CPlayer target = GetLocalPlayer();
	if (args.size() >= 2)
	{
		target = GetPlayerByName(args[1]);
		if (!target.Exists())
		{
			NotifyMap("~r~Invalid player.");
			return false;
		}
	}
	CreateExplosion(target.GetCoordinates(), ExplosionTypeRocket, 150.0f);
	NotifyMap("~g~Boom.");
	return true;
}

bool ExplodeNearbyVehiclesCommand(std::vector<std::string>)
{
		int killCount = 0;
		UpdateNearbyVehicles(GetLocalPlayer().GetPed().GetHandle(), 7500);

		for each(Vehicle v in GetNearbyVehicles())
		{
			CVehicle cv = CVehicle(v);
			if (cv.GetDriver().GetRelationshipBetweenPed(GetLocalPlayer().GetPed()) == RelationshipDislike || cv.GetDriver().GetRelationshipBetweenPed(GetLocalPlayer().GetPed()) == RelationshipHate)
			{
				cv.RequestControl(true);
				cv.Explode();
				killCount++;
			}
		}
		char msg[128];
		sprintf_s(msg, sizeof(msg), "~g~Exploded ~b~%i ~g~vehicles.", killCount);
		NotifyMap(std::string(msg));
		return true;
}

bool ToggleSelfDrop(std::vector<std::string>)
{
	selfdrop = !selfdrop;
	char msg[128];
	sprintf_s(msg, sizeof(msg), "~g~Self-drop now ~p~%s.", (selfdrop) ? "enabled" : "disabled");
	NotifyMap(std::string(msg));
	return true;
}

bool ExplodePedsCommand(std::vector<std::string>)
{
	UpdateNearbyPeds(GetLocalPlayer().GetPed().GetHandle(), 150);
	for each(Ped p in GetNearbyPeds())
	{
		CPlayer ply = CPlayer(p);
		if (!ply.IsPlayer())
			CreateExplosion(ply.GetCoordinates(), ExplosionTypeRocket, 150.0f);
	}
	NotifyMap("~r~Boom.");
	return true;
}

void RegisterCommands()
{
	AddCommand("wanted_level", WantedLevelCommand);
	AddCommand("godmode", InvincibilityCommand);
	AddCommand("godmode_vehicle", InvincibilityVehicleCommand);
	AddCommand("drop_money", DropMoneyCommand);
	AddCommand("find_vehicle", FindVehicleCommand);
	AddCommand("self_drop", ToggleSelfDrop);
	AddCommand("explode_peds", ExplodePedsCommand);
	AddCommand("spawn_vehicle", SpawnVehicleCommand);
	AddCommand("kill_nearby", KillNearbyEnemiesCommand);
	AddCommand("overlay", OverlayCommand);
	AddCommand("fix_vehicle", FixVehicleCommand);
	AddCommand("explode", ExplodeCommand);
	AddCommand("into_vehicle", IntoPlayerVehicleCommand);
	AddCommand("explode_nearby", ExplodeNearbyVehiclesCommand);
	AddCommand("give_weapons", GiveAllWeaponsCommand);
	AddCommand("fly_windscreen", FlyThroughWindshieldCommand);
	AddCommand("teleport", TeleportCommand);
	AddCommand("teleport_waypoint", TeleportWaypointCommand);
	AddCommand("speed", SetVehicleSpeedCommand);
	AddCommand("_give_you_up_", SecretCommand);
}
