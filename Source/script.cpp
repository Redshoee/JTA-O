#include "stdafx.h"
#include "script.h"

Player dropPlayer = -1;
float speed = 50.0f;

int waitTime = 20;

uint weapons[128] = {
	0x99B507EA,
	0x678B81B1,
	0x4E875F73,
	0x958A4A8F,
	0x440E4788,
	0x84BD7BFD,
	0xF9E6AA4B,
	0xDFE37640,
	0x1B06D571,
	0x5EF9FEC4,
	0x22D8FE39,
	0x99AEEB3B,
	0x47757124,
	0xDC4DB296,
	0xC1B3C3D1,
	0x13532244,
	0x2BE6766B,
	0xEFE7E2DF,
	0x0A3D4D34,
	0xBFEFFF6D,
	0x83BF0278,
	0xAF113F99,
	0x624FE830,
	0x9D07F764,
	0x7FD62962,
	0x1D073A89,
	0x7846A318,
	0xE284C527,
	0x9D61E50F,
	0xEF951FBB,
	0x3656C8C1,
	0x5FC3C11,
	0xC472FE2,
	0xA284510B,
	0x4DD2DC56,
	0xB1CA77B1,
	0x42BF8A85,
	0x93E220BD,
	0x2C3731D9,
	0xFDBC8A50,
	0xA0973D5E,
	0x24B17070,
	0x60EC506,
	0x34A67B97,
	0xBFD21232,
	0xC0A3098D,
	0xD205520E,
	0x7F229F94,
	0x63AB0442,
	0xAB564B93,
	0x787F0BB,
	0x83839C4,
	0x92A27487,
	0x7F7497E5,
	0xA89CB99E,
	0xC734385A,
	0x3AABBBAA,
	0x61012683,
	0xF9DCBF2D,
	0x6D544C99,
	0xA2719263,
	0xD8DF3C3C,
	0xDD5DF8D9,
	0xDB1AA450,
	0x8BB05FD7,
	0x23C9F95C,
	0x497FACC3,
	0xA720365C,
	0xFBAB5776
};

std::vector<std::string> Split(std::string str, std::string sep) {
	char* cstr = const_cast<char*>(str.c_str());
	char* current;
	std::vector<std::string> arr;
	current = strtok(cstr, sep.c_str());
	while (current != NULL) {
		arr.push_back(current);
		current = strtok(NULL, sep.c_str());
	}
	return arr;
}

bool Script::IsInit()
{
	return true;
}

void Script::OnTick()
{
	Player ply = PLAYER::PLAYER_ID();
	Ped plyPed = PLAYER::PLAYER_PED_ID();
	Vehicle plyVeh = PED::GET_VEHICLE_PED_IS_IN(plyPed, FALSE);

	if (KeyJustUp(VK_F7))
	{
		std::string cmd = ShowKeyboard("FMMC_KEY_TIP8", "");
		if (cmd.empty())
			return;
		std::vector<std::string> splitCmd = Split(cmd, " ");
		NotifyMap(ParseCommand(splitCmd[0], splitCmd), FALSE);
	}

	if(KeyJustUp(VK_KEY_L))
	{ 
		if (PED::IS_PED_IN_ANY_VEHICLE(plyPed, TRUE))
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_IN(plyPed, FALSE), speed);
	}

	if (dropPlayer != -1)
	{
		Vector3 loc = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(dropPlayer), TRUE);
		DropMoney(loc.x, loc.y, loc.z);
		WAIT(waitTime);
	}
}

