#include "stdafx.h"
#include "entity.h"
#include "player.h"

CPed CPlayer::GetPed()
{
	return CPed(GetHandle());
}

uint CPlayer::GetPlayerHandle()
{
	return plyHandle;
}

void CPlayer::SetModel(Hash model)
{
	PLAYER::SET_PLAYER_MODEL(GetPlayerHandle(), model);
}

int CPlayer::GetTeam()
{
	return PLAYER::GET_PLAYER_TEAM(GetPlayerHandle());
}

void CPlayer::SetTeam(int team)
{
	PLAYER::SET_PLAYER_TEAM(GetPlayerHandle(), team);
}

char *CPlayer::GetName()
{
	return PLAYER::GET_PLAYER_NAME(GetPlayerHandle());
}

float CPlayer::GetWantedLevelRadius()
{
	return PLAYER::GET_WANTED_LEVEL_RADIUS(GetPlayerHandle());
}

void CPlayer::SetWantedLevel(int level, bool now)
{
	PLAYER::SET_PLAYER_WANTED_LEVEL(GetPlayerHandle(), level, FALSE);
	if (now)
		PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(GetPlayerHandle(), FALSE);
}

void CPlayer::SetDispatchCops(bool toggle)
{
	PLAYER::SET_DISPATCH_COPS_FOR_PLAYER(GetPlayerHandle(), BoolToBoolDef(toggle));
}

bool CPlayer::IsPlaying()
{
	return BoolDefToBool(PLAYER::IS_PLAYER_PLAYING(GetPlayerHandle()));
}

void CPlayer::ClearWantedLevel()
{
	PLAYER::CLEAR_PLAYER_WANTED_LEVEL(GetPlayerHandle());
}

bool CPlayer::IsPressingHorn()
{
	return BoolDefToBool(PLAYER::IS_PLAYER_PRESSING_HORN(GetPlayerHandle()));
}

int CPlayer::GetWantedLevel()
{
	return PLAYER::GET_PLAYER_WANTED_LEVEL(GetPlayerHandle());
}

void CPlayer::SetPoliceIgnore(bool toggle)
{
	PLAYER::SET_POLICE_IGNORE_PLAYER(GetPlayerHandle(), BoolToBoolDef(toggle));
}

void CPlayer::SetPoliceBlips(bool toggle)
{
	PLAYER::SET_POLICE_RADAR_BLIPS(BoolToBoolDef(toggle));
}

void CPlayer::SetEveryoneIgnore(bool toggle)
{
	PLAYER::SET_EVERYONE_IGNORE_PLAYER(GetPlayerHandle(), BoolToBoolDef(toggle));
}

void CPlayer::ResetWantedLevelDifficulty()
{
	PLAYER::RESET_WANTED_LEVEL_DIFFICULTY(GetPlayerHandle());
}

void CPlayer::SetWantedLevelDifficulty(float difficulty)
{
	PLAYER::SET_WANTED_LEVEL_DIFFICULTY(GetPlayerHandle(), difficulty);
}

void CPlayer::ReportCrime(int crimeType, int wantedLvlThresh)
{
	PLAYER::REPORT_CRIME(GetPlayerHandle(), crimeType, wantedLvlThresh);
}

bool CPlayer::CanStartMission()
{
	return BoolDefToBool(PLAYER::CAN_PLAYER_START_MISSION(GetPlayerHandle()));
}

void CPlayer::ResetStamina()
{
	PLAYER::RESET_PLAYER_STAMINA(GetPlayerHandle());
}

float CPlayer::GetRemainingSprintTime()
{
	return PLAYER::GET_PLAYER_SPRINT_TIME_REMAINING(GetPlayerHandle());
}

float CPlayer::GetRemainingSprintStamina()
{
	return PLAYER::GET_PLAYER_SPRINT_STAMINA_REMAINING(GetPlayerHandle());
}

bool CPlayer::GiveAchievement(int achieve)
{
	return BoolDefToBool(PLAYER::GIVE_ACHIEVEMENT_TO_PLAYER(achieve));
}

bool CPlayer::IsOnline()
{
	return BoolDefToBool(PLAYER::IS_PLAYER_ONLINE());
}

void CPlayer::SetInvincible(bool toggle)
{
	PLAYER::SET_PLAYER_INVINCIBLE(GetPlayerHandle(), BoolToBoolDef(toggle));
}

bool CPlayer::IsInvincible()
{
	return BoolDefToBool(PLAYER::GET_PLAYER_INVINCIBLE(GetPlayerHandle()));
}

void CPlayer::RemoveHelmet()
{
	PLAYER::REMOVE_PLAYER_HELMET(GetPlayerHandle(), TRUE);
}

void CPlayer::SetRagdollControl(bool toggle)
{
	PLAYER::GIVE_PLAYER_RAGDOLL_CONTROL(GetPlayerHandle(), BoolToBoolDef(toggle));
}

void CPlayer::SetTargetingMode(int mode)
{
	PLAYER::SET_PLAYER_TARGETING_MODE(mode);
}

bool CPlayer::CanPedHear(CPed ped)
{
	return BoolDefToBool(PLAYER::CAN_PED_HEAR_PLAYER(GetPlayerHandle(), ped.GetHandle()));
}