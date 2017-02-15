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

void SetTargetingMode(int mode)
{
	PLAYER::SET_PLAYER_TARGETING_MODE(mode);
}

bool CPlayer::CanPedHear(CPed ped)
{
	return BoolDefToBool(PLAYER::CAN_PED_HEAR_PLAYER(GetPlayerHandle(), ped.GetHandle()));
}

Color3 CPlayer::GetPlayerRGB()
{
	int *r, *g, *b;
	PLAYER::GET_PLAYER_RGB_COLOUR(GetPlayerHandle(), r, g, b);
	return Color3(*r, *g, *b);
}

CPlayer GetPlayerByName(std::string pname) //Returns a Player by name. Returns -1 if no player found.
{
	for each(Player plyHandle in GetPlayersInGame())
	{
		CPlayer ply = CPlayer(plyHandle);
		if (strcmp(ply.GetName(), pname.c_str()) == 0)
			return ply;
	}
	return CPlayer(-1);
}


CPlayer GetLocalPlayer()
{
	return CPlayer(PLAYER::PLAYER_ID());
}

int CPlayer::GetPlayerTeam()
{
	return PLAYER::GET_PLAYER_TEAM(GetPlayerHandle());
}

void CPlayer::SetPlayerTeam(int team)
{
	PLAYER::SET_PLAYER_TEAM(GetPlayerHandle(), team);
}

Raycast GetLookCoordinates()
{
	Vector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
	Vector3 camRot = CAM::GET_GAMEPLAY_CAM_ROT(2);
	float retz = camRot.z * 0.0174532924F;
	float retx = camRot.x * 0.0174532924F;
	float absx = abs(cos(retx));
	Vector3 camStuff;
	camStuff.x = sin(retz) * absx  * -1;
	camStuff.y = cos(retz) * absx;
	camStuff.z = sin(retx);
	return CastRay(camCoords, camStuff, 9999999.0f, IntersectFlagsEverything);
}

bool CPlayer::IsTargetingAnything()
{
	return BoolDefToBool(PLAYER::IS_PLAYER_TARGETTING_ANYTHING(GetPlayerHandle()));
}

void NotifyMap(std::string msg, bool blink)
{
	UI::SET_TEXT_OUTLINE();
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(&msg[0u]);
	UI::_DRAW_NOTIFICATION(BoolToBoolDef(blink), FALSE);
}

void HelpText(std::string msg, int shape)
{
	UI::_SET_TEXT_COMPONENT_FORMAT("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(&msg[0u]);
	UI::_DISPLAY_HELP_TEXT_FROM_STRING_LABEL(0, 0, 0, shape);
}

bool IsOnline()
{
	return BoolDefToBool(PLAYER::IS_PLAYER_ONLINE());
}

std::set<Player> GetPlayersInGame() //TODO: Use CPlayer
{
	std::set<Player> players;
	for (int i = 0; i < 30; i++)
	{
		if (CPlayer(i).Exists())
			players.insert(i);
	}
	return players;
}

CPlayer GetPlayerByPed(CPed ped)
{
	for each(Player ply in GetPlayersInGame())
	{
		CPlayer targ = CPlayer(ply);
		if (targ.GetPed().GetHandle() == ped.GetHandle())
			return targ;
		return CPlayer(-1);
	}
}