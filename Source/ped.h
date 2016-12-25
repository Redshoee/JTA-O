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
	CVehicle GetCurrentVehicle();
	CVehicle GetLastVehicle();
	void ResetLastVehicle();
	bool IsInAnyVehicle(bool atGetIn);
	bool IsJumpingFromVehicle();
	bool IsDucking();
	void SetDucking(bool toggle);
	bool IsProne();
	bool IsInCombat(CPed target);
	bool IsJacking();
	bool IsBeingJacked();
	bool IsBeingStunned();
	int GetType();
	void SetIsCop(bool toggle);
	bool IsRagdoll();
	bool CanRagdoll();
	void SetCanRagdoll(bool toggle);
	void Resurrect();
};