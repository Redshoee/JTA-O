// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// Windows Library Files:
#pragma comment(lib, "ws2_32.lib")

// Windows Header Files:
#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <Psapi.h>
#include <MinHook.h>
#include <timeapi.h>
#include <time.h>
#include <thread>

#pragma comment(lib, "winmm.lib")

// Additional Header Files:
#include "Log.h"
#include "memory.h"
#include "types.h"
#include "enums.h"
#include "input_hook.h"
#include "keyboard.h"
#include "cross_mapping.h"
#include "native_invoker.h"
#include "native_caller.h"
#include "natives.h"
#include "hooking.h"
#include "structs.h"
#include "script.h"
#include "utils.h"
#include "entity.h"
#include "ped.h"
#include "vehicle.h"
#include "player.h"
#include "globalnatives.h"