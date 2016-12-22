#pragma once

std::set<Ped> GetNearbyPeds();

Ped ClonePed(Ped ped);
Ped CreatePed(char* PedName, Vector3 SpawnCoordinates, int ped_type, bool network_handle);

void LoadAnim(char * dict);
void PlayAnimation(Ped ped, bool loop, char * dict, char * anim);
void RequestControlOfEnt(Entity entity);
void ApplyForceToEntity(Entity e, float x, float y, float z);
void GodMode(bool toggle);
void SetAllNearbyPedsToCalm();
void UpdateNearbyPeds(Ped playerPed, int count);
void TeleportToMarker();
void TeleportToObjective();
void TeleportToCoords(Entity e, Vector3 coords);
void NotifyMap(std::string msg, BOOL blink);

bool ApplyChosenSkin(std::string skinName);

float DegToRad(float degs);
float DistanceBetween(Vector3 A, Vector3 B);

Hash $(std::string str);

Vector3 CoordsOf(Entity entity);
Vector3 GetBlipMarker();

int RndInt(int start, int end);

std::string ShowKeyboard(char* title_id, char* prepopulated_text);