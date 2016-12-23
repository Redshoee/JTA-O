#pragma once

std::set<Ped> GetNearbyPeds(); //Get nearby peds. (See 'UpdateNearbyPeds')

Ped ClonePed(Ped ped); //Clone a Ped.
Ped CreatePed(Hash PedHash, Vector3 SpawnCoordinates, int ped_type, BOOL network_handle); //Create a Ped.

Vehicle CreateVehicle(Hash VehicleHash, Vector3 SpawnCoordinates, BOOL network_handle); //Create a Vehicle.

void LoadAnim(char * dict); //Load an animation by name.
void PlayAnimation(Ped ped, bool loop, char * dict, char * anim); //Play Ped animation.
void RequestControlOfEnt(Entity entity); //Request network control of an entity.
void ApplyForceToEntity(Entity e, Vector3 vec); //Apply force in a given Vector.
void GodMode(Player ply, bool toggle); //Toggle godmode on an entity.
void SetAllNearbyPedsToCalm(); //Sets all nearby Peds to calm; removing flee events. (see 'GetNearbyPeds')
void UpdateNearbyPeds(Ped playerPed, int count); //Update nearby Peds. (see 'GetNearbyPeds')
void TeleportToMarker(); //Teleport to Waypoint marker location.
void TeleportToCoords(Entity e, Vector3 coords); //Teleport an entity to a given coord.
void NotifyMap(std::string msg, BOOL blink); //Notification tray; shown above map, bottom left.
void HelpText(std::string msg, int shape); //Help message; shown above map, top left.
void DropMoney(float x, float y, float z); //Drop a money picup at a location.

bool LoadModel(Hash model); //Loads a Model Hash. Returns whether the model was valid.
bool ApplyChosenSkin(std::string skinName); //Apply skin to Player. Returns 

float DegToRad(float degs); //Converts Degrees to Radians.
float DistanceBetween(Vector3 A, Vector3 B); //Get the distance between two Vectors.

Hash $(std::string str); //Convert a String Hash into a Hash key.

Vector3 CoordsOf(Entity entity); //Get the coordinates of an entity.
Vector3 GetBlipMarker(); //Get Waypoint blip.

int RndInt(int start, int end); //Generates a random number.

std::string ShowKeyboard(char* title_id, char* prepopulated_text); //Show an onscreen keyboard; allowing user input. (see http://www.dev-c.com/nativedb/func/info/00dc833f2568dbf6 for title id's)

Player GetPlayerByName(std::string pname); //Get's a player by name. Returns -1 on failure.