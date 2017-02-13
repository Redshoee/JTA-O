#include "stdafx.h"
#include "entity.h"

CEntity::CEntity(uint handle)
{
	this->handle = handle;
}

Vector3 CEntity::GetCoordinates(bool alive)
{
	return ENTITY::GET_ENTITY_COORDS(GetHandle(), BoolToBoolDef(alive));
}

void CEntity::SetCoordinates(Vector3 coords, bool clearArea)
{
	ENTITY::SET_ENTITY_COORDS(GetHandle(), coords.x, coords.y, coords.z, TRUE, TRUE, TRUE, BoolToBoolDef(clearArea));
}

void CEntity::SetHeading(float heading)
{
	ENTITY::SET_ENTITY_HEADING(GetHandle(), heading);
}

bool CEntity::HasLineOfSightTo(CEntity ent, int traceType)
{
	return BoolDefToBool(ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(GetHandle(), ent.GetHandle(), traceType));
}

bool CEntity::RequestControl(bool waitforcontrol)
{
	time_t start = time(NULL);
	if (waitforcontrol)
	{
		while (!BoolDefToBool(NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(GetHandle())) && time(NULL) >= (start + REQ_NETWORK_CONTROL_TIMEOUT))
			WAIT(0);
		return BoolDefToBool(NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(GetHandle())); //Returning form the loop doesn't mean we have control, we might have timed out.
	}
	else
		return BoolDefToBool(NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(GetHandle()));
}

void CEntity::Delete()
{
	ENTITY::DELETE_ENTITY((Entity *)GetHandle());
}

bool CEntity::Exists()
{
	return BoolDefToBool(ENTITY::DOES_ENTITY_EXIST(GetHandle()));
}

eEntityType CEntity::GetEntityType()
{
	return (eEntityType) ENTITY::GET_ENTITY_TYPE(GetHandle());
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
