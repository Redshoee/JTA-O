#pragma once
#include "stdafx.h"

class Command
{
public:
	Command(std::string cmd);
	void DoCommand(std::set<std::string> args);
};