void ReplaceAll(std::string& str, const std::string& from, const std::string& to)
{
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

std::string Script::ParseCommand(std::string cmd, std::vector<std::string> args) //First argument is command. Return format: Player names are orange, ints are blue, strings and such are purple, and default text is red or green depending on failed state.
{
	for (int i = 0; i < args.size(); i++) //Cause I get lazy a lot.
		if (strcmp(args[i].c_str(), "@me") == 0)
			args[i] = PLAYER::GET_PLAYER_NAME(PLAYER::PLAYER_ID());

	if (strcmp(cmd.c_str(), "wanted_level") == 0)
	{
		if (args.size() < 3)
			return "~r~Usage: wanted_level [player name] [level]";
		Player ply = GetPlayerByName(args[1]);
		if (ply == -1)
			return "~r~Invalid player.";
		int level = atoi(args[2].c_str());
		if (level < 0 || level > 5)
			return "~r~Invalid wanted level. (0-5)";
		PLAYER::SET_PLAYER_WANTED_LEVEL(ply, level, FALSE);
		PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(ply, FALSE);
		char msg[128];
		sprintf_s(msg, sizeof(msg), "~o~%s's ~g~wanted level is now ~b~%i.", PLAYER::GET_PLAYER_NAME(ply), level);
		return std::string(msg);
	}

	if (strcmp(cmd.c_str(), "give_weapons") == 0)
	{
		if (args.size() < 2)
			return "~r~Usage: give_weapons [player name]";
		Player ply = GetPlayerByName(args[1]);
		if (ply == -1)
			return "~r~Invalid player.";
		Ped plyPed = PLAYER::GET_PLAYER_PED(ply);
		for (int i = 0; i < sizeof(weapons); i++)
		{
			WEAPON::GIVE_WEAPON_TO_PED(plyPed, weapons[i], 99999, FALSE, FALSE);
		}
		char msg[128];
		sprintf_s(msg, sizeof(msg), "~g~Gave ~o~%s ~g~all weapons.", PLAYER::GET_PLAYER_NAME(ply));
		return std::string(msg);
	}

	if (strcmp(cmd.c_str(), "drop_money") == 0)
	{
		if (args.size() == 1)
		{
			dropPlayer = -1;
			return "~g~Reset drop player.";
		}
		Player ply = GetPlayerByName(args[1]);
		if (ply == -1)
			return "~r~Invalid player.";
		dropPlayer = ply;
		char msg[128];
		sprintf_s(msg, sizeof(msg), "~g~Dropping money on ~o~%s.", PLAYER::GET_PLAYER_NAME(ply));
		return std::string(msg);
	}

	if (strcmp(cmd.c_str(), "place_bounty") == 0)
	{
		if (args.size() < 3)
			return "~r~Usage: place_bounty [amount] [player name] [p1 bool] [p2 bool]";
		Player ply = GetPlayerByName(args[2]);
		if (ply == -1)
			return "~r~Invalid player.";
		int amount = atoi(args[1].c_str());
		NETWORKCASH::NETWORK_BUY_BOUNTY(amount, ply, atoi(args[3].c_str()), atoi(args[4].c_str()));
		char msg[128];
		sprintf_s(msg, sizeof(msg), "~g~You placed a bounty on ~o~%s ~g~for ~b~$%i.", PLAYER::GET_PLAYER_NAME(ply), amount);
		return std::string(msg);
	}

	if (strcmp(cmd.c_str(), "godmode") == 0)
	{
		if (args.size() < 2)
			return "~r~Usage: godmode [player name]";
		Player ply = GetPlayerByName(args[1]);
		if (ply == -1)
			return "~r~Invalid player.";
		GodMode(ply, !PLAYER::GET_PLAYER_INVINCIBLE(ply));
		char msg[128];
		sprintf_s(msg, sizeof(msg), "~o~%s ~g~is %s.", PLAYER::GET_PLAYER_NAME(ply), (PLAYER::GET_PLAYER_INVINCIBLE(ply) ? "now invincible" : "no longer invincible"));
		return std::string(msg);
	}
	if (strcmp(cmd.c_str(), "teleport") == 0)
	{
		if (args.size() < 2)
			return "~r~Usage: teleport [player name]";
		Player ply = GetPlayerByName(args[1]);
		if (ply == -1)
			return "~r~Invalid player.";
		Entity e = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_IN_ANY_VEHICLE(e, TRUE))
			e = PED::GET_VEHICLE_PED_IS_IN(e, FALSE);
		Vector3 loc = CoordsOf(PLAYER::GET_PLAYER_PED(ply));
		TeleportToCoords(e, loc);
		char msg[128];
		sprintf_s(msg, sizeof(msg), "~g~You were teleported to ~o~%s.", PLAYER::GET_PLAYER_NAME(ply));
		return std::string(msg);
	}

	if (strcmp(cmd.c_str(), "wait_time") == 0)
	{
		if (args.size() < 2)
			return "~r~Usage: wait_time [time ms]";
		int wait = atoi(args[1].c_str());
		waitTime = wait;
		char msg[128];
		sprintf_s(msg, sizeof(msg), "~g~Money drop wait is now ~b~%i.", waitTime);
		return std::string(msg);
	}

	if (strcmp(cmd.c_str(), "teleport_waypoint") == 0)
	{
		TeleportToMarker();
		return "~g~Teleported to waypoint";
	}

	if (strcmp(cmd.c_str(), "spawn_vehicle") == 0)
	{
		if (args.size() < 2)
			return "~r~Usage: spawn_vehicle [model name]";
		Hash h = $(args[1]);
		Vector3 loc = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);
		Vehicle veh = CreateVehicle(h, loc, FALSE);
		if (veh == -1)
			return "~r~Invalid model.";
		PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
		char msg[128];
		sprintf_s(msg, sizeof(msg), "~g~Created Vehicle ~p~%s.", args[1].c_str());
		return std::string(msg);
	}

	if (strcmp(cmd.c_str(), "spawn_ped") == 0)
	{
		if (args.size() < 3)
			return "~r~Usage: spawn_ped [model name] [type]";
		Hash h = $(args[1]);
		int type = atoi(args[2].c_str());
		Vector3 loc = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);
		CreatePed(h, loc, type, FALSE);
		if()
		char msg[128];
		sprintf_s(msg, sizeof(msg), "~g~Created Ped ~p~%s.", args[1].c_str());
		return std::string(msg);
	}

	if (strcmp(cmd.c_str(), "kill_cops") == 0)
	{
		UpdateNearbyPeds(PLAYER::PLAYER_PED_ID(), 2000);
		int killed = 0;
		for each(Ped p in GetNearbyPeds())
		{
			if (PED::GET_PED_TYPE(p) == 6) //Da Fuzz
			{
				ENTITY::SET_ENTITY_HEALTH(p, 0); //Read my newest book: "I'm dead; now what?"
				killed++;
			}
		}
		char msg[128];
		sprintf_s(msg, sizeof(msg), "~b~%i ~g~cops killed.", killed);
		return std::string(msg);
	}

	if (strcmp(cmd.c_str(), "fix_car") == 0)
	{
		if (args.size() < 2)
			return "~r~Usage: fix_car [player name]";
		Player ply = GetPlayerByName(args[1]);
		if (ply == -1)
			return "~r~Invalid player.";
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(ply), TRUE))
		{
			char msg[128];
			sprintf_s(msg, sizeof(msg), "~o~%s ~g~is not in a Vehicle.", PLAYER::GET_PLAYER_NAME(ply));
			return std::string(msg);
		}
		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(ply), FALSE);
		VEHICLE::SET_VEHICLE_FIXED(veh);
		char msg[128];
		sprintf_s(msg, sizeof(msg), "~g~Fixed ~o~%s's ~g~Vehicle.", PLAYER::GET_PLAYER_NAME(ply));
		return std::string(msg);
	}

	if (strcmp(cmd.c_str(), "speed") == 0)
	{
		if (args.size() < 2)
			return "~r~Usage: speed [speed]";
		speed = atof(args[1].c_str());
		char msg[128];
		sprintf_s(msg, sizeof(msg), "~g~Vehicle is now ~b~%f.", speed);
		return std::string(msg);
	}

	if (strcmp(cmd.c_str(), "vehicle_torque") == 0)
	{
		if (args.size() < 2)
			return "~r~Usage: vehicle_torque [player name] [torque]";
		Player ply = GetPlayerByName(args[1]);
		if (ply == -1)
			return "~r~Invalid player.";
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(ply), TRUE))
		{
			char msg[128];
			sprintf_s(msg, sizeof(msg), "~o~%s ~g~is not in a Vehicle.", PLAYER::GET_PLAYER_NAME(ply));
			return std::string(msg);
		}
		float torque = atof(args[2].c_str());
		Vehicle plyVeh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(ply), FALSE);
		VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(plyVeh, torque);
		char msg[128];
		sprintf_s(msg, sizeof(msg), "~o~%s's ~g~Vehicle torque is now %f.", PLAYER::GET_PLAYER_NAME(ply), torque);
		return std::string(msg);
	}

	if (strcmp(cmd.c_str(), "vehicle_power") == 0)
	{
		if (args.size() < 2)
			return "~r~Usage: vehicle_power [player name] [power]";
		Player ply = GetPlayerByName(args[1]);
		if (ply == -1)
			return "~r~Invalid player.";
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(ply), TRUE))
		{
			char msg[128];
			sprintf_s(msg, sizeof(msg), "~o~%s ~g~is not in a Vehicle.", PLAYER::GET_PLAYER_NAME(ply));
			return std::string(msg);
		}
		float power = atof(args[2].c_str());
		Vehicle plyVeh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(ply), FALSE);
		VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(plyVeh, power);
		char msg[128];
		sprintf_s(msg, sizeof(msg), "~o~%s's ~g~Vehicle power is now %f.", PLAYER::GET_PLAYER_NAME(ply), power);
		return std::string(msg);
	}
	return "Unknown command.";
}
