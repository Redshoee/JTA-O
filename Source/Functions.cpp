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

Hash $(std::string str) {
	return GAMEPLAY::GET_HASH_KEY(&str[0u]);
}

float DistanceBetween(Vector3 A, Vector3 B) {
	return GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(A.x, A.y, A.z, B.x, B.y, B.z, 1);
}

int RndInt(int start, int end) {
	return GAMEPLAY::GET_RANDOM_INT_IN_RANGE(start, end);
}
