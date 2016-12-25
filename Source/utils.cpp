#include "stdafx.h"

BOOL BoolToBoolDef(bool b)
{
	return (b) ? TRUE : FALSE;
}

bool BoolDefToBool(BOOL b) 
{
	return b == 1;
}