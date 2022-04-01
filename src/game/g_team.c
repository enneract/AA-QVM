/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.
Copyright (C) 2000-2006 Tim Angus

This file is part of Tremulous.

Tremulous is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Tremulous is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Tremulous; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/

#include "g_local.h"

// NULL for everyone
void QDECL PrintMsg(gentity_t * ent, const char *fmt, ...)
{
	char msg[1024];
	va_list argptr;
	char *p;

	va_start(argptr, fmt);

	if (vsprintf(msg, fmt, argptr) > sizeof(msg))
		G_Error("PrintMsg overrun");

	va_end(argptr);

	// double quotes are bad
	while ((p = strchr(msg, '"')) != NULL)
		*p = '\'';

	trap_SendServerCommand(((ent == NULL) ? -1 : ent - g_entities),
			       va("print \"%s\"", msg));
}

/*
==============
OnSameTeam
==============
*/
qboolean OnSameTeam(gentity_t * ent1, gentity_t * ent2)
{
	if (!ent1->client || !ent2->client)
		return qfalse;

	if (ent1->client->pers.teamSelection ==
	    ent2->client->pers.teamSelection)
		return qtrue;

	return qfalse;
}

/*
===========
Team_GetLocation

Report a location for the player. Uses placed nearby target_location entities
============
*/
gentity_t *Team_GetLocation(gentity_t * ent)
{
	gentity_t *eloc, *best;
	float bestlen, len;
	vec3_t origin;

	best = NULL;
	bestlen = 3.0f * 8192.0f * 8192.0f;

	VectorCopy(ent->r.currentOrigin, origin);

	for (eloc = level.locationHead; eloc; eloc = eloc->nextTrain) {
		len =
		    (origin[0] - eloc->r.currentOrigin[0]) * (origin[0] -
							      eloc->r.
							      currentOrigin[0])
		    + (origin[1] - eloc->r.currentOrigin[1]) * (origin[1] -
								eloc->r.
								currentOrigin
								[1])
		    + (origin[2] - eloc->r.currentOrigin[2]) * (origin[2] -
								eloc->r.
								currentOrigin
								[2]);

		if (len > bestlen)
			continue;

		if (!trap_InPVS(origin, eloc->r.currentOrigin))
			continue;

		bestlen = len;
		best = eloc;
	}

	return best;
}

/*
===========
Team_GetLocationMsg

Report a location message for the player. Uses placed nearby target_location entities
============
*/
qboolean Team_GetLocationMsg(gentity_t * ent, char *loc, int loclen)
{
	gentity_t *best;

	if (ent->client->pers.teamSelection == PTE_NONE)
		return qfalse; // no need for locations for spectators

	best = Team_GetLocation(ent);

	if (!best)
		return qfalse;

	if (best->count) {
		if (best->count < 0)
			best->count = 0;

		if (best->count > 7)
			best->count = 7;

		Com_sprintf(loc, loclen, "%c%c%s" S_COLOR_WHITE, Q_COLOR_ESCAPE,
			    best->count + '0', best->message);
	} else
		Com_sprintf(loc, loclen, "%s", best->message);

	return qtrue;
}

/*---------------------------------------------------------------------------*/

