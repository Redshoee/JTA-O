#pragma once
#include "stdafx.h"

extern std::vector<std::string> weapons;

bool BoolDefToBool(BOOL b);
BOOL BoolToBoolDef(bool b);
std::vector<std::string> Split(std::string str, std::string sep);
void ReplaceAll(std::string& str, const std::string& from, const std::string& to);
void AddCommand(std::string cmd, CmdPtr func);
bool RunCommand(std::string cmd, std::vector<std::string> args);
std::string ShowKeyboard(char* title_id, char* prepopulated_text);
bool LoadModel(Hash model);
void TeleportToMarker();
Vector3 GetBlipMarker();
void DropMoney(float x, float y, float z);
std::set<Ped> GetNearbyPeds();
void UpdateNearbyPeds(Ped playerPed, int count);
Hash $(std::string name);