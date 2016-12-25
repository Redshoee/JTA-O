#include "stdafx.h"
#include "ped.h"

bool CPed::IsInVehicle(CVehicle veh, bool atGetIn)
{
	return BoolDefToBool(PED::IS_PED_IN_VEHICLE(GetHandle(), veh.GetHandle(), BoolToBoolDef(atGetIn)));
}

bool CPed::IsInjured()
{
	return BoolDefToBool(PED::IS_PED_INJURED(GetHandle()));
}

bool CPed::IsReloading()
{
	return BoolDefToBool(PED::IS_PED_RELOADING(GetHandle()));
}

bool CPed::IsPlayer()
{
	return BoolDefToBool(PED::IS_PED_A_PLAYER(GetHandle()));
}

bool CPed::IsMale()
{
	return BoolDefToBool(PED::IS_PED_MALE(GetHandle()));
}

bool CPed::IsHuman()
{
	return BoolDefToBool(PED::IS_PED_HUMAN(GetHandle()));
}

CVehicle CPed::GetCurrentVehicle()
{
	return CVehicle(PED::GET_VEHICLE_PED_IS_IN(GetHandle(), FALSE));
}

CVehicle CPed::GetLastVehicle()
{
	return CVehicle(PED::GET_VEHICLE_PED_IS_IN(GetHandle(), TRUE));
}

void CPed::ResetLastVehicle()
{
	PED::RESET_PED_LAST_VEHICLE(GetHandle());
}

bool CPed::IsInAnyVehicle(bool atGetIn)
{
	return BoolDefToBool(PED::IS_PED_IN_ANY_VEHICLE(GetHandle(), BoolToBoolDef(atGetIn)));
}

bool CPed::IsJumpingFromVehicle()
{
	return BoolDefToBool(PED::IS_PED_JUMPING_OUT_OF_VEHICLE(GetHandle()));
}

bool CPed::IsDucking()
{
	return BoolDefToBool(PED::IS_PED_DUCKING(GetHandle()));
}

void CPed::SetDucking(bool toggle)
{
	PED::SET_PED_DUCKING(GetHandle(), BoolToBoolDef(toggle));
}

bool CPed::IsProne()
{
	return BoolDefToBool(PED::IS_PED_PRONE(GetHandle()));
}

bool CPed::IsInCombat(CPed target)
{
	return BoolDefToBool(PED::IS_PED_IN_COMBAT(GetHandle(), target.GetHandle()));
}

bool CPed::IsJacking()
{
	return BoolDefToBool(PED::IS_PED_JACKING(GetHandle()));
}

bool CPed::IsBeingJacked()
{
	return BoolDefToBool(PED::IS_PED_BEING_JACKED(GetHandle()));
}

bool CPed::IsBeingStunned()
{
	return BoolDefToBool(PED::IS_PED_BEING_STUNNED(GetHandle(), 0));
}

int CPed::GetType()
{
	return PED::GET_PED_TYPE(GetHandle());
}

void CPed::SetIsCop(bool toggle)
{
	PED::SET_PED_AS_COP(GetHandle(), BoolToBoolDef(toggle));
}

bool CPed::IsRagdoll()
{
	return BoolDefToBool(PED::IS_PED_RAGDOLL(GetHandle()));
}

bool CPed::CanRagdoll()
{
	return BoolDefToBool(PED::CAN_PED_RAGDOLL(GetHandle()));
}

void CPed::SetCanRagdoll(bool toggle)
{
	PED::SET_PED_CAN_RAGDOLL(GetHandle(), BoolToBoolDef(toggle));
}

void CPed::Resurrect()
{
	PED::RESURRECT_PED(GetHandle());
}