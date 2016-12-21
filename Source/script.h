#pragma once

class Script
{
public:
	static bool isInit();
	static void onTick();
	static std::string ParseCommand(std::string, std::vector<std::string>);
	static Player GetPlayerByName(std::string);
	static void DropMoney(float, float, float);
}; 