#include "stdafx.h"

std::map<std::string, CmdPtr> conCommands;

BOOL BoolToBoolDef(bool b)
{
	return (b) ? TRUE : FALSE;
}

bool BoolDefToBool(BOOL b) 
{
	return b == 1;
}

std::vector<std::string> Split(std::string str, std::string sep) {
	char* cstr = const_cast<char*>(str.c_str());
	char* current;
	std::vector<std::string> arr;
	current = strtok(cstr, sep.c_str());
	while (current != NULL) {
		arr.push_back(current);
		current = strtok(NULL, sep.c_str());
	}
	return arr;
}

void ReplaceAll(std::string& str, const std::string& from, const std::string& to)
{
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

void AddCommand(std::string cmd, CmdPtr func)
{
	conCommands[cmd] = func;
	Log::Msg("Registed command %s.", cmd.c_str());
}

bool RunCommand(std::string cmd, std::vector<std::string> args)
{
	CmdPtr commandToExec = conCommands[cmd];
	if (commandToExec == nullptr)
	{
		CPlayer::NotifyMap("Unknown command.", FALSE);
		Log::Msg("WARNING: Attempted to run a command that didn't exist?");
		return false;
	}
	bool ret = commandToExec(args);
	Log::Msg("Running command %s. (returned %d)", cmd.c_str(), ret);
	return ret;
}

std::string ShowKeyboard(char* title_id, char* prepopulated_text)
{
	DWORD time = GetTickCount() + 400;
	while (GetTickCount() < time)
		WAIT(0);

	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, (title_id == NULL ? "HUD_TITLE" : title_id), "", (prepopulated_text == NULL ? "" : prepopulated_text), "", "", "", 64);

	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0)
		WAIT(0);

	std::stringstream ss;
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT())
		return std::string("");
	else
		return std::string(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
}

bool LoadModel(Hash model)
{
	if (!STREAMING::IS_MODEL_IN_CDIMAGE(model))
		return false;
	if (!STREAMING::IS_MODEL_VALID(model))
		return false;
	STREAMING::REQUEST_MODEL(model);
	while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
	return true;
}