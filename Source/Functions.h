#pragma once

//=================
// PED FUNCTIONS
//=================

Ped ClonePed(Ped ped);
Ped CreatePed(char* PedName, Vector3 SpawnCoordinates, int ped_type, bool network_handle);

//Animations
void LoadAnim(char * dict);
void PlayAnimation(Ped ped, bool loop, char * dict, char * anim);

//SKINS
bool ApplyChosenSkin(std::string skinName);

//CONTROL
void RequestControlOfEnt(Entity entity);

//FORCE
void ApplyForceToEntity(Entity e, float x, float y, float z);

//GOD MODE
void GodMode(bool toggle);

//CALM PEDS
void SetAllNearbyPedsToCalm();

//NEARBY PEDS
std::set<Ped> GetNearbyPeds();
void UpdateNearbyPeds(Ped playerPed, int count);

//little one-line function called '$' to convert $TRING into a hash-key:
Hash $(std::string str);

//Converts Radians to Degrees
float DegToRad(float degs);

//quick function to get-coords-of-entity:
Vector3 CoordsOf(Entity entity);

//quick function to get distance between 2 points:
float DistanceBetween(Vector3 A, Vector3 B);

//quick "get random int in range 0-x" function:
int RndInt(int start, int end);

//TELEPORTATION
Vector3 GetBlipMarker();
void TeleportToMarker();
void TeleportToObjective();
void TeleportToCoords(Entity e, Vector3 coords);

//KEYBOARD
std::string ShowKeyboard(char* title_id, char* prepopulated_text);

//NOTIFICATION
void NotifyMap(std::string msg, BOOL blink);