static int QDECL SortClients(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

/*
==================
TeamplayLocationsMessage

Format:
  clientNum location health armor weapon powerups

==================
*/
void TeamplayInfoMessage(gentity_t * ent)
{
	char entry[1024];
	char string[8192];
	int stringlength;
	int i, j;
	gentity_t *player;
	int cnt;
	int h, a = 0;
	int clients[TEAM_MAXOVERLAY];

	if (!ent->client->pers.teamInfo)
		return;

	// figure out what client should be on the display
	// we are limited to 8, but we want to use the top eight players
	// but in client order (so they don't keep changing position on the overlay)
	for (i = 0, cnt = 0; i < g_maxclients.integer && cnt < TEAM_MAXOVERLAY;
	     i++) {
		player = g_entities + level.sortedClients[i];

		if (player->inuse && player->client->sess.sessionTeam ==
		    ent->client->sess.sessionTeam)
			clients[cnt++] = level.sortedClients[i];
	}

	// We have the top eight players, sort them by clientNum
	qsort(clients, cnt, sizeof(clients[0]), SortClients);

	// send the latest information on all clients
	string[0] = 0;
	stringlength = 0;

	for (i = 0, cnt = 0; i < g_maxclients.integer && cnt < TEAM_MAXOVERLAY;
	     i++) {
		player = g_entities + i;

		if (player->inuse && player->client->sess.sessionTeam ==
		    ent->client->sess.sessionTeam) {
			h = player->client->ps.stats[STAT_HEALTH];

			if (h < 0)
				h = 0;

			Com_sprintf(entry, sizeof(entry), " %i %i %i %i %i %i",
//        level.sortedClients[i], player->client->pers.teamState.location, h, a,
				    i, player->client->pers.teamState.location,
				    h, a, player->client->ps.weapon,
				    player->s.misc);

			j = strlen(entry);

			if (stringlength + j > sizeof(string))
				break;

			strcpy(string + stringlength, entry);
			stringlength += j;
			cnt++;
		}
	}

	trap_SendServerCommand(ent - g_entities,
			       va("tinfo %i %s", cnt, string));
}

void CheckTeamStatus(void)
{
	int i;
	gentity_t *loc, *ent;

	if (level.time - level.lastTeamLocationTime > TEAM_LOCATION_UPDATE_TIME) {
		level.lastTeamLocationTime = level.time;

		for (i = 0; i < g_maxclients.integer; i++) {
			ent = g_entities + i;
			if (ent->client->pers.connected != CON_CONNECTED)
				continue;

			if (ent->inuse
			    && (ent->client->ps.stats[STAT_PTEAM] == PTE_HUMANS
				|| ent->client->ps.stats[STAT_PTEAM] ==
				PTE_ALIENS)) {

				loc = Team_GetLocation(ent);

				if (loc)
					ent->client->pers.teamState.location =
					    loc->health;
				else
					ent->client->pers.teamState.location =
					    0;
			}
		}

		for (i = 0; i < g_maxclients.integer; i++) {
			ent = g_entities + i;
			if (ent->client->pers.connected != CON_CONNECTED)
				continue;

			if (ent->inuse
			    && (ent->client->ps.stats[STAT_PTEAM] == PTE_HUMANS
				|| ent->client->ps.stats[STAT_PTEAM] ==
				PTE_ALIENS))
				TeamplayInfoMessage(ent);
		}
	}
	//Warn on unbalanced teams
	if (g_teamImbalanceWarnings.integer && !level.intermissiontime
	    && level.time - level.lastTeamUnbalancedTime >
	    (g_teamImbalanceWarnings.integer * 1000)
	    && level.numTeamWarnings < 3) {
		level.lastTeamUnbalancedTime = level.time;
		if (level.numAlienSpawns > 0
		    && level.numHumanClients - level.numAlienClients > 2) {
			trap_SendServerCommand(-1,
					       "print \"Teams are unbalanced. Humans have more players.\n Humans will keep their points when switching teams.\n\"");
			level.numTeamWarnings++;
		} else if (level.numHumanSpawns > 0
			   && level.numAlienClients - level.numHumanClients >
			   2) {
			trap_SendServerCommand(-1,
					       "print \"Teams are unbalanced. Aliens have more players.\n Aliens will keep their points when switching teams.\n\"");
			level.numTeamWarnings++;
		} else {
			level.numTeamWarnings = 0;
		}
	}
}

/*
==================
G_LeaveTeam
==================
*/
void G_LeaveTeam(gentity_t * self)
{
	pTeam_t team = self->client->pers.teamSelection;
	gentity_t *ent;
	int i, clientNum, cs_offset;

	clientNum = self->client->ps.clientNum;

	if (team == PTE_ALIENS)
		G_RemoveFromSpawnQueue(&level.alienSpawnQueue,
				       self->client->ps.clientNum);
	else if (team == PTE_HUMANS)
		G_RemoveFromSpawnQueue(&level.humanSpawnQueue,
				       self->client->ps.clientNum);
	else {
		if (self->client->sess.spectatorState == SPECTATOR_FOLLOW) {
			G_StopFollowing(self);
		}
		return;
	}

	// Cancel pending suicides
	self->suicideTime = 0;

	// stop any following clients
	G_StopFromFollowing(self);

	for (i = 0; i < level.num_entities; i++) {
		ent = &g_entities[i];
		if (!ent->inuse)
			continue;

		// clean up projectiles
		if (ent->s.eType == ET_MISSILE
		    && ent->r.ownerNum == self->s.number)
			G_FreeEntity(ent);
		if (ent->client && ent->client->pers.connected == CON_CONNECTED) {
			// cure poison
			if (ent->client->ps.stats[STAT_STATE] & SS_POISONCLOUDED
			    && ent->client->lastPoisonCloudedClient == self)
				ent->client->ps.stats[STAT_STATE] &=
				    ~SS_POISONCLOUDED;
			if (ent->client->ps.stats[STAT_STATE] & SS_POISONED
			    && ent->client->lastPoisonClient == self)
				ent->client->ps.stats[STAT_STATE] &=
				    ~SS_POISONED;
			if (ent->client->grangerCurse && ent->client->grangerCursedBy == self)
				ent->client->grangerCurse = qfalse;
		}
	}

	cs_offset = (team == PTE_ALIENS ? 1 : 0);

	if (level.teamVoteTime[cs_offset] && level.teamVotedHow[cs_offset][clientNum]) {

		if (level.teamVotedHow[cs_offset][clientNum] > 0) {
			level.teamVoteYes[cs_offset]--;
			trap_SetConfigstring(CS_TEAMVOTE_YES + cs_offset,
					     va("%i", level.teamVoteYes[cs_offset]));
		} else {
			level.teamVoteNo[cs_offset]--;
			trap_SetConfigstring(CS_TEAMVOTE_NO + cs_offset,
					     va("%i", level.teamVoteNo[cs_offset]));
		}

		level.teamVotedHow[cs_offset][clientNum] = 0;
	}
}

/*
=================
G_ChangeTeam
=================
*/
void G_ChangeTeam(gentity_t * ent, pTeam_t newTeam, qboolean keepScores)
{
	pTeam_t oldTeam = ent->client->pers.teamSelection;
	qboolean isFixingImbalance = qfalse;

	if (oldTeam == newTeam)
		return;

	G_LeaveTeam(ent);
	ent->client->pers.teamSelection = newTeam;

	ent->client->pers.lastFreekillTime = level.time;

	// G_LeaveTeam() calls G_StopFollowing() which sets spec mode to free. 
	// Undo that in this case, or else people can freespec while in the spawn queue on their new team
	if (newTeam != PTE_NONE) {
		ent->client->sess.spectatorState = SPECTATOR_LOCKED;
	}

	if ((level.numAlienClients - level.numHumanClients > 2
	     && oldTeam == PTE_ALIENS && newTeam == PTE_HUMANS
	     && level.numHumanSpawns > 0)
	    || (level.numHumanClients - level.numAlienClients > 2
		&& oldTeam == PTE_HUMANS && newTeam == PTE_ALIENS
		&& level.numAlienSpawns > 0)) {
		isFixingImbalance = qtrue;
	}
	// under certain circumstances, clients can keep their kills and credits
	// when switching teams
	if (!keepScores && !G_admin_permission(ent, ADMF_TEAMCHANGEFREE) &&
	    !(g_teamImbalanceWarnings.integer && isFixingImbalance) &&
	    !((oldTeam == PTE_HUMANS || oldTeam == PTE_ALIENS)
	      && (level.time - ent->client->pers.teamChangeTime) > 60000)) {
		ent->client->pers.credit = 0;
		ent->client->pers.score = 0;
	}

	ent->client->ps.persistant[PERS_KILLED] = 0;
	memset(&ent->client->pers.statscounters, 0, sizeof(statsCounters_t));

	if (G_admin_permission(ent, ADMF_DBUILDER)) {
		if (!ent->client->pers.designatedBuilder) {
			ent->client->pers.designatedBuilder = qtrue;
			trap_SendServerCommand(ent - g_entities,
					       "print \"Your designation has been restored\n\"");
		}
	} else if (ent->client->pers.designatedBuilder) {
		ent->client->pers.designatedBuilder = qfalse;
		trap_SendServerCommand(ent - g_entities,
				       "print \"You have lost designation due to teamchange\n\"");
	}

	ent->client->pers.classSelection = PCL_NONE;
	ClientSpawn(ent, NULL, NULL, NULL);

	ent->client->pers.joinedATeam = qtrue;
	ent->client->pers.teamChangeTime = level.time;

	//update ClientInfo
	ClientUserinfoChanged(ent->client->ps.clientNum, qfalse);
	G_CheckDBProtection();
}

/*
=================
G_ShuffleTeams
=================
*/
void G_ShuffleTeams(void)
{
	gentity_t *players[MAX_CLIENTS];
	int i, numPlayers = 0, toShuffle;
	pTeam_t team;

	// Compile a list of players (non-spectators).
	for (i = 0; i < MAX_CLIENTS; i++) {
		gentity_t *ent = g_entities + i;

		if (!ent->client)
			continue;

		if (ent->client->pers.teamSelection == PTE_NONE)
			continue;

		players[numPlayers++] = ent;
	}

	// Shuffle the array to randomize the remaining code.
	toShuffle = numPlayers;

	// Fisher-Yates shuffle
	while (toShuffle) {
		int i;
		gentity_t *temp;

		i = rand() % toShuffle--;

		temp = players[toShuffle];
		players[toShuffle] = players[i];
		players[i] = temp;
	}

	// Pick the starting team at random.
	team = (rand() & 256) ? PTE_HUMANS : PTE_ALIENS;

	for (i = 0; i < numPlayers; i++) {
		G_LogPrintf("ShuffleTeams: %d %s", players[i] - g_entities,
			    team == PTE_ALIENS ? "aliens" : "humans");
		G_ChangeTeam(players[i], team, qtrue);

		if (team == PTE_ALIENS)
			team = PTE_HUMANS;
		else
			team = PTE_ALIENS;
	}
}
