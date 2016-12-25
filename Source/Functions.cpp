#include "stdafx.h"

/*
	!! WARNING: !!
	THIS FILE WILL SOON BE REMOVED. IT IS NOT EXPECTED TO MAKE IT OUT OF V2.
*/

std::set<Ped> lastSeenPeds;

Ped ClonePed(Ped ped)
{
	if (ENTITY::DOES_ENTITY_EXIST(ped) && !ENTITY::IS_ENTITY_DEAD(ped))
		return PED::CLONE_PED(ped, ENTITY::GET_ENTITY_HEADING(ped), 1, 1);
	return 0;
}

Ped CreatePed(Hash PedHash, Vector3 SpawnCoordinates, int PedType, BOOL NetworkHandle)
{
	Ped NewPed;
	if (!LoadModel(PedHash))
		return -1;

	NewPed = PED::CREATE_PED(PedType, PedHash, SpawnCoordinates.x, SpawnCoordinates.y, SpawnCoordinates.z, 0, NetworkHandle, 1);
	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PedHash);
	return NewPed;
}

Vehicle CreateVehicle(Hash VehicleHash, Vector3 SpawnCoordinates, BOOL NetworkHandle)
{
	Vehicle NewVehicle;
	if (!LoadModel(VehicleHash))
		return -1;

	NewVehicle = VEHICLE::CREATE_VEHICLE(VehicleHash, SpawnCoordinates.x, SpawnCoordinates.y, SpawnCoordinates.z, 0, NetworkHandle, 1);
	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(VehicleHash);
	return NewVehicle;
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

void LoadAnim(char * dict)
{
	int tick = 0;
	STREAMING::REQUEST_ANIM_DICT(dict);
	while (tick < 100 && !STREAMING::HAS_ANIM_DICT_LOADED(dict))
	{
		tick++;
		WAIT(0);
	}
}

void PlayAnimation(Ped ped, bool loop, char * dict, char * anim)
{
	LoadAnim(dict);
	int a = -1;
	int b = 1;

	if (!loop)
	{
		a = 1;
		b = 0;
	}

	AI::TASK_PLAY_ANIM(ped, dict, anim, 10000.0f, -1.5f, a, b, 0.445f, false, false, false);

}

bool ApplyChosenSkin(DWORD model)
{
	if (!LoadModel(model))
		return false;
	Vehicle veh = NULL;

	if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE))
		veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

	PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
	//PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), FALSE);
	PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
	WAIT(0);

	if (veh != NULL)
		PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);

	WAIT(100);
	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
	return true;
}

bool ApplyChosenSkin(std::string skinName)
{
	DWORD model = $((char *)skinName.c_str());
	return ApplyChosenSkin(model);
}

void RequestControlOfid(Entity netid)
{
	int tick = 0;

	while (!NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netid) && tick <= 25)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netid);
		tick++;
	}
}

void RequestControlOfEnt(Entity entity)
{
	int tick = 0;
	while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && tick <= 25)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
		tick++;
	}
	if (NETWORK::NETWORK_IS_SESSION_STARTED()) 
	{
		int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
		RequestControlOfid(netID);
		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
	}
}

void ApplyForceToEntity(Entity e, Vector3 vec)
{
	if (e != PLAYER::PLAYER_PED_ID() && NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(e) == FALSE)
		RequestControlOfEnt(e);

	ENTITY::APPLY_FORCE_TO_ENTITY(e, 1, vec.x, vec.y, vec.z, 0, 0, 0, 0, 1, 1, 1, 0, 1);

}

