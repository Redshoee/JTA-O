#pragma once
#include "stdafx.h"

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

	void SetCoordinates(Vector3 coords, bool clearArea);
	bool Exists();
	int GetHealth();
	Hash GetModel();
	int GetMaxHealth();
	float GetHeading();
	void Kill();
	void SetHealth(int hp);
	void SetMaxHealth(int maxhp);
	void SetHeading(float heading);
	Vector3 GetCoordinates(bool alive);
	uint GetHandle();
	bool IsDead();
};