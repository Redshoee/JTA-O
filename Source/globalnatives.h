#pragma once
#include "stdafx.h"

void SetWeatherNow(eWeather w);
void SetWeatherOverDuration(eWeather w, float time);
void SetRandomWeather();
void SetTimeScale(float scale);
float GetWindSpeed();
int GetGameTimer();
float GetFrameTime();
int GetFrameCount();
bool GetGroundZCoord(Vector3 pos, float *groundZ, bool unk = 0);
float DistanceBetween(Vector3 pos1, Vector3 pos2, bool useZ);
void CreateExplosion(Vector3 pos, eExplosionType type, float damageScale = 1.0f, bool audiable = true, bool visible = true, float cameraShake = 1.0f);
void CreateOwnedExplosion(CPed owner, Vector3 pos, eExplosionType type, float damageScale = 1.0f, bool audiable = true, bool visible = true, float cameraShake = 1.0f);
Raycast CastRay(Vector3 source, Vector3 direction, float maxDistance, eIntersectFlags intersectOptions);
void DrawLine(Vector3 from, Vector3 to, Color4 col);
void DrawPoly(Vector3 a, Vector3 b, Vector3 c, Color4 col);
void DrawBox(Vector3 a, Vector3 b, Color4 col);
Vector2 WorldToScreen(Vector3 pos);