void GodMode(Player ply, bool toggle)
{
	static int armor_player = 0;
	Ped playerPed = PLAYER::GET_PLAYER_PED(ply);
	if (armor_player == 0)
		armor_player = PED::GET_PED_ARMOUR(playerPed);

	if (toggle)
	{
		PLAYER::SET_PLAYER_INVINCIBLE(ply, true);
		ENTITY::SET_ENTITY_PROOFS(playerPed, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE);
		PED::SET_PED_CAN_RAGDOLL(playerPed, FALSE);
		PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(playerPed, FALSE);
		PED::ADD_ARMOUR_TO_PED(playerPed, PLAYER::GET_PLAYER_MAX_ARMOUR(ply) - PED::GET_PED_ARMOUR(playerPed));
	}
	else
	{
		PLAYER::SET_PLAYER_INVINCIBLE(ply, false);
		ENTITY::SET_ENTITY_PROOFS(playerPed, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE);
		PED::SET_PED_CAN_RAGDOLL(playerPed, TRUE);
		PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(playerPed, TRUE);
		if (armor_player != 0)
		{
			PED::SET_PED_ARMOUR(playerPed, armor_player);
			armor_player = 0;
		}
	}
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
	{
		if (!ENTITY::DOES_ENTITY_EXIST(*it))
			lastSeenPeds.erase(it++);
		else
			++it;
	}

	delete peds;
}

void SetAllNearbyPedsToCalm()
{
	for each (Ped xped in lastSeenPeds)
	{
		PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(xped, true);
		PED::SET_PED_FLEE_ATTRIBUTES(xped, 0, 0);
		PED::SET_PED_COMBAT_ATTRIBUTES(xped, 17, 1);
	}
}

float DegToRad(float degs)
{
	return degs*3.141592653589793f / 180.f;
}

Hash $(std::string str) {
	return GAMEPLAY::GET_HASH_KEY(&str[0u]);
}

Vector3 CoordsOf(Entity entity) {
	return ENTITY::GET_ENTITY_COORDS(entity, 1);
}

float DistanceBetween(Vector3 A, Vector3 B) {
	return GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(A.x, A.y, A.z, B.x, B.y, B.z, 1);
}

int RndInt(int start, int end) {
	return GAMEPLAY::GET_RANDOM_INT_IN_RANGE(start, end);
}

void TeleportToCoords(Entity e, Vector3 coords)
{
	ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, coords.z, 0, 0, 1);
	WAIT(0);
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

void TeleportToMarker()
{
	Vector3 coords = GetBlipMarker();

	if (coords.x == 0 && coords.y == 0)
	{
		NotifyMap("No Waypoint has been set!", FALSE);
		return;
	}

	// get entity to teleport
	Entity e = PLAYER::PLAYER_PED_ID();
	if (PED::IS_PED_IN_ANY_VEHICLE(e, 0))
		e = PED::GET_VEHICLE_PED_IS_USING(e);

	// load needed map region and check height levels for ground existence
	bool groundFound = false;
	static float groundCheckHeight[] =
	{ 100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 };
	for (int i = 0; i < sizeof(groundCheckHeight) / sizeof(float); i++)
	{
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);
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
	TeleportToCoords(e, coords);
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

void NotifyMap(std::string msg, BOOL blink) {
	UI::SET_TEXT_OUTLINE();
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(&msg[0u]);
	UI::_DRAW_NOTIFICATION(blink, FALSE);
}

void HelpText(std::string msg, int shape = -1)
{
	UI::_SET_TEXT_COMPONENT_FORMAT("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(&msg[0u]);
	UI::_DISPLAY_HELP_TEXT_FROM_STRING_LABEL(0, 0, 0, shape);
}

Player GetPlayerByName(std::string pname)
{
	for (int i = 0; i < 30; i++)
		if (strcmp(PLAYER::GET_PLAYER_NAME(i), pname.c_str()) == 0)
			return i;
	return -1;
}

void DropMoney(float x, float y, float z)
{
	//VERY UNSTABLE -- USE WITH CAUTION, DON'T FUCK THE VALUES TOO BADLY.
	OBJECT::CREATE_MONEY_PICKUPS(x, y, z, 2000, 1, 0);
}
