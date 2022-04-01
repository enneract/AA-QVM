#include "g_local.h"

#define PUTIN_RADIUS 32
#define PUTIN_HEIGHT 80
#define PUTIN_RANGE 40
#define PUTIN_SPAWN_DIST 100.0f // 1000
#define MAX_PUTINS 20
#define PUTIN_PROBABILITY 1.0f // 0.05f

static const vec3_t rcMins = {-PUTIN_RADIUS, -PUTIN_RADIUS, 0.0f};
static const vec3_t rcMaxs = {PUTIN_RADIUS, PUTIN_RADIUS, PUTIN_HEIGHT};

void G_RunPutin(gentity_t *ent, int msec)
{
	vec3_t mins, maxs;
	int nearby[MAX_GENTITIES];
	int i, nearbyCount;

	G_Physics(ent, msec);
	VectorCopy(ent->r.currentOrigin, ent->s.origin);

	mins[0] = ent->s.origin[0] - PUTIN_RANGE;
	mins[1] = ent->s.origin[1] - PUTIN_RANGE;
	mins[2] = ent->s.origin[2] + PUTIN_HEIGHT / 2.0f - PUTIN_RANGE;

	maxs[0] = ent->s.origin[0] + PUTIN_RANGE;
	maxs[1] = ent->s.origin[1] + PUTIN_RANGE;
	maxs[2] = ent->s.origin[2] + PUTIN_HEIGHT / 2.0f + PUTIN_RANGE;

	nearbyCount = trap_EntitiesInBox(mins, maxs, nearby, MAX_GENTITIES);
	for (i = 0; i < nearbyCount; i++) {
		gentity_t *other = g_entities + nearby[i];

		if (other->s.eType == ET_PLAYER) {
            // pass
		} else if (other->s.eType == ET_BUILDABLE) {
			if (other->health <= 0)
				continue;
		} else
			continue;

		// Trigger the Putin
		ent->putinActive = 5000;
		ent->s.pos.trType = TR_GRAVITY;
		ent->s.pos.trDelta[0] = crandom() * 4000;
		ent->s.pos.trDelta[1] = crandom() * 4000;
		ent->s.pos.trDelta[2] = 4000 + crandom() * 4000;
		ent->s.pos.trTime = level.time;
		ent->s.groundEntityNum = ENTITYNUM_WORLD;
	}

	ent->putinActive -= msec;
	if (ent->putinActive <= 0) {
		ent->putinActive = 0;
		ent->s.generic1 = 0;
	} else
		ent->s.generic1 = 1;
}

#define MAX_PUTIN_RING 40
static vec3_t putinRing[MAX_PUTIN_RING] = {0};
static int putinRingSize = 0;

static qboolean G_CheckPutin(vec3_t origin, int ignore)
{
	int i, numNearby, nearby[MAX_GENTITIES];
	vec3_t mins, maxs;

	mins[0] = origin[0] - PUTIN_SPAWN_DIST;
	mins[1] = origin[1] - PUTIN_SPAWN_DIST;
	mins[2] = origin[2] - PUTIN_SPAWN_DIST;

	maxs[0] = origin[0] + PUTIN_SPAWN_DIST;
	maxs[1] = origin[1] + PUTIN_SPAWN_DIST;
	maxs[2] = origin[2] + PUTIN_SPAWN_DIST;

	numNearby = trap_EntitiesInBox(mins, maxs, nearby, MAX_GENTITIES);

	for (i = 0; i < numNearby; i++)
	{
		gentity_t *other = g_entities + nearby[i];

		if (nearby[i] == ignore)
			continue;

		if (other->s.eType == ET_PLAYER)
			return qfalse;

		if (other->s.eType == ET_BUILDABLE)
			return qfalse;

		if (other->s.eType == ET_PUTIN)
			return qfalse;
	}

	return qtrue;
}

void G_AddPutinCandidate(gentity_t *src, vec3_t origin)
{
	trace_t tr;
	const vec3_t down = {0, 0, -1000.0f};
	vec3_t end;

	if (crandom() < 0.9f)
		return;

	if (!G_CheckPutin(origin, src - g_entities))
		return;

	VectorAdd(origin, down, end);
	trap_Trace(&tr, origin, rcMins, rcMaxs, end, -1, CONTENTS_SOLID);

	if (tr.startsolid)
		return;

	if (tr.entityNum != ENTITYNUM_WORLD)
		return;

	VectorCopy(tr.endpos, putinRing[putinRingSize % MAX_PUTIN_RING]);
	putinRingSize++;
}

gentity_t *G_SpawnPutin(vec3_t origin)
{
	gentity_t *ent;

	ent = G_Spawn();
	ent->s.eType = ET_PUTIN;
	G_SetOrigin(ent, origin);

	ent->s.pos.trType = TR_GRAVITY;
	ent->s.pos.trTime = level.time;
	ent->physicsBounce = 0.95f;
	ent->clipmask = MASK_PLAYERSOLID;

	VectorCopy(rcMins, ent->r.mins);
	VectorCopy(rcMaxs, ent->r.maxs);
	ent->r.contents = MASK_SOLID;

	trap_LinkEntity(ent);
	return ent;
}

void G_CheckSpawnPutins(void)
{
	int pick;
	vec3_t origin;
	static int numPutins = 0;

	if (numPutins >= MAX_PUTINS)
		return;

	if (!putinRingSize)
		return;

	if (crandom() > PUTIN_PROBABILITY)
		return;

	if (putinRingSize < MAX_PUTIN_RING)
		pick = rand() % putinRingSize;
	else
		pick = rand() % MAX_PUTIN_RING;

	VectorCopy(putinRing[pick], origin);

	if (!G_CheckPutin(origin, -1))
		return;

	G_SpawnPutin(origin);
	numPutins++;
}
