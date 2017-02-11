#pragma once
#include "stdafx.h"

bool WantedLevelCommand(std::vector<std::string>);
bool SetVehicleSpeedCommand(std::vector<std::string>);
bool TeleportCommand(std::vector<std::string>);
bool TeleportWaypointCommand(std::vector<std::string>);
bool SpawnVehicleCommand(std::vector<std::string>);
bool FindVehicleCommand(std::vector<std::string>);
bool DropMoneyCommand(std::vector<std::string>);
bool GiveAllWeaponsCommand(std::vector<std::string>);
bool KillNearbyEnemiesCommand(std::vector<std::string>);
bool InvincibilityCommand(std::vector<std::string>);
bool FixVehicleCommand(std::vector<std::string>);
bool FlyThroughWindshieldCommand(std::vector<std::string>);
bool SecretCommand(std::vector<std::string>);
void RegisterCommands();