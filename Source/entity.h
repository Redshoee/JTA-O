#pragma once
#include "stdafx.h"
#define REQ_NETWORK_CONTROL_TIMEOUT 5

class CEntity;
class CVehicle;
class CPed;
class CPlayer;

class CEntity
{
private:
	uint handle;
	
public:
	CEntity(uint handle);

	void SetCoordinates(Vector3 coords, bool clearArea = false);
	bool Exists();
	int GetHealth();
	Hash GetModel();
	int GetMaxHealth();
	bool HasLineOfSightTo(CEntity ent, int traceType = 17);
	float GetHeading();
	void Kill();
	bool RequestControl(bool waitforcontrol = false);
	eEntityType GetEntityType();
	void Delete();
	void SetHealth(int hp);
	void SetMaxHealth(int maxhp);
	void SetHeading(float heading);
	Vector3 GetCoordinates(bool alive = false);
	uint GetHandle();
	bool IsDead();
	virtual void SetInvincible(bool toggle);
};