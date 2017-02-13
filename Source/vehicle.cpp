#include "stdafx.h"
#include "vehicle.h"

void CVehicle::Explode(bool audible, bool visible)
{
	VEHICLE::EXPLODE_VEHICLE(GetHandle(), BoolToBoolDef(audible), BoolToBoolDef(!visible));
}

Color3 CVehicle::GetPrimaryColor()
{
	int *r = 0, *g = 0, *b = 0;
	VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(GetHandle(), r, g, b);
	return Color3(*r, *g, *b);
}

Color3 CVehicle::GetSecondaryColor()
{
	int *r = 0, *g = 0, *b = 0;
	VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(GetHandle(), r, g, b);
	return Color3(*r, *g, *b);
}

void CVehicle::SetPrimaryColor(Color3 color)
{
	VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(GetHandle(), color.r, color.g, color.b);
}

void CVehicle::SetSecondaryColor(Color3 color)
{
	VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(GetHandle(), color.r, color.g, color.b);
}

void CVehicle::Fix()
{
	VEHICLE::SET_VEHICLE_FIXED(GetHandle());
}

bool CVehicle::IsDriveable()
{
	return BoolDefToBool(VEHICLE::IS_VEHICLE_DRIVEABLE(GetHandle(), FALSE));
}

void CVehicle::SetDriveable(bool toggle)
{
	VEHICLE::SET_VEHICLE_UNDRIVEABLE(GetHandle(), BoolToBoolDef(!toggle));
}

void CVehicle::ToggleSiren(bool toggle)
{
	VEHICLE::SET_VEHICLE_SIREN(GetHandle(), BoolToBoolDef(toggle));
}

bool CVehicle::IsSirenOn()
{
	return BoolDefToBool(VEHICLE::IS_VEHICLE_SIREN_ON(GetHandle()));
}

CPed CVehicle::GetPedOnSeat(eVehicleSeat seat)
{
	return CPed(VEHICLE::GET_PED_IN_VEHICLE_SEAT(GetHandle(), seat));
}

CPed CVehicle::GetDriver()
{
	return GetPedOnSeat(VehicleSeatDriver);
}

void CVehicle::SetForwardSpeed(float speed)
{
	VEHICLE::SET_VEHICLE_FORWARD_SPEED(GetHandle(), speed);
}

void CVehicle::SetCanTiresBurst(bool toggle)
{
	VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(GetHandle(), BoolToBoolDef(toggle));
}

bool CVehicle::CanTiresBurst()
{
	return BoolDefToBool(VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(GetHandle()));
}

void CVehicle::RolldownWindow(eVehicleWindow window)
{
	VEHICLE::ROLL_DOWN_WINDOW(GetHandle(), window);
}

void CVehicle::RollupWindow(eVehicleWindow window)
{
	VEHICLE::ROLL_UP_WINDOW(GetHandle(), window);
}

void CVehicle::SetAlarm(bool toggle)
{
	VEHICLE::SET_VEHICLE_ALARM(GetHandle(), toggle);
}

bool CVehicle::IsAlarmActive()
{
	return BoolDefToBool(VEHICLE::IS_VEHICLE_ALARM_ACTIVATED(GetHandle()));
}

void CVehicle::RaiseRoof(bool instant)
{
	VEHICLE::RAISE_CONVERTIBLE_ROOF(GetHandle(), BoolToBoolDef(instant));
}

void CVehicle::LowerRoof(bool instant)
{
	VEHICLE::LOWER_CONVERTIBLE_ROOF(GetHandle(), BoolToBoolDef(instant));
}

eVehicleRoofState CVehicle::GetRoofState()
{
	return static_cast<eVehicleRoofState>(VEHICLE::GET_CONVERTIBLE_ROOF_STATE(GetHandle()));
}

float CVehicle::GetEngineHealth()
{
	return VEHICLE::GET_VEHICLE_ENGINE_HEALTH(GetHandle());
}

void CVehicle::SetEngineHealth(float hp)
{
	VEHICLE::SET_VEHICLE_ENGINE_HEALTH(GetHandle(), hp);
}

float CVehicle::GetBodyHealth()
{
	return VEHICLE::GET_VEHICLE_BODY_HEALTH(GetHandle());
}

void CVehicle::SetBodyHealth(float hp)
{
	VEHICLE::SET_VEHICLE_BODY_HEALTH(GetHandle(), hp);
}

void CVehicle::SetNeedsHotwire(bool toggle)
{
	VEHICLE::SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(GetHandle(), BoolToBoolDef(toggle));
}

void CVehicle::StartHorn(int duration, Hash mode, bool forever)
{
	VEHICLE::START_VEHICLE_HORN(GetHandle(), duration, mode, BoolToBoolDef(forever));
}

bool CVehicle::HasWeapons()
{
	return BoolDefToBool(VEHICLE::DOES_VEHICLE_HAVE_WEAPONS(GetHandle()));
}

CVehicle CreateVehicle(Hash model, Vector3 pos, float heading)
{
	return CVehicle(VEHICLE::CREATE_VEHICLE(model, pos.x, pos.y, pos.z, heading, FALSE, TRUE));
}