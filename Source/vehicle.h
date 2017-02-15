#pragma once
#include "entity.h"
#include "ped.h"

class CVehicle : public CEntity
{
public:
	CVehicle(uint handle) : CEntity(handle) {};

	void Explode(bool audible = true, bool visible = true);
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
	void RaiseRoof(bool instant = false);
	void LowerRoof(bool instant = false);
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
CVehicle CreateVehicle(Hash model, Vector3 pos, float heading = 0.0f);
CVehicle GetClosestVehicle(Vector3 pos, float radius, int flags = 0, Hash model = 0);