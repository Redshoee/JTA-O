#pragma once
#include "entity.h"
#include "vehicle.h"
#include "stdafx.h"

class CPed : public CEntity
{
public:
	CPed(uint handle) : CEntity(handle) {};

	bool IsInVehicle(CVehicle veh, bool atGetIn);
	bool IsInjured();
	bool IsReloading();
	bool IsPlayer();
	bool IsMale();
	bool IsHuman();
	void SetIntoVehicle(CVehicle veh, int seat);
	CVehicle GetCurrentVehicle();
	CVehicle GetLastVehicle();
	void ResetLastVehicle();
	bool IsInAnyVehicle(bool atGetIn);
	bool IsJumpingFromVehicle();
	bool IsDucking();
	void GiveWeapon(uint wep, int ammo, bool hide, bool equipNow);
	void SetDucking(bool toggle);
	bool IsProne();
	int GetArmor();
	bool IsInCombat(CPed target);
	bool IsJacking();
	bool IsBeingJacked();
	bool IsBeingStunned();
	bool CanFlyThroughWindscreen();
	void SetFlyThroughWindscreen(bool toggle);
	int GetType();
	void SetIsCop(bool toggle);
	bool IsRagdoll();
	bool CanRagdoll();
	void SetCanRagdoll(bool toggle);
	void Resurrect();
	int GetRelationshipBetweenPed(CPed ped);
};
CPed CreatePed(Hash model, Vector3 pos, int type, float heading = 0.0f);