#pragma once

class Script
{
public:
	static bool IsInit();
	static void OnTick();
	static std::string ParseCommand(std::string, std::vector<std::string>);
}; 