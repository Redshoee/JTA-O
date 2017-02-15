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
	void SetInvincible(bool toggle);
	bool IsInvincible();
	void RemoveHelmet();
	void SetRagdollControl(bool toggle);
	bool CanPedHear(CPed ped);
	Color3 GetPlayerRGB();
	int GetPlayerTeam();
	void SetPlayerTeam(int team);
	bool IsTargetingAnything();
};
CPlayer GetLocalPlayer();
void SetTargetingMode(int mode);
bool IsOnline();
CPlayer GetPlayerByName(std::string pname); //TODO: Rewrite
void NotifyMap(std::string msg, bool blink = false);
void HelpText(std::string msg, int shape = -1);
int GetPlayerCount();
Raycast GetLookCoordinates();
std::set<Player> GetPlayersInGame();
CPlayer GetPlayerByPed(CPed ped);