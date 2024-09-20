#include "Lunacy/Reallocators/Consts.h"

VOID Constants::UNLOCK(CONST VOID* ADDR, size_t S)
{
	DWORD OLD;
	VirtualProtect((LPVOID)ADDR, S, PAGE_EXECUTE_READWRITE, &OLD);
}

VOID Constants::UNLOCK(VOID* ADDR, size_t S)
{
	DWORD OLD;
	VirtualProtect((LPVOID)ADDR, S, PAGE_EXECUTE_READWRITE, &OLD);
}

VOID Constants::UNLOCK(DWORD ADDR, size_t S)
{
	DWORD OLD;
	VirtualProtect((LPVOID)ADDR, S, PAGE_EXECUTE_READWRITE, &OLD);
}

VOID Constants::UNLOCK()
{
	UNLOCK(MAX_LEVEL_ADDR, 1);
	UNLOCK(PlantDef::PLANT_DEFINITIONS, PlantDef::PLANT_DEF_SIZE);
	UNLOCK(ProjDef::PROJ_DEFINITIONS, ProjDef::PROJ_DEF_SIZE);

	*MAX_LEVEL_ADDR = MAX_LEVELS;
}

PlantDefinition* Constants::PlantDef::NEW_DEFS = NULL;
VOID* Constants::PlantDef::REALLOCATE(DWORD NEW_COUNT)
{
	NEW_DEFS = (PlantDefinition*)operator new(sizeof(PlantDefinition) * NEW_COUNT);
	memset(NEW_DEFS, 0, sizeof(PlantDefinition) * NEW_COUNT);
	memcpy(NEW_DEFS, (VOID*)PLANT_DEFINITIONS, PLANT_DEF_SIZE);
	DWORD NewDefAddress = (DWORD)NEW_DEFS;

	for (int i = 0; i < REFCOUNT; i++)
	{
		DWORD* RefP = (DWORD*)REFS[i];
		DWORD Ref;

		UNLOCK(RefP);
		Ref = *RefP;

		DWORD Offset = Ref - PLANT_DEFINITIONS;
		Ref = NewDefAddress + Offset;
		*RefP = Ref;
	}

	return NEW_DEFS;
}

ProjectileDefinition* Constants::ProjDef::NEW_DEFS = NULL;
VOID* Constants::ProjDef::REALLOCATE(DWORD NEW_COUNT)
{
	NEW_DEFS = (ProjectileDefinition*)operator new(sizeof(ProjectileDefinition) * NEW_COUNT);
	memset(NEW_DEFS, 0, sizeof(ProjectileDefinition) * NEW_COUNT);
	memcpy(NEW_DEFS, (VOID*)PROJ_DEFINITIONS, PROJ_DEF_SIZE);
	DWORD NewDefAddress = (DWORD)NEW_DEFS;

	for (int i = 0; i < REFCOUNT; i++)
	{
		DWORD* RefP = (DWORD*)REFS[i];
		DWORD Ref;

		UNLOCK(RefP);
		Ref = *RefP;

		DWORD Offset = Ref - PROJ_DEFINITIONS;
		Ref = NewDefAddress + Offset;
		*RefP = Ref;
	}

	return NEW_DEFS;
}

ZombieDefinition* Constants::ZombieDef::NEW_DEFS = NULL;
VOID* Constants::ZombieDef::REALLOCATE(DWORD NEW_COUNT)
{
	NEW_DEFS = (ZombieDefinition*)operator new(sizeof(ZombieDefinition) * NEW_COUNT);
	memset(NEW_DEFS, 0, sizeof(ZombieDefinition) * NEW_COUNT);
	memcpy(NEW_DEFS, (VOID*)ZOMBIE_DEFINITIONS, ZOMBIE_DEF_SIZE);
	DWORD NewDefAddress = (DWORD)NEW_DEFS;

	for (int i = 0; i < REFCOUNT; i++)
	{
		DWORD* RefP = (DWORD*)REFS[i];
		DWORD Ref;

		UNLOCK(RefP);
		Ref = *RefP;

		DWORD Offset = Ref - ZOMBIE_DEFINITIONS;
		Ref = NewDefAddress + Offset;
		*RefP = Ref;
	}

	return NEW_DEFS;
}

ReanimationParams* Constants::ReanimDef::NEW_PARAMS = NULL;
VOID* Constants::ReanimDef::REALLOCATE(DWORD NEW_COUNT)
{
	UNLOCK(G_OG_REANIM_PARAM, G_OG_REANIM_PARAM_SIZE);

	NEW_PARAMS = (ReanimationParams*)operator new(sizeof(ReanimationParams) * NEW_COUNT);
	memcpy(NEW_PARAMS, (CONST VOID*)G_OG_REANIM_PARAM, G_OG_REANIM_PARAM_SIZE);


	for (int i = 0; i < PARAMREFCOUNT; i++)
	{
		DWORD* RefP = (DWORD*)PARAM_REFS[i];
		DWORD Ref;

		UNLOCK(RefP);
		Ref = *RefP;

		DWORD Offset = Ref - G_OG_REANIM_PARAM;
		Ref = (DWORD)NEW_PARAMS + Offset;
		*RefP = Ref;
	}

	for (int i = 0; i < REANIMCREFCOUNT; i++)
	{
		DWORD* RefP = (DWORD*)REANIM_COUNT_REFS[i];
		UNLOCK(RefP);
		DWORD Offset = OG_REANIM_COUNT - *RefP;
		*RefP = NEW_COUNT + Offset;
	}

	return DEFINITIONS;
}