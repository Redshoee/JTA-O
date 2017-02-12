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

Raycast CastRay(Vector3 source, Vector3 direction, float maxDistance, eIntersectFlags intersectOptions)
{
	Vector3 target;
	BOOL hit;
	Vector3 endCoords;
	Vector3 surfaceNormal;
	Entity hitEntity;

	int ray = WORLDPROBE::_CAST_RAY_POINT_TO_POINT(source.x, source.y, source.z, direction.x, direction.y, direction.z, intersectOptions, 0, 7);
	WORLDPROBE::GET_SHAPE_TEST_RESULT(ray, &hit, &endCoords, &surfaceNormal, &hitEntity);
	return Raycast(source, endCoords, BoolDefToBool(hit), CEntity(hitEntity));
}

void DrawLine(Vector3 from, Vector3 to, Color4 col)
{
	GRAPHICS::DRAW_LINE(from.x, from.y, from.z, to.x, to.y, to.z, col.r, col.g, col.b, col.a);
}

void DrawPoly(Vector3 a, Vector3 b, Vector3 c, Color4 col)
{
	GRAPHICS::DRAW_POLY(a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z, col.r, col.g, col.b, col.a);
}

void DrawBox(Vector3 a, Vector3 b, Color4 col)
{
	GRAPHICS::DRAW_BOX(a.x, a.y, a.z, b.x, b.y, b.z, col.r, col.g, col.b, col.a);
}

Vector2 WorldToScreen(Vector3 pos)
{
	float outx, outy;
	GRAPHICS::_WORLD3D_TO_SCREEN2D(pos.x, pos.y, pos.z, &outx, &outy);
	return Vector2(outx, outy);
}