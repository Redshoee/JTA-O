#pragma once
#include "entity.h"
#include "ped.h"

class CPlayer : public CPed
{
private:
	uint plyHandle;
public:
	CPlayer(uint plyHandle) : CPed(PLAYER::GET_PLAYER_PED(plyHandle)) { this->plyHandle = plyHandle; }
	
	CPed GetPed();
	uint GetPlayerHandle();
	void SetModel(Hash model);
	int GetTeam();
	void SetTeam(int team);
	char* GetName();
	float GetWantedLevelRadius();
	void SetWantedLevel(int level, bool now);
	void SetDispatchCops(bool toggle);
	bool IsPlaying();
	void ClearWantedLevel();
	bool IsPressingHorn();
	int GetWantedLevel();
	void SetPoliceIgnore(bool toggle);
	void SetPoliceBlips(bool toggle);
	void SetEveryoneIgnore(bool toggle);
	void ResetWantedLevelDifficulty();
	void SetWantedLevelDifficulty(float difficulty);
	void ReportCrime(int crimeType, int wantedLvlThresh);
	bool CanStartMission();
	void ResetStamina();
	float GetRemainingSprintTime();
	float GetRemainingSprintStamina();
	bool GiveAchievement(int achieve);
	static bool IsOnline();
	void SetInvincible(bool toggle);
	bool IsInvincible();
	void RemoveHelmet();
	void SetRagdollControl(bool toggle);
	static void SetTargetingMode(int mode);
	bool CanPedHear(CPed ped);
};