#include "stdafx.h"
#include "entity.h"

CEntity::CEntity(uint handle)
{
	this->handle = handle;
}

Vector3 CEntity::GetCoordinates(BOOL alive)
{
	return ENTITY::GET_ENTITY_COORDS(GetHandle(), alive);
}

void CEntity::SetCoordinates(Vector3 coords, BOOL clearArea)
{
	ENTITY::SET_ENTITY_COORDS(GetHandle(), coords.x, coords.y, coords.z, TRUE, TRUE, TRUE, clearArea);
}

void CEntity::SetHeading(float heading)
{
	ENTITY::SET_ENTITY_HEADING(GetHandle(), heading);
}

int CEntity::GetHealth()
{
	return ENTITY::GET_ENTITY_HEALTH(GetHandle());
}

int CEntity::GetMaxHealth()
{
	return ENTITY::GET_ENTITY_MAX_HEALTH(GetHandle());
}

void CEntity::SetHealth(int hp)
{
	ENTITY::SET_ENTITY_HEALTH(GetHandle(), hp);
}

Hash CEntity::GetModel()
{
	return ENTITY::GET_ENTITY_MODEL(GetHandle());
}

void CEntity::SetMaxHealth(int maxhp)
{
	ENTITY::SET_ENTITY_MAX_HEALTH(GetHandle(), maxhp);
}

void CEntity::Kill()
{
	SetHealth(0);
}

float CEntity::GetHeading()
{
	return ENTITY::GET_ENTITY_HEADING(GetHandle());
}

bool CEntity::IsDead()
{
	return ENTITY::IS_ENTITY_DEAD(GetHandle()) == 1;
}

uint CEntity::GetHandle()
{
	return handle;
}
