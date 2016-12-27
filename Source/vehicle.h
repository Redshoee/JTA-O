#pragma once
#include "entity.h"
#include "ped.h"

class CVehicle : public CEntity
{
public:
	CVehicle(uint handle) : CEntity(handle) {};

	static CVehicle CreateVehicle(Hash model, Vector3 loc, float heading = 0.0f);
	void Explode(bool audible, bool visible);
	Color3 GetPrimaryColor();
	Color3 GetSecondaryColor();
	void SetPrimaryColor(Color3 color);
	void SetSecondaryColor(Color3 color);
	void ToggleSiren(bool toggle);
	bool IsSirenOn();
	CPed GetPedOnSeat(eVehicleSeat seat);
	CPed GetDriver();
	void SetForwardSpeed(float speed);
	void SetCanTiresBurst(bool toggle);
	bool CanTiresBurst();
	void RolldownWindow(eVehicleWindow window);
	void RollupWindow(eVehicleWindow window);
	void SetAlarm(bool toggle);
	bool IsAlarmActive();
	void RaiseRoof(bool instant);
	void LowerRoof(bool instant);
	eVehicleRoofState GetRoofState();
	void SetDriveable(bool toggle);
	float GetEngineHealth();
	void SetEngineHealth(float hp);
	float GetBodyHealth();
	void SetBodyHealth(float hp);
	bool IsDriveable();
	void SetNeedsHotwire(bool toggle);
	void StartHorn(int duration, Hash mode, bool forever);
	void Fix();
	bool HasWeapons();
};