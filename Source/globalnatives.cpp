#include "stdafx.h"

static char weatherStrings[64][32] = { "CLEAR", "EXTRASUNNY", "CLOUDS", "OVERCAST", "RAIN", "CLEARING", "THUNDER", "SMOG", "FOGGY", "XMAS", "SNOWLIGHT", "BLIZZARD" };

void SetWeatherNow(eWeather w)
{
	GAMEPLAY::SET_WEATHER_TYPE_NOW(weatherStrings[w]);
}

void  SetWeatherOverDuration(eWeather w, float time)
{
	GAMEPLAY::_SET_WEATHER_TYPE_OVER_TIME(weatherStrings[w], time);
}

void SetRandomWeather()
{
	GAMEPLAY::SET_RANDOM_WEATHER_TYPE();
}

void SetTimeScale(float scale)
{
	GAMEPLAY::SET_TIME_SCALE((scale < 0 ? 0 : (scale > 1 ? 1 : scale)));
}

bool GetGroundZCoord(Vector3 pos, float *groundZ, bool unk)
{
	return BoolDefToBool(GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(pos.x, pos.y, pos.z, groundZ, BoolToBoolDef(unk)));
}

int GetFrameCount()
{
	return GAMEPLAY::GET_FRAME_COUNT();
}

float GetFrameTime()
{
	return GAMEPLAY::GET_FRAME_TIME();
}

int GetGameTimer()
{
	return GAMEPLAY::GET_GAME_TIMER();
}

float DistanceBetween(Vector3 pos1, Vector3 pos2, bool useZ)
{
	return GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z, BoolToBoolDef(useZ));
}
void CreateExplosion(Vector3 pos, eExplosionType type, float damageScale, bool audiable, bool visible, float cameraShake)
{
	FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, type, damageScale, BoolToBoolDef(audiable), BoolToBoolDef(!visible), cameraShake);
}

void CreateOwnedExplosion(Vector3 pos, eExplosionType type, float damageScale, bool audiable, bool visible, float cameraShake, CPed owner)
{
	FIRE::ADD_OWNED_EXPLOSION(owner.GetHandle(), pos.x, pos.y, pos.z, type, damageScale, BoolToBoolDef(audiable), BoolToBoolDef(!visible), cameraShake);
}