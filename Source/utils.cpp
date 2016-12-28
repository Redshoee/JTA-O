#include "stdafx.h"

std::map<std::string, CmdPtr> conCommands;

std::set<Ped>lastSeenPeds;

std::vector<std::string> weapons = {
"WEAPON_UNARMED", //Add weapons after this

"WEAPON_KNIFE",
"WEAPON_NIGHTSTICK",
"WEAPON_HAMMER",
"WEAPON_BAT",
"WEAPON_GOLFCLUB",
"WEAPON_CROWBAR",
"WEAPON_PISTOL",
"WEAPON_COMBATPISTOL",
"WEAPON_APPISTOL",
"WEAPON_PISTOL50",
"WEAPON_MICROSMG",
"WEAPON_SMG",
"WEAPON_ASSAULTSMG",
"WEAPON_ASSAULTRIFLE",
"WEAPON_CARBINERIFLE",
"WEAPON_ADVANCEDRIFLE",
"WEAPON_MG",
"WEAPON_COMBATMG",
"WEAPON_PUMPSHOTGUN",
"WEAPON_SAWNOFFSHOTGUN",
"WEAPON_ASSAULTSHOTGUN",
"WEAPON_BULLPUPSHOTGUN",
"WEAPON_STUNGUN",
"WEAPON_SNIPERRIFLE",
"WEAPON_HEAVYSNIPER",
"WEAPON_REMOTESNIPER",
"WEAPON_GRENADELAUNCHER",
"WEAPON_RPG",
"WEAPON_STINGER",
"WEAPON_MINIGUN",
"WEAPON_GRENADE",
"WEAPON_STICKYBOMB",
"WEAPON_SMOKEGRENADE",
"WEAPON_BZGAS",
"WEAPON_MOLOTOV",
"WEAPON_FIREEXTINGUISHER",
"WEAPON_PETROLCAN",
"WEAPON_DIGISCANNER",
"WEAPON_BALL",
"WEAPON_FLARE" //Add weapons before this.
};

BOOL BoolToBoolDef(bool b)
{
	return (b) ? TRUE : FALSE;
}

bool BoolDefToBool(BOOL b) 
{
	return b == 1;
}

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

void AddCommand(std::string cmd, CmdPtr func)
{
	conCommands[cmd] = func;
	Log::Msg("Registed command %s.", cmd.c_str());
}

bool RunCommand(std::string cmd, std::vector<std::string> args)
{
	CmdPtr commandToExec = conCommands[cmd];
	if (commandToExec == nullptr)
	{
		CPlayer::NotifyMap("Unknown command.");
		Log::Msg("WARNING: Attempted to run a command that didn't exist?");
		return false;
	}
	bool ret = commandToExec(args);
	Log::Msg("Running command %s. (returned %d)", cmd.c_str(), ret);
	return ret;
}

std::string ShowKeyboard(char* title_id, char* prepopulated_text)
{
	DWORD time = GetTickCount() + 400;
	while (GetTickCount() < time)
		WAIT(0);

	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, (title_id == NULL ? "HUD_TITLE" : title_id), "", (prepopulated_text == NULL ? "" : prepopulated_text), "", "", "", 64);

	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0)
		WAIT(0);

	std::stringstream ss;
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT())
		return std::string("");
	else
		return std::string(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
}

bool LoadModel(Hash model)
{
	if (!STREAMING::IS_MODEL_IN_CDIMAGE(model))
		return false;
	if (!STREAMING::IS_MODEL_VALID(model))
		return false;
	STREAMING::REQUEST_MODEL(model);
	while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
	return true;
}

void TeleportToMarker()
{
	Vector3 coords = GetBlipMarker();

	if (coords.x == 0 && coords.y == 0)
	{
		CPlayer::NotifyMap("No Waypoint has been set!");
		return;
	}

	// get entity to teleport
	CEntity e = CPlayer::GetLocalPlayer().GetPed();
	if (CPed(e.GetHandle()).IsInAnyVehicle(true))
		e = CPed(e.GetHandle()).GetCurrentVehicle();

	// load needed map region and check height levels for ground existence
	bool groundFound = false;
	static float groundCheckHeight[] =
	{ 100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 };
	for (int i = 0; i < sizeof(groundCheckHeight) / sizeof(float); i++)
	{
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e.GetHandle(), coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);
		WAIT(100);
		if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[i], &coords.z, 0))
		{
			groundFound = true;
			coords.z += 3.0;
			break;
		}
	}
	// if ground not found then set Z in air and give player a parachute
	if (!groundFound)
	{
		coords.z = 1000.0;
		WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
	}
	//do it
	e.SetCoordinates(coords, TRUE);
}

Vector3 GetBlipMarker()
{
	static Vector3 zero;
	Vector3 coords;

	bool blipFound = false;
	// search for marker blip
	int blipIterator = UI::_GET_BLIP_INFO_ID_ITERATOR();
	for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator))
		if (UI::GET_BLIP_INFO_ID_TYPE(i) == 4)
		{
			coords = UI::GET_BLIP_INFO_ID_COORD(i);
			blipFound = true;
			break;
		}

	if (blipFound)
		return coords;

	return zero;
}

void DropMoney(float x, float y, float z)
{
	OBJECT::CREATE_MONEY_PICKUPS(x, y, z, 2000, 1, 0);
}

std::set<Ped> GetNearbyPeds()
{
	return lastSeenPeds;
}

void UpdateNearbyPeds(Ped playerPed, int count)
{
	const int numElements = count;
	const int arrSize = numElements * 2 + 2;

	Ped *peds = new Ped[arrSize];
	peds[0] = numElements;
	int found = PED::GET_PED_NEARBY_PEDS(playerPed, peds, -1);

	for (int i = 0; i < found; i++)
	{
		int offsettedID = i * 2 + 2;

		if (!ENTITY::DOES_ENTITY_EXIST(peds[offsettedID]))
			continue;

		Ped xped = peds[offsettedID];

		bool inSet = lastSeenPeds.find(xped) != lastSeenPeds.end();
		if (!inSet)
			lastSeenPeds.insert(xped);
	}

	std::set<Ped>::iterator it;
	for (it = lastSeenPeds.begin(); it != lastSeenPeds.end();)
		if (!ENTITY::DOES_ENTITY_EXIST(*it))
			lastSeenPeds.erase(it++);
		else
			++it;

	delete peds;
}