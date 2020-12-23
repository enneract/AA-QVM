#include "g_local.h"

#define RAZORCHRIST_RADIUS 32
#define RAZORCHRIST_HEIGHT 80
#define RAZORCHRIST_RANGE 40
#define RAZORCHRIST_SPAWN_DIST 500
#define MAX_RAZORCHRISTS 40


static const vec3_t rcMins = {-RAZORCHRIST_RADIUS, -RAZORCHRIST_RADIUS, 0.0f};
static const vec3_t rcMaxs = {RAZORCHRIST_RADIUS, RAZORCHRIST_RADIUS, RAZORCHRIST_HEIGHT};

void G_RunRazorchrist(gentity_t *ent, int msec)
{
	vec3_t mins, maxs;
	int nearby[MAX_GENTITIES];
	int i, nearbyCount;

	G_Physics(ent, msec);
	VectorCopy(ent->s.origin, ent->r.currentOrigin);

	mins[0] = ent->s.origin[0] - RAZORCHRIST_RANGE;
	mins[1] = ent->s.origin[1] - RAZORCHRIST_RANGE;
	mins[2] = ent->s.origin[2] + RAZORCHRIST_HEIGHT / 2.0f - RAZORCHRIST_RANGE;

	maxs[0] = ent->s.origin[0] + RAZORCHRIST_RANGE;
	maxs[1] = ent->s.origin[1] + RAZORCHRIST_RANGE;
	maxs[2] = ent->s.origin[2] + RAZORCHRIST_HEIGHT / 2.0f + RAZORCHRIST_RANGE;

	nearbyCount = trap_EntitiesInBox(mins, maxs, nearby, MAX_GENTITIES);
	for (i = 0; i < nearbyCount; i++) {
		gentity_t *other = g_entities + nearby[i];

		if (other->s.eType != ET_PLAYER
		    && other->s.eType != ET_BUILDABLE)
			continue;

		G_Damage(other, ent, ent, NULL, NULL, 30, 0, MOD_RAZORCHRIST);

		// Trigger the Razorchrist
		ent->razorchristActive = 10000;
		ent->s.pos.trDelta[0] = crandom() * 1000.0f;
		ent->s.pos.trDelta[1] = crandom() * 1000.0f;
		ent->s.pos.trDelta[2] = crandom() * 1000.0f;
	}

	ent->razorchristActive -= 100;
	if (ent->razorchristActive <= 0) {
		ent->razorchristActive = 0;
		ent->s.generic1 = 0;
		//VectorScale(ent->s.pos.trDelta, 0.5f, ent->s.pos.trDelta);
	} else
		ent->s.generic1 = 1;
}

#define MAX_RAZORCHRIST_RING 40
static vec3_t razorchristRing[MAX_RAZORCHRIST_RING] = {0};
static int razorchristRingSize = 0;

static qboolean G_CheckRazorchrist(vec3_t origin, int ignore)
{
	int i, numNearby, nearby[MAX_GENTITIES];
	vec3_t mins, maxs;

	mins[0] = origin[0] - RAZORCHRIST_SPAWN_DIST;
	mins[1] = origin[1] - RAZORCHRIST_SPAWN_DIST;
	mins[2] = origin[2] - RAZORCHRIST_SPAWN_DIST;

	maxs[0] = origin[0] + RAZORCHRIST_SPAWN_DIST;
	maxs[1] = origin[1] + RAZORCHRIST_SPAWN_DIST;
	maxs[2] = origin[2] + RAZORCHRIST_SPAWN_DIST;

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

		if (other->s.eType == ET_RAZORCHRIST)
			return qfalse;
	}

	return qtrue;
}

void G_AddRazorchristCandidate(gentity_t *src, vec3_t origin)
{
	trace_t tr;
	const vec3_t down = {0, 0, -1000.0f};
	vec3_t end;

	if (crandom() < 0.9f)
		return;

	if (!G_CheckRazorchrist(origin, src - g_entities))
		return;

	VectorAdd(origin, down, end);
	trap_Trace(&tr, origin, rcMins, rcMaxs, end, -1, CONTENTS_SOLID);

	if (tr.startsolid)
		return;

	if (tr.entityNum != ENTITYNUM_WORLD)
		return;

	VectorCopy(tr.endpos, razorchristRing[razorchristRingSize % MAX_RAZORCHRIST_RING]);
	razorchristRingSize++;
}

gentity_t *G_SpawnRazorchrist(vec3_t origin)
{
	gentity_t *ent;

	ent = G_Spawn();
	ent->s.eType = ET_RAZORCHRIST;
	G_SetOrigin(ent, origin);

	ent->s.pos.trType = BG_FindTrajectoryForBuildable(BA_H_MGTURRET);
	ent->s.pos.trTime = level.time;
	ent->physicsBounce = 0.9f;
	ent->clipmask = MASK_PLAYERSOLID;

	VectorCopy(rcMins, ent->r.mins);
	VectorCopy(rcMaxs, ent->r.maxs);
	ent->r.contents = MASK_SOLID;

	trap_LinkEntity(ent);
	return ent;
}

void G_CheckSpawnRazorchrists(void)
{
	int pick;
	vec3_t origin;
	static int numRazorchrists = 0;

	if (numRazorchrists >= MAX_RAZORCHRISTS)
		return;

	if (!razorchristRingSize)
		return;

	if (crandom() < 0.95f)
		return;

	if (razorchristRingSize < MAX_RAZORCHRIST_RING)
		pick = rand() % razorchristRingSize;
	else
		pick = rand() % MAX_RAZORCHRIST_RING;

	VectorCopy(razorchristRing[pick], origin);

	if (!G_CheckRazorchrist(origin, -1))
		return;

	G_SpawnRazorchrist(origin);
	numRazorchrists++;
}
