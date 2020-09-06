/*
===========================================================================
Copyright (C) 2004-2006 Tony J. White

This file is part of Tremulous.

This shrubbot implementation is the original work of Tony J. White.

Contains contributions from Wesley van Beelen, Chris Bajumpaa, Josh Menke,
and Travis Maurer.

The functionality of this code mimics the behaviour of the currently
inactive project shrubet (http://www.etstats.com/shrubet/index.php?ver=2)
by Ryan Mannion.   However, shrubet was a closed-source project and 
none of it's code has been copied, only it's functionality.

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

// big ugly global buffer for use with buffered printing of long outputs
static char g_bfb[ 32000 ];

// note: list ordered alphabetically
g_admin_schachts_t g_admin_schachts[ ] =
  {
    {"adjustban", "%s^7, bans are issued as-is with with no warranty or accidental damage cover.", NULL},
    {"adminlog", "sorry, %s^7, but only the NSA have access to this feature.", NULL},
    {"admintest", "you have no power here, %s^7.", NULL},
    {"allready", "%s^7 must gather their party before venturing forth from this place.", NULL},
    {"buildlog", "perhaps %s^7 is looking for a compiler, have they tried clang?", NULL},
    {"ban", "wir fahren, fahren, fahren, auf die Autoban - %s^7.", NULL},
    {"cp", "I didn't you were into ^1that, ^7%s^7. I'm calling the cops.", NULL},
    {"devmap", "%s^7 should be using ^3!setdevmode^7 in the middle of a pub, just like a true Zittriger would.", NULL},
    {"cancelvote", "this is a democracy, and %s^7 cannot change that.", NULL},
    {"decon", "sorry, %s^7! no refunds, no returns!", NULL},
    {"demo", "did you mean OBS, %s^7?", NULL},
    {"designate", "the team shall decide the designation, not you, %s^7.", NULL},
    {"denybuild", "denywhat? sorry %s^7, never heard of that here.", NULL},
    {"denyweapon", "%s^7 should be using callvote!", NULL},
    {"drop", "%s^7 is trying to hide something by not using ^3!kick^7.", NULL},
    {"flag", "%s^7 wants to put up the white flag and surrender.", NULL},
    {"flaglist", "sorry, %s^7, i can't even shitpost country flags because this game doesn't support emoticons :(", NULL},
    {"help", "no one can help you now, %s^7.", NULL},
    {"invisible", "how about /disconnect, eh %s^7?", NULL},
    {"kick", "ever tried using ^3!drop^7, %s^7?", NULL},
    {"l0", "the Overmind needs spawns, %s^7, do you have some?", NULL},
    {"l1", "the Overmind needs spawns, %s^7, do you have some?", NULL},
    {"layoutsave", "it's 2007 again and %s^7 forgot to use microsoft visio", NULL},
    {"listadmins", "uh, there's a bunch of people on the list, but %s^7 isn't one of them.", NULL},
    {"listlayouts", "*DEFAULT*, *DEFAULT*, *DEFAULT*, ...", NULL},
    {"listplayers", "some NPCs, campers, stackers, a few overseers, and you, %s^7.", NULL},
    {"listmaps", "might as well contain atcs, utcs, nano and niveus, which are %s^7's favourite maps, right?", NULL},
    {"lock", "can't lock the team as %s^7 lost the keys.", NULL},
    {"map", "go open an Atlas, %s^7.", NULL},
    {"maplog", "atcs, atcs, atcs, atcs, atcs, atcs, atcs....", NULL},
    {"mute", "this is a democracy, where people like %s^7 should be using /callvote", NULL},
    {"namelog", "sorry, %s^7, but only the NSA have access to this feature.", NULL},
    {"nextmap", "%s^7 must gather their party before venturing forth from this place.", NULL},
    {"nobuild", "it's not like %s^7 would know how to use it anyway.", NULL},
    {"passvote", "this is a democracy, and %s^7 cannot change that.", NULL},
    {"pause", "there's no stopping now, %s^7.", NULL},
    {"putteam", "%s^7 attempted to force the hand of the People.", NULL},
    {"readconfig", "shitpost mode already active.", NULL},
    {"register", "we already know who you are, %s^7.", NULL},
    {"rename", "sorry, %s^7, but only the NSA have access to this feature.", NULL},
    {"restart", "sorry, %s^7! no refunds, no returns!", NULL},
    {"revert", "sorry, %s^7! no refunds, no returns!", NULL},
    {"rotation", "%s^7, is a circular movement of an object around a center (or point) of rotation. (from Wikipedia, the free encyclopedia)", NULL},
    {"seen", "seen who, %s^7? ( o).( o)", NULL},
    {"setlevel", "the Overmind needs spawns, %s^7, do you have some?", NULL},
    {"showbans", "%s^7, bans are issued as-is with with no warranty or accidental damage cover (and you cannot view the Policy right now).", NULL},
    {"slap", "%s^7 is trying to get kinky!", NULL},
    {"spec999", "999ing is still a thing in 2020? %s^7 should up their game...", NULL},
    {"specme", "%s^7 is a confirmed ragequitter.", NULL},
    {"subnetban", "%s^7, bans are issued as-is with with no warranty or accidental damage cover.", NULL},
    {"suspendban", "%s^7, bans are issued as-is with with no warranty or accidental damage cover.", NULL},
    {"time", "time %s^7 got a watch.", NULL},
    {"unban", "%s^7, bans are issued as-is with with no warranty or accidental damage cover.", NULL},
    {"unlock", "can't unlock the team as %s^7 lost the keys.", NULL},
    {"undesignate", "the team shall decide the designation, not you, %s^7.", NULL},
    {"unflag", "%s^7 wants to put up the white flag and surrender.", NULL},
    {"unmute", "this is a democracy, where people like %s^7 should be using /callvote", NULL},
    {"unpause", "there's no stopping now, %s^7.", NULL},
    {"warn", "it's not like they would have taken any notice of %s^7's warning anyway.", NULL},

    {"setdevmode", "%s^7 should be using ^3!devmap^7 to start a new game with cheats on!", NULL},
    {"hstage", "the Game cannot be changed, %s^7.", NULL},
    {"astage", "the Game cannot be changed, %s^7.", NULL},
    {"bubble", "try /disconnect to see bubbles, %s^7.", NULL},
    {"scrim", "this is a pub, %s^7.", NULL},
    {"give", "in accordance with the Zittrig Code of Conduct, %s^7 is not permitted to ^3!give^7 credits or evos.", NULL},
    {"setrotation", "the laws of physics set the rotation, not mere mortals like you, %s^7.", NULL},
    {"print", "^ilp0 is on fire.", NULL},
    {"drug", "%s^7 should try using Basilisk gas instead.", NULL},
    {"god", "too late, %s^7 killed them.", NULL},
    {"range", "don't know what you're on about, %s^7.", NULL},
    {"practise", "get gud, %s^7.", NULL},
    {"switch", "%s^7, ^3!switch^7 functionality not invented yet.", NULL},
    {"spawn", "%s^7, ^7reproduce.", NULL},
    {"shuffle", "%s^7: ^2As I lay there listening to the strange night sounds, I hear the shuffle of someone creeping by outside in the grass.", NULL},
  };

g_admin_cmd_t g_admin_cmds[ ] = 
  {
    {"adjustban", G_admin_adjustban, "ban",
      "change the duration or reason of a ban.  time is specified as numbers "
      "followed by units 'w' (weeks), 'd' (days), 'h' (hours) or 'm' (minutes),"
      " or seconds if no units are specified. if the duration is"
      " preceded by a + or -, the ban duration will be extended or shortened by"
      " the specified amount",
      "[^3ban#^7] (^5duration^7) (^5reason^7)"
    },
    
    {"adminlog", G_admin_adminlog, "adminlog",
      "list recent admin activity",
      "(^5start id#|name|!command|-skip#^7) (^5search skip#^7)"
    },

    {"admintest", G_admin_admintest, "admintest",
      "display your current admin level",
      ""
    },

    {"allowbuild", G_admin_denybuild, "denybuild",
      "restore a player's ability to build",
      "[^3name|slot#^7]"
    },

    {"allowweapon", G_admin_denyweapon, "denyweapon",
      "restore a player's ability to use a weapon or class",
      "[^3name|slot#^7] [^3class|weapon|all^7]"
    },
    
    {"allready", G_admin_allready, "allready",
      "makes everyone ready in intermission",
      ""
    },

    {"ban", G_admin_ban, "ban",
      "ban a player by IP and GUID with an optional expiration time and reason."
      "  time is specified as numbers followed by units 'w' (weeks), 'd' "
      "(days), 'h' (hours) or 'm' (minutes), or seconds if no units are "
      "specified",
      "[^3name|slot#|IP^7] (^5time^7) (^5reason^7)"
    },

    {"buildlog", G_admin_buildlog, "buildlog",
      "display a list of recent builds and deconstructs, optionally specifying"
      " a team",
      "(^5xnum^7) (^5#skip^7) (^5-name|num^7) (^5a|h^7)"
      "\n ^3Example:^7 '!buildlog #10 h' skips 10 events, then shows the previous 10 events affecting human buildables"
    },

    {"cancelvote", G_admin_cancelvote, "cancelvote",
      "cancel a vote taking place",
      ""
    },
    
    {"cp", G_admin_cp, "cp",
      "display a CP message to users, optionally specifying team(s) to send to",
      "(-AHS) [^3message^7]"
    },

    {"decon", G_admin_decon, "decon",
      "Reverts a decon previously made and ban the user for the time specified in g_deconBanTime",
      "[^3name|slot#^7]"
    },

    {"demo", G_admin_demo, "demo",
      "turn admin chat off for the caller so it does not appear in demos. "
      "this is a toggle use !demo again to turn warnings back on",
      ""
    },

    {"denybuild", G_admin_denybuild, "denybuild",
      "take away a player's ability to build",
      "[^3name|slot#^7]"
    },

    {"designate", G_admin_designate, "designate",
      "give the player designated builder privileges",
      "[^3name|slot#^7]"
    },

    {"devmap", G_admin_devmap, "devmap",
      "load a map with cheats (and optionally force layout)",
      "[^3mapname^7] (^5layout^7)"
    },

    {"denyweapon", G_admin_denyweapon, "denyweapon",
      "take away a player's ability to use a weapon or class",
      "[^3name|slot#^7] [^3class|weapon^7]"
    },

    {"drop", G_admin_drop, "drop",
      "kick a client from the server without log",
      "[^3name|slot#^7] [^3message^7]"
    },

    {"flag", G_admin_flag, "flag",
      "add an admin flag to a player, prefix flag with '-' to disallow the flag. "
      "console can use this command on admin levels by prefacing a '*' to the admin level value.",
      "[^3name|slot#|admin#|*adminlevel^7] (^5+^7|^5-^7)[^3flag^7]"
    },

    {"flaglist", G_admin_flaglist, "flag",
      "list all flags understood by this server",
      ""
    },

    {"help", G_admin_help, "help",
      "display commands available to you or help on a specific command",
      "(^5command^7)"
    },

    {"info", G_admin_info, "info",
      "display the contents of server info files",
      "(^5subject^7)"
    },
    
    {"invisible", G_admin_invisible, "invisible",
      "hides a player so they cannot be seen in playerlists",
      ""
    },
    
    {"kick", G_admin_kick, "kick",
      "kick a player with an optional reason",
      "[^3name|slot#^7] (^5reason^7)"
    },
    
    {"L0", G_admin_L0, "l0",
      "Sets a level 1 to level 0",
      "[^3name|slot#^7]"
    },
    
    {"L1", G_admin_L1, "l1",
      "Sets a level 0 to level 1",
      "[^3name|slot#^7]"
    },
    
    {"layoutsave", G_admin_layoutsave, "layoutsave",
      "save a map layout",
      "[^3mapname^7]"
    },
    
    {"listadmins", G_admin_listadmins, "listadmins",
      "display a list of all server admins and their levels",
      "(^5name|start admin#^7) (^5minimum level to display^7)"
    },
    
    {"listlayouts", G_admin_listlayouts, "listlayouts",
      "display a list of all available layouts for a map",
      "(^5mapname^7)"
    },

    {"listplayers", G_admin_listplayers, "listplayers",
      "display a list of players, their client numbers and their levels",
      ""
    },
    
    {"listmaps", G_admin_listmaps, "listmaps",
      "display a list of available maps on the server",
      "(^5map name^7)"
    },
    
    {"lock", G_admin_lock, "lock",
      "lock a team to prevent anyone from joining it",
      "[^3a|h^7]"
    },
    
    {"map", G_admin_map, "map",
      "load a map (and optionally force layout)",
      "[^3mapname^7] (^5layout^7)"
    },

    {"maplog", G_admin_maplog, "maplog",
      "show recently played maps",
      ""
    },

    {"mute", G_admin_mute, "mute",
      "mute a player",
      "[^3name|slot#^7] (Duration)"
    },
    
    {"namelog", G_admin_namelog, "namelog",
      "display a list of names used by recently connected players",
      "(^5name^7)"
    },

    {"nextmap", G_admin_nextmap, "nextmap",
      "go to the next map in the cycle",
      ""
    },

    {"nobuild", G_admin_nobuild, "nobuild",
      "set nobuild markers to prevent players from building in an area",
      "(^5area^7) (^5height^7)"
    },

    {"passvote", G_admin_passvote, "passvote",
      "pass a vote currently taking place",
      ""
    },
    
    {"pause", G_admin_pause, "pause",
      "prevent a player from interacting with the game."
      "  * will pause all players, using no argument will pause game clock",
      "(^5name|slot|*^7)"
    },


    {"putteam", G_admin_putteam, "putteam",
      "move a player to a specified team",
      "[^3name|slot#^7] [^3h|a|s^7] (^3duration^7)"
    },

    {"readconfig", G_admin_readconfig, "readconfig",
      "reloads the admin config file and refreshes permission flags",
      ""
    },
    
    {"register", G_admin_register, "register",
      "Registers your name to protect it from being used by others or updates your admin name to your current name.",
      ""
    },

    {"rename", G_admin_rename, "rename",
      "rename a player",
      "[^3name|slot#^7] [^3new name^7]"
    },

    {"restart", G_admin_restart, "restart",
      "restart the current map (optionally using named layout or keeping/switching teams)",
      "(^5layout^7) (^5keepteams|switchteams|keepteamslock|switchteamslock^7)"
    },

    {"revert", G_admin_revert, "revert",
      "revert one or more buildlog events, optionally of only one team",
      "(^5xnum^7) (^5#ID^7) (^5-name|num^7) (^5a|h^7)"
      "\n ^3Example:^7 '!revert x5 h' reverts the last 5 events affecting human buildables"
    },

    {"rotation", G_admin_listrotation, "rotation",
       "display a list of maps that are in the active map rotation",
       ""
    },

    {"seen", G_admin_seen, "seen",
      "find the last time a player was on the server",
      "[^3name|admin#^7]"
    },

    {"setlevel", G_admin_setlevel, "setlevel",
      "sets the admin level of a player",
      "[^3name|slot#|admin#^7] [^3level^7]"
    },

    {"showbans", G_admin_showbans, "showbans",
      "display a (partial) list of active bans",
      "(^5start at ban#^7) (^5name|IP|'-subnet'^7)"
    },

    {"slap", G_admin_slap, "slap",
      "Do damage to a player, and send them flying",
      "[^3name|slot^7] (damage)"
    },

    {"spec999", G_admin_spec999, "spec999",
      "move 999 pingers to the spectator team",
      ""
    },

    {"specme", G_admin_putmespec, "specme",
      "moves you to the spectators",
      ""
    },

    {"subnetban", G_admin_subnetban, "subnetban",
      "Add or change a subnet mask on a ban",
      "[^3ban#^7] [^5CIDR mask^7]"
      "\n ^3Example:^7 '!subnetban 10 16' changes ban #10 to be a ban on XXX.XXX.*.*"
      "\n ^3Example:^7 '!subnetban 10 24' changes ban #10 to be a ban on XXX.XXX.XXX.*"
      "\n ^3Example:^7 '!subnetban 10 32' changes ban #10 to be a regular (non-subnet) ban"
      "\n ^1WARNING:^7 Use of this command may make your admin.dat incompatible with other game.qvms"
    },

    {"suspendban", G_admin_suspendban, "ban",
      "suspend a ban for a length of time. time is specified as numbers "
      "followed by units 'w' (weeks), 'd' (days), 'h' (hours) or 'm' (minutes),"
      " or seconds if no units are specified",
      "[^5ban #^7] [^5length^7]"
    },

    {"time", G_admin_time, "time",
      "show the current local server time",
      ""
    },

    {"unban", G_admin_unban, "ban",
      "unbans a player specified by the slot as seen in showbans",
      "[^3ban#^7]"
    },
    
    {"undesignate", G_admin_designate, "designate",
      "revoke designated builder privileges",
      "[^3name|slot#^7]"
    },
    
    {"unflag", G_admin_flag, "flag",
      "clears an admin flag from a player. "
      "console can use this command on admin levels by prefacing a '*' to the admin level value.",
      "[^3name|slot#|admin#|*adminlevel^7] (^5+^7|^5-^7)[^3flag^7]"
    },

    {"unlock", G_admin_unlock, "lock",
      "unlock a locked team",
      "[^3a|h^7]"
    },
    
    {"unmute", G_admin_mute, "mute",
      "unmute a muted player",
      "[^3name|slot#^7]"
    },

    {"unpause", G_admin_pause, "pause",
      "allow a player to interact with the game."
      "  * will unpause all players, using no argument will unpause game clock",
      "(^5name|slot|*^7)"
    },

    {
     "warn", G_admin_warn, "warn",
      "Warn a player to cease or face admin intervention",
      "[^3name|slot#^7] [reason]"
    },

    {"setdevmode", G_admin_setdevmode, "setdevmode",
      "switch developer mode on or off",
      "[^3on|off^7]"
    },

    {"hstage", G_admin_hstage, "stage",
      "change the stage for humans",
      "[^3#^7]"
    },

    {"astage", G_admin_astage, "stage",
      "change the stage for aliens",
      "[^3#^7]"
    },

    {"bubble", G_admin_bubble, "bubble",
      "continuously spawn bubbles around a player",
      "[^3name|slot#^7]"
    },

    {"scrim", G_admin_scrim, "scrim",
       "toggles scrim mode",
       "[on|off]",
    },

    {"give", G_admin_give, "give",
      "give funds to a player",
      "[^3name|slot#^7] [^3amount^7]"
    },

    {"setrotation", G_admin_setrotation, "setrotation",
      "sets the map rotation",
      "[^3rotation^7]"
    },

    {"versions", G_admin_versions, "namelog",
     "Check what versions of Tremulous players are running.",
     ""
    },

    {"showff", G_admin_showff, "showff",
      "shows how much friendly damage a player has done this game"
      "\nno arguments will list all connected players",
      "(^3name|slot^7)"
      "\n ^3Example:^7 ^120% ^7means 1/5th of the damage dealt this game was dealt to the team"
    },

    {"tklog", G_admin_tklog, "tklog",
      "list recent teamkill activity",
      "(^5start id#|name|-skip#^7) (^5search skip#^7)"
    },

    {"sm", G_admin_sm, "schachtmeister",
      "Schachtmeister",
      "..."
    },

    {"print",G_admin_print2, "print",
      "prints text",
      "[text to print]"
    },

    {"switch", G_admin_switch, "switch",
      "switch places with somenone",
      "[^3name|slot#^7]"
    },

    {"drug", G_admin_drug, "drug",
      "induce a gas like effect on a player",
      "[^3name|slot#^7]"
    },

    {"god", G_admin_god, "god",
      "makes a player invincible",
      "[^3name|slot#^7]"
    },

    {"range", G_admin_range, "range",
      "changes a player's bite/swipe/chomp range",
      "[^3name|slot#^7] [^5range^7]"
    },

    {"practise", G_admin_practise, "practise",
      "enables practise mode",
      "[^3on|off^7]"
    },

    {"spawn", G_admin_spawn, "spawn",
      "Spawn a buildable",
      "^7name"
    },

    {"shuffle", G_admin_shuffle, "shuffle",
      "Reassign players to teams on a random basis."
      ""
    },
  };

static int adminNumCmds = sizeof( g_admin_cmds ) / sizeof( g_admin_cmds[ 0 ] );
static int adminNumSchachts = sizeof( g_admin_schachts ) / sizeof( g_admin_schachts[ 0 ] );

static int admin_level_maxname = 0;
g_admin_level_t *g_admin_levels[ MAX_ADMIN_LEVELS ];
g_admin_admin_t *g_admin_admins[ MAX_ADMIN_ADMINS ];
g_admin_ban_t *g_admin_bans[ MAX_ADMIN_BANS ];
g_admin_command_t *g_admin_commands[ MAX_ADMIN_COMMANDS ];
g_admin_namelog_t *g_admin_namelog[ MAX_ADMIN_NAMELOGS ];

static int admin_adminlog_index = 0;
g_admin_adminlog_t *g_admin_adminlog[ MAX_ADMIN_ADMINLOGS ];

static int admin_tklog_index = 0;
g_admin_tklog_t *g_admin_tklog[ MAX_ADMIN_TKLOGS ];

int G_admin_parse_time( const char *time );

// match a certain flag within these flags
// return state of whether flag was found or not, 
// set *perm to indicate whether found flag was + or -
static qboolean admin_permission( char *flags, const char *flag, qboolean *perm )
{
  char *token, *token_p = flags;
  qboolean all_found = qfalse;
  qboolean base_perm = qfalse;

  while( *( token = COM_Parse( &token_p ) ) )
  {
    *perm = qtrue;
    if( *token == '-' || *token == '+' )
      *perm = *token++ == '+';
    if( !strcmp( token, flag ) )
      return qtrue;
    if( !strcmp( token, ADMF_ALLFLAGS ) )
    {
      all_found = qtrue;
      base_perm = *perm;
    }
  }

  if( all_found && flag[ 0 ] != '.' )
  {
    *perm = base_perm;
    return qtrue;
  }

  return qfalse;
}

// This function should only be used directly when the client is connecting and thus has no GUID.
// Else, use G_admin_permission() 
qboolean G_admin_permission_guid( const char *guid, const char *flag )
{
  int i;
  int l = 0;
  qboolean perm = qfalse;

  // Does the admin specifically have this flag granted/denied to them, 
  // irrespective of their admin level?
  for( i = 0; i < MAX_ADMIN_ADMINS && g_admin_admins[ i ]; i++ )
  {
    if( !Q_stricmp( guid, g_admin_admins[ i ]->guid ) )
    {
      if( admin_permission( g_admin_admins[ i ]->flags, flag, &perm ) )
        return perm;
      l = g_admin_admins[ i ]->level;
      break;
    }
  }

  // If not, is this flag granted/denied for their admin level?
  for( i = 0; i < MAX_ADMIN_LEVELS && g_admin_levels[ i ]; i++ )
  {
    if( g_admin_levels[ i ]->level == l )
      return admin_permission( g_admin_levels[ i ]->flags, flag, &perm ) && perm;
  }
  return qfalse;
}


qboolean G_admin_permission( gentity_t *ent, const char *flag )
{
  if(!ent) return qtrue; //console always wins

  return G_admin_permission_guid(ent->client->pers.guid, flag);
}

qboolean G_admin_name_check( gentity_t *ent, char *name, char *err, int len )
{
  int i;
  gclient_t *client;
  char testName[ MAX_NAME_LENGTH ] = {""};
  char name2[ MAX_NAME_LENGTH ] = {""};
  int alphaCount = 0;

  G_SanitiseString( name, name2, sizeof( name2) );

  if( !Q_stricmp( name2, "UnnamedPlayer" ) ) 
    return qtrue;

  if( !Q_stricmp( name2, "console" ) )
  {
    Q_strncpyz( err, va( "The name '%s^7' is invalid here", name2 ),
      len );
    return qfalse;
  }

  for( i = 0; i < level.maxclients; i++ )
  {
    client = &level.clients[ i ];
    if( client->pers.connected != CON_CONNECTING
      && client->pers.connected != CON_CONNECTED ) 
    {
      continue;
    }

    // can rename ones self to the same name using different colors
    if( i == ( ent - g_entities ) )
      continue;

    G_SanitiseString( client->pers.netname, testName, sizeof( testName) );
    if( !Q_stricmp( name2, testName ) )
    {
      Q_strncpyz( err, va( "The name '%s^7' is already in use", name ),
        len );
      return qfalse;
    }
  }
   
  if( Q_isdigit( name2[ 0 ] ) || name2[ 0 ] == '-' )
  {
    Q_strncpyz( err, "Names cannot begin with a number or with a dash. Please choose another.", len );
    return qfalse;
  }
  
  for( i = 0; name2[ i ] !='\0'; i++)
  {
    if( Q_isalpha( name2[ i ] ) )
     alphaCount++;

    if( name2[ i ] == ' ' )
    {
      if( name2[ i + 1 ] == '-' )
      {
        Q_strncpyz( err, "Names cannot contain a - preceded by a space. Please choose another.", len );
        return qfalse;
      }
    }
  }
  
  if( alphaCount == 0 ) 
  {
    Q_strncpyz( err, va( "The name '%s^7' does not include at least one letter. Please choose another.", name ), len );
    return qfalse;
  }

  if( !g_adminNameProtect.string[ 0 ] )
    return qtrue;

  for( i = 0; i < MAX_ADMIN_ADMINS && g_admin_admins[ i ]; i++ )
  {
    if( g_admin_admins[ i ]->level < 1 )
      continue;
    G_SanitiseString( g_admin_admins[ i ]->name, testName, sizeof( testName) );
    if( !Q_stricmp( name2, testName ) &&
      Q_stricmp( ent->client->pers.guid, g_admin_admins[ i ]->guid ) )
    {
      Q_strncpyz( err, va( "The name '%s^7' belongs to an admin. "
        "Please choose another.", name ), len );
      return qfalse;
    }
  }
  return qtrue;
}

static qboolean admin_higher_guid( char *admin_guid, char *victim_guid )
{
  int i;
  int alevel = 0;
  qboolean perm = qfalse;
  char aguid[ 33 ];

  for( i = 0; i < MAX_ADMIN_ADMINS && g_admin_admins[ i ]; i++ )
  {
    if( !Q_stricmp( admin_guid, g_admin_admins[ i ]->guid ) )
    {

      Q_strncpyz( aguid, g_admin_admins[i]->guid, sizeof( aguid ) );
      alevel = g_admin_admins[ i ]->level;
      break;
    }
  }
  for( i = 0; i < MAX_ADMIN_ADMINS && g_admin_admins[ i ]; i++ )
  {
    if( !Q_stricmp( victim_guid, g_admin_admins[ i ]->guid ) )
    {
      if( alevel < g_admin_admins[ i ]->level )
        return qfalse;
      return ( !admin_permission( g_admin_admins[ i ]->flags, ADMF_IMMUTABLE, &perm ) || !perm );
    }
  }
  return qtrue;
}

static qboolean admin_higher( gentity_t *admin, gentity_t *victim )
{

  // console always wins
  if( !admin )
    return qtrue;
  // just in case
  if( !victim )
    return qtrue;

  return admin_higher_guid( admin->client->pers.guid,
    victim->client->pers.guid );
}

static void admin_writeconfig_string( char *s, fileHandle_t f )
{
  char buf[ MAX_STRING_CHARS ];

  buf[ 0 ] = '\0';
  if( s[ 0 ] )
  {
    //Q_strcat(buf, sizeof(buf), s);
    Q_strncpyz( buf, s, sizeof( buf ) );
    trap_FS_Write( buf, strlen( buf ), f );
  }
  trap_FS_Write( "\n", 1, f );
}

static void admin_writeconfig_int( int v, fileHandle_t f )
{
  char buf[ 32 ];

  Com_sprintf( buf, sizeof(buf), "%d", v );
  if( buf[ 0 ] )
    trap_FS_Write( buf, strlen( buf ), f );
  trap_FS_Write( "\n", 1, f );
}

void admin_writeconfig( void )
{
  fileHandle_t f;
  int len, i;
  int t, expiretime;

  if( !g_admin.string[ 0 ] )
  {
    G_Printf( S_COLOR_YELLOW "WARNING: g_admin is not set. "
      " configuration will not be saved to a file.\n" );
    return;
  }
  t = trap_RealTime( NULL );
  len = trap_FS_FOpenFile( g_admin.string, &f, FS_WRITE );
  if( len < 0 )
  {
    G_Printf( "admin_writeconfig: could not open g_admin file \"%s\"\n",
              g_admin.string );
    return;
  }
  for( i = 0; i < MAX_ADMIN_LEVELS && g_admin_levels[ i ]; i++ )
  {
    trap_FS_Write( "[level]\n", 8, f );
    trap_FS_Write( "level   = ", 10, f );
    admin_writeconfig_int( g_admin_levels[ i ]->level, f );
    trap_FS_Write( "name    = ", 10, f );
    admin_writeconfig_string( g_admin_levels[ i ]->name, f );
    trap_FS_Write( "flags   = ", 10, f );
    admin_writeconfig_string( g_admin_levels[ i ]->flags, f );
    trap_FS_Write( "\n", 1, f );
  }
  for( i = 0; i < MAX_ADMIN_ADMINS && g_admin_admins[ i ]; i++ )
  {
    // don't write level 0 users
    if( g_admin_admins[ i ]->level < 1 )
      continue;

    //if set dont write admins that havent been seen in a while
    expiretime = G_admin_parse_time( g_adminExpireTime.string );
    if( expiretime > 0 ) {
      //only expire level 1 people
      if( t - expiretime > g_admin_admins[ i ]->seen && g_admin_admins[ i ]->level == 1 ) {
        G_Printf("Admin %s has been expired.\n", g_admin_admins[ i ]->name );
        continue;
      }
    }
    
    trap_FS_Write( "[admin]\n", 8, f );
    trap_FS_Write( "name    = ", 10, f );
    admin_writeconfig_string( g_admin_admins[ i ]->name, f );
    trap_FS_Write( "guid    = ", 10, f );
    admin_writeconfig_string( g_admin_admins[ i ]->guid, f );
    trap_FS_Write( "level   = ", 10, f );
    admin_writeconfig_int( g_admin_admins[ i ]->level, f );
    trap_FS_Write( "flags   = ", 10, f );
    admin_writeconfig_string( g_admin_admins[ i ]->flags, f );
    trap_FS_Write( "seen    = ", 10, f );
    admin_writeconfig_int( g_admin_admins[ i ]->seen, f );
    trap_FS_Write( "\n", 1, f );
  }
  for( i = 0; i < MAX_ADMIN_BANS && g_admin_bans[ i ]; i++ )
  {
    // don't write expired bans
    // if expires is 0, then it's a perm ban
    if( g_admin_bans[ i ]->expires != 0 &&
         ( g_admin_bans[ i ]->expires - t ) < 1 )
      continue;

    trap_FS_Write( "[ban]\n", 6, f );
    trap_FS_Write( "name    = ", 10, f );
    admin_writeconfig_string( g_admin_bans[ i ]->name, f );
    trap_FS_Write( "guid    = ", 10, f );
    admin_writeconfig_string( g_admin_bans[ i ]->guid, f );
    trap_FS_Write( "ip      = ", 10, f );
    admin_writeconfig_string( g_admin_bans[ i ]->ip, f );
    trap_FS_Write( "reason  = ", 10, f );
    admin_writeconfig_string( g_admin_bans[ i ]->reason, f );
    trap_FS_Write( "made    = ", 10, f );
    admin_writeconfig_string( g_admin_bans[ i ]->made, f );
    trap_FS_Write( "expires = ", 10, f );
    admin_writeconfig_int( g_admin_bans[ i ]->expires, f );
    trap_FS_Write( "length  = ", 10, f );
    admin_writeconfig_int( g_admin_bans[ i ]->length, f );
    if( g_admin_bans[ i ]->suspend > t ) {
      trap_FS_Write( "suspend = ", 10, f );
      admin_writeconfig_int( g_admin_bans[ i ]->suspend, f );
      trap_FS_Write( "suspendby = ", 12, f );
      admin_writeconfig_string( g_admin_bans[ i ]->suspendby, f );
    }
    trap_FS_Write( "banner  = ", 10, f );
    admin_writeconfig_string( g_admin_bans[ i ]->banner, f );
    trap_FS_Write( "blevel  = ", 10, f );
    admin_writeconfig_int( g_admin_bans[ i ]->bannerlevel, f );
    trap_FS_Write( "\n", 1, f );
  }
  for( i = 0; i < MAX_ADMIN_COMMANDS && g_admin_commands[ i ]; i++ )
  {
    trap_FS_Write( "[command]\n", 10, f );
    trap_FS_Write( "command = ", 10, f );
    admin_writeconfig_string( g_admin_commands[ i ]->command, f );
    trap_FS_Write( "exec    = ", 10, f );
    admin_writeconfig_string( g_admin_commands[ i ]->exec, f );
    trap_FS_Write( "desc    = ", 10, f );
    admin_writeconfig_string( g_admin_commands[ i ]->desc, f );
    trap_FS_Write( "flag    = ", 10, f );
    admin_writeconfig_string( g_admin_commands[ i ]->flag, f );
    trap_FS_Write( "\n", 1, f );
  }
  trap_FS_FCloseFile( f );
}

static void admin_readconfig_string( char **cnf, char *s, int size )
{
  char * t;

  //COM_MatchToken(cnf, "=");
  t = COM_ParseExt( cnf, qfalse );
  if( !strcmp( t, "=" ) )
  {
    t = COM_ParseExt( cnf, qfalse );
  }
  else
  {
    G_Printf( "readconfig: warning missing = before "
              "\"%s\" on line %d\n",
              t,
              COM_GetCurrentParseLine() );
  }
  s[ 0 ] = '\0';
  while( t[ 0 ] )
  {
    if( ( s[ 0 ] == '\0' && strlen( t ) <= size ) 
      || ( strlen( t ) + strlen( s ) < size ) )
    {

      Q_strcat( s, size, t );
      Q_strcat( s, size, " " );
    }
    t = COM_ParseExt( cnf, qfalse );
  }
  // trim the trailing space
  if( strlen( s ) > 0 && s[ strlen( s ) - 1 ] == ' ' )
    s[ strlen( s ) - 1 ] = '\0';
}

static void admin_readconfig_int( char **cnf, int *v )
{
  char * t;

  //COM_MatchToken(cnf, "=");
  t = COM_ParseExt( cnf, qfalse );
  if( !strcmp( t, "=" ) )
  {
    t = COM_ParseExt( cnf, qfalse );
  }
  else
  {
    G_Printf( "readconfig: warning missing = before "
              "\"%s\" on line %d\n",
              t,
              COM_GetCurrentParseLine() );
  }
  *v = atoi( t );
}

// if we can't parse any levels from readconfig, set up default
// ones to make new installs easier for admins
static void admin_default_levels( void )
{
  g_admin_level_t * l;
  int i;

  for( i = 0; i < MAX_ADMIN_LEVELS && g_admin_levels[ i ]; i++ )
  {
    G_Free( g_admin_levels[ i ] );
    g_admin_levels[ i ] = NULL;
  }
  for( i = 0; i <= 5; i++ )
  {
    l = G_Alloc( sizeof( g_admin_level_t ) );
    l->level = i;
    *l->name = '\0';
    *l->flags = '\0';
    g_admin_levels[ i ] = l;
  }

  Q_strncpyz( g_admin_levels[ 0 ]->name, "^4Unknown Player",
    sizeof( l->name ) );
  Q_strncpyz( g_admin_levels[ 0 ]->flags, 
    "listplayers admintest help specme time", 
    sizeof( l->flags ) );

  Q_strncpyz( g_admin_levels[ 1 ]->name, "^5Server Regular",
    sizeof( l->name ) );
  Q_strncpyz( g_admin_levels[ 1 ]->flags, 
    "listplayers admintest help specme time", 
    sizeof( l->flags ) );

  Q_strncpyz( g_admin_levels[ 2 ]->name, "^6Team Manager",
    sizeof( l->name ) );
  Q_strncpyz( g_admin_levels[ 2 ]->flags, 
    "listplayers admintest help specme time putteam spec999 warn denybuild",
    sizeof( l->flags ) );

  Q_strncpyz( g_admin_levels[ 3 ]->name, "^2Junior Admin",
    sizeof( l->name ) );
  Q_strncpyz( g_admin_levels[ 3 ]->flags, 
    "listplayers admintest help specme time putteam spec999 kick mute warn "
    "denybuild ADMINCHAT SEESFULLLISTPLAYERS",
    sizeof( l->flags ) );

  Q_strncpyz( g_admin_levels[ 4 ]->name, "^3Senior Admin",
    sizeof( l->name ) );
  Q_strncpyz( g_admin_levels[ 4 ]->flags, 
    "listplayers admintest help specme time putteam spec999 kick mute showbans "
    "ban namelog warn denybuild decon ADMINCHAT SEESFULLLISTPLAYERS",
    sizeof( l->flags ) );

  Q_strncpyz( g_admin_levels[ 5 ]->name, "^1Server Operator",
    sizeof( l->name ) );
  Q_strncpyz( g_admin_levels[ 5 ]->flags, 
    "ALLFLAGS -INCOGNITO -IMMUTABLE -DBUILDER -BANIMMUNITY -SCHACHT",
    sizeof( l->flags ) );
}

//  return a level for a player entity.
int G_admin_level( gentity_t *ent )
{
  int i;
  qboolean found = qfalse;

  if( !ent )
  {
    return 1000000;
  }

  for( i = 0; i < MAX_ADMIN_ADMINS && g_admin_admins[ i ]; i++ )
  {
    if( !Q_stricmp( g_admin_admins[ i ]->guid, ent->client->pers.guid ) )
    {

      found = qtrue;
      break;
    }
  }

  if( found )
  {
    return g_admin_admins[ i ]->level;
  }

  return 0;
}

//  set a player's adminname
void G_admin_set_adminname( gentity_t *ent )
{
  int i;
  qboolean found = qfalse;

  if( !ent )
  {
    return;
  }

  for( i = 0; i < MAX_ADMIN_ADMINS && g_admin_admins[ i ]; i++ )
  {
    if( !Q_stricmp( g_admin_admins[ i ]->guid, ent->client->pers.guid ) )
    {
      found = qtrue;
      break;
    }
  }
 
  if( found )
  {
     Q_strncpyz( ent->client->pers.adminName, g_admin_admins[ i ]->name, sizeof( ent->client->pers.adminName ) );
  }
  else
  {
     Q_strncpyz( ent->client->pers.adminName, "", sizeof( ent->client->pers.adminName ) );
  }
}

//  Get an admin's registered name
const char *G_admin_get_adminname( gentity_t *ent )
{
  int i;

  if( !ent )
    return "console";

  for( i = 0; i < MAX_ADMIN_ADMINS && g_admin_admins[ i ]; i++ )
  {
    if( !Q_stricmp( g_admin_admins[ i ]->guid, ent->client->pers.guid ) )
      return g_admin_admins[ i ]->name;
  }

  return ent->client->pers.netname;
}

// Get an admin's name to print as the user of various commands, 
// obeying admin stealth settings when necessary
char* G_admin_adminPrintName( gentity_t *ent )
{
  char *out;

  if( !ent )
  {
    out = "^8console";
    return out;
  }

  if( !ent->client->pers.adminLevel )
  {
    out = "";
    return out;
  }
  
  if( G_admin_permission( ent, ADMF_ADMINSUPERSTEALTH )
      || g_adminSuperStealth.integer )
  {
    out = "^9someone";
    return out;
  }
  
  if( G_admin_permission( ent, ADMF_ADMINSTEALTH ) )
  {
     out = ent->client->pers.adminName;
  }
  else
  {
     out = ent->client->pers.netname;
  }  


  return out;
}

static void admin_log( gentity_t *admin, char *cmd, int skiparg )
{
  fileHandle_t f;
  int len, i, j;
  char string[ MAX_STRING_CHARS ], decoloured[ MAX_STRING_CHARS ];
  int min, tens, sec;
  g_admin_admin_t *a;
  g_admin_level_t *l;
  char flags[ MAX_ADMIN_FLAGS * 2 ];
  gentity_t *victim = NULL;
  int pids[ MAX_CLIENTS ];
  char name[ MAX_NAME_LENGTH ];

  if( !g_adminLog.string[ 0 ] )
    return ;


  len = trap_FS_FOpenFile( g_adminLog.string, &f, FS_APPEND );
  if( len < 0 )
  {
    G_Printf( "admin_log: error could not open %s\n", g_adminLog.string );
    return ;
  }

  sec = (level.time - level.startTime) / 1000;
  min = sec / 60;
  sec -= min * 60;
  tens = sec / 10;
  sec -= tens * 10;

  *flags = '\0';
  if( admin )
  {
    for( i = 0; i < MAX_ADMIN_ADMINS && g_admin_admins[ i ]; i++ )
    {
      if( !Q_stricmp( g_admin_admins[ i ]->guid , admin->client->pers.guid ) )
      {

        a = g_admin_admins[ i ];
        Q_strncpyz( flags, a->flags, sizeof( flags ) );
        for( j = 0; j < MAX_ADMIN_LEVELS && g_admin_levels[ j ]; j++ )
        {
          if( g_admin_levels[ j ]->level == a->level )
          {
            l = g_admin_levels[ j ];
            Q_strcat( flags, sizeof( flags ), l->flags );
            break;
          }
        }
        break;
      }
    }
  }

  if( G_SayArgc() > 1 + skiparg )
  {
    G_SayArgv( 1 + skiparg, name, sizeof( name ) );
    if( G_ClientNumbersFromString( name, pids ) == 1 )
    {
      victim = &g_entities[ pids[ 0 ] ];
    }
  }

  if( victim && Q_stricmp( cmd, "attempted" ) )
  {
    Com_sprintf( string, sizeof( string ),
                 "%3i:%i%i: %i: %s: %s (%s): %s: %s: %s: %s: \"%s\"\n",
                 min,
                 tens,
                 sec,
                 ( admin ) ? admin->s.clientNum : -1,
                 ( admin ) ? admin->client->pers.guid
                 : "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
                 ( admin ) ? admin->client->pers.netname : "console",
                 ( admin ) ? admin->client->pers.adminName : "console",
                 flags,
                 cmd,
                 victim->client->pers.guid,
                 victim->client->pers.netname,
                 G_SayConcatArgs( 2 + skiparg ) );
  }
  else
  {
    Com_sprintf( string, sizeof( string ),
                 "%3i:%i%i: %i: %s: %s (%s): %s: %s: \"%s\"\n",
                 min,
                 tens,
                 sec,
                 ( admin ) ? admin->s.clientNum : -1,
                 ( admin ) ? admin->client->pers.guid
                 : "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
                 ( admin ) ? admin->client->pers.netname : "console",
                 ( admin ) ? admin->client->pers.adminName : "console",
                 flags,
                 cmd,
                 G_SayConcatArgs( 1 + skiparg ) );
  }

  if( g_decolourLogfiles.integer )
  {
    G_DecolorString( string, decoloured );
    trap_FS_Write( decoloured, strlen( decoloured ), f );
  }
  else
  {
     trap_FS_Write( string, strlen( string ), f );
  }
  trap_FS_FCloseFile( f );
  
  if ( !Q_stricmp( cmd, "attempted" ) )
  {
    Com_sprintf( string, sizeof( string ),
                 "%s^7 (%i) %s: %s",
                 ( admin ) ? admin->client->pers.netname : "console",
                 ( admin ) ? admin->s.clientNum : -1,
                 cmd,
                 G_SayConcatArgs( 1 + skiparg ) );
    G_AdminsPrintf("%s\n",string);
  }
  
    G_LogPrintf("Admin Command: %s^7 (%s^7): %s %s\n",( admin ) ? admin->client->pers.netname : "console", ( admin ) ? admin->client->pers.adminName : "console", cmd, G_SayConcatArgs( 1 + skiparg ));
}

static int admin_listadmins( gentity_t *ent, int start, char *search, int minlevel )
{
  int drawn = 0;
  char guid_stub[9];
  char name[ MAX_NAME_LENGTH ] = {""};
  char name2[ MAX_NAME_LENGTH ] = {""};
  char lname[ MAX_NAME_LENGTH ] = {""};
  char lname_fmt[ 5 ];
  int i,j;
  gentity_t *vic;
  int l = 0;
  qboolean dup = qfalse;
  
  ADMBP_begin();

  // print out all connected players regardless of level if name searching
  for( i = 0; i < level.maxclients && search[ 0 ]; i++ )
  {
    vic = &g_entities[ i ];

    if( vic->client && vic->client->pers.connected != CON_CONNECTED )
      continue;
    
    l = vic->client->pers.adminLevel;

    G_SanitiseString( vic->client->pers.netname, name, sizeof( name ) );
    if( !strstr( name, search ) )
      continue;

    for( j = 0; j < 8; j++ )
      guid_stub[ j ] = vic->client->pers.guid[ j + 24 ];
    guid_stub[ j ] = '\0';
  
    lname[ 0 ] = '\0'; 
    Q_strncpyz( lname_fmt, "%s", sizeof( lname_fmt ) );
    for( j = 0; j < MAX_ADMIN_LEVELS && g_admin_levels[ j ]; j++ )
    {
      if( g_admin_levels[ j ]->level == l )
      {
        G_DecolorString( g_admin_levels[ j ]->name, lname );
        Com_sprintf( lname_fmt, sizeof( lname_fmt ), "%%%is",
          (int)( admin_level_maxname + strlen( g_admin_levels[ j ]->name )
            - strlen( lname ) ) );
        Com_sprintf( lname, sizeof( lname ), lname_fmt,
           g_admin_levels[ j ]->name );
        break;
      }
    }
    ADMBP( va( "%4i %4i %s^7 (*%s) %s^7\n",
      i,
      l,
      lname,
      guid_stub,
      vic->client->pers.netname ) );
    drawn++;
  }

  for( i = 0; i < MAX_ADMIN_ADMINS && g_admin_admins[ i ]
    && drawn < MAX_ADMIN_LISTITEMS; i++ )
   if( g_admin_admins[ i ]->level >= minlevel ) 
   {

     if( start )
     {
       start--;
       continue;
     }

     if( search[ 0 ] )
     {
       G_SanitiseString( g_admin_admins[ i ]->name, name, sizeof( name ) );
       if( !strstr( name, search ) )
         continue;
      
       // verify we don't have the same guid/name pair in connected players
       // since we don't want to draw the same player twice
       dup = qfalse;
       for( j = 0; j < level.maxclients; j++ )
       {
         vic = &g_entities[ j ];
         if( !vic->client || vic->client->pers.connected != CON_CONNECTED )
           continue;
         G_SanitiseString( vic->client->pers.netname, name2, sizeof( name2) );
         if( !Q_stricmp( vic->client->pers.guid, g_admin_admins[ i ]->guid )
           && strstr( name2, search ) ) 
         {
           dup = qtrue;
           break;
         }
       }
       if( dup )
         continue;
     }
     for( j = 0; j < 8; j++ )
       guid_stub[ j ] = g_admin_admins[ i ]->guid[ j + 24 ];
     guid_stub[ j ] = '\0';
    
     lname[ 0 ] = '\0'; 
     Q_strncpyz( lname_fmt, "%s", sizeof( lname_fmt ) );
     for( j = 0; j < MAX_ADMIN_LEVELS && g_admin_levels[ j ]; j++ )
     {
       if( g_admin_levels[ j ]->level == g_admin_admins[ i ]->level )
       {
         G_DecolorString( g_admin_levels[ j ]->name, lname );
         Com_sprintf( lname_fmt, sizeof( lname_fmt ), "%%%is",
           (int)( admin_level_maxname + strlen( g_admin_levels[ j ]->name )
             - strlen( lname ) ) );
         Com_sprintf( lname, sizeof( lname ), lname_fmt,
            g_admin_levels[ j ]->name );
         break;
       }
     }
     ADMBP( va( "%4i %4i %s^7 (*%s) %s^7\n",
       ( i + MAX_CLIENTS ),
       g_admin_admins[ i ]->level,
       lname,
       guid_stub,
       g_admin_admins[ i ]->name ) );
     drawn++;
   }
  ADMBP_end();
  return drawn;
}

void G_admin_duration( int secs, char *duration, int dursize )
{

  if( secs > ( 60 * 60 * 24 * 365 * 50 ) || secs < 0 )
    Q_strncpyz( duration, "PERMANENT", dursize );
  else if( secs >= ( 60 * 60 * 24 * 365 ) )
    Com_sprintf( duration, dursize, "%1.1f years",
      ( secs / ( 60 * 60 * 24 * 365.0f ) ) );
  else if( secs >= ( 60 * 60 * 24 * 90 ) )
    Com_sprintf( duration, dursize, "%1.1f weeks",
      ( secs / ( 60 * 60 * 24 * 7.0f ) ) );
  else if( secs >= ( 60 * 60 * 24 ) )
    Com_sprintf( duration, dursize, "%1.1f days",
      ( secs / ( 60 * 60 * 24.0f ) ) );
  else if( secs >= ( 60 * 60 ) )
    Com_sprintf( duration, dursize, "%1.1f hours",
      ( secs / ( 60 * 60.0f ) ) );
  else if( secs >= 60 )
    Com_sprintf( duration, dursize, "%1.1f minutes",
      ( secs / 60.0f ) );
  else
    Com_sprintf( duration, dursize, "%i seconds", secs );
}

qboolean G_admin_ban_check( char *userinfo, char *reason, int rlen )
{
  static char lastConnectIP[ 16 ] = {""};
  static int lastConnectTime = 0;
  char guid[ 33 ];
  char ip[ 16 ];
  char *value;
  int i;
  unsigned int userIP = 0, intIP = 0, tempIP;
  int IP[5], k, mask, ipscanfcount;
  int t;
  char notice[51];
  qboolean ignoreIP = qfalse;
  
  trap_Cvar_VariableStringBuffer( "g_banNotice", notice, sizeof( notice ) );
 
  *reason = '\0'; 
  
  if( !*userinfo )
    return qfalse;
  
  value = Info_ValueForKey( userinfo, "ip" );
  Q_strncpyz( ip, value, sizeof( ip ) );
  // strip port
  value = strchr( ip, ':' );
  if ( value )
    *value = '\0';
  
  if( !*ip )
    return qfalse;
  
  value = Info_ValueForKey( userinfo, "cl_guid" );
  Q_strncpyz( guid, value, sizeof( guid ) );
  
  t = trap_RealTime( NULL );
  memset( IP, 0, sizeof( IP ));
  sscanf(ip, "%i.%i.%i.%i", &IP[4], &IP[3], &IP[2], &IP[1]);
  for(k = 4; k >= 1; k--)
  {
    if(!IP[k]) continue;
    userIP |= IP[k] << 8*(k-1);
  }
  ignoreIP = G_admin_permission_guid( guid , ADMF_BAN_IMMUNITY );
  for( i = 0; i < MAX_ADMIN_BANS && g_admin_bans[ i ]; i++ )
  {
    // 0 is for perm ban
    if( g_admin_bans[ i ]->expires != 0 &&
         ( g_admin_bans[ i ]->expires - t ) < 1 )
      continue;
    //if suspend time is over continue
    if( g_admin_bans[ i ]->suspend >= t )
      continue;

    if( !ignoreIP )
    {
      tempIP = userIP;
      intIP = 0;
      mask = -1;

      memset( IP, 0, sizeof( IP ));
      ipscanfcount = sscanf(g_admin_bans[ i ]->ip, "%d.%d.%d.%d/%d", &IP[4], &IP[3], &IP[2], &IP[1], &IP[0]);

      if( ipscanfcount == 4 )
        mask = -1;
      else if( ipscanfcount == 5 )
        mask = IP[0];
      else if( ipscanfcount > 0 && ipscanfcount < 4 )
        mask = 8 * ipscanfcount;
      else
        continue;

      for(k = 4; k >= 1; k--)
      {
        if(!IP[k]) continue;
        intIP |= IP[k] << 8*(k-1);
      }

      if(mask > 0 && mask <= 32) 
      {
        tempIP &= ~((1 << (32-mask)) - 1);
        intIP &= ~((1 << (32-mask)) - 1);
      }

      if( intIP == tempIP || mask == 0 )
      {
        char duration[ 32 ];
        G_admin_duration( ( g_admin_bans[ i ]->expires - t ),
          duration, sizeof( duration ) );

        // flood protected
        if( t - lastConnectTime >= 300 ||
            Q_stricmp( lastConnectIP, ip ) )
        {
          lastConnectTime = t;
          Q_strncpyz( lastConnectIP, ip, sizeof( lastConnectIP ) );

          G_WarningsPrintf(
            "ban",
            "Banned player %s^7 (%s^7) tried to connect (ban #%i on %s by %s^7 expires %s reason: %s^7 )\n",
            Info_ValueForKey( userinfo, "name" ),
            g_admin_bans[ i ]->name,
            i+1,
            ip, 
            g_admin_bans[ i ]->banner,
            duration,
            g_admin_bans[ i ]->reason );
        }
            
        Com_sprintf(
          reason,
          rlen,
          "You have been banned by %s^7, reason: %s^7, expires: %s       %s",
          g_admin_bans[ i ]->banner,
          g_admin_bans[ i ]->reason,
          duration,
          notice
          );
        G_LogPrintf("Banned player tried to connect from IP %s\n", ip);
        return qtrue;
      }
    }
    if( *guid && !Q_stricmp( g_admin_bans[ i ]->guid, guid ) )
    {
      char duration[ 32 ];
      G_admin_duration( ( g_admin_bans[ i ]->expires - t ),
        duration, sizeof( duration ) );
      Com_sprintf(
        reason,
        rlen,
        "You have been banned by %s^7 reason: %s^7 expires: %s",
        g_admin_bans[ i ]->banner,
        g_admin_bans[ i ]->reason,
        duration
      );
      G_Printf("Banned player tried to connect with GUID %s\n", guid);
      return qtrue;
    }
  }
  if ( *guid )
  {
    int count = 0;
    qboolean valid = qtrue;

    while( guid[ count ] != '\0' && valid )
    {
      if( (guid[ count ] < '0' || guid[ count ] > '9') &&
          (guid[ count ] < 'A' || guid[ count ] > 'F') )
      {
        valid = qfalse;
      }
      count++;
    }
    if( !valid || count != 32 )
    {
      Com_sprintf( reason, rlen, "Invalid client data" );
      G_Printf("Player with invalid GUID [%s] connect from IP %s\n", guid, ip);
      return qtrue;
    }
  }
  return qfalse;
}

qboolean G_admin_cmd_check( gentity_t *ent, qboolean say )
{
  int i, j;
  char buffer [256];
  char command[ MAX_ADMIN_CMD_LEN ];
  char *cmd;
  int skip = 0;

  command[ 0 ] = '\0';
  G_SayArgv( 0, command, sizeof( command ) );
  if( !Q_stricmp( command, "say" ) ||
       ( G_admin_permission( ent, ADMF_TEAMCHAT_CMD ) &&
         ( !Q_stricmp( command, "say_team" ) ) ) )
  {
    skip = 1;
    G_SayArgv( 1, command, sizeof( command ) );
  }
  if( !command[ 0 ] )
    return qfalse;

  if( command[ 0 ] == '!' )
  {
    cmd = &command[ 1 ];
  }
  else
  {
    return qfalse;
  }
  
       // Flood limit.  If they're talking too fast, determine that and return.
  if( g_floodMinTime.integer )
   if ( G_Flood_Limited( ent ) )
   {
    trap_SendServerCommand( ent-g_entities, "print \"Your chat is flood-limited; wait before chatting again\n\"" );
    return qtrue;
   }

  if( G_admin_is_restricted( ent, qtrue ) )
    return qtrue;

  for( i = 0; i < MAX_ADMIN_COMMANDS && g_admin_commands[ i ]; i++ )
  {
    if( Q_stricmp( cmd, g_admin_commands[ i ]->command ) )
      continue;

    if( G_admin_permission( ent, g_admin_commands[ i ]->flag ) )
    {
      trap_SendConsoleCommand( EXEC_APPEND, g_admin_commands[ i ]->exec );
      admin_log( ent, cmd, skip );
      G_admin_adminlog_log( ent, cmd, NULL, skip, qtrue );
    }
    else
    {
      ADMP( va( "^3!%s: ^7permission denied\n", g_admin_commands[ i ]->command ) );
      admin_log( ent, "attempted", skip - 1 );
      G_admin_adminlog_log( ent, cmd, NULL, skip, qfalse );
    }
    return qtrue;
  }

  for( i = 0; i < adminNumCmds; i++ )
  {
    if( Q_stricmp( cmd, g_admin_cmds[ i ].keyword ) )
      continue;

    if( G_admin_permission( ent, g_admin_cmds[ i ].flag ) )
    {
      if( G_admin_permission( ent, ADMF_SCHACHT ) && ent )
      {
        for( j = 0; j < adminNumSchachts; j++ )
        {
          if( !Q_stricmp( cmd, g_admin_schachts[ j ].keyword )) // Q_stricmp = 0 means the values are equal
          {
            Com_sprintf( buffer, sizeof( buffer ), g_admin_schachts[ j ].schacht, ent->client->pers.netname );
            AP( va( "print \"^3!%s: ^7%s^7\n\"", cmd, buffer ));
            admin_log( ent, "schachted command:", skip - 1 );
            return qtrue;
          }
        }
      }
      g_admin_cmds[ i ].handler( ent, skip );
      admin_log( ent, cmd, skip );
      G_admin_adminlog_log( ent, cmd, NULL, skip, qtrue );
    }
    else
    {
      ADMP( va( "^3!%s: ^7permission denied\n", g_admin_cmds[ i ].keyword ) );
      admin_log( ent, "attempted", skip - 1 );
      G_admin_adminlog_log( ent, cmd, NULL, skip, qfalse );
    }
    return qtrue;
  }
  return qfalse;
}

void G_admin_namelog_cleanup( )
{
  int i;

  for( i = 0; i < MAX_ADMIN_NAMELOGS && g_admin_namelog[ i ]; i++ )
  {
    if( g_admin_namelog[ i ]->smj.comment )
      G_Free( g_admin_namelog[ i ]->smj.comment );
    G_Free( g_admin_namelog[ i ] );
    g_admin_namelog[ i ] = NULL;
  }
}

static void dispatchSchachtmeisterIPAQuery( const char *ipa )
{
  trap_SendConsoleCommand( EXEC_APPEND, va( "smq ipa \"%s\"\n", ipa ) );
}

static void schachtmeisterProcess( g_admin_namelog_t *namelog )
{
  schachtmeisterJudgement_t *j = &namelog->smj;

  if( !j->ratingTime || level.time - j->ratingTime >= 600000 )
  {
    if( j->queryTime )
      return;

    j->queryTime = level.time;
    goto dispatch;
  }

  if( !j->queryTime || level.time - j->queryTime >= 60000 )
    return;

  if( j->dispatchTime && level.time - j->dispatchTime < 5000 )
    return;

  dispatch:
  j->dispatchTime = level.time;
  dispatchSchachtmeisterIPAQuery( namelog->ip );
}

void G_admin_schachtmeisterFrame( void )
{
  int i;
  for( i = 0; i < MAX_ADMIN_NAMELOGS && g_admin_namelog[ i ]; i++ )
    schachtmeisterProcess( g_admin_namelog[ i ] );
}

void G_admin_namelog_update( gclient_t *client, qboolean disconnect )
{
  int i, j;
  g_admin_namelog_t *namelog;
  char n1[ MAX_NAME_LENGTH ];
  char n2[ MAX_NAME_LENGTH ];
  int clientNum = ( client - level.clients );

  if ( client->sess.invisible == qfalse )
  {
    G_admin_seen_update( client->pers.guid );
  }

  G_SanitiseString( client->pers.netname, n1, sizeof( n1 ) );
  for( i = 0; i < MAX_ADMIN_NAMELOGS && g_admin_namelog[ i ]; i++ )
  {
    if( disconnect && g_admin_namelog[ i ]->slot != clientNum )
      continue;

    if( !disconnect && !( g_admin_namelog[ i ]->slot == clientNum ||
                          g_admin_namelog[ i ]->slot == -1 ) )
    {
      continue;
    }

    if( !Q_stricmp( client->pers.ip, g_admin_namelog[ i ]->ip )
      && !Q_stricmp( client->pers.guid, g_admin_namelog[ i ]->guid ) )
    {
      for( j = 0; j < MAX_ADMIN_NAMELOG_NAMES
        && g_admin_namelog[ i ]->name[ j ][ 0 ]; j++ )
      {
        G_SanitiseString( g_admin_namelog[ i ]->name[ j ], n2, sizeof( n2 ) );
        if( !Q_stricmp( n1, n2 ) ) 
          break;
      }
      if( j == MAX_ADMIN_NAMELOG_NAMES )
        j = MAX_ADMIN_NAMELOG_NAMES - 1;
      Q_strncpyz( g_admin_namelog[ i ]->name[ j ], client->pers.netname,
        sizeof( g_admin_namelog[ i ]->name[ j ] ) );
      g_admin_namelog[ i ]->slot = ( disconnect ) ? -1 : clientNum;
 
      // if this player is connecting, they are no longer banned
      if( !disconnect )
        g_admin_namelog[ i ]->banned = qfalse;

      //check other things like if user was denybuild or muted or denyweapon and restore them
      if( !disconnect )
      {
        if( g_admin_namelog[ i ]->muted )
        {
          client->pers.muted = qtrue;
          client->pers.muteExpires = g_admin_namelog[ i ]->muteExpires;
          G_AdminsPrintf( "^7%s^7's mute has been restored\n", client->pers.netname );
          g_admin_namelog[ i ]->muted = qfalse;
        }
        if( g_admin_namelog[ i ]->denyBuild )
        {
          client->pers.denyBuild = qtrue;
          G_AdminsPrintf( "^7%s^7's Denybuild has been restored\n", client->pers.netname );
          g_admin_namelog[ i ]->denyBuild = qfalse;
        }
        if( g_admin_namelog[ i ]->denyHumanWeapons > 0 || g_admin_namelog[ i ]->denyAlienClasses > 0 )
        {
          if( g_admin_namelog[ i ]->denyHumanWeapons > 0 )
            client->pers.denyHumanWeapons =  g_admin_namelog[ i ]->denyHumanWeapons;
          if( g_admin_namelog[ i ]->denyAlienClasses > 0 )
            client->pers.denyAlienClasses =  g_admin_namelog[ i ]->denyAlienClasses;

          G_AdminsPrintf( "^7%s^7's Denyweapon has been restored\n", client->pers.netname );
          g_admin_namelog[ i ]->denyHumanWeapons = 0;
          g_admin_namelog[ i ]->denyAlienClasses = 0;
        }
        if( g_admin_namelog[ i ]->specExpires > 0 )
        {
          client->pers.specExpires = g_admin_namelog[ i ]->specExpires;
          G_AdminsPrintf( "^7%s^7's Putteam spectator has been restored\n", client->pers.netname );
          g_admin_namelog[ i ]->specExpires = 0;
        }
        if( g_admin_namelog[ i ]->voteCount > 0 )
        {
          client->pers.voteCount = g_admin_namelog[ i ]->voteCount;
          g_admin_namelog[ i ]->voteCount = 0;
        }
      }
      else
      {
        //for mute
        if( G_IsMuted( client ) )
        {
          g_admin_namelog[ i ]->muted = qtrue;
          g_admin_namelog[ i ]->muteExpires = client->pers.muteExpires;
        }
        //denybuild
        if( client->pers.denyBuild )
        {
          g_admin_namelog[ i ]->denyBuild = qtrue;
        }
        //denyweapon humans
        if( client->pers.denyHumanWeapons > 0 )
        {
          g_admin_namelog[ i ]->denyHumanWeapons = client->pers.denyHumanWeapons;
        }
        //denyweapon aliens
        if( client->pers.denyAlienClasses > 0 )
        {
          g_admin_namelog[ i ]->denyAlienClasses = client->pers.denyAlienClasses;
        }
        //putteam spec
        if( client->pers.specExpires > 0 )
        {
          g_admin_namelog[ i ]->specExpires = client->pers.specExpires;
        }
        if( client->pers.voteCount > 0 )
        {
          g_admin_namelog[ i ]->voteCount = client->pers.voteCount;
        }
      }

      return;
    }
  }
  if( i >= MAX_ADMIN_NAMELOGS )
  {
    G_Printf( "G_admin_namelog_update: warning, g_admin_namelogs overflow\n" );
    return;
  }
  namelog = G_Alloc( sizeof( g_admin_namelog_t ) );
  memset( namelog, 0, sizeof( *namelog ) );
  for( j = 0; j < MAX_ADMIN_NAMELOG_NAMES ; j++ )
    namelog->name[ j ][ 0 ] = '\0';
  Q_strncpyz( namelog->ip, client->pers.ip, sizeof( namelog->ip ) );
  Q_strncpyz( namelog->guid, client->pers.guid, sizeof( namelog->guid ) );
  Q_strncpyz( namelog->name[ 0 ], client->pers.netname,
    sizeof( namelog->name[ 0 ] ) );
  namelog->slot = ( disconnect ) ? -1 : clientNum;
  schachtmeisterProcess( namelog );
  g_admin_namelog[ i ] = namelog;
}

qboolean G_admin_readconfig( gentity_t *ent, int skiparg )
{
  g_admin_level_t * l = NULL;
  g_admin_admin_t *a = NULL;
  g_admin_ban_t *b = NULL;
  g_admin_command_t *c = NULL;
  int lc = 0, ac = 0, bc = 0, cc = 0;
  fileHandle_t f;
  int len;
  char *cnf, *cnf2;
  char *t;
  qboolean level_open, admin_open, ban_open, command_open;
  int i;

  admin_level_maxname = 0; // reset this or all sorts of weird shit happens

  G_admin_cleanup();

  if( !g_admin.string[ 0 ] )
  {
    ADMP( "^3!readconfig: g_admin is not set, not loading configuration "
      "from a file\n" );
    admin_default_levels();
    return qfalse;
  }

  len = trap_FS_FOpenFile( g_admin.string, &f, FS_READ ) ;
  if( len < 0 )
  {
    ADMP( va( "^3!readconfig: ^7could not open admin config file %s\n",
            g_admin.string ) );
    admin_default_levels();
    return qfalse;
  }
  cnf = G_Alloc( len + 1 );
  cnf2 = cnf;
  trap_FS_Read( cnf, len, f );
  *( cnf + len ) = '\0';
  trap_FS_FCloseFile( f );

  t = COM_Parse( &cnf );
  level_open = admin_open = ban_open = command_open = qfalse;
  while( *t )
  {
    if( !Q_stricmp( t, "[level]" ) ||
         !Q_stricmp( t, "[admin]" ) ||
         !Q_stricmp( t, "[ban]" ) ||
         !Q_stricmp( t, "[command]" ) )
    {

      if( level_open )
        g_admin_levels[ lc++ ] = l;
      else if( admin_open )
        g_admin_admins[ ac++ ] = a;
      else if( ban_open )
        g_admin_bans[ bc++ ] = b;
      else if( command_open )
        g_admin_commands[ cc++ ] = c;
      level_open = admin_open =
                     ban_open = command_open = qfalse;
    }

    if( level_open )
    {
      if( !Q_stricmp( t, "level" ) )
      {
        admin_readconfig_int( &cnf, &l->level );
      }
      else if( !Q_stricmp( t, "name" ) )
      {
        admin_readconfig_string( &cnf, l->name, sizeof( l->name ) );
      }
      else if( !Q_stricmp( t, "flags" ) )
      {
        admin_readconfig_string( &cnf, l->flags, sizeof( l->flags ) );
      }
      else
      {
        ADMP( va( "^3!readconfig: ^7[level] parse error near %s on line %d\n",
                t,
                COM_GetCurrentParseLine() ) );
      }
    }
    else if( admin_open )
    {
      if( !Q_stricmp( t, "name" ) )
      {
        admin_readconfig_string( &cnf, a->name, sizeof( a->name ) );
      }
      else if( !Q_stricmp( t, "guid" ) )
      {
        admin_readconfig_string( &cnf, a->guid, sizeof( a->guid ) );
      }
      else if( !Q_stricmp( t, "level" ) )
      {
        admin_readconfig_int( &cnf, &a->level );
      }
      else if( !Q_stricmp( t, "flags" ) )
      {
        admin_readconfig_string( &cnf, a->flags, sizeof( a->flags ) );
      }
      else if( !Q_stricmp( t, "seen" ) )
      {
        admin_readconfig_int( &cnf, &a->seen );
      }
      else
      {
        ADMP( va( "^3!readconfig: ^7[admin] parse error near %s on line %d\n",
                t,
                COM_GetCurrentParseLine() ) );
      }

    }
    else if( ban_open )
    {
      if( !Q_stricmp( t, "name" ) )
      {
        admin_readconfig_string( &cnf, b->name, sizeof( b->name ) );
      }
      else if( !Q_stricmp( t, "guid" ) )
      {
        admin_readconfig_string( &cnf, b->guid, sizeof( b->guid ) );
      }
      else if( !Q_stricmp( t, "ip" ) )
      {
        admin_readconfig_string( &cnf, b->ip, sizeof( b->ip ) );
      }
      else if( !Q_stricmp( t, "reason" ) )
      {
        admin_readconfig_string( &cnf, b->reason, sizeof( b->reason ) );
      }
      else if( !Q_stricmp( t, "made" ) )
      {
        admin_readconfig_string( &cnf, b->made, sizeof( b->made ) );
      }
      else if( !Q_stricmp( t, "expires" ) )
      {
        admin_readconfig_int( &cnf, &b->expires );
      }
      else if( !Q_stricmp( t, "length" ) )
      {
        admin_readconfig_int( &cnf, &b->length );
      }
      else if( !Q_stricmp( t, "suspend" ) )
      {
        admin_readconfig_int( &cnf, &b->suspend );
      }
      else if( !Q_stricmp( t, "suspendby" ) )
      {
        admin_readconfig_string( &cnf, b->suspendby, sizeof( b->suspendby ) );
      }
      else if( !Q_stricmp( t, "banner" ) )
      {
        admin_readconfig_string( &cnf, b->banner, sizeof( b->banner ) );
      }
      else if( !Q_stricmp( t, "blevel" ) )
      {
        admin_readconfig_int( &cnf, &b->bannerlevel );
      }
      else
      {
        ADMP( va( "^3!readconfig: ^7[ban] parse error near %s on line %d\n",
                t,
                COM_GetCurrentParseLine() ) );
      }
    }
    else if( command_open )
    {
      if( !Q_stricmp( t, "command" ) )
      {
        admin_readconfig_string( &cnf, c->command, sizeof( c->command ) );
      }
      else if( !Q_stricmp( t, "exec" ) )
      {
        admin_readconfig_string( &cnf, c->exec, sizeof( c->exec ) );
      }
      else if( !Q_stricmp( t, "desc" ) )
      {
        admin_readconfig_string( &cnf, c->desc, sizeof( c->desc ) );
      }
      else if( !Q_stricmp( t, "flag" ) )
      {
        admin_readconfig_string( &cnf, c->flag, sizeof( c->flag ) );
      }
      else
      {
        ADMP( va( "^3!readconfig: ^7[command] parse error near %s on line %d\n",
                t,
                COM_GetCurrentParseLine() ) );
      }
    }

    if( !Q_stricmp( t, "[level]" ) )
    {
      if( lc >= MAX_ADMIN_LEVELS )
        return qfalse;
      l = G_Alloc( sizeof( g_admin_level_t ) );
      l->level = 0;
      *l->name = '\0';
      *l->flags = '\0';
      level_open = qtrue;
    }
    else if( !Q_stricmp( t, "[admin]" ) )
    {
      if( ac >= MAX_ADMIN_ADMINS )
        return qfalse;
      a = G_Alloc( sizeof( g_admin_admin_t ) );
      *a->name = '\0';
      *a->guid = '\0';
      a->level = 0;
      *a->flags = '\0';
      a->seen = 0;
      admin_open = qtrue;
    }
    else if( !Q_stricmp( t, "[ban]" ) )
    {
      if( bc >= MAX_ADMIN_BANS )
        return qfalse;
      b = G_Alloc( sizeof( g_admin_ban_t ) );
      *b->name = '\0';
      *b->guid = '\0';
      *b->ip = '\0';
      *b->made = '\0';
      b->expires = 0;
      b->length = 0;
      b->suspend = 0;
      *b->suspendby = '\0';
      *b->reason = '\0';
      b->bannerlevel = 0;
      ban_open = qtrue;
    }
    else if( !Q_stricmp( t, "[command]" ) )
    {
      if( cc >= MAX_ADMIN_COMMANDS )
        return qfalse;
      c = G_Alloc( sizeof( g_admin_command_t ) );
      *c->command = '\0';
      *c->exec = '\0';
      *c->desc = '\0';
      *c->flag = '\0';
      command_open = qtrue;
    }
    t = COM_Parse( &cnf );
  }
  if( level_open )
  {

    g_admin_levels[ lc++ ] = l;
  }
  if( admin_open )
    g_admin_admins[ ac++ ] = a;
  if( ban_open )
    g_admin_bans[ bc++ ] = b;
  if( command_open )
    g_admin_commands[ cc++ ] = c;
  G_Free( cnf2 );
  ADMP( va( "^3!readconfig: ^7loaded %d levels, %d admins, %d bans, %d commands\n",
          lc, ac, bc, cc ) );
  if( lc == 0 )
    admin_default_levels();
  else
  {
    char n[ MAX_NAME_LENGTH ] = {""};
 
    // max printable name length for formatting 
    for( i = 0; i < MAX_ADMIN_LEVELS && g_admin_levels[ i ]; i++ )
    {
      G_DecolorString( g_admin_levels[ i ]->name, n );
      if( strlen( n ) > admin_level_maxname )
        admin_level_maxname = strlen( n );
    }
  }
  // reset adminLevel
  for( i = 0; i < level.maxclients; i++ )
    if( level.clients[ i ].pers.connected != CON_DISCONNECTED )
      level.clients[ i ].pers.adminLevel = G_admin_level( &g_entities[ i ] );
  return qtrue;
}

qboolean G_admin_time( gentity_t *ent, int skiparg )
{
  qtime_t qt;
  int     mins, seconds;
  int     msec;
  char    *pluralM, *pluralS;

  msec = level.time - level.startTime;

  seconds = msec / 1000;
  mins = seconds / 60;
  seconds -= mins * 60;

  trap_RealTime( &qt );
  ADMP( va( "^3!time: ^7local time is ^3%02i:%02i:%02i^7\n",
    qt.tm_hour, qt.tm_min, qt.tm_sec ) );

  pluralM = "s";
  pluralS = "s";

  if( mins == 1 ){ pluralM = ""; }
  if( seconds == 1 ){ pluralS = ""; }

  if( mins == 0 )
  {
    ADMP( va( "^3!time: ^7this match has been going on for ^3%i ^7seconds.\n", seconds ) );
  }
  else
  {
    ADMP( va( "^3!time: ^7this match has been going on for ^3%i ^7minute%s and ^3%i ^7second%s\n", mins, pluralM, seconds, pluralS ) );
  }

  if( g_suddenDeathTime.integer > 0 && !g_suddenDeath.integer )
  {
    ADMP( va( "^3!time: ^7sudden death will be at ^3%02i:00^7, in about ^3%i ^7minutes\n", 
      level.suddenDeathBeginTime / 60000, G_TimeTilSuddenDeath( ) / 60000 ) );
  }
  else if( g_suddenDeathTime.integer && g_suddenDeath.integer )
  {
    ADMP( va( "^3!time: ^7sudden death started at ^3%02i:00^7\n", 
      level.suddenDeathBeginTime / 60000 ) );
  }

  if( g_timelimit.integer > 0 )
  {
    ADMP( va( "^3!time: ^7timelimit is at ^3%02i:00^7\n", 
      g_timelimit.integer ) );
  }
    
  return qtrue;
}

static int G_admin_find_slot( gentity_t *ent, char *namearg, const char *command )
{
  char name[ MAX_NAME_LENGTH ];
  char testname[ MAX_NAME_LENGTH ];
  char *guid = NULL;
  int matches = 0;
  int id = -1;
  int i;
  qboolean numeric = qtrue;

  G_SanitiseString( namearg, name, sizeof( name ) );
  for( i = 0; i < sizeof( name ) && name[ i ] ; i++ )
  {
    if( !isdigit( name[ i ] ) )
    {
      numeric = qfalse;
      break;
    }
  }
  if( numeric )
  {
    id = atoi( name );

    if( id >= 0 && id < level.maxclients )
    {
      gentity_t *vic;

      vic = &g_entities[ id ];
      if( vic && vic->client && vic->client->pers.connected != CON_DISCONNECTED )
        return id;

      ADMP( va( "^3!%s:^7 no one connected by that slot number\n", command ) );
      return -1;
    }
    if( id >= MAX_CLIENTS && id < MAX_CLIENTS + MAX_ADMIN_ADMINS &&
        g_admin_admins[ id - MAX_CLIENTS ] )
    {
      return id;
    }

    ADMP( va( "^3!%s:^7 no match for slot or admin number %d\n", command, id ) );
    return -1;
  }

  for( i = 0; i < MAX_ADMIN_ADMINS && g_admin_admins[ i ] && matches < 2; i++ )
  {
    G_SanitiseString( g_admin_admins[ i ]->name, testname, sizeof( testname ) );
    if( strstr( testname, name ) )
    {
      id = i + MAX_CLIENTS;
      guid = g_admin_admins[ i ]->guid;
      matches++;
    }
  }
  for( i = 0; i < level.maxclients && matches < 2; i++ )
  {
    if( level.clients[ i ].pers.connected == CON_DISCONNECTED )
      continue;

    if( matches && guid && !Q_stricmp( level.clients[ i ].pers.guid, guid ) )
      continue;

    G_SanitiseString( level.clients[ i ].pers.netname, testname, sizeof( testname ) );
    if( strstr( testname, name ) )
    {
      id = i;
      matches++;
    }
  }

  if( matches == 0 )
  {
    ADMP( va( "^3!%s:^7 no match, use !listplayers or !listadmins to "
      "find an appropriate number to use instead of name.\n", command ) );
    return -1; 
  }

  if( matches == 1 )
    return id;

  ADMP( va( "^3!%s:^7 multiple matches, use the admin number instead:\n", command ) );
  admin_listadmins( ent, 0, name, 0 );

  return -1;
}

static int G_admin_find_admin_slot( gentity_t *ent, char *namearg, char *command, char *nick, int nick_len )
{
  gentity_t *vic;
  char *guid;
  int id;
  int i;

  if ( nick )
    nick[ 0 ] = '\0';

  id = G_admin_find_slot( ent, namearg, command );
  if( id < 0 )
    return -1;

  if( id < MAX_CLIENTS )
  {
    vic = &g_entities[ id ];
    guid = vic->client->pers.guid;
    for( i = 0; i < MAX_ADMIN_ADMINS && g_admin_admins[ i ]; i++ )
    {
      if( !Q_stricmp( guid, g_admin_admins[ i ]->guid ) )
      {
        id = i + MAX_CLIENTS;
        if( nick )
          Q_strncpyz( nick, vic->client->pers.netname, nick_len );
        break;
      }
    }
    if( id < MAX_CLIENTS )
    {
      ADMP( va( "^3!%s:^7 player is not !registered\n", command ) );
      return -1;
    }
  }

  id -= MAX_CLIENTS;
  if( nick && !nick[ 0 ] )
    Q_strncpyz( nick, g_admin_admins[ id ]->name, nick_len );

  return id;
}

qboolean G_admin_setlevel( gentity_t *ent, int skiparg )
{
  char lstr[ 11 ]; // 10 is max strlen() for 32-bit int
  char adminname[ MAX_NAME_LENGTH ] = {""};
  char testname[ MAX_NAME_LENGTH ] = {""};
  char guid[ 33 ];
  int l, i;
  gentity_t *vic = NULL;
  qboolean updated = qfalse;
  g_admin_admin_t *a;
  qboolean found = qfalse;
  int id = -1;

  if( G_SayArgc() < 3 + skiparg )
  {
    ADMP( "^3!setlevel: ^7usage: !setlevel [name|slot#] [level]\n" );
    return qfalse;
  }
  G_SayArgv( 1 + skiparg, testname, sizeof( testname ) );
  G_SayArgv( 2 + skiparg, lstr, sizeof( lstr ) );
  l = atoi( lstr );

  if( ent && l > ent->client->pers.adminLevel )
  {
    ADMP( "^3!setlevel: ^7you may not use !setlevel to set a level higher "
      "than your current level\n" );
    return qfalse;
  }

  // if admin is activated for the first time on a running server, we need
  // to ensure at least the default levels get created
  if( !ent && !g_admin_levels[ 0 ] )
    G_admin_readconfig(NULL, 0);

  for( i = 0; i < MAX_ADMIN_LEVELS && g_admin_levels[ i ]; i++ )
  {
    if( g_admin_levels[ i ]->level == l )
    {
      found = qtrue;
      break;
    }
  }
  if( !found )
  {
    ADMP( "^3!setlevel: ^7level is not defined\n" );
    return qfalse;
  }

  id = G_admin_find_slot( ent, testname, "setlevel" );
  if( id >=0 && id < MAX_CLIENTS )
  {
    vic = &g_entities[ id ];
    Q_strncpyz( adminname, vic->client->pers.netname, sizeof( adminname ) );
    Q_strncpyz( guid, vic->client->pers.guid, sizeof( guid ) );
  }
  else if( id >= MAX_CLIENTS && id < MAX_CLIENTS + MAX_ADMIN_ADMINS &&
    g_admin_admins[ id - MAX_CLIENTS ] )
  {
    Q_strncpyz( adminname, g_admin_admins[ id - MAX_CLIENTS ]->name,
      sizeof( adminname ) );
    Q_strncpyz( guid, g_admin_admins[ id - MAX_CLIENTS ]->guid,
      sizeof( guid ) );
    for( i = 0; i < level.maxclients; i++ )
    {
      if( level.clients[ i ].pers.connected == CON_DISCONNECTED )
        continue;
      if( !Q_stricmp( level.clients[ i ].pers.guid, guid ) )
      {
        vic = &g_entities[ i ];
        Q_strncpyz( adminname, vic->client->pers.netname, sizeof( adminname ) );
      }
    }
  }
  else
  {
    return qfalse;
  }

  if( !Q_stricmp( guid, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" ) )
  {
    ADMP( va( "^3!setlevel: ^7%s does not have a valid GUID\n", adminname ) );
    return qfalse;
  }
  if( ent && !admin_higher_guid( ent->client->pers.guid, guid ) )
  {
    ADMP( "^3!setlevel: ^7sorry, but your intended victim has a higher"
        " admin level than you\n" );
    return qfalse;
  }

  for( i = 0; i < MAX_ADMIN_ADMINS && g_admin_admins[ i ];i++ )
  {
    if( !Q_stricmp( g_admin_admins[ i ]->guid, guid ) )
    {
      g_admin_admins[ i ]->level = l;
      Q_strncpyz( g_admin_admins[ i ]->name, adminname,
                  sizeof( g_admin_admins[ i ]->name ) );
      updated = qtrue;
    }
  }
  if( !updated )
  {
    if( i == MAX_ADMIN_ADMINS )
    {
      ADMP( "^3!setlevel: ^7too many admins\n" );
      return qfalse;
    }
    a = G_Alloc( sizeof( g_admin_admin_t ) );
    a->level = l;
    Q_strncpyz( a->name, adminname, sizeof( a->name ) );
    Q_strncpyz( a->guid, guid, sizeof( a->guid ) );
    *a->flags = '\0';
    g_admin_admins[ i ] = a;
  }

  AP( va( 
    "print \"^3!setlevel: ^7%s^7 was given level %d admin rights by %s\n\"",
    adminname, l, G_admin_adminPrintName( ent ) ) );
  if( vic )
  {
    vic->client->pers.adminLevel = l;
    G_admin_set_adminname( vic );
  }
  
  if( !g_admin.string[ 0 ] )
    ADMP( "^3!setlevel: ^7WARNING g_admin not set, not saving admin record "
      "to a file\n" );
  else
    admin_writeconfig();
  return qtrue;
}

static int SortFlags( const void *pa, const void *pb )
{
  char *a = (char *)pa;
  char *b = (char *)pb;

  if( *a == '-' || *a == '+' )
    a++;
  if( *b == '-' || *b == '+' )
    b++;
  return strcmp(a, b);
}

#define MAX_USER_FLAGS 200
const char *G_admin_user_flag( char *oldflags, char *flag, qboolean add, qboolean clear,
                               char *newflags, int size )
{
  char *token, *token_p;
  char *key;
  char head_flags[ MAX_USER_FLAGS ][ MAX_ADMIN_FLAG_LEN ];
  char tail_flags[ MAX_USER_FLAGS ][ MAX_ADMIN_FLAG_LEN ];
  char allflag[ MAX_ADMIN_FLAG_LEN ];
  char newflag[ MAX_ADMIN_FLAG_LEN ];
  int head_count = 0;
  int tail_count = 0;
  qboolean flagset = qfalse;
  int i;

  if( !flag[ 0 ] )
  {
    return "invalid admin flag";
  }

  allflag[ 0 ] = '\0';
  token_p = oldflags;
  while( *( token = COM_Parse( &token_p ) ) )
  {
    key = token;
    if( *key == '-' || *key == '+' )
      key++;

    if( !strcmp( key, flag ) )
    {
      if( flagset )
        continue;
      flagset = qtrue;
      if( clear )
      {
        // clearing ALLFLAGS will result in clearing any following flags
        if( !strcmp( key, ADMF_ALLFLAGS ) )
          break;
        else
          continue;
      }
      Com_sprintf( newflag, sizeof( newflag ), "%s%s",
        ( add ) ? "+" : "-", key );
    }
    else
    {
      Q_strncpyz( newflag, token, sizeof( newflag ) );
    }

    if( !strcmp( key, ADMF_ALLFLAGS ) )
    {
      if( !allflag[ 0 ] )
        Q_strncpyz( allflag, newflag, sizeof( allflag ) );
      continue;
    }

    if( !allflag[ 0 ] )
    {
      if( head_count < MAX_USER_FLAGS )
      {
        Q_strncpyz( head_flags[ head_count ], newflag,
                    sizeof( head_flags[ head_count ] ) );
        head_count++;
      }
    }
    else
    {
      if( tail_count < MAX_USER_FLAGS )
      {
        Q_strncpyz( tail_flags[ tail_count ], newflag,
                    sizeof( tail_flags[ tail_count ] ) );
        tail_count++;
      }
    }
  }

  if( !flagset && !clear )
  {
    if( !strcmp( flag, ADMF_ALLFLAGS ) )
    {
      Com_sprintf( allflag, sizeof( allflag ), "%s%s",
        ( add ) ? "" : "-", ADMF_ALLFLAGS );
    }
    else if( !allflag[ 0 ] )
    {
      if( head_count < MAX_USER_FLAGS )
      {
        Com_sprintf( head_flags[ head_count ], sizeof( head_flags[ head_count ] ),
          "%s%s", ( add ) ? "" : "-", flag );
        head_count++;
      }
    }
    else
    {
      if( tail_count < MAX_USER_FLAGS )
      {
        Com_sprintf( tail_flags[ tail_count ], sizeof( tail_flags[ tail_count ] ),
          "%s%s", ( add ) ? "+" : "-", flag );
        tail_count++;
      }
    }
  }

  qsort( head_flags, head_count, sizeof( head_flags[ 0 ] ), SortFlags );
  qsort( tail_flags, tail_count, sizeof( tail_flags[ 0 ] ), SortFlags );

  // rebuild flags
  newflags[ 0 ] = '\0';
  for( i = 0; i < head_count; i++ )
  {
    Q_strcat( newflags, size,
              va( "%s%s", ( i ) ? " ": "", head_flags[ i ] ) );
  }
  if( allflag[ 0 ] )
  {
    Q_strcat( newflags, size,
      va( "%s%s", ( newflags[ 0 ] ) ? " ": "", allflag ) );

    for( i = 0; i < tail_count; i++ )
    {
      Q_strcat( newflags, size,
                va( " %s", tail_flags[ i ] ) );
    }
  }

  return NULL;
}

typedef struct {
  char *flag;
  char *description;
} AdminFlagListEntry_t;
static AdminFlagListEntry_t adminFlagList[] =
{
  { ADMF_ACTIVITY,             "inactivity rules do not apply" },
  { ADMF_ADMINCHAT,            "can see and use admin chat" },
  { ADMF_HIGHADMINCHAT,        "can see and use high admin chat" },
  { ADMF_ALLFLAGS,             "has all flags and can use any command" },
  { ADMF_BAN_IMMUNITY,         "immune from IP bans" },
  { ADMF_CAN_PERM_BAN,         "can permanently ban players" },
  { ADMF_DBUILDER,             "permanent designated builder" },
  { ADMF_FORCETEAMCHANGE,      "team balance rules do not apply" },
  { ADMF_INCOGNITO,            "does not show as admin in !listplayers" },
  { ADMF_SEESINCOGNITO,        "sees registered name of players flagged with INCOGNITO" },
  { ADMF_IMMUNITY,             "cannot be vote kicked or muted" },
  { ADMF_IMMUTABLE,            "admin commands cannot be used on them" },
  { ADMF_NOCENSORFLOOD,        "no flood protection" },
  { ADMF_NO_VOTE_LIMIT,        "vote limitations do not apply" },
  { ADMF_SEESFULLLISTPLAYERS,  "sees all info in !listplayers" },
  { ADMF_SPEC_ALLCHAT,         "can see team chat as spectator" },
  { ADMF_ADMINSTEALTH,         "uses admin stealth" },
  { ADMF_ADMINSUPERSTEALTH,    "uses admin 'super' stealth" },
  { ADMF_TEAMCHANGEFREE,       "keeps credits on team switch" },
  { ADMF_TEAMCHAT_CMD,         "can run commands from team chat" },
  { ADMF_UNACCOUNTABLE,        "does not need to specify reason for kick/ban" },
  { ADMF_NOSCRIMRESTRICTION,   "team joining, vote and chat restrictions during scrims do not apply" },
  { ADMF_NO_BUILD,             "can not build" },
  { ADMF_NO_CHAT,              "can not talk" },
  { ADMF_NO_VOTE,              "can not call votes" },
  { ADMF_NOAUTOBAHN,           "ignored by the Autobahn system" }
};
static int adminNumFlags= sizeof( adminFlagList ) / sizeof( adminFlagList[ 0 ] );

#define MAX_LISTCOMMANDS 128
qboolean G_admin_flaglist( gentity_t *ent, int skiparg )
{
  qboolean shown[ MAX_LISTCOMMANDS ];
  int i, j;
  int count = 0;

  ADMBP_begin();

  ADMBP( "^3Ability flags:\n" );

  for( i = 0; i < adminNumFlags; i++ )
  {
    ADMBP( va( "  %s%-20s ^7%s\n",
      ( adminFlagList[ i ].flag[ 0 ] != '.' ) ? "^5" : "^1",
      adminFlagList[ i ].flag,
      adminFlagList[ i ].description ) );
  }

  ADMBP( "^3Command flags:\n" );

  memset( shown, 0, sizeof( shown ) );
  for( i = 0; i < adminNumCmds; i++ )
  {
    if( i < MAX_LISTCOMMANDS && shown[ i ] )
      continue;
    ADMBP( va( "  ^5%-20s^7", g_admin_cmds[ i ].flag ) );
    for( j = i; j < adminNumCmds; j++ )
    {
      if( !strcmp( g_admin_cmds[ j ].flag, g_admin_cmds[ i ].flag ) )
      {
        ADMBP( va( " %s", g_admin_cmds[ j ].keyword ) );
        if( j < MAX_LISTCOMMANDS )
          shown[ j ] = qtrue;
      }
    }
    ADMBP( "\n" );
    count++;
  }

  ADMBP( va( "^3!flaglist: ^7listed %d abilities and %d command flags\n",
    adminNumFlags, count ) );

  ADMBP_end();

  return qtrue;
}

qboolean G_admin_flag( gentity_t *ent, int skiparg )
{
  char command[ MAX_ADMIN_CMD_LEN ], *cmd;
  char name[ MAX_NAME_LENGTH ];
  char flagbuf[ MAX_ADMIN_FLAG_LEN ];
  char *flag;
  int id;
  char adminname[ MAX_NAME_LENGTH ] = {""};
  const char *result;
  qboolean add = qtrue;
  qboolean clear = qfalse;
  int admin_level = -1;
  int i, level;

  G_SayArgv( skiparg, command, sizeof( command ) );
  cmd = command;
  if( *cmd == '!' )
    cmd++;

  if( G_SayArgc() < 2 + skiparg )
  {
    ADMP( va( "^3!%s: ^7usage: !%s slot# flag\n", cmd, cmd ) );
    return qfalse;
  }

  G_SayArgv( 1 + skiparg, name, sizeof( name ) );
  if( name[ 0 ] == '*' )
  {
    if( ent )
    {
      ADMP( va( "^3!%s: only console can change admin level flags\n", cmd ) );
      return qfalse;
    }
    id = atoi( name + 1 );
    for( i = 0; i < MAX_ADMIN_LEVELS && g_admin_levels[ i ]; i++ )
    {
      if( g_admin_levels[ i ]->level == id )
      {
        admin_level = i;
        break;
      }
    }
    if( admin_level < 0 )
    {
      ADMP( va( "^3!%s: admin level %d does not exist\n", cmd, id ) );
      return qfalse;
    }
    Com_sprintf( adminname, sizeof( adminname ), "admin level %d", id );
  }
  else
  {
    id = G_admin_find_admin_slot( ent, name, cmd, adminname, sizeof( adminname ) );
    if( id < 0 )
      return qfalse;

    if( ent && !admin_higher_guid( ent->client->pers.guid, g_admin_admins[ id ]->guid ) )
    {
      ADMP( va( "^3%s:^7 your intended victim has a higher admin level than you\n", cmd ) );
      return qfalse;
    }
  }

  if( G_SayArgc() < 3 + skiparg )
  {
    flag = "";
    level = 0;
    if( admin_level < 0 )
    {
      for( i = 0; i < MAX_ADMIN_LEVELS && g_admin_levels[ i ]; i++ )
      {
        if( g_admin_admins[ id ]->level == g_admin_levels[ i ]->level )
        {
          flag = g_admin_levels[ i ]->flags;
          level = g_admin_admins[ id ]->level;
          break;
        }
      }
      ADMP( va( "^3%s:^7 flags for %s^7 are '^3%s^7'\n",
        cmd, adminname, g_admin_admins[ id ]->flags) );
    }
    else
    {
      flag = g_admin_levels[ admin_level ]->flags;
      level = g_admin_levels[ admin_level ]->level;
    }
    ADMP( va( "^3%s:^7  level %d flags are '%s'\n",
      cmd, level, flag ) );

    return qtrue;
  }

  G_SayArgv( 2 + skiparg, flagbuf, sizeof( flagbuf ) );
  flag = flagbuf;
  if( flag[ 0 ] == '-' || flag[ 0 ] == '+' )
  {
    add = ( flag[ 0 ] == '+' );
    flag++;
  }
  if( ent && !Q_stricmp( ent->client->pers.guid, g_admin_admins[ id ]->guid ) )
  {
    ADMP( va( "^3%s:^7 you may not change your own flags (use rcon)\n", cmd ) );
    return qfalse;
  }
  if( flag[ 0 ] != '.' && !G_admin_permission( ent, flag ) )
  {
    ADMP( va( "^3%s:^7 you can only change flags that you also have\n", cmd ) );
    return qfalse;
  }

  if( !Q_stricmp( cmd, "unflag" ) )
  {
    clear = qtrue;
  }

  if( admin_level < 0 )
  {
    result = G_admin_user_flag( g_admin_admins[ id ]->flags, flag, add, clear,
                                g_admin_admins[ id ]->flags, sizeof( g_admin_admins[ id ]->flags ) );
  }
  else
  {
    result = G_admin_user_flag( g_admin_levels[ admin_level ]->flags, flag, add, clear,
                                g_admin_levels[ admin_level ]->flags,
                                sizeof( g_admin_levels[ admin_level ]->flags ) );
  }
  if( result )
  {
    ADMP( va( "^3!flag: ^7an error occured setting flag '^3%s^7', %s\n",
      flag, result ) );
    return qfalse;
  }

  if( !Q_stricmp( cmd, "flag" ) )
  {
    G_AdminsPrintf( "^3!%s: ^7%s^7 was %s admin flag '%s' by %s\n",
      cmd, adminname,
      ( add ) ? "given" : "denied",
      flag,
      G_admin_adminPrintName( ent ) );
  }
  else
  {
    G_AdminsPrintf( "^3!%s: ^7admin flag '%s' for %s^7 cleared by %s\n",
      cmd, flag, adminname,
      G_admin_adminPrintName( ent ) );
  }

  if( !g_admin.string[ 0 ] )
    ADMP( va( "^3!%s: ^7WARNING g_admin not set, not saving admin record "
      "to a file\n", cmd ) );
  else
    admin_writeconfig();

  return qtrue;
}

int G_admin_parse_time( const char *time )
{
  int seconds = 0, num = 0;
  int i;
  for( i = 0; time[ i ]; i++ )
  {
    if( isdigit( time[ i ] ) )
    {
      num = num * 10 + time[ i ] - '0';
      continue;
    }
    if( i == 0 || !isdigit( time[ i - 1 ] ) )
      return -1;
    switch( time[ i ] )
    {
      case 'w': num *= 7;
      case 'd': num *= 24;
      case 'h': num *= 60;
      case 'm': num *= 60;
      case 's': break;
      default:  return -1;
    }
    seconds += num;
    num = 0;
  }
  if( num )
    seconds += num;
  // overflow
  if( seconds < 0 )
    seconds = 0;
  return seconds;
}

static qboolean admin_create_ban( gentity_t *ent,
  char *netname,
  char *guid,
  char *ip,
  int seconds,
  char *reason ) 
{
  g_admin_ban_t *b = NULL;
  qtime_t qt;
  int t;
  int i;

  t = trap_RealTime( &qt );
  b = G_Alloc( sizeof( g_admin_ban_t ) );

  if( !b )
    return qfalse;

  Q_strncpyz( b->name, netname, sizeof( b->name ) );
  Q_strncpyz( b->guid, guid, sizeof( b->guid ) );
  Q_strncpyz( b->ip, ip, sizeof( b->ip ) );
  b->suspend = 0;
  Q_strncpyz( b->suspendby, "", sizeof( b->suspendby ) );

  //strftime( b->made, sizeof( b->made ), "%m/%d/%y %H:%M:%S", lt );
  Q_strncpyz( b->made, va( "%02i/%02i/%02i %02i:%02i:%02i",
    (qt.tm_mon + 1), qt.tm_mday, (qt.tm_year - 100),
    qt.tm_hour, qt.tm_min, qt.tm_sec ),
    sizeof( b->made ) );

  Q_strncpyz( b->banner, G_admin_get_adminname( ent ), sizeof( b->banner ) );

  if( ent )
    b->bannerlevel = G_admin_level( ent );
  else
    b->bannerlevel = 0;

  if( !seconds )
  {
    b->expires = 0;
    b->length = 0;
  }
  else
  {
    b->expires = t + seconds;
    b->length = seconds;
  }

  if( !*reason )
    Q_strncpyz( b->reason, "banned by admin", sizeof( b->reason ) );
  else
    Q_strncpyz( b->reason, reason, sizeof( b->reason ) );
  for( i = 0; i < MAX_ADMIN_BANS && g_admin_bans[ i ]; i++ )
    ;
  if( i == MAX_ADMIN_BANS )
  {
    ADMP( "^3!ban: ^7too many bans\n" );
    G_Free( b );
    return qfalse;
  }
  g_admin_bans[ i ] = b;
  return qtrue;
}

qboolean G_admin_kick( gentity_t *ent, int skiparg )
{
  int pids[ MAX_CLIENTS ];
  char name[ MAX_NAME_LENGTH ], *reason, err[ MAX_STRING_CHARS ];
  int minargc;
  gentity_t *vic;
  char notice[51];
  
  trap_Cvar_VariableStringBuffer( "g_banNotice", notice, sizeof( notice ) );

  minargc = 3 + skiparg;
  if( G_admin_permission( ent, ADMF_UNACCOUNTABLE ) )
    minargc = 2 + skiparg;

  if( G_SayArgc() < minargc )
  {
    ADMP( "^3!kick: ^7usage: !kick [name] [reason]\n" );
    return qfalse;
  }
  G_SayArgv( 1 + skiparg, name, sizeof( name ) );
  reason = G_SayConcatArgs( 2 + skiparg );
  if( G_ClientNumbersFromString( name, pids ) != 1 )
  {
    G_MatchOnePlayer( pids, err, sizeof( err ) );
    ADMP( va( "^3!kick: ^7%s\n", err ) );
    return qfalse;
  }
  if( !admin_higher( ent, &g_entities[ pids[ 0 ] ] ) )
  {
    ADMP( "^3!kick: ^7sorry, but your intended victim has a higher admin"
        " level than you\n" );
    return qfalse;
  }
  vic = &g_entities[ pids[ 0 ] ];
  admin_create_ban( ent,
    vic->client->pers.netname,
    vic->client->pers.guid,
    vic->client->pers.ip, G_admin_parse_time( g_adminTempBan.string ),
    ( *reason ) ? reason : "kicked by admin" );
  if( g_admin.string[ 0 ] )
    admin_writeconfig();

  trap_SendServerCommand( pids[ 0 ],
    va( "disconnect \"You have been kicked.\n%s^7\nreason:\n%s\n%s\"",
      ( ent ) ? va( "admin:\n%s", G_admin_adminPrintName( ent ) ) : "admin\nconsole",
      ( *reason ) ? reason : "kicked by admin", notice ) );

  AP( va( "print \"^3!kick: ^7%s ^7was kicked by %s^7, reason: %s\n\"",
    vic->client->pers.netname,
    G_admin_adminPrintName( ent ),
    ( *reason ) ? reason : "kicked by admin" ) );

  return qtrue;
}

qboolean G_admin_ban( gentity_t *ent, int skiparg )
{
  int seconds;
  char search[ MAX_NAME_LENGTH ];
  char secs[ 7 ];
  char *reason;
  int minargc;
  char duration[ 32 ];
  int logmatch = -1, logmatches = 0;
  int i, j;
  qboolean exactmatch = qfalse;
  char n2[ MAX_NAME_LENGTH ];
  char s2[ MAX_NAME_LENGTH ];
  char guid_stub[ 9 ];
  char notice[51];
  
  trap_Cvar_VariableStringBuffer( "g_banNotice", notice, sizeof( notice ) );
  
  if( G_admin_permission( ent, ADMF_CAN_PERM_BAN ) &&
       G_admin_permission( ent, ADMF_UNACCOUNTABLE ) )
  {
    minargc = 2 + skiparg;
  }
  else if( ( G_admin_permission( ent, ADMF_CAN_PERM_BAN ) || g_adminMaxBan.integer ) ||
            G_admin_permission( ent, ADMF_UNACCOUNTABLE ) )
  {
    minargc = 3 + skiparg;
  }
  else
  {
    minargc = 4 + skiparg;
  }
  if( G_SayArgc() < minargc )
  {
    ADMP( "^3!ban: ^7usage: !ban [name|slot|ip] [time] [reason]\n" );
    return qfalse;
  }
  G_SayArgv( 1 + skiparg, search, sizeof( search ) );
  G_SanitiseString( search, s2, sizeof( s2 ) );
  G_SayArgv( 2 + skiparg, secs, sizeof( secs ) );

  seconds = G_admin_parse_time( secs );
  if( seconds <= 0 )
  {
    if( g_adminMaxBan.integer && !G_admin_permission( ent, ADMF_CAN_PERM_BAN ) )
    {
      ADMP( va( "^3!ban: ^7using your admin level's maximum ban length of %s\n",
        g_adminMaxBan.string ) );
      seconds = G_admin_parse_time( g_adminMaxBan.string );
    }
    else if( G_admin_permission( ent, ADMF_CAN_PERM_BAN ) )
    {
      seconds = 0;
    }
    else
    {
      ADMP( "^3!ban: ^7ban time must be positive\n" );
      return qfalse;
    }
    reason = G_SayConcatArgs( 2 + skiparg );
  }
  else
  {
    reason = G_SayConcatArgs( 3 + skiparg );

    if( g_adminMaxBan.integer &&
        seconds > G_admin_parse_time( g_adminMaxBan.string ) &&
        !G_admin_permission( ent, ADMF_CAN_PERM_BAN ) )
    {
      seconds = G_admin_parse_time( g_adminMaxBan.string );
      ADMP( va( "^3!ban: ^7ban length limited to %s for your admin level\n",
        g_adminMaxBan.string ) );
    }
  }

  for( i = 0; i < MAX_ADMIN_NAMELOGS && g_admin_namelog[ i ]; i++ )
  {
    // skip players in the namelog who have already been banned
    if( g_admin_namelog[ i ]->banned )
      continue;

    // skip disconnected players when banning on slot number
    if( g_admin_namelog[ i ]->slot == -1 )
      continue;

    if( !Q_stricmp( va( "%d", g_admin_namelog[ i ]->slot ), s2 ) )
    {
      logmatches = 1;
      logmatch = i;
      exactmatch = qtrue;
      break;
    }
  } 

  for( i = 0;
       !exactmatch && i < MAX_ADMIN_NAMELOGS && g_admin_namelog[ i ];
       i++ )
  {
    // skip players in the namelog who have already been banned
    if( g_admin_namelog[ i ]->banned )
      continue;

    if( !Q_stricmp( g_admin_namelog[ i ]->ip, s2 ) )
    {
      logmatches = 1;
      logmatch = i;
      exactmatch = qtrue;
      break;
    }
    for( j = 0; j < MAX_ADMIN_NAMELOG_NAMES
      && g_admin_namelog[ i ]->name[ j ][ 0 ]; j++ )
    {
      G_SanitiseString(g_admin_namelog[ i ]->name[ j ], n2, sizeof( n2 ) );
      if( strstr( n2, s2 ) )
      {
        if( logmatch != i )
          logmatches++;
        logmatch = i; 
      }
    }
  }
  
  if( !logmatches ) 
  {
    ADMP( "^3!ban: ^7no player found by that name, IP, or slot number\n" );
    return qfalse;
  } 
  else if( logmatches > 1 )
  {
    ADMBP_begin();
    ADMBP( "^3!ban: ^7multiple recent clients match name, use IP or slot#:\n" );
    for( i = 0; i < MAX_ADMIN_NAMELOGS && g_admin_namelog[ i ]; i++ )
    {
      for( j = 0; j < 8; j++ )
        guid_stub[ j ] = g_admin_namelog[ i ]->guid[ j + 24 ];
      guid_stub[ j ] = '\0';
      for( j = 0; j < MAX_ADMIN_NAMELOG_NAMES
        && g_admin_namelog[ i ]->name[ j ][ 0 ]; j++ )
      {
        G_SanitiseString(g_admin_namelog[ i ]->name[ j ], n2, sizeof( n2 ) );
        if( strstr( n2, s2 ) )
        {
          if( g_admin_namelog[ i ]->slot > -1 )
            ADMBP( "^3" );
          ADMBP( va( "%-2s (*%s) %15s ^7'%s^7'\n",
           (g_admin_namelog[ i ]->slot > -1) ?
             va( "%d", g_admin_namelog[ i ]->slot ) : "-",
           guid_stub,
           g_admin_namelog[ i ]->ip,
           g_admin_namelog[ i ]->name[ j ] ) );
        }
      }
    }
    ADMBP_end();
    return qfalse;
  }
  
  G_admin_duration( ( seconds ) ? seconds : -1,
    duration, sizeof( duration ) );

  if( ent && !admin_higher_guid( ent->client->pers.guid,
    g_admin_namelog[ logmatch ]->guid ) )
  {

    ADMP( "^3!ban: ^7sorry, but your intended victim has a higher admin"
      " level than you\n" );
    return qfalse;
  }

  admin_create_ban( ent,
    g_admin_namelog[ logmatch ]->name[ 0 ],
    g_admin_namelog[ logmatch ]->guid,
    g_admin_namelog[ logmatch ]->ip,
    seconds, reason ); 

  g_admin_namelog[ logmatch ]->banned = qtrue;

  if( !g_admin.string[ 0 ] )
    ADMP( "^3!ban: ^7WARNING g_admin not set, not saving ban to a file\n" );
  else
    admin_writeconfig();

  if( g_admin_namelog[ logmatch ]->slot == -1 ) 
  {
    // client is already disconnected so stop here
    AP( va( "print \"^3!ban:^7 %s^7 has been banned by %s^7 "
      "duration: %s, reason: %s\n\"",
      g_admin_namelog[ logmatch ]->name[ 0 ],
      G_admin_adminPrintName( ent ),
      duration,
      ( *reason ) ? reason : "banned by admin" ) );
    return qtrue;
  }
  
  trap_SendServerCommand( g_admin_namelog[ logmatch ]->slot,
    va( "disconnect \"You have been banned.\n"
      "admin:\n%s^7\nduration:\n%s\nreason:\n%s\n%s\"",
      G_admin_adminPrintName( ent ),
      duration,
      ( *reason ) ? reason : "banned by admin", notice ) );

  AP( va( "print \"^3!ban: ^7%s ^7was banned by %s^7, duration: %s, reason: %s\n\"",
    g_admin_namelog[ logmatch ]->name[ 0 ],
    G_admin_adminPrintName( ent ),
    duration,
    ( *reason ) ? reason : "banned by admin" ) );

  return qtrue;
}

// If true then don't let the player join a team, use the chat or run commands.
qboolean G_admin_is_restricted(gentity_t *ent, qboolean sendMessage)
{
	schachtmeisterJudgement_t *j = NULL;
	int i;

	// Never restrict admins or whitelisted players.
	if (G_admin_permission(ent, ADMF_NOAUTOBAHN) ||
	    G_admin_permission(ent, ADMF_IMMUNITY))
		return qfalse;

	// Find the relevant namelog.
	// FIXME: this shouldn't require looping over *all* namelogs.
	for (i = 0; i < MAX_ADMIN_NAMELOGS && g_admin_namelog[i]; i++) {
		if (g_admin_namelog[i]->slot == ent - g_entities) {
			j = &g_admin_namelog[i]->smj;
			break;
		}
	}

	// A missing namelog shouldn't happen.
	if (!j)
		return qfalse;

	// Restrictions concern only unrated players.
	if (j->ratingTime)
		return qfalse;

	// Don't wait forever, allow up to 15 seconds.
	if (level.time - j->queryTime >= 15000)
		return qfalse;

	if (sendMessage)
		trap_SendServerCommand(ent - g_entities, "print \"Please wait a moment before doing anything.\n\"");

	return qtrue;
}

static void admin_autobahn(gentity_t *ent, int rating)
{
	// Allow per-GUID exceptions and never autoban admins.
	if (G_admin_permission(ent, ADMF_NOAUTOBAHN) ||
	    G_admin_permission(ent, ADMF_IMMUNITY))
		return;

	// Don't do anything if the rating is clear.
	if (rating >= g_schachtmeisterClearThreshold.integer)
		return;

	// Ban only if the rating is low enough.
	if (rating > g_schachtmeisterAutobahnThreshold.integer) {
		G_AdminsPrintf("%s^7 (#%d) has rating %d\n",
		               ent->client->pers.netname, ent - g_entities,
		               rating);
		return;
	}

	G_LogAutobahn(ent, NULL, rating, qfalse);

	trap_SendServerCommand(ent - g_entities, va("disconnect \"%s\"\n",
	                       g_schachtmeisterAutobahnMessage.string));
	trap_DropClient(ent - g_entities, "dropped by the Autobahn");
}

void G_admin_IPA_judgement( const char *ipa, int rating, const char *comment )
{
  int i;
  for( i = 0; i < MAX_ADMIN_NAMELOGS && g_admin_namelog[ i ]; i++ )
  {
    if( !strcmp( g_admin_namelog[ i ]->ip, ipa ) )
    {
      schachtmeisterJudgement_t *j = &g_admin_namelog[ i ]->smj;

      j->ratingTime = level.time;
      j->queryTime = 0;
      j->dispatchTime = 0;

      j->rating = rating;

      if( j->comment )
        G_Free( j->comment );

      if( comment )
      {
        j->comment = G_Alloc( strlen( comment ) + 1 );
        strcpy( j->comment, comment );
      }
      else
        j->comment = NULL;

      if( g_admin_namelog[ i ]->slot != -1 )
        admin_autobahn( g_entities + g_admin_namelog[ i ]->slot, j->rating );
    }
  }
}

qboolean G_admin_adjustban( gentity_t *ent, int skiparg )
{
  int bnum;
  int length;
  int expires;
  int time = trap_RealTime( NULL );
  char duration[ 32 ] = {""};
  char *reason;
  char bs[ 5 ];
  char secs[ MAX_TOKEN_CHARS ];
  char mode = '\0';

  if( G_SayArgc() < 3 + skiparg )
  {
    ADMP( "^3!adjustban: ^7usage: !adjustban [ban#] [time] [reason]\n" );
    return qfalse;
  }
  G_SayArgv( 1 + skiparg, bs, sizeof( bs ) );
  bnum = atoi( bs );
  if( bnum < 1 || bnum > MAX_ADMIN_BANS || !g_admin_bans[ bnum - 1] )
  {
    ADMP( "^3!adjustban: ^7invalid ban#\n" );
    return qfalse;
  }
  if( g_admin_bans[ bnum - 1 ]->expires == 0 &&
      !G_admin_permission( ent, ADMF_CAN_PERM_BAN ) )
  {
    ADMP( "^3!adjustban: ^7you cannot modify permanent bans\n" );
    return qfalse;
  }
  if( g_admin_bans[ bnum - 1 ]->bannerlevel > G_admin_level( ent ) )
  {
    ADMP( "^3!adjustban: ^7you cannot modify Bans made by admins higher than you\n" );
    return qfalse;
  }
  if( g_adminMaxBan.integer &&
      !G_admin_permission( ent, ADMF_CAN_PERM_BAN ) &&
      g_admin_bans[ bnum - 1 ]->expires - time > G_admin_parse_time( g_adminMaxBan.string ) )
  {
    ADMP( va( "^3!adjustban: ^7your admin level cannot modify bans longer than %s\n",
              g_adminMaxBan.string ) );
    return qfalse;
  }
  G_SayArgv( 2 + skiparg, secs, sizeof( secs ) );
  if( secs[ 0 ] == '+' || secs[ 0 ] == '-' )
    mode = secs[ 0 ];
  length = G_admin_parse_time( &secs[ mode ? 1 : 0 ] );
  if( length < 0 )
    skiparg--;
  else
  {
    if( length )
    {
      if( g_admin_bans[ bnum - 1 ]->expires == 0 && mode )
      {
        ADMP( "^3!adjustban: ^7new duration must be explicit\n" );
        return qfalse;
      }
      if( mode == '+' )
        expires = g_admin_bans[ bnum - 1 ]->expires + length;
      else if( mode == '-' )
        expires = g_admin_bans[ bnum - 1 ]->expires - length;
      else
        expires = time + length;
      if( expires <= time )
      {
        ADMP( "^3!adjustban: ^7ban time must be positive\n" );
        return qfalse;
      }
      if( g_adminMaxBan.integer &&
          !G_admin_permission( ent, ADMF_CAN_PERM_BAN ) &&
          expires - time > G_admin_parse_time( g_adminMaxBan.string ) )
      {
        ADMP( va( "^3!adjustban: ^7ban length is limited to %s for your admin level\n",
                  g_adminMaxBan.string ) );
        length = G_admin_parse_time( g_adminMaxBan.string );
        expires = time + length;
      }
    }
    else if( G_admin_permission( ent, ADMF_CAN_PERM_BAN ) )
      expires = 0;
    else
    {
      ADMP( "^3!adjustban: ^7ban time must be positive\n" );
      return qfalse;
    }

    g_admin_bans[ bnum - 1 ]->expires = expires;
    g_admin_bans[ bnum - 1 ]->length = length;
    G_admin_duration( ( expires ) ? expires - time : -1,
      duration, sizeof( duration ) );
  }
  reason = G_SayConcatArgs( 3 + skiparg );
  if( *reason )
    Q_strncpyz( g_admin_bans[ bnum - 1 ]->reason, reason,
      sizeof( g_admin_bans[ bnum - 1 ]->reason ) );
  AP( va( "print \"^3!adjustban: ^7ban #%d for %s^7 has been updated by %s^7 "
    "%s%s%s%s%s\n\"",
    bnum,
    g_admin_bans[ bnum - 1 ]->name,
    G_admin_adminPrintName( ent ),
    ( length >= 0 ) ? "duration: " : "",
    duration,
    ( length >= 0 && *reason ) ? ", " : "",
    ( *reason ) ? "reason: " : "",
    reason ) );
  if( ent ) {
    Q_strncpyz( g_admin_bans[ bnum - 1 ]->banner, G_admin_get_adminname( ent ),
      sizeof( g_admin_bans[ bnum - 1 ]->banner ) );
    g_admin_bans[ bnum - 1 ]->bannerlevel = G_admin_level( ent );
  }

  if( g_admin.string[ 0 ] )
    admin_writeconfig();
  return qtrue;
}


qboolean G_admin_subnetban( gentity_t *ent, int skiparg )
{
  int bnum;
  int mask;
  unsigned int IPRlow = 0, IPRhigh = 0;
  char cIPRlow[ 32 ], cIPRhigh[ 32 ];
  char bs[ 5 ];
  char strmask[ 5 ];
  char exl[2];
  int k, IP[5];
  
  if( G_SayArgc() < 3 + skiparg )
  {
    ADMP( "^3!subnetban: ^7usage: !subnetban [ban#] [mask]\n" );
    return qfalse;
  }
  G_SayArgv( 1 + skiparg, bs, sizeof( bs ) );
  bnum = atoi( bs );
  if( bnum < 1 || bnum > MAX_ADMIN_BANS || !g_admin_bans[ bnum - 1] )
  {
    ADMP( "^3!subnetban: ^7invalid ban#\n" );
    return qfalse;
  }
  if( g_admin_bans[ bnum - 1 ]->bannerlevel > G_admin_level( ent ) )
  {
    ADMP( "^3!subnetban: ^7you cannot subnetban Bans on bans made by admins higher than you\n" );
    return qfalse;
  }

  G_SayArgv( 2 + skiparg, strmask, sizeof( strmask ) );
  mask = atoi( strmask );
  
  if( mask >= 0 && mask <= 32)
  {
    G_SayArgv( 3 + skiparg, exl, sizeof( exl ) );
    if( mask >= 0 && mask < 16 )
    {
      if( ent )
      {
        ADMP( "^3!subnetban: ^7Only console may ban such a large network. Regular admins may only ban >=16.\n" );
        return qfalse;
      }
      if( strcmp(exl, "!") )
      {
        ADMP( "^3!subnetban: ^1WARNING:^7 you are about to ban a large network, use !subnetban [ban] [mask] ! to force^7\n" );
        return qfalse;
      }
    }

    memset( IP, 0, sizeof( IP ) );
    sscanf(g_admin_bans[ bnum - 1 ]->ip, "%d.%d.%d.%d/%d", &IP[4], &IP[3], &IP[2], &IP[1], &IP[0]);
    for(k = 4; k >= 1; k--)
    {
      if( IP[k] )
        IPRlow |= IP[k] << 8*(k-1);
    }
    IPRhigh = IPRlow;
    if( mask == 32 )
    {
      Q_strncpyz( 
        g_admin_bans[ bnum - 1 ]->ip, 
        va("%i.%i.%i.%i", IP[4], IP[3], IP[2], IP[1]), 
        sizeof( g_admin_bans[ bnum - 1 ]->ip ) 
      );
    }
    else
    {
      Q_strncpyz( 
        g_admin_bans[ bnum - 1 ]->ip, 
        va("%i.%i.%i.%i/%i", IP[4], IP[3], IP[2], IP[1], mask ), 
        sizeof( g_admin_bans[ bnum - 1 ]->ip )
      );
      IPRlow &= ~((1 << (32-mask)) - 1);
      IPRhigh |= ((1 << (32-mask)) - 1);
    }
  }
  else
  {
    ADMP( "^3!subnetban: ^7mask is out of range, please use 0-32 inclusive\n" );
    return qfalse;
  }
  if( mask > 0 )
  {
    Q_strncpyz( 
      cIPRlow, 
      va("%u.%u.%u.%u", (IPRlow & (255 << 24)) >> 24, (IPRlow & (255 << 16)) >> 16, (IPRlow & (255 << 8)) >> 8, IPRlow & 255), 
      sizeof( cIPRlow ) 
    );
    Q_strncpyz( 
      cIPRhigh, 
      va("%u.%u.%u.%u", (IPRhigh & (255 << 24)) >> 24, (IPRhigh & (255 << 16)) >> 16, (IPRhigh & (255 << 8)) >> 8, IPRhigh & 255), 
      sizeof( cIPRhigh ) 
    );
  }
  else
  {
    Q_strncpyz( cIPRlow, "0.0.0.0", sizeof( cIPRlow ) );
    Q_strncpyz( cIPRhigh, "255.255.255.255", sizeof( cIPRhigh ) );
    
  }
  
  AP( va( "print \"^3!subnetban: ^7ban #%d for %s^7 has been updated by %s^7 "
    "%s (%s - %s)\n\"",
    bnum,
    g_admin_bans[ bnum - 1 ]->name,
    G_admin_adminPrintName( ent ),
    g_admin_bans[ bnum - 1 ]->ip,
    cIPRlow,
    cIPRhigh) );
  if( ent )
    Q_strncpyz( g_admin_bans[ bnum - 1 ]->banner, G_admin_get_adminname( ent ),
      sizeof( g_admin_bans[ bnum - 1 ]->banner ) );
  if( g_admin.string[ 0 ] )
    admin_writeconfig();
  return qtrue;
}

qboolean G_admin_suspendban( gentity_t *ent, int skiparg )
{
  int bnum;
  int length;
  int timenow = 0;
  int expires = 0;
  char *arg;
  char bs[ 5 ];
  char duration[ 32 ];
  qtime_t qt;

  if( G_SayArgc() < 3 + skiparg )
  {
    ADMP( "^3!suspendban: ^7usage: !suspendban [ban #] [length]\n" );
    return qfalse;
  }
  G_SayArgv( 1 + skiparg, bs, sizeof( bs ) );
  bnum = atoi( bs );
  if( bnum < 1 || !g_admin_bans[ bnum - 1] )
  {
    ADMP( "^3!suspendban: ^7invalid ban #\n" );
    return qfalse;
  }
  if( g_admin_bans[ bnum - 1 ]->bannerlevel > G_admin_level( ent ) )
  {
    ADMP( "^3!suspendban: ^7you cannot suspend Bans made by admins higher than you\n" );
    return qfalse;
  }

  arg = G_SayConcatArgs( 2 + skiparg );
  timenow = trap_RealTime( &qt );
  length = G_admin_parse_time( arg );

  if( length < 0 )
  {
    ADMP( "^3!suspendban: ^7invalid length\n" );
    return qfalse;
  }
  if( length > MAX_ADMIN_BANSUSPEND_DAYS * 24 * 60 * 60 )
  {
    length = MAX_ADMIN_BANSUSPEND_DAYS * 24 * 60 * 60;
    ADMP( va( "^3!suspendban: ^7maximum ban suspension is %d days\n",
      MAX_ADMIN_BANSUSPEND_DAYS ) );
  } else if( g_admin_bans[ bnum - 1 ]->expires > 0 && length + timenow > g_admin_bans[ bnum - 1 ]->expires ) {
    length = g_admin_bans[ bnum - 1 ]->expires - timenow;
    G_admin_duration( length , duration, sizeof( duration ) );
    ADMP( va( "^3!suspendban: ^7Suspension Duration trimmed to Ban duration: %s\n",
          duration ) );
  }

  if ( length > 0 )
  {
    expires = timenow + length;
  }
  if( g_admin_bans[ bnum - 1 ]->suspend == expires )
  {
    ADMP( "^3!suspendban: ^7no change\n" );
    return qfalse;
  }

  g_admin_bans[ bnum - 1 ]->suspend = expires;
  Q_strncpyz( g_admin_bans[ bnum - 1 ]->suspendby, G_admin_get_adminname( ent ), sizeof( g_admin_bans[ bnum - 1 ]->suspendby ) );

  if ( length > 0 )
  {
    G_admin_duration( length , duration, sizeof( duration ) );
    AP( va( "print \"^3!suspendban: ^7ban ^3#%d^7 for %s^7 suspended for ^3%s^7 by %s^7\n\"",
      bnum, g_admin_bans[ bnum - 1 ]->name, duration, G_admin_adminPrintName( ent ) ) );
  }
  else
  {
    AP( va( "print \"^3!suspendban: ^7ban ^3#%d^7 for %s^7 suspension removed by %s^7\n\"",
      bnum, g_admin_bans[ bnum - 1 ]->name, G_admin_adminPrintName( ent ) ) );
  }

  if( !g_admin.string[ 0 ] )
    ADMP( "^3!adjustban: ^7WARNING g_admin not set, not saving ban to a file\n" );
  else
    admin_writeconfig();
  return qtrue;
}

qboolean G_admin_unban( gentity_t *ent, int skiparg )
{
  int bnum;
  char bs[ 5 ];
  int t;

  t = trap_RealTime( NULL );
  if( G_SayArgc() < 2 + skiparg )
  {
    ADMP( "^3!unban: ^7usage: !unban [ban#]\n" );
    return qfalse;
  }
  G_SayArgv( 1 + skiparg, bs, sizeof( bs ) );
  bnum = atoi( bs );
  if( bnum < 1 || bnum > MAX_ADMIN_BANS || !g_admin_bans[ bnum - 1 ] )
  {
    ADMP( "^3!unban: ^7invalid ban#\n" );
    return qfalse;
  }
  if( g_admin_bans[ bnum - 1 ]->expires == 0 &&
      !G_admin_permission( ent, ADMF_CAN_PERM_BAN ) )
  {
    ADMP( "^3!unban: ^7you cannot remove permanent bans\n" );
    return qfalse;
  }
  if( g_admin_bans[ bnum - 1 ]->bannerlevel > G_admin_level( ent ) )
  {
    ADMP( "^3!unban: ^7you cannot Remove Bans made by admins higher than you\n" );
    return qfalse;
  }
  if( g_adminMaxBan.integer &&
      !G_admin_permission( ent, ADMF_CAN_PERM_BAN ) &&
      g_admin_bans[ bnum - 1 ]->expires - t > G_admin_parse_time( g_adminMaxBan.string ) )
  {
    ADMP( va( "^3!unban: ^7your admin level cannot remove bans longer than %s\n",
              g_adminMaxBan.string ) );
    return qfalse;
  }
  g_admin_bans[ bnum -1 ]->expires = t;
  AP( va( "print \"^3!unban: ^7ban #%d for %s^7 has been removed by %s\n\"",
          bnum,
          g_admin_bans[ bnum - 1 ]->name,
          G_admin_adminPrintName( ent ) ) );
  if( g_admin.string[ 0 ] )
    admin_writeconfig();
  return qtrue;
}

qboolean G_admin_putteam( gentity_t *ent, int skiparg )
{
  int pids[ MAX_CLIENTS ];
  char name[ MAX_NAME_LENGTH ], team[ 7 ], err[ MAX_STRING_CHARS ];
  gentity_t *vic;
  pTeam_t teamnum = PTE_NONE;
  char teamdesc[ 32 ] = {"spectators"};
  char secs[ 7 ];
  int seconds = 0;
  qboolean useDuration = qfalse;

  G_SayArgv( 1 + skiparg, name, sizeof( name ) );
  G_SayArgv( 2 + skiparg, team, sizeof( team ) );
  if( G_SayArgc() < 3 + skiparg )
  {
    ADMP( "^3!putteam: ^7usage: !putteam [name] [h|a|s] (duration)\n" );
    return qfalse;
  }

  if( G_ClientNumbersFromString( name, pids ) != 1 )
  {
    G_MatchOnePlayer( pids, err, sizeof( err ) );
    ADMP( va( "^3!putteam: ^7%s\n", err ) );
    return qfalse;
  }
  if( !admin_higher( ent, &g_entities[ pids[ 0 ] ] ) )
  {
    ADMP( "^3!putteam: ^7sorry, but your intended victim has a higher "
        " admin level than you\n" );
    return qfalse;
  }
  vic = &g_entities[ pids[ 0 ] ];

  if ( vic->client->sess.invisible == qtrue )
  {
    ADMP( "^3!putteam: ^7invisible players cannot join a team\n" );
    return qfalse;
  }

  switch( team[ 0 ] )
  {
  case 'a':
    teamnum = PTE_ALIENS;
    Q_strncpyz( teamdesc, "aliens", sizeof( teamdesc ) );
    break;
  case 'h':
    teamnum = PTE_HUMANS;
    Q_strncpyz( teamdesc, "humans", sizeof( teamdesc ) );
    break;
  case 's':
    teamnum = PTE_NONE;
    break;
  default:
    ADMP( va( "^3!putteam: ^7unknown team %c\n", team[ 0 ] ) );
    return qfalse;
  }
  //duration code
  if( G_SayArgc() > 3 + skiparg ) {
    //can only lock players in spectator
    if ( teamnum != PTE_NONE )
    {
      ADMP( "^3!putteam: ^7You can only lock a player into the spectators team\n" );
      return qfalse;
    }
    G_SayArgv( 3 + skiparg, secs, sizeof( secs ) );
    seconds = G_admin_parse_time( secs );
    useDuration = qtrue;
  }

  if( vic->client->pers.teamSelection == teamnum && teamnum != PTE_NONE )
  {
    ADMP( va( "^3!putteam: ^7%s ^7is already on the %s team\n", vic->client->pers.netname, teamdesc ) );
    return qfalse;
  }

  if( useDuration == qtrue && seconds > 0 ) {
    vic->client->pers.specExpires = level.time + ( seconds * 1000 );
  }
  G_ChangeTeam( vic, teamnum, qfalse );

  AP( va( "print \"^3!putteam: ^7%s^7 put %s^7 on to the %s team%s\n\"",
          G_admin_adminPrintName( ent ),
          vic->client->pers.netname, teamdesc,
          ( seconds ) ? va( " for %i seconds", seconds ) : "" ) );
  return qtrue;
}

qboolean G_admin_seen(gentity_t *ent, int skiparg )
{
  char name[ MAX_NAME_LENGTH ];
  char search[ MAX_NAME_LENGTH ];
  char sduration[ 32 ];
  qboolean numeric = qtrue;
  int i, j;
  int id = -1;
  int count = 0;
  int t;
  qtime_t qt;
  gentity_t *vic;
  qboolean ison;

  if( G_SayArgc() < 2 + skiparg )
  {
    ADMP( "^3!seen: ^7usage: !seen [name|admin#]\n" );
    return qfalse;
  }
  G_SayArgv( 1 + skiparg, name, sizeof( name ) );
  G_SanitiseString( name, search, sizeof( search ) );
  for( i = 0; i < sizeof( search ) && search[ i ] ; i++ )
  {
    if( search[ i ] < '0' || search[ i ] > '9' )
    {
      numeric = qfalse;
      break;
    }
  }

  if( numeric )
  {
    id = atoi( name );
    search[ 0 ] = '\0';
  }

  ADMBP_begin();
  t = trap_RealTime( &qt );

  for( i = 0; i < level.maxclients && count < 10; i ++ )
  {
    vic = &g_entities[ i ];

    if( !vic->client || vic->client->pers.connected != CON_CONNECTED )
      continue;

    G_SanitiseString( vic->client->pers.netname, name, sizeof( name ) );

    if( i == id || (search[ 0 ] && strstr( name, search ) ) )
    {
      if ( vic->client->sess.invisible == qfalse )
      {
        ADMBP( va( "^3%4d ^7%s^7 is currently playing\n", i, vic->client->pers.netname ) );
        count++;
      }
    }
  }
  for( i = 0; i < MAX_ADMIN_ADMINS && g_admin_admins[ i ] && count < 10; i++ )
  {
    G_SanitiseString( g_admin_admins[ i ]->name, name, sizeof( name ) );
    if( i + MAX_CLIENTS == id || (search[ 0 ] && strstr( name, search ) ) )
    {
      ison = qfalse;
      for( j = 0; j < level.maxclients; j++ )
      {
        vic = &g_entities[ j ];
        if( !vic->client || vic->client->pers.connected != CON_CONNECTED )
          continue;
        G_SanitiseString( vic->client->pers.netname, name, sizeof( name ) );
        if( !Q_stricmp( vic->client->pers.guid, g_admin_admins[ i ]->guid )
          && strstr( name, search ) )
        {
          if ( vic->client->sess.invisible == qfalse )
          {
            ison = qtrue;
            break;
          }
        }
      }

      if( ison )
      {
        if( id == -1 )
          continue;
        ADMBP( va( "^3%4d ^7%s^7 is currently playing\n",
          i + MAX_CLIENTS, g_admin_admins[ i ]->name ) );
      }
      else
      {
        G_admin_duration( t - g_admin_admins[ i ]->seen,
          sduration, sizeof( sduration ) );
        ADMBP( va( "%4d %s^7 last seen %s%s\n",
          i + MAX_CLIENTS, g_admin_admins[ i ]->name ,
          ( g_admin_admins[ i ]->seen ) ? sduration : "",
          ( g_admin_admins[ i ]->seen ) ? " ago" : "time is unknown" ) );
      }
      count++;
    }
  }

  if( search[ 0 ] )
    ADMBP( va( "^3!seen:^7 found %d player%s matching '%s'\n",
      count, (count == 1) ? "" : "s", search ) );
  else if ( !count )
    ADMBP( "^3!seen:^7 no one connectd by that slot number\n" );

  ADMBP_end();
  return qtrue;
}

void G_admin_seen_update( char *guid )
{
  int i;

  for( i = 0; i < MAX_ADMIN_ADMINS && g_admin_admins[ i ] ; i++ )
  {
    if( !Q_stricmp( g_admin_admins[ i ]->guid, guid ) )
    {
      qtime_t qt;

      g_admin_admins[ i ]->seen = trap_RealTime( &qt );
      return;
    }
  }
}

void G_admin_adminlog_cleanup( void )
{
  int i;

  for( i = 0; i < MAX_ADMIN_ADMINLOGS && g_admin_adminlog[ i ]; i++ )
  {
    G_Free( g_admin_adminlog[ i ] );
    g_admin_adminlog[ i ] = NULL;
  }

  admin_adminlog_index = 0;
}

void G_admin_adminlog_log( gentity_t *ent, char *command, char *args, int skiparg, qboolean success )
{
  g_admin_adminlog_t *adminlog;
  int previous;
  int count = 1;
  int i;

  if( !command )
    return;

  if( !Q_stricmp( command, "adminlog" ) ||
      !Q_stricmp( command, "admintest" ) ||
      !Q_stricmp( command, "help" ) ||
      !Q_stricmp( command, "info" ) ||
      !Q_stricmp( command, "listadmins" ) ||
      !Q_stricmp( command, "listplayers" ) ||
      !Q_stricmp( command, "namelog" ) ||
      !Q_stricmp( command, "showbans" ) ||
      !Q_stricmp( command, "seen" ) ||
      !Q_stricmp( command, "time" ) )
    return;

  previous = admin_adminlog_index - 1;
  if( previous < 0 )
    previous = MAX_ADMIN_ADMINLOGS - 1;

  if( g_admin_adminlog[ previous ] )
    count = g_admin_adminlog[ previous ]->id + 1;

  if( g_admin_adminlog[ admin_adminlog_index ] )
    adminlog = g_admin_adminlog[ admin_adminlog_index ];
  else
    adminlog = G_Alloc( sizeof( g_admin_adminlog_t ) );

  memset( adminlog, 0, sizeof( *adminlog ) );
  adminlog->id = count;
  adminlog->time = level.time - level.startTime;
  adminlog->success = success;
  Q_strncpyz( adminlog->command, command, sizeof( adminlog->command ) );

  if ( args )
    Q_strncpyz( adminlog->args, args, sizeof( adminlog->args ) );
  else
    Q_strncpyz( adminlog->args, G_SayConcatArgs( 1 + skiparg ), sizeof( adminlog->args ) );

  if( ent )
  {
    qboolean found = qfalse;
    // real admin name
    for( i = 0; i < MAX_ADMIN_ADMINS && g_admin_admins[ i ]; i++ )
    {
      if( !Q_stricmp( g_admin_admins[ i ]->guid, ent->client->pers.guid ) )
      {
        Q_strncpyz( adminlog->name, g_admin_admins[ i ]->name, sizeof( adminlog->name ) );
        found = qtrue;
        break;
      }
    }
    if( !found )
      Q_strncpyz( adminlog->name, ent->client->pers.netname, sizeof( adminlog->name ) );

    adminlog->level = ent->client->pers.adminLevel;
  }
  else
  {
    Q_strncpyz( adminlog->name, "console", sizeof( adminlog->name ) );
    adminlog->level = 10000;
  }

  g_admin_adminlog[ admin_adminlog_index ] = adminlog;
  admin_adminlog_index++;
  if( admin_adminlog_index >= MAX_ADMIN_ADMINLOGS )
    admin_adminlog_index = 0;
}

qboolean G_admin_adminlog( gentity_t *ent, int skiparg )
{
  g_admin_adminlog_t *results[ 10 ];
  int result_index = 0;
  char *search_cmd = NULL;
  char *search_name = NULL;
  int index;
  int skip = 0;
  int skipped = 0;
  int checked = 0;
  char n1[ MAX_NAME_LENGTH ];
  char fmt_name[ 16 ];
  char argbuf[ 32 ];
  int name_length = 12;
  int max_id = 0;
  int i;
  qboolean match;

  memset( results, 0, sizeof( results ) );

  index = admin_adminlog_index;
  for( i = 0; i < 10; i++ )
  {
    int prev;

    prev = index - 1;
    if( prev < 0 )
      prev = MAX_ADMIN_ADMINLOGS - 1;
    if( !g_admin_adminlog[ prev ] )
      break;
    if( g_admin_adminlog[ prev ]->id > max_id )
      max_id = g_admin_adminlog[ prev ]->id;
    index = prev;
  }

  if( G_SayArgc() > 1 + skiparg )
  {
    G_SayArgv( 1 + skiparg, argbuf, sizeof( argbuf ) );
    if( ( *argbuf >= '0' && *argbuf <= '9' ) || *argbuf == '-' )
    {
      int id;

      id = atoi( argbuf );
      if( id < 0 )
        id += ( max_id - 9 );
      else if( id <= max_id - MAX_ADMIN_ADMINLOGS )
        id = max_id - MAX_ADMIN_ADMINLOGS + 1;

      if( id + 9 >= max_id )
        id = max_id - 9;
      if( id < 1 )
        id = 1;
      for( i = 0; i < MAX_ADMIN_ADMINLOGS; i++ )
      {
        if( g_admin_adminlog[i] && g_admin_adminlog[ i ]->id == id )
        {
          index = i;
          break;
        }
      }
    }
    else if ( *argbuf == '!' )
    {
      search_cmd = argbuf + 1;
    }
    else
    {
      search_name = argbuf;
    }

    if( G_SayArgc() > 2 + skiparg && ( search_cmd || search_name ) )
    {
      char skipbuf[ 4 ];
      G_SayArgv( 2 + skiparg, skipbuf, sizeof( skipbuf ) );
      skip = atoi( skipbuf );
    }
  }

  if( search_cmd || search_name )
  {
    g_admin_adminlog_t *result_swap[ 10 ];

    memset( result_swap, 0, sizeof( result_swap ) );

    index = admin_adminlog_index - 1;
    if( index < 0 )
      index = MAX_ADMIN_ADMINLOGS - 1;

    while( g_admin_adminlog[ index ] &&
      checked < MAX_ADMIN_ADMINLOGS &&
      result_index < 10 )
    {
      match = qfalse;
      if( search_cmd )
      {
        if( !Q_stricmp( search_cmd, g_admin_adminlog[ index ]->command ) )
          match = qtrue;
      }
      if( search_name )
      {
        G_SanitiseString( g_admin_adminlog[ index ]->name, n1, sizeof( n1 ) );
        if( strstr( n1, search_name ) )
          match = qtrue;
      }

      if( match && skip > 0 )
      {
        match = qfalse;
        skip--;
        skipped++;
      }
      if( match )
      {
        result_swap[ result_index ] = g_admin_adminlog[ index ];
        result_index++;
      }

      checked++;
      index--;
      if( index < 0 )
        index = MAX_ADMIN_ADMINLOGS - 1;
    }
    // search runs backwards, turn it around
    for( i = 0; i < result_index; i++ )
      results[ i ] = result_swap[ result_index - i - 1 ];
  }
  else
  {
    while( g_admin_adminlog[ index ] && result_index < 10 )
    {
      results[ result_index ] = g_admin_adminlog[ index ];
      result_index++;
      index++;
      if( index >= MAX_ADMIN_ADMINLOGS )
        index = 0;
    }
  }

  for( i = 0; results[ i ] && i < 10; i++ )
  {
    int l;

    G_DecolorString( results[ i ]->name, n1 );
    l = strlen( n1 );
    if( l > name_length )
      name_length = l;
  }
  ADMBP_begin( );
  for( i = 0; results[ i ] && i < 10; i++ )
  {
    char levelbuf[ 8 ];
    int t;

    t = results[ i ]->time / 1000;
    G_DecolorString( results[ i ]->name, n1 );
    Com_sprintf( fmt_name, sizeof( fmt_name ), "%%%ds", 
      (int)( name_length + strlen( results[ i ]->name ) - strlen( n1 ) ) );
    Com_sprintf( n1, sizeof( n1 ), fmt_name, results[ i ]->name );
    Com_sprintf( levelbuf, sizeof( levelbuf ), "%2d", results[ i ]->level );
    ADMBP( va( "%s%3d %3d:%02d %2s ^7%s^7 %s!%s ^7%s^7\n",
      ( results[ i ]->success ) ? "^7" : "^1",
      results[ i ]->id,
      t / 60, t % 60,
      ( results[ i ]->level ) < 10000 ? levelbuf : " -",
      n1,
      ( results[ i ]->success ) ? "^3" : "^1",
      results[ i ]->command,
      results[ i ]->args ) );
  }
  if( search_cmd || search_name )
  {
    ADMBP( va( "^3!adminlog:^7 Showing %d matches for '%s^7'.",
      result_index,
      argbuf ) );
    if( checked < MAX_ADMIN_ADMINLOGS && g_admin_adminlog[ checked ] )
      ADMBP( va( " run '!adminlog %s^7 %d' to see more",
       argbuf,
       skipped + result_index ) );
    ADMBP( "\n" );
  }
  else if ( results[ 0 ] )
  {
    ADMBP( va( "^3!adminlog:^7 Showing %d - %d of %d.\n",
      results[ 0 ]->id,
      results[ result_index - 1 ]->id,
      max_id ) );
  }
  else
  {
    ADMBP( "^3!adminlog:^7 log is empty.\n" );
  }
  ADMBP_end( );

  return qtrue;
}

qboolean G_admin_map( gentity_t *ent, int skiparg )
{
  char map[ MAX_QPATH ];
  char layout[ MAX_QPATH ] = { "" };
  
  if( G_SayArgc( ) < 2 + skiparg )
  {
    ADMP( "^3!map: ^7usage: !map [map] (layout)\n" );
    return qfalse;
  }

  G_SayArgv( skiparg + 1, map, sizeof( map ) );

  if( !trap_FS_FOpenFile( va( "maps/%s.bsp", map ), NULL, FS_READ ) )
  {
    ADMP( va( "^3!map: ^7invalid map name '%s'\n", map ) );
    return qfalse;
  }

  if( G_SayArgc( ) > 2 + skiparg )
  {
    G_SayArgv( skiparg + 2, layout, sizeof( layout ) );
    if( !Q_stricmp( layout, "*BUILTIN*" ) ||
      trap_FS_FOpenFile( va( "layouts/%s/%s.dat", map, layout ),
        NULL, FS_READ ) > 0 )
    {
      trap_Cvar_Set( "g_layouts", layout );
    }
    else
    {
      ADMP( va( "^3!map: ^7invalid layout name '%s'\n", layout ) );
      return qfalse;
    }
  }

  trap_SendConsoleCommand( EXEC_APPEND, va( "map %s", map ) );
  level.restarted = qtrue;
  AP( va( "print \"^3!map: ^7map '%s' started by %s^7 %s\n\"", map,
          G_admin_adminPrintName( ent ),
          ( layout[ 0 ] ) ? va( "(forcing layout '%s')", layout ) : "" ) );
  G_admin_maplog_result( "M" );
  return qtrue;
}

qboolean G_admin_devmap( gentity_t *ent, int skiparg )
{
  char map[ MAX_QPATH ];
  char layout[ MAX_QPATH ] = { "" };

  if( G_SayArgc( ) < 2 + skiparg )
  {
    ADMP( "^3!devmap: ^7usage: !devmap [map] (layout)\n" );
    return qfalse;
  }

  G_SayArgv( skiparg + 1, map, sizeof( map ) );

  if( !trap_FS_FOpenFile( va( "maps/%s.bsp", map ), NULL, FS_READ ) )
  {
    ADMP( va( "^3!devmap: ^7invalid map name '%s'\n", map ) );
    return qfalse;
  }

  if( G_SayArgc( ) > 2 + skiparg )
  {
    G_SayArgv( skiparg + 2, layout, sizeof( layout ) );
    if( !Q_stricmp( layout, "*BUILTIN*" ) ||
      trap_FS_FOpenFile( va( "layouts/%s/%s.dat", map, layout ),
        NULL, FS_READ ) > 0 )
    {
      trap_Cvar_Set( "g_layouts", layout );
    }
    else
    {
      ADMP( va( "^3!devmap: ^7invalid layout name '%s'\n", layout ) );
      return qfalse;
    }
  }

  trap_SendConsoleCommand( EXEC_APPEND, va( "devmap %s", map ) );
  level.restarted = qtrue;
  AP( va( "print \"^3!devmap: ^7map '%s' started by %s^7 with cheats %s\n\"", map,
          G_admin_adminPrintName( ent ),
          ( layout[ 0 ] ) ? va( "(forcing layout '%s')", layout ) : "" ) );
  G_admin_maplog_result( "D" );
  return qtrue;
}

void G_admin_maplog_update( void )
{
  char map[ 64 ];
  char maplog[ MAX_CVAR_VALUE_STRING ];
  char *ptr;
  int count = 0;

  trap_Cvar_VariableStringBuffer( "mapname", map, sizeof( map ) );

  Q_strncpyz( maplog, g_adminMapLog.string, sizeof( maplog ) );
  ptr = maplog;
  while( *ptr && count < MAX_ADMIN_MAPLOG_LENGTH ) 
  {
    while( *ptr != ' ' && *ptr != '\0' ) ptr++;

    count++;
    if( count >= MAX_ADMIN_MAPLOG_LENGTH )
    {
      *ptr = '\0';
    }

    if( *ptr == ' ' ) ptr++;
  }

  trap_Cvar_Set( "g_adminMapLog", va( "%s%s%s",
    map,
    ( maplog[0] != '\0'  ) ? " " : "",
    maplog ) );
}

void G_admin_maplog_result( char *flag )
{
  static int lastTime = 0;
  char maplog[ MAX_CVAR_VALUE_STRING ];
  int t;

  if( !flag )
    return;

  // avoid race when called in same frame
  if( level.time == lastTime )
    return;

  lastTime = level.time;

  if( g_adminMapLog.string[ 0 ] &&
    g_adminMapLog.string[ 1 ] == ';' )
  {
    // only one result allowed
    return;
  }
  
  if ( level.surrenderTeam != PTE_NONE )
  {
    if( flag[ 0 ] == 'a' )
    {
      if( level.surrenderTeam == PTE_HUMANS )
        flag = "A";
    }
    else if( flag[ 0 ] == 'h' )
    {
      if( level.surrenderTeam == PTE_ALIENS )
        flag = "H";
    }
  }

  t = ( level.time - level.startTime ) / 1000;
  Q_strncpyz( maplog, g_adminMapLog.string, sizeof( maplog ) );
  trap_Cvar_Set( "g_adminMapLog", va( "%1s;%03d:%02d;%s",
    flag,
    t / 60, t % 60,
    maplog ) );
}


qboolean G_admin_maplog( gentity_t *ent, int skiparg )
{
  char maplog[ MAX_CVAR_VALUE_STRING ];
  char *ptr, *curTime;
  int count = 0;
  int     mins, seconds, tens;
  int     msec;

  msec = level.time - level.startTime;

  seconds = msec / 1000;
  mins = seconds / 60;
  seconds -= mins * 60;
  tens = seconds / 10;
  seconds -= tens * 10;

  curTime = va( "%3i^7:^3%i%i", mins, tens, seconds );
  Q_strncpyz( maplog, g_adminMapLog.string, sizeof( maplog ) );

  ADMBP_begin( );
  ptr = maplog;
  while( *ptr != '\0' && count < MAX_ADMIN_MAPLOG_LENGTH + 1 )
  {
    char *end;
    const char *result = NULL;
    char *clock = NULL;
    char *colon;

    end = ptr;
    while( *end != ' ' && *end != '\0' ) end++;
    if( *end == ' ' )
    {
      *end = '\0';
      end++;
    }

     if( ptr[ 0 ] && ptr[ 1 ] == ';' )
     {
       switch( ptr[ 0 ] )
       {
         case 't':
           result = "^7tie";
           break;
         case 'a':
           result = "^1Alien win";
           break;
         case 'A':
           result = "^1Alien win ^7/ Humans admitted defeat";
           break;
         case 'h':
           result = "^4Human win";
           break;
         case 'H':
           result = "^4Human win ^7/ Aliens admitted defeat";
           break;
         case 'd':
           result = "^5draw vote";
           break;
         case 'N':
           result = "^6admin loaded next map";
           break;
         case 'r':
           result = "^2restart vote";
           break;
         case 'R':
           result = "^6admin restarted map";
           break;
         case 'm':
           result = "^2map vote";
           break;
         case 'M':
           result = "^6admin changed map";
           break;
         case 'D':
           result = "^6admin loaded devmap";
           break;
         default:
           result = "^7unknown end cause";
           break;
       }
       ptr += 2;
       colon = strchr( ptr, ';' );
       if ( colon )
       {
         clock = ptr;
         ptr = colon + 1;
         *colon = '\0';
 
         // right justification with -6%s doesnt work..
         if( clock[ 0 ] == '0' && clock[ 1 ] != ':' )
         {
           if( clock[ 1 ] == '0' && clock[ 2 ] != ':' )
             clock[ 1 ] = ' ';
           clock[ 0 ] = ' ';
         }
       }
     }
     else if( count == 0 )
     {
       result = "^3current map";
       clock = curTime;
     }
 
     ADMBP( va( "%s%20s %-6s %s^7\n",
       ( count == 0 ) ? "^3" : "^7",
       ptr,
       ( clock ) ? clock : "",
       ( result ) ? result : "^7unknown end cause" ) );

    ptr = end;
    count++;
  }
  ADMBP_end( );

  return qtrue;
}

qboolean G_admin_layoutsave( gentity_t *ent, int skiparg )
{
  char layout[ MAX_QPATH ];

  if( G_SayArgc( ) < 2 + skiparg )
  {
    ADMP( "^3!layoutsave: ^7usage: !layoutsave [layout]\n" );
    return qfalse;
  }

  G_SayArgv( skiparg + 1, layout, sizeof( layout ) );

  trap_SendConsoleCommand( EXEC_APPEND, va( "layoutsave %s", layout ) );
  AP( va( "print \"^3!layoutsave: ^7layout saved as '%s' by %s\n\"", layout,
          G_admin_adminPrintName( ent ) ) );
  return qtrue;
}

qboolean G_admin_demo( gentity_t *ent, int skiparg )
{
  if( !ent )
  {
    ADMP( "!demo: console can not use demo.\n" );
    return qfalse;
  }

  ent->client->pers.ignoreAdminWarnings = !( ent->client->pers.ignoreAdminWarnings );

  ADMP( va( "^3!demo: ^7your visibility of admin chat is now %s\n",
    ( ent->client->pers.ignoreAdminWarnings ) ? "^1disabled" : "^2enabled" ) );

  return qtrue;
}

qboolean G_admin_mute( gentity_t *ent, int skiparg )
{
  int pids[ MAX_CLIENTS ];
  char name[ MAX_NAME_LENGTH ], err[ MAX_STRING_CHARS ];
  char command[ MAX_ADMIN_CMD_LEN ], *cmd;
  gentity_t *vic;
  char secs[ 7 ];
  int seconds = 0;

  G_SayArgv( skiparg, command, sizeof( command ) );
  cmd = command;

  if( cmd && *cmd == '!' )
    cmd++;

  if( G_SayArgc() < 2 + skiparg )
  {
    ADMP( va( "^3!%s: ^7usage: !%s [name|slot#] (duration)\n", cmd, cmd ) );
    return qfalse;
  }

  G_SayArgv( 1 + skiparg, name, sizeof( name ) );

  if( G_ClientNumbersFromString( name, pids ) != 1 )
  {
    G_MatchOnePlayer( pids, err, sizeof( err ) );
    ADMP( va( "^3!%s: ^7%s\n", cmd, err ) );
    return qfalse;
  }

  if( !admin_higher( ent, &g_entities[ pids[ 0 ] ] ) )
  {
    ADMP( va( "^3!%s: ^7sorry, but your intended victim has a higher admin"
        " level than you\n", cmd ) );
    return qfalse;
  }

  vic = &g_entities[ pids[ 0 ] ];
  if( !Q_stricmp( cmd, "unmute" ) )
  {
    if( vic->client->pers.muted == qfalse )
    {
      ADMP( "^3!unmute: ^7player is not currently muted\n" );
      return qtrue;
    }

    vic->client->pers.muteExpires = 0;
    vic->client->pers.muted = qfalse;

    CPx( pids[ 0 ], "cp \"^1You have been unmuted\"" );
    AP( va( "print \"^3!unmute: ^7%s^7 has been unmuted by %s\n\"",
        vic->client->pers.netname,
        G_admin_adminPrintName( ent ) ) );
  } else {
    // Duration
    if( G_SayArgc() > 2 + skiparg )
    {
      G_SayArgv( 2 + skiparg, secs, sizeof( secs ) );
      seconds = G_admin_parse_time( secs );
      vic->client->pers.muteExpires = level.time + ( seconds * 1000 );
    }

    vic->client->pers.muted = qtrue;

    CPx( pids[ 0 ], "cp \"^1You've been muted\"" );
    AP( va( "print \"^3!mute: ^7%s^7 has been muted by ^7%s%s\n\"",
        vic->client->pers.netname,
        G_admin_adminPrintName( ent ),
          ( seconds ) ? va( " ^7for %i seconds", seconds ) : "" ) );
  }

  return qtrue;
}

qboolean G_admin_cp( gentity_t *ent, int skiparg )
{
  int minargc;

  minargc = 2 + skiparg;

  if( G_SayArgc() < minargc )
  {
    ADMP( "^3!cp: ^7usage: !cp [message]\n" );
    return qfalse;
  }

  G_CP(ent);
  return qtrue;
}

qboolean G_admin_denybuild( gentity_t *ent, int skiparg )
{
  int pids[ MAX_CLIENTS ];
  char name[ MAX_NAME_LENGTH ], err[ MAX_STRING_CHARS ];
  char command[ MAX_ADMIN_CMD_LEN ], *cmd;
  gentity_t *vic;

  G_SayArgv( skiparg, command, sizeof( command ) );
  cmd = command;
  if( cmd && *cmd == '!' )
    cmd++;
  if( G_SayArgc() < 2 + skiparg )
  {
    ADMP( va( "^3!%s: ^7usage: !%s [name|slot#]\n", cmd, cmd ) );
    return qfalse;
  }
  G_SayArgv( 1 + skiparg, name, sizeof( name ) );
  if( G_ClientNumbersFromString( name, pids ) != 1 )
  {
    G_MatchOnePlayer( pids, err, sizeof( err ) );
    ADMP( va( "^3!%s: ^7%s\n", cmd, err ) );
    return qfalse;
  }
  if( !admin_higher( ent, &g_entities[ pids[ 0 ] ] ) )
  {
    ADMP( va( "^3!%s: ^7sorry, but your intended victim has a higher admin"
              " level than you\n", cmd ) );
    return qfalse;
  }
  vic = &g_entities[ pids[ 0 ] ];
  if( vic->client->pers.denyBuild )
  {
    if( !Q_stricmp( cmd, "denybuild" ) )
    {
      ADMP( "^3!denybuild: ^7player already has no building rights\n" );
      return qtrue;
    }
    vic->client->pers.denyBuild = qfalse;
    CPx( pids[ 0 ], "cp \"^1You've regained your building rights\"" );
    AP( va(
      "print \"^3!allowbuild: ^7building rights for ^7%s^7 restored by %s\n\"",
      vic->client->pers.netname,
      G_admin_adminPrintName( ent ) ) );
  }
  else
  {
    if( !Q_stricmp( cmd, "allowbuild" ) )
    {
      ADMP( "^3!allowbuild: ^7player already has building rights\n" );
      return qtrue;
    }
    vic->client->pers.denyBuild = qtrue;
    vic->client->ps.stats[ STAT_BUILDABLE ] = BA_NONE;
    if( vic->client->ps.stats[ STAT_PCLASS ]== PCL_ALIEN_BUILDER0 || vic->client->ps.stats[ STAT_PCLASS ] == PCL_ALIEN_BUILDER0_UPG )
    {
      vic->suicideTime = level.time + 1000;
    }
    CPx( pids[ 0 ], "cp \"^1You've lost your building rights\"" );
    AP( va(
      "print \"^3!denybuild: ^7building rights for ^7%s^7 revoked by ^7%s\n\"",
      vic->client->pers.netname,
      G_admin_adminPrintName( ent ) ) );
  }
  return qtrue;
}

qboolean G_admin_denyweapon( gentity_t *ent, int skiparg )
{
  int pids[ MAX_CLIENTS ];
  char name[ MAX_NAME_LENGTH ], err[ MAX_STRING_CHARS ];
  char command[ MAX_ADMIN_CMD_LEN ], *cmd;
  char buffer[ 32 ];
  int weapon = WP_NONE;
  int class = PCL_NONE;
  char *realname;
  gentity_t *vic;
  int flag;
  qboolean all = qfalse;

  G_SayArgv( skiparg, command, sizeof( command ) );
  cmd = command;
  if( cmd && *cmd == '!' )
    cmd++;
  if( G_SayArgc() < 3 + skiparg )
  {
    ADMP( va( "^3!%s: ^7usage: !%s [name|slot#] [class|weapon]\n", cmd, cmd ) );
    return qfalse;
  }
  G_SayArgv( 1 + skiparg, name, sizeof( name ) );
  if( G_ClientNumbersFromString( name, pids ) != 1 )
  {
    G_MatchOnePlayer( pids, err, sizeof( err ) );
    ADMP( va( "^3!%s: ^7%s\n", cmd, err ) );
    return qfalse;
  }
  if( !admin_higher( ent, &g_entities[ pids[ 0 ] ] ) )
  {
    ADMP( va( "^3!%s: ^7sorry, but your intended victim has a higher admin"
              " level than you\n", cmd ) );
    return qfalse;
  }
  vic = &g_entities[ pids[ 0 ] ];

  if( vic == ent &&
      !Q_stricmp( cmd, "denyweapon" ) )
  {
    ADMP( va( "^3!%s: ^7sorry, you cannot %s yourself\n", cmd, cmd ) );
    return qfalse;
  }

  G_SayArgv( 2 + skiparg, buffer, sizeof( buffer ) );

  if( !Q_stricmp( buffer, "all" ) &&
      !Q_stricmp( cmd, "allowweapon" ) )
  {
    if( vic->client->pers.denyHumanWeapons ||
        vic->client->pers.denyAlienClasses )
    {
      vic->client->pers.denyHumanWeapons = 0;
      vic->client->pers.denyAlienClasses = 0;

      CPx( pids[ 0 ], "cp \"^1You've regained all weapon and class rights\"" );
      AP( va( "print \"^3!%s: ^7all weapon and class rights for ^7%s^7 restored by %s\n\"",
        cmd,
        vic->client->pers.netname,
        G_admin_adminPrintName( ent ) ) );
    }
    else
    {
      ADMP( va( "^3!%s: ^7player already has all rights\n", cmd ) );
    }
    return qtrue;
  }

  if( !Q_stricmp( buffer, "all" ) &&
      !Q_stricmp( cmd, "denyweapon" ) )
  {
    all = qtrue;
    weapon = WP_NONE;
    class = PCL_NONE;

    if( vic->client->pers.denyHumanWeapons == 0xFFFFFF &&
        vic->client->pers.denyAlienClasses == 0xFFFFFF )
    {
      ADMP( va( "^3!%s: ^7player already has no weapon or class rights\n", cmd ) );
      return qtrue;
    }

    if( vic->client->pers.teamSelection == PTE_HUMANS )
    {
      weapon = vic->client->ps.weapon;
      if( weapon < WP_PAIN_SAW || weapon > WP_GRENADE )
        weapon = WP_NONE;
    }
    if( vic->client->pers.teamSelection == PTE_ALIENS )
    {
      class = vic->client->pers.classSelection;
      if( class < PCL_ALIEN_LEVEL1 || class > PCL_ALIEN_LEVEL4 )
        class = PCL_NONE;
    }

    vic->client->pers.denyHumanWeapons = 0xFFFFFF;
    vic->client->pers.denyAlienClasses = 0xFFFFFF;
  }
  else
  {
    weapon = BG_FindWeaponNumForName( buffer );
    if( weapon < WP_PAIN_SAW || weapon > WP_GRENADE )
      class = BG_FindClassNumForName( buffer );
    if( ( weapon < WP_PAIN_SAW || weapon > WP_GRENADE ) &&
        ( class < PCL_ALIEN_LEVEL1 || class > PCL_ALIEN_LEVEL4 ) )
    {
      {
        ADMP( va( "^3!%s: ^7unknown weapon or class\n", cmd ) );
        return qfalse;
      }
    }
  }

  if( class == PCL_NONE )
  {
    realname = BG_FindHumanNameForWeapon( weapon );
    flag = 1 << (weapon - WP_BLASTER);
    if( !Q_stricmp( cmd, "denyweapon" ) )
    {
      if( ( vic->client->pers.denyHumanWeapons & flag ) && !all )
      {
        ADMP( va( "^3!%s: ^7player already has no %s rights\n", cmd, realname ) );
        return qtrue;
      }
      vic->client->pers.denyHumanWeapons |= flag;
      if( vic->client->pers.teamSelection == PTE_HUMANS )
      {
        if( ( weapon == WP_GRENADE || all ) &&
            BG_InventoryContainsUpgrade( UP_GRENADE, vic->client->ps.stats ) )
        {
          BG_RemoveUpgradeFromInventory( UP_GRENADE, vic->client->ps.stats );
          G_AddCreditToClient( vic->client, (short)BG_FindPriceForUpgrade( UP_GRENADE ), qfalse );
        }
        if( BG_InventoryContainsWeapon( weapon, vic->client->ps.stats ) )
        {
          int maxAmmo, maxClips;

          BG_RemoveWeaponFromInventory( weapon, vic->client->ps.stats );
          G_AddCreditToClient( vic->client, (short)BG_FindPriceForWeapon( weapon ), qfalse );

          BG_AddWeaponToInventory( WP_MACHINEGUN, vic->client->ps.stats );
          BG_FindAmmoForWeapon( WP_MACHINEGUN, &maxAmmo, &maxClips );
          vic->client->ps.ammo = maxAmmo;
          vic->client->ps.clips = maxClips;
          G_ForceWeaponChange( vic, WP_MACHINEGUN );
          vic->client->ps.stats[ STAT_MISC ] = 0;
          ClientUserinfoChanged( pids[ 0 ], qfalse );
        }
      }
    }
    else
    {
      if( !( vic->client->pers.denyHumanWeapons & flag ) )
      {
        ADMP( va( "^3!%s: ^7player already has %s rights\n", cmd, realname ) );
        return qtrue;
      }
      vic->client->pers.denyHumanWeapons &= ~flag;
    }
  }
  else
  {
    realname = BG_FindHumanNameForClassNum( class );
    flag = 1 << class;
    if( !Q_stricmp( cmd, "denyweapon" ) )
    {
      if( ( vic->client->pers.denyAlienClasses & flag ) && !all )
      {
        ADMP( va( "^3!%s: ^7player already has no %s rights\n", cmd, realname ) );
        return qtrue;
      }
      vic->client->pers.denyAlienClasses |= flag;
      if( vic->client->pers.teamSelection == PTE_ALIENS &&
          vic->client->pers.classSelection == class )
      {
        vec3_t infestOrigin;
        short cost;

        G_RoomForClassChange( vic, PCL_ALIEN_LEVEL0, infestOrigin );

        vic->client->pers.evolveHealthFraction = (float)vic->client->ps.stats[ STAT_HEALTH ] /
            (float)BG_FindHealthForClass( class );
        if( vic->client->pers.evolveHealthFraction < 0.0f )
          vic->client->pers.evolveHealthFraction = 0.0f;
        else if( vic->client->pers.evolveHealthFraction > 1.0f )
          vic->client->pers.evolveHealthFraction = 1.0f;

        vic->client->pers.classSelection = PCL_ALIEN_LEVEL0;
        cost = BG_ClassCanEvolveFromTo( PCL_ALIEN_LEVEL0, class, 9, 0 );
        if( cost < 0 ) cost = 0;
        G_AddCreditToClient( vic->client, cost, qfalse );
        ClientUserinfoChanged( pids[ 0 ], qfalse );
        VectorCopy( infestOrigin, vic->s.pos.trBase );
        ClientSpawn( vic, vic, vic->s.pos.trBase, vic->s.apos.trBase );
      }
    }
    else
    {
      if( !( vic->client->pers.denyAlienClasses & flag ) )
      {
        ADMP( va( "^3!%s: ^7player already has %s rights\n", cmd, realname ) );
        return qtrue;
      }
      vic->client->pers.denyAlienClasses &= ~flag;
    }
  }

  if( all )
    realname = "weapon and class";

  CPx( pids[ 0 ], va( "cp \"^1You've %s your %s rights\"",
    ( !Q_stricmp( cmd, "denyweapon" ) ) ? "lost" : "regained",
    realname ) );
  AP( va(
    "print \"^3!%s: ^7%s rights for ^7%s^7 %s by %s\n\"",
    cmd, realname,
    vic->client->pers.netname,
    ( !Q_stricmp( cmd, "denyweapon" ) ) ? "revoked" : "restored",
    G_admin_adminPrintName( ent ) ) );
  
  return qtrue;
}

qboolean G_admin_listadmins( gentity_t *ent, int skiparg )
{
  int i, found = 0;
  char search[ MAX_NAME_LENGTH ] = {""};
  char s[ MAX_NAME_LENGTH ] = {""};
  int start = 0;
  qboolean numeric = qtrue;
  int drawn = 0;
  int minlevel = 1;

  if( G_SayArgc() == 3 + skiparg )
  {
    G_SayArgv( 2 + skiparg, s, sizeof( s ) );
    if( s[ 0 ] >= '0' && s[ 0] <= '9' )
    {
      minlevel = atoi( s );
      if( minlevel < 1 ) 
       minlevel = 1;
    }
  }

  for( i = 0; i < MAX_ADMIN_ADMINS && g_admin_admins[ i ]; i++ )
  {
    if( g_admin_admins[ i ]->level >= minlevel )
      found++;
  }
  if( !found )
  {
    if( minlevel > 1 )
    {
      ADMP( va( "^3!listadmins: ^7no admins level %i or greater found\n", minlevel ) );
    }
    else
    {
       ADMP( "^3!listadmins: ^7no admins defined\n" );
    }
    return qfalse;
  }

  if( G_SayArgc() >= 2 + skiparg )
  {
    G_SayArgv( 1 + skiparg, s, sizeof( s ) );
    for( i = 0; i < sizeof( s ) && s[ i ]; i++ )
    {
      if( s[ i ] >= '0' && s[ i ] <= '9' )
        continue;
      numeric = qfalse; 
    }
    if( numeric ) 
    {
      start = atoi( s );
      if( start > 0 )
        start -= 1;
      else if( start < 0 )
        start = found + start;
    }
    else
      G_SanitiseString( s, search, sizeof( search ) );
  }

  if( start >= found || start < 0 )
    start = 0;

  drawn = admin_listadmins( ent, start, search, minlevel );

  if( search[ 0 ] )
  {
    if( drawn <= 20 )
    {
      ADMP( va( "^3!listadmins:^7 found %d admins level %i or greater matching '%s^7'\n",
        drawn, minlevel, search ) );
    }
    else
    {
      ADMP( va( "^3!listadmins:^7 found >20 admins level %i or greater matching '%s^7. Try a more narrow search.'\n",
        minlevel, search ) );
    }
  }
  else
  {
    ADMBP_begin();
    ADMBP( va( "^3!listadmins:^7 showing admins level %i or greater %d - %d of %d.  ",
      minlevel,
      ( found ) ? ( start + 1 ) : 0,
      ( ( start + MAX_ADMIN_LISTITEMS ) > found ) ?
       found : ( start + MAX_ADMIN_LISTITEMS ),
      found ) );
    if( ( start + MAX_ADMIN_LISTITEMS ) < found )
    {
      if( minlevel > 1)
      {
        ADMBP( va( "run '!listadmins %d %d' to see more",
          ( start + MAX_ADMIN_LISTITEMS + 1 ), minlevel ) );
      }
      else
      {
        ADMBP( va( "run '!listadmins %d' to see more",
          ( start + MAX_ADMIN_LISTITEMS + 1 ) ) );
      }
    }
    ADMBP( "\n" );
    ADMBP_end();
  }
  return qtrue;
}

qboolean G_admin_listlayouts( gentity_t *ent, int skiparg )
{
  char list[ MAX_CVAR_VALUE_STRING ];
  char map[ MAX_QPATH ];
  int count = 0;
  char *s;
  char layout[ MAX_QPATH ] = { "" };
  int i = 0;
  
  if( G_SayArgc( ) == 2 + skiparg ) 
    G_SayArgv( 1 +skiparg, map, sizeof( map ) );
  else
    trap_Cvar_VariableStringBuffer( "mapname", map, sizeof( map ) );
  
  count = G_LayoutList( map, list, sizeof( list ) );
  ADMBP_begin( );
  ADMBP( va( "^3!listlayouts:^7 %d layouts found for '%s':\n", count, map ) );
  s = &list[ 0 ];
  while( *s )
  {
    if( *s == ' ' )
    {
      ADMBP( va ( " %s\n", layout ) );
      layout[ 0 ] = '\0';
      i = 0;
    }
    else if( i < sizeof( layout ) - 2 )
    {
      layout[ i++ ] = *s;
      layout[ i ] = '\0';
    }
    s++;
  }
  if( layout[ 0 ] )
    ADMBP( va ( " %s\n", layout ) );
  ADMBP_end( );
  return qtrue;
}

qboolean G_admin_listplayers( gentity_t *ent, int skiparg )
{
  int i, j;
  int invisiblePlayers = 0;
  gclient_t *p;
  char c[ 3 ], t[ 2 ]; // color and team letter
  char n[ MAX_NAME_LENGTH ] = {""};
  char n2[ MAX_NAME_LENGTH ] = {""};
  char n3[ MAX_NAME_LENGTH ] = {""};
  char lname[ MAX_NAME_LENGTH ];
  char lname2[ MAX_NAME_LENGTH ];
  char muted[ 2 ], denied[ 2 ], dbuilder[ 2 ], immune[ 2 ], guidless[ 2 ];
  int l;
  char lname_fmt[ 5 ];

  //get amount of invisible players
  for( i = 0; i < level.maxclients; i++ ) {
    p = &level.clients[ i ];
    if ( p->sess.invisible == qtrue )
      invisiblePlayers++;
  }

  ADMBP_begin();
  ADMBP( va( "^3!listplayers^7: %d players connected:\n",
    level.numConnectedClients - invisiblePlayers ) );
  for( i = 0; i < level.maxclients; i++ )
  {
    p = &level.clients[ i ];

    // Ignore invisible players
    if ( p->sess.invisible == qtrue )
      continue;

    Q_strncpyz( t, "S", sizeof( t ) );
    Q_strncpyz( c, S_COLOR_YELLOW, sizeof( c ) );
    if( p->pers.teamSelection == PTE_HUMANS )
    {
      Q_strncpyz( t, "H", sizeof( t ) );
      Q_strncpyz( c, S_COLOR_BLUE, sizeof( c ) );
    }
    else if( p->pers.teamSelection == PTE_ALIENS )
    {
      Q_strncpyz( t, "A", sizeof( t ) );
      Q_strncpyz( c, S_COLOR_RED, sizeof( c ) );
    }

    if( p->pers.connected == CON_CONNECTING )
    {
      Q_strncpyz( t, "C", sizeof( t ) );
      Q_strncpyz( c, S_COLOR_CYAN, sizeof( c ) );
    }
    else if( p->pers.connected != CON_CONNECTED )
    {
      continue;
    }

    guidless[ 0 ] = '\0';
    if( !Q_stricmp( p->pers.guid, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" ) 
        || ( G_admin_permission( &g_entities[ i ], ADMF_INCOGNITO )
             && !admin_higher( ent, &g_entities[ i ] )
             && !G_admin_permission( ent, ADMF_SEESINCOGNITO ) ) )
    {
      Q_strncpyz( guidless, "G", sizeof( guidless ) );
    }
    muted[ 0 ] = '\0';
    if( G_admin_permission( &g_entities[ i ], ADMF_NO_VOTE ) || G_admin_permission( &g_entities[ i ], ADMF_FAKE_NO_VOTE )  )
    {
      Q_strncpyz( muted, "V", sizeof( muted ) );
    }
    if( p->pers.muted )
    {
      Q_strncpyz( muted, "M", sizeof( muted ) );
    }
    denied[ 0 ] = '\0';
    if( p->pers.denyBuild )
    {
      Q_strncpyz( denied, "B", sizeof( denied ) );
    }
    if( p->pers.denyHumanWeapons || p->pers.denyAlienClasses )
    {
      Q_strncpyz( denied, "W", sizeof( denied ) );
    }

    dbuilder[ 0 ] = '\0';
    if( p->pers.designatedBuilder )
    {
      if( !G_admin_permission( &g_entities[ i ], ADMF_INCOGNITO ) &&
          G_admin_permission( &g_entities[ i ], ADMF_DBUILDER ) && 
          G_admin_permission(ent, ADMF_SEESFULLLISTPLAYERS ) )
      {
        Q_strncpyz( dbuilder, "P", sizeof( dbuilder ) );
      }
      else
      {
        Q_strncpyz( dbuilder, "D", sizeof( dbuilder ) );
      }
    }
    immune[ 0 ] = '\0';
    if( G_admin_permission( &g_entities[ i ], ADMF_BAN_IMMUNITY ) &&
        G_admin_permission(ent, ADMF_SEESFULLLISTPLAYERS ) )
    {
      Q_strncpyz( immune, "I", sizeof( immune ) );
    }

    if( p->pers.paused )
    {
      // use immunity slot for paused player status
      Q_strncpyz( immune, "L", sizeof( immune ) );
    }

    l = 0;
    G_SanitiseString( p->pers.netname, n2, sizeof( n2 ) );
    n[ 0 ] = '\0';
    for( j = 0; j < MAX_ADMIN_ADMINS && g_admin_admins[ j ]; j++ )
    {
      if( !Q_stricmp( g_admin_admins[ j ]->guid, p->pers.guid ) )
      {

        // don't gather aka or level info if the admin is incognito
        if( ent && G_admin_permission( &g_entities[ i ], ADMF_INCOGNITO ) 
                && !G_admin_permission(ent, ADMF_SEESINCOGNITO) 
                && ( &g_entities[ i ] != ent ) )
        {
          break;
        }
        l = g_admin_admins[ j ]->level;
        G_SanitiseString( g_admin_admins[ j ]->name, n3, sizeof( n3 ) );
        if( Q_stricmp( n2, n3 ) )
        {
          Q_strncpyz( n, g_admin_admins[ j ]->name, sizeof( n ) );
        }
        break;
      }
    }
    lname[ 0 ] = '\0';
    Q_strncpyz( lname_fmt, "%s", sizeof( lname_fmt ) );
    for( j = 0; j < MAX_ADMIN_LEVELS && g_admin_levels[ j ]; j++ )
    {
      if( g_admin_levels[ j ]->level == l )
      {
        Q_strncpyz( lname, g_admin_levels[ j ]->name, sizeof( lname ) );
        if( *lname )
        {
          G_DecolorString( lname, lname2 );
          Com_sprintf( lname_fmt, sizeof( lname_fmt ), "%%%is",
            ( admin_level_maxname + (int)( strlen( lname ) - strlen( lname2 ) ) ) );
          Com_sprintf( lname2, sizeof( lname2 ), lname_fmt, lname );
        }
        break;
      }

    }

    if ( G_admin_permission(ent, ADMF_SEESFULLLISTPLAYERS ) ) {
      ADMBP( va( "%2i %s%s^7 %-3i %s^7 ^1%1s%1s%1s%1s%1s^7 %s^7 %s%s^7%s\n",
               i,
               c,
               t,
               l,
               ( *lname ) ? lname2 : "", 
               immune,
               muted,
               dbuilder,
               denied,
               guidless,
               p->pers.netname,
               ( *n ) ? "(a.k.a. " : "",
               n,
               ( *n ) ? ")" : ""
             ) );
    } else {
      ADMBP( va( "%2i %s%s^7 %-3i %s^7 ^1%1s%1s%1s%1s^7 %s^7 %s%s^7%s\n",
               i,
               c,
               t,
               l,
               ( *lname ) ? lname2 : "", 
               immune,
               muted,
               dbuilder,
               denied,
               p->pers.netname,
               ( *n ) ? "(a.k.a. " : "",
               n,
               ( *n ) ? ")" : ""
             ) );
    }
  }
  ADMBP_end();
  return qtrue;
}

#define MAX_LISTMAPS_MAPS 256

static int SortMaps(const void *a, const void *b)
{
  return strcmp(*(char **)a, *(char **)b);
}

qboolean G_admin_listmaps( gentity_t *ent, int skiparg )
{
  char fileList[ 4096 ] = {""};
  char *fileSort[ MAX_LISTMAPS_MAPS ];
  char search[ 16 ] = {""};
  int numFiles;
  int i;
  int fileLen = 0;
  int  count = 0;
  char *filePtr;
  int rows;

  if( G_SayArgc( ) > 1 + skiparg )
  {
    G_SayArgv( skiparg + 1, search, sizeof( search ) );
  }

  numFiles = trap_FS_GetFileList( "maps/", ".bsp",
    fileList, sizeof( fileList ) );
  filePtr = fileList;
  for( i = 0; i < numFiles && count < MAX_LISTMAPS_MAPS; i++, filePtr += fileLen + 1 )
  {
    fileLen = strlen( filePtr );
    if (fileLen < 5)
      continue;

    filePtr[ fileLen - 4 ] = '\0';

    if( search[ 0 ] && !strstr( filePtr, search ) )
      continue;

    fileSort[ count ] = filePtr;
    count++;
  }

  qsort(fileSort, count, sizeof(fileSort[ 0 ]), SortMaps);

  rows = count / 3;
  if ( rows * 3 < count ) rows++;

  ADMBP_begin();
  for( i = 0; i < rows; i++ )
  {
    ADMBP( va( "^7%20s %20s %20s\n",
      fileSort[ i ],
      ( rows + i < count ) ? fileSort[ rows + i ] : "",
      ( rows * 2 + i < count ) ? fileSort[ rows * 2 + i ] : "" ) );
  }
  if ( search[ 0 ] )
    ADMBP( va( "^3!listmaps: ^7found %d maps matching '%s^7'.\n", count, search ) );
  else
    ADMBP( va( "^3!listmaps: ^7listing %d maps.\n", count ) );

  ADMBP_end();

  return qtrue;
}

qboolean G_admin_listrotation( gentity_t *ent, int skiparg )
{
  int i, j, statusColor;
  char mapnames[ MAX_STRING_CHARS ];
  char *status = NULL;

  extern mapRotations_t mapRotations;

  // Check for an active map rotation
  if ( !G_MapRotationActive() ||
       g_currentMapRotation.integer == NOT_ROTATING )
  {
    trap_SendServerCommand( ent-g_entities, "print \"^3!rotation: ^7There is no active map rotation on this server\n\"" );
    return qfalse;
  }

  // Locate the active map rotation and output its contents
  for( i = 0; i < mapRotations.numRotations; i++ )
  {
    if ( i == g_currentMapRotation.integer )
    {
      int currentMap = G_GetCurrentMap( i );

      ADMBP_begin();
      ADMBP( va( "^3!rotation: ^7%s\n", mapRotations.rotations[ i ].name ) );

      for( j = 0; j < mapRotations.rotations[ i ].numMaps; j++ )
      {
        Q_strncpyz( mapnames, mapRotations.rotations[ i ].maps[ j ].name, sizeof( mapnames ) );

        if( !Q_stricmp( mapRotations.rotations[ i ].maps[ j ].name, "*VOTE*" ) )
        {
          char slotMap[ 64 ];
          int lineLen = 0;
          int k;

          trap_Cvar_VariableStringBuffer( "mapname", slotMap, sizeof( slotMap ) );
          mapnames[ 0 ] = '\0';
          for( k = 0; k < mapRotations.rotations[ i ].maps[ j ].numConditions; k++ )
          {
            char *thisMap;
            int mc = 7;

            if( mapRotations.rotations[ i ].maps[ j ].conditions[ k ].lhs != MCV_VOTE )
              continue;

            thisMap = mapRotations.rotations[ i ].maps[ j ].conditions[ k ].dest;
            lineLen += strlen( thisMap ) + 1;

            if( currentMap == j && !Q_stricmp( thisMap, slotMap ) )
              mc = 3;
            Q_strcat( mapnames, sizeof( mapnames ), va( "^7%s%s^%i%s",
              ( k ) ? ", " : "",
              ( lineLen > 50 ) ? "\n                  " : "",
              mc, thisMap ) );
            if( lineLen > 50 )
              lineLen = strlen( thisMap ) + 2;
            else
              lineLen++;
          }

          if( currentMap == j )
          {
            statusColor = 3;
            status = "current slot";
          }
          else if( !k )
          {
            statusColor = 1;
            status = "empty vote";
          }
          else
          {
            statusColor = 7;
            status = "vote";
          }
        } else if( !Q_stricmp( mapRotations.rotations[ i ].maps[ j ].name, "*RANDOM*" ) )
        {
          char slotMap[ 64 ];
          int lineLen = 0;
          int k;

          trap_Cvar_VariableStringBuffer( "mapname", slotMap, sizeof( slotMap ) );
          mapnames[ 0 ] = '\0';
          for( k = 0; k < mapRotations.rotations[ i ].maps[ j ].numConditions; k++ )
          {
            char *thisMap;
            int mc = 7;

            if( mapRotations.rotations[ i ].maps[ j ].conditions[ k ].lhs != MCV_SELECTEDRANDOM )
              continue;

            thisMap = mapRotations.rotations[ i ].maps[ j ].conditions[ k ].dest;
            lineLen += strlen( thisMap ) + 1;

            if( currentMap == j && !Q_stricmp( thisMap, slotMap ) )
              mc = 3;
            Q_strcat( mapnames, sizeof( mapnames ), va( "^7%s%s^%i%s",
                      ( k ) ? ", " : "",
                        ( lineLen > 50 ) ? "\n                  " : "",
                          mc, thisMap ) );
            if( lineLen > 50 )
              lineLen = strlen( thisMap ) + 2;
            else
              lineLen++;
          }

          if( currentMap == j )
          {
            statusColor = 3;
            status = "current slot";
          }
          else if( !k )
          {
            statusColor = 1;
            status = "empty Random";
          }
          else
          {
            statusColor = 7;
            status = "Random";
          }
        }
        else if ( currentMap == j )
        {
          statusColor = 3;
          status = "current slot";
        }
        else if ( !G_MapExists( mapRotations.rotations[ i ].maps[ j ].name ) )
        {
          statusColor = 1;
          status = "missing";
        }
        else
        {
          statusColor = 7;
          status = "";
        }
        ADMBP( va( " ^%i%-12s %3i %s\n", statusColor, status, j + 1, mapnames ) );
      }

      ADMBP_end();

      // No maps were found in the active map rotation
      if ( mapRotations.rotations[ i ].numMaps < 1 )
      {
        trap_SendServerCommand( ent-g_entities, "print \"  - ^7Empty!\n\"" );
        return qfalse;
      }
    }
  }

  if( g_nextMap.string[0] )
  {
    ADMP( va ("^5 Next map overriden by g_nextMap to: %s\n", g_nextMap.string ) );
  }
  
  return qtrue;
}


qboolean G_admin_showbans( gentity_t *ent, int skiparg )
{
  int i, found = 0;
  int t;
  char length[ 32 ];
  char duration[ 32 ];
  char sduration[ 32 ];
  char status[ 64 ] = { "" };
  int max_name = 1, max_banner = 1;
  int secs;
  int start = 0;
  char filter[ MAX_NAME_LENGTH ] = {""};
  char date[ 11 ];
  char *made;
  int j;
  char n1[ MAX_NAME_LENGTH * 2 ] = {""};
  char n2[ MAX_NAME_LENGTH * 2 ] = {""};
  qboolean numeric = qtrue;
  char *ip_match = NULL;
  int ip_match_len = 0;
  char name_match[ MAX_NAME_LENGTH ] = {""};
  int show_count = 0;
  qboolean subnetfilter = qfalse;

  t = trap_RealTime( NULL );

  for( i = 0; i < MAX_ADMIN_BANS && g_admin_bans[ i ]; i++ )
  {
    if( g_admin_bans[ i ]->expires != 0
      && ( g_admin_bans[ i ]->expires - t ) < 1 )
    {
      continue;
    }
    found++;
  }

  if( G_SayArgc() >= 2 + skiparg )
  {
    G_SayArgv( 1 + skiparg, filter, sizeof( filter ) );
    if( G_SayArgc() >= 3 + skiparg )
    {
      start = atoi( filter );
      G_SayArgv( 2 + skiparg, filter, sizeof( filter ) );
    }
    for( i = 0; i < sizeof( filter ) && filter[ i ] ; i++ )
    {
      if( ( filter[ i ] < '0' || filter[ i ] > '9' )
        && filter[ i ] != '.' && filter[ i ] != '-' )
      {
        numeric = qfalse;
        break;
      }
    }

    if (!numeric)
    {
      if( filter[ 0 ] != '-' )
      {
        G_SanitiseString( filter, name_match, sizeof( name_match) );

      }
      else
      {
        if( !Q_strncmp( filter, "-sub", 4 ) )
        {
          subnetfilter = qtrue;
        }
        else
        {
          ADMP( va( "^3!showbans: ^7invalid argument %s\n", filter ) );
          return qfalse;
        }
      }
    }
    else if( strchr( filter, '.' ) != NULL )
    {
      ip_match = filter;
      ip_match_len = strlen(ip_match);
    }
    else
    {
      start = atoi( filter );
      filter[0] = '\0';
    }
    // showbans 1 means start with ban 0
    if( start > 0 )
      start -= 1;
    else if( start < 0 )
      start = found + start;
  }
  
  if( start >= MAX_ADMIN_BANS || start < 0 )
    start = 0;

  for( i = start; i < MAX_ADMIN_BANS && g_admin_bans[ i ] 
    && show_count < MAX_ADMIN_SHOWBANS; i++ )
  {
    qboolean match = qfalse;

    if (!numeric)
      {
        if( !subnetfilter )
        {
          G_SanitiseString( g_admin_bans[ i ]->name, n1, sizeof( n1 ) );
          if (strstr( n1, name_match) )
            match = qtrue;
        }
        else
        {
          int mask = -1;
          int dummy;
          int scanflen = 0;
          scanflen = sscanf( g_admin_bans[ i ]->ip, "%d.%d.%d.%d/%d", &dummy, &dummy, &dummy, &dummy, &mask );
          if( scanflen == 5 && mask < 32 )
          {
            match = qtrue;
          }
        }
      }

    if ( ( match ) || !ip_match
      || Q_strncmp( ip_match, g_admin_bans[ i ]->ip, ip_match_len) == 0 )
    {
      G_DecolorString( g_admin_bans[ i ]->name, n1 );
      G_DecolorString( g_admin_bans[ i ]->banner, n2 );
      if( strlen( n1 ) > max_name )
      {
        max_name = strlen( n1 );
      }
      if( strlen( n2 ) > max_banner )
        max_banner = strlen( n2 );
 
      show_count++;
    }
  }

  if( start >= found )
  {
    ADMP( va( "^3!showbans: ^7there are %d active bans\n", found ) );
    return qfalse;
  }
  ADMBP_begin();
  show_count = 0;
  for( i = start; i < MAX_ADMIN_BANS && g_admin_bans[ i ]
    && show_count < MAX_ADMIN_SHOWBANS; i++ )
  {
    if (!numeric)
    {
      if( !subnetfilter )
      {
        G_SanitiseString( g_admin_bans[ i ]->name, n1, sizeof( n1 ) );
        if ( strstr ( n1, name_match ) == NULL )
          continue;
      }
      else
      {
        int mask = -1;
        int dummy;
        int scanflen = 0;
        scanflen = sscanf( g_admin_bans[ i ]->ip, "%d.%d.%d.%d/%d", &dummy, &dummy, &dummy, &dummy, &mask );
        if( scanflen != 5 || mask >= 32 )
        {
          continue;
        }
      }
    }
    else if( ip_match != NULL
      && Q_strncmp( ip_match, g_admin_bans[ i ]->ip, ip_match_len ) != 0)
      continue;

    // only print out the the date part of made
    date[ 0 ] = '\0';
    made = g_admin_bans[ i ]->made;
    for( j = 0; made && *made; j++ )
    {
      if( ( j + 1 ) >= sizeof( date ) )
        break;
      if( *made == ' ' )
        break;
      date[ j ] = *made;
      date[ j + 1 ] = '\0';
      made++;
    }
    
    status[0] = '\0'; 
    duration[0] = '\0';
    secs = ( g_admin_bans[ i ]->expires - t );

    if( g_admin_bans[ i ]->length == 0 ) // is it permanent?
    {
      Com_sprintf( length, sizeof( length ), "^1PERMANENT" );
    }
    else // otherwise just show how much time is left
    {
      G_admin_duration( g_admin_bans[ i ]->length, length, sizeof( length ) );
      if( secs > 1 )
      {
        G_admin_duration( secs, duration, sizeof( duration ) );
        Com_sprintf( duration, sizeof( duration ), " ^7(^3%s^7 remaining)", duration );
      }
    }

    if( g_admin_bans[ i ]->expires != 0
        && ( g_admin_bans[ i ]->expires - t ) < 1 ) // are they unbanned?
    {
      Com_sprintf( status, sizeof( status ), " ^7(^2expired or unbanned^7)" );
    }
    
    if( ( g_admin_bans[ i ]->suspend > t ) 
        && ( !g_admin_bans[ i ]->expires 
          || g_admin_bans[ i ]->expires - t > 0 ) )
    {
      G_admin_duration( g_admin_bans[ i ]->suspend - t, sduration, sizeof( sduration ) );
      Com_sprintf( status, sizeof( status ), " ^7(^3suspended^7 for ^3%s^7 by %s^7)", sduration, g_admin_bans[ i ]->suspendby );
    }


  
    ADMBP( va( 
      "%4i ^3------------------------------\n"
      "    ^7Name:     ^7%s^7\n"
      "    ^7IP:       ^3%s^7\n"
      "    ^7Admin:    ^7%s^7 (^3%i^7)\n" // admin & level
      "    ^7Reason:   ^3%s^7\n"
      "    ^7Date:     ^3%s^7\n"
      "    ^7Duration: ^3%s%s%s^7\n", // ban length, time remaining & ban status (if applicable)
      ( i + 1 ),
      g_admin_bans[ i ]->name,
      g_admin_bans[ i ]->ip,
      g_admin_bans[ i ]->banner, g_admin_bans[ i ]->bannerlevel,
      g_admin_bans[ i ]->reason,
      date,
      length, duration, status
    ) );

    show_count++;
  }

  if (!numeric || ip_match)
  {
    char matchmethod[50];
    if( numeric ) 
      Com_sprintf( matchmethod, sizeof(matchmethod), "IP" );
    else if( !subnetfilter )
      Com_sprintf( matchmethod, sizeof(matchmethod), "name" );
    else
      Com_sprintf( matchmethod, sizeof(matchmethod), "ip range size" );


    ADMBP( va( "^3!showbans:^7 found %d matching bans by %s.  ",
             show_count,
             matchmethod ) );
  }
  else
  {
    ADMBP( va( "^3!showbans:^7 showing bans %d - %d of %d.  ",
             ( found ) ? ( start + 1 ) : 0,
             ( ( start + MAX_ADMIN_SHOWBANS ) > found ) ?
             found : ( start + MAX_ADMIN_SHOWBANS ),
             found ) );
  }

  if( ( start + MAX_ADMIN_SHOWBANS ) < found )
  {
    ADMBP( va( "run !showbans %d %s to see more",
             ( start + MAX_ADMIN_SHOWBANS + 1 ),
             (filter[0]) ? filter : "" ) );
  }
  ADMBP( "\n" );
  ADMBP_end();
  return qtrue;
}

qboolean G_admin_help( gentity_t *ent, int skiparg )
{
  int i;
  int commandsPerLine = 6;

  if( G_SayArgc() < 2 + skiparg )
  {
    int j = 0;
    int count = 0;

    ADMBP_begin();
    for( i = 0; i < adminNumCmds; i++ )
    {
      if( G_admin_permission( ent, g_admin_cmds[ i ].flag ) )
      {
        ADMBP( va( "^3!%-12s", g_admin_cmds[ i ].keyword ) );
        j++;
        count++;
      }
      // show 6 commands per line
      if( j == 6 )
      {
        ADMBP( "\n" );
        j = 0;
      }
    }
    for( i = 0; i < MAX_ADMIN_COMMANDS && g_admin_commands[ i ]; i++ )
    {
      if( !G_admin_permission( ent, g_admin_commands[ i ]->flag ) )
        continue;
      ADMBP( va( "^3!%-12s", g_admin_commands[ i ]->command ) );
      j++;
      count++;
      // show 6 commands per line
      if( j == 6 )
      {
        ADMBP( "\n" );
        j = 0;
      }
    }

    if( count )
      ADMBP( "\n" );
    ADMBP( va( "^3!help: ^7%i available commands\n", count ) );
    ADMBP( "run !help [^3command^7] for help with a specific command.\n" );
    ADMBP( "The following non-standard /commands may also be available to you: \n" );
    count = 1;

    if( ent && g_AllStats.integer ) {
      if( count > commandsPerLine && ( count % commandsPerLine ) == 1 ) ADMBP( "\n" );
      ADMBP( va( "^5/%-12s", "allstats" ) );
      count++;
    }
    if ( ent ) {
      if( count > commandsPerLine && ( count % commandsPerLine ) == 1 ) ADMBP( "\n" );
      ADMBP( va( "^5/%-12s", "builder" ) );
      count++;
    }
    if( ent && g_allowVote.integer && G_admin_permission( ent, ADMF_NO_VOTE ) ) {
      if( count > commandsPerLine && ( count % commandsPerLine ) == 1 ) ADMBP( "\n" );
      ADMBP( va( "^5/%-12s", "callvote" ) );
      count++;
    }
    if( ent && g_allowVote.integer && G_admin_permission( ent, ADMF_NO_VOTE ) && ( ent->client->ps.stats[ STAT_PTEAM ] == PTE_ALIENS || ent->client->ps.stats[ STAT_PTEAM ] == PTE_HUMANS ) ) {
      if( count > commandsPerLine && ( count % commandsPerLine ) == 1 ) ADMBP( "\n" );
      ADMBP( va( "^5/%-12s", "callteamvote" ) );
      count++;
    }
    if( ent && g_allowShare.integer && ( ent->client->ps.stats[ STAT_PTEAM ] == PTE_ALIENS || ent->client->ps.stats[ STAT_PTEAM ] == PTE_HUMANS ) ) {
      if( count > commandsPerLine && ( count % commandsPerLine ) == 1 ) ADMBP( "\n" );
      ADMBP( va( "^5/%-12s", "donate" ) );
      count++;
    }
    if( g_privateMessages.integer ) {
      if( count > commandsPerLine && ( count % commandsPerLine ) == 1 ) ADMBP( "\n" );
      ADMBP( va( "^5/%-12s", "m" ) );
      count++;
    }
    if( ent && g_markDeconstruct.integer == 2 && ( ent->client->ps.stats[ STAT_PTEAM ] == PTE_ALIENS || ent->client->ps.stats[ STAT_PTEAM ] == PTE_HUMANS ) ) {
      if( count > commandsPerLine && ( count % commandsPerLine ) == 1 ) ADMBP( "\n" );
      ADMBP( va( "^5/%-12s", "mark" ) );
      count++;
    }
    if( ent && g_actionPrefix.string[0] ) {
      if( count > commandsPerLine && ( count % commandsPerLine ) == 1 ) ADMBP( "\n" );
      ADMBP( va( "^5/%-12s", "me" ) );
      count++;
    }
    if( ent && g_actionPrefix.string[0] ) {
      if( count > commandsPerLine && ( count % commandsPerLine ) == 1 ) ADMBP( "\n" );
      ADMBP( va( "^5/%-12s", "me_team" ) );
      count++;
    }
    if( ent && g_actionPrefix.string[0] && ( ent->client->ps.stats[ STAT_PTEAM ] == PTE_ALIENS || ent->client->ps.stats[ STAT_PTEAM ] == PTE_HUMANS ) ) {
      if( count > commandsPerLine && ( count % commandsPerLine ) == 1 ) ADMBP( "\n" );
      ADMBP( va( "^5/%-12s", "mt" ) );
      count++;
    }
    if( ent && g_myStats.integer && ( ent->client->ps.stats[ STAT_PTEAM ] == PTE_ALIENS || ent->client->ps.stats[ STAT_PTEAM ] == PTE_HUMANS ) ) {
      if( count > commandsPerLine && ( count % commandsPerLine ) == 1 ) ADMBP( "\n" );
      ADMBP( va( "^5/%-12s", "mystats" ) );
      count++;
    }
    if( ent && ent->client->pers.designatedBuilder && ( ent->client->ps.stats[ STAT_PTEAM ] == PTE_ALIENS || ent->client->ps.stats[ STAT_PTEAM ] == PTE_HUMANS ) ) {
      if( count > commandsPerLine && ( count % commandsPerLine ) == 1 ) ADMBP( "\n" );
      ADMBP( va( "^5/%-12s", "protect" ) );
      count++;
    }
    if( ent && ent->client->pers.designatedBuilder && ( ent->client->ps.stats[ STAT_PTEAM ] == PTE_ALIENS || ent->client->ps.stats[ STAT_PTEAM ] == PTE_HUMANS ) ) {
      if( count > commandsPerLine && ( count % commandsPerLine ) == 1 ) ADMBP( "\n" );
      ADMBP( va( "^5/%-12s", "resign" ) );
      count++;
    }
    if( g_publicSayadmins.integer || G_admin_permission( ent, ADMF_ADMINCHAT ) ) {
      if( count > commandsPerLine && ( count % commandsPerLine ) == 1 ) ADMBP( "\n" );
      ADMBP( va( "^5/%-12s", "say_admins" ) );
      count++;
    }
    if( ent && ( ent->client->ps.stats[ STAT_PTEAM ] == PTE_ALIENS || ent->client->ps.stats[ STAT_PTEAM ] == PTE_HUMANS ) ) {
      if( count > commandsPerLine && ( count % commandsPerLine ) == 1 ) ADMBP( "\n" );
      ADMBP( va( "^5/%-12s", "say_area" ) );
      count++;
    }
    if( ent && g_allowShare.integer && ( ent->client->ps.stats[ STAT_PTEAM ] == PTE_ALIENS || ent->client->ps.stats[ STAT_PTEAM ] == PTE_HUMANS ) ) {
      if( count > commandsPerLine && ( count % commandsPerLine ) == 1 ) ADMBP( "\n" );
      ADMBP( va( "^5/%-12s", "share" ) );
      count++;
    }
    if( ent && g_teamStatus.integer && ( ent->client->ps.stats[ STAT_PTEAM ] == PTE_ALIENS || ent->client->ps.stats[ STAT_PTEAM ] == PTE_HUMANS ) ) {
      if( count > commandsPerLine && ( count % commandsPerLine ) == 1 ) ADMBP( "\n" );
      ADMBP( va( "^5/%-12s", "teamstatus" ) );
      count++;
    }
    ADMBP( "\n" );
    ADMBP_end();

    return qtrue;
  }
  else
  {
    //!help param
    char param[ MAX_ADMIN_CMD_LEN ];
    char *cmd;

    G_SayArgv( 1 + skiparg, param, sizeof( param ) );
    cmd = ( param[0] == '!' ) ? &param[1] : &param[0];
    ADMBP_begin();
    for( i = 0; i < adminNumCmds; i++ )
    {
      if( !Q_stricmp( cmd, g_admin_cmds[ i ].keyword ) )
      {
        if( !G_admin_permission( ent, g_admin_cmds[ i ].flag ) )
        {
          ADMBP( va( "^3!help: ^7you have no permission to use '%s'\n",
                   g_admin_cmds[ i ].keyword ) );
          ADMBP_end();
          return qfalse;
        }
        ADMBP( va( "^3!help: ^7help for '!%s':\n",
          g_admin_cmds[ i ].keyword ) );
        ADMBP( va( " ^3Function: ^7%s\n", g_admin_cmds[ i ].function ) );
        ADMBP( va( " ^3Syntax: ^7!%s %s\n", g_admin_cmds[ i ].keyword,
                 g_admin_cmds[ i ].syntax ) );
        ADMBP( va( " ^3Flag: ^7'%s'\n", g_admin_cmds[ i ].flag ) );
        ADMBP_end();
        return qtrue;
      }
    }
    for( i = 0; i < MAX_ADMIN_COMMANDS && g_admin_commands[ i ]; i++ )
    {
      if( !Q_stricmp( cmd, g_admin_commands[ i ]->command ) )
      {
        if( !G_admin_permission( ent, g_admin_commands[ i ]->flag ) )
        {
          ADMBP( va( "^3!help: ^7you have no permission to use '%s'\n",
                   g_admin_commands[ i ]->command ) );
          ADMBP_end();
          return qfalse;
        }
        ADMBP( va( "^3!help: ^7help for '%s':\n",
          g_admin_commands[ i ]->command ) );
        ADMBP( va( " ^3Description: ^7%s\n", g_admin_commands[ i ]->desc ) );
        ADMBP( va( " ^3Syntax: ^7!%s\n", g_admin_commands[ i ]->command ) );
        ADMBP_end();
        return qtrue;
      }
    }
    ADMBP( va( "^3!help: ^7no help found for '%s'\n", cmd ) );
    ADMBP_end();
    return qfalse;
  }
}

qboolean G_admin_admintest( gentity_t *ent, int skiparg )
{
  int i, l = 0;
  qboolean found = qfalse;
  qboolean lname = qfalse;

  if( !ent )
  {
    ADMP( "^3!admintest: ^7you are on the console.\n" );
    return qtrue;
  }
  for( i = 0; i < MAX_ADMIN_ADMINS && g_admin_admins[ i ]; i++ )
  {
    if( !Q_stricmp( g_admin_admins[ i ]->guid, ent->client->pers.guid ) )
    {
      found = qtrue;
      break;
    }
  }

  if( found )
  {
    l = g_admin_admins[ i ]->level;
    for( i = 0; i < MAX_ADMIN_LEVELS && g_admin_levels[ i ]; i++ )
    {
      if( g_admin_levels[ i ]->level != l )
        continue;
      if( *g_admin_levels[ i ]->name )
      {
        lname = qtrue;
        break;
      }
    }
  }
  AP( va( "print \"^3!admintest: ^7%s^7 is a level %d admin %s%s^7%s\n\"",
          ent->client->pers.netname,
          l,
          ( lname ) ? "(" : "",
          ( lname ) ? g_admin_levels[ i ]->name : "",
          ( lname ) ? ")" : "" ) );
  return qtrue;
}

qboolean G_admin_allready( gentity_t *ent, int skiparg )
{
  int i = 0;
  gclient_t *cl;

  if( !level.intermissiontime )
  {
    ADMP( "^3!allready: ^7this command is only valid during intermission\n" );
    return qfalse;
  }

  for( i = 0; i < g_maxclients.integer; i++ )
  {
    cl = level.clients + i;
    if( cl->pers.connected != CON_CONNECTED )
      continue;

    if( cl->pers.teamSelection == PTE_NONE )
      continue;

    cl->readyToExit = 1;
  }
  AP( va( "print \"^3!allready:^7 %s^7 says everyone is READY now\n\"",
     G_admin_adminPrintName( ent ) ) ); 
  return qtrue;
}

qboolean G_admin_cancelvote( gentity_t *ent, int skiparg )
{

  if(!level.voteTime && !level.teamVoteTime[ 0 ] && !level.teamVoteTime[ 1 ] )
  {
    ADMP( "^3!cancelvote^7: no vote in progress\n" );
    return qfalse;
  }
  level.voteNo = level.numConnectedClients;
  level.voteYes = 0;
  CheckVote( );
  level.teamVoteNo[ 0 ] = level.numConnectedClients;
  level.teamVoteYes[ 0 ] = 0;
  CheckTeamVote( PTE_HUMANS );
  level.teamVoteNo[ 1 ] = level.numConnectedClients;
  level.teamVoteYes[ 1 ] = 0;
  CheckTeamVote( PTE_ALIENS );
  AP( va( "print \"^3!cancelvote: ^7%s^7 decided that everyone voted No\n\"",
          G_admin_adminPrintName( ent ) ) );
  return qtrue;
}

qboolean G_admin_passvote( gentity_t *ent, int skiparg )
{
  if(!level.voteTime && !level.teamVoteTime[ 0 ] && !level.teamVoteTime[ 1 ] )
  {
    ADMP( "^3!passvote^7: no vote in progress\n" );
    return qfalse;
  }
  level.voteYes = level.numConnectedClients;
  level.voteNo = 0;
  CheckVote( );
  level.teamVoteYes[ 0 ] = level.numConnectedClients;
  level.teamVoteNo[ 0 ] = 0;
  CheckTeamVote( PTE_HUMANS );
  level.teamVoteYes[ 1 ] = level.numConnectedClients;
  level.teamVoteNo[ 1 ] = 0;
  CheckTeamVote( PTE_ALIENS );
  AP( va( "print \"^3!passvote: ^7%s^7 decided that everyone voted Yes\n\"",
          G_admin_adminPrintName( ent ) ) );
  return qtrue;
}

static qboolean G_admin_global_pause( gentity_t *ent, int skiparg )
{
  if( level.paused )
  {
    level.pauseTime = level.time;
    ADMP( "^3!pause: ^7Game is already paused, unpause timer reset\n" );
    return qfalse;
  }

  level.paused = qtrue;
  level.pauseTime = level.time;

  level.pause_speed = g_speed.value;
  level.pause_gravity = g_gravity.value;
  level.pause_knockback = g_knockback.value;
  level.pause_ff = g_friendlyFire.integer;
  level.pause_ffb = g_friendlyBuildableFire.integer;

  g_speed.value = 0;
  g_gravity.value = 0;
  g_knockback.value = 0;
  g_friendlyFire.integer = 0;
  g_friendlyBuildableFire.integer = 0;

  CP( "cp \"^1Game is PAUSED\"" );
  AP( va( "print \"^3!pause: ^7The game has been paused by %s\n\"",
    G_admin_adminPrintName( ent ) ) );

  return qtrue;
}

static qboolean G_admin_global_unpause( gentity_t *ent, int skiparg )
{
  if( !level.paused )
  {
    ADMP( "^3!unpause: ^7Game is not paused\n" );
    return qfalse;
  }

  level.paused = qfalse;

  g_speed.value = level.pause_speed;
  g_gravity.value = level.pause_gravity;
  g_knockback.value = level.pause_knockback;
  g_friendlyFire.integer = level.pause_ff;
  g_friendlyBuildableFire.integer = level.pause_ffb;

  CP( "cp \"^2Game is RESUMED\"" );
  AP( va( "print \"^3!unpause: ^7The game has been resumed by %s\n\"",
    G_admin_adminPrintName( ent ) ) );

  return qtrue;
}

static qboolean is_numeric(const char *str)
{
	const char *p;

	if (!*str)
		return qfalse;

	for (p = str; *p; p++)
		if (*p < '0' || *p > '9')
			return qfalse;

	return qtrue;
}

qboolean G_admin_pause( gentity_t *ent, int skiparg )
{
  int pids[ MAX_CLIENTS ];
  char name[ MAX_NAME_LENGTH ], err[ MAX_STRING_CHARS ];
  char command[ MAX_ADMIN_CMD_LEN ], *cmd;
  int i;
  int count = 0;
  gentity_t *vic;

  G_SayArgv( skiparg, command, sizeof( command ) );
  cmd = command;
  if( cmd && *cmd == '!' )
    cmd++;

  if( G_SayArgc() < 2 + skiparg )
  {
    // global pause
    if( !Q_stricmp( cmd, "pause" ) )
      return G_admin_global_pause( ent, skiparg );
    else
      return G_admin_global_unpause( ent, skiparg );
  }
  if( G_SayArgc() != 2 + skiparg )
  {
    ADMP( va( "^3!%s: ^7usage: !%s (^5name|slot|*^7)\n", cmd, cmd ) );
    return qfalse;
  }

  G_SayArgv( 1 + skiparg, name, sizeof( name ) );
  if( !Q_stricmp( name, "*" ) )
  {
    for( i = 0; i < MAX_CLIENTS; i++ )
    {
      vic = &g_entities[ i ];
      if( vic && vic->client &&
          vic->client->pers.connected == CON_CONNECTED )
      {
        pids[ count ] = i;
        count++;
      }
    }
  }
  else
  {
    if( G_ClientNumbersFromString( name, pids ) != 1 )
    {
      G_MatchOnePlayer( pids, err, sizeof( err ) );
      ADMP( va( "^3!%s: ^7%s\n", cmd, err ) );
      return qfalse;
    }
    count = 1;
  }

  for( i = 0; i < count; i++ )
  {
    vic = &g_entities[ pids[ i ] ];
    if ( !vic || !vic->client ) continue;
    if( !admin_higher( ent, vic ) )
    {
      if( count == 1 )
        ADMP( va( "^3!%s: ^7sorry, but your intended victim has a higher admin"
                    " level than you\n", cmd ) );
      continue;
    }
    if( vic->client->pers.paused )
    {
      if( !Q_stricmp( cmd, "pause" ) )
      {
        if( count == 1 )
          ADMP( "^3!pause: ^7player is already paused\n" );
        continue;
      }
      vic->client->pers.paused = qfalse;
      CPx( pids[ i ], "cp \"^2You've been unpaused\"" );
      if( count == 1 )
        AP( va( "print \"^3!unpause: ^7%s^7 unpaused by %s\n\"",
            vic->client->pers.netname,
            G_admin_adminPrintName( ent ) ) );
    }
    else
    {
      if( !Q_stricmp( cmd, "unpause" ) )
      {
        if( count == 1 )
          ADMP( "^3!unpause: ^7player is already unpaused\n" );
        continue;
      }
      if( count == 1 && ent == vic)
      {
        ADMP( "^3!pause: ^7you can not pause yourself\n" );
        continue;
      }
      vic->client->pers.paused = qtrue;
      CPx( pids[ i ], va( "cp \"^1You've been paused by ^7%s\"",
          G_admin_adminPrintName( ent ) ) );
      if( count == 1 )
        AP( va( "print \"^3!pause: ^7%s^7 paused by %s\n\"",
            vic->client->pers.netname,
            G_admin_adminPrintName( ent ) ) );
    }
    ClientUserinfoChanged( pids[ i ], qfalse );
  }
  return qtrue;
}

qboolean G_admin_spec999( gentity_t *ent, int skiparg )
{
  int i;
  gentity_t *vic;

  for( i = 0; i < level.maxclients; i++ )
  {
    vic = &g_entities[ i ];
    if( !vic->client )
      continue;
    if( vic->client->pers.connected != CON_CONNECTED )
      continue;
    if( vic->client->pers.teamSelection == PTE_NONE )
      continue;
    if( vic->client->ps.ping == 999 )
    {
      G_ChangeTeam( vic, PTE_NONE, qfalse );
      AP( va( "print \"^3!spec999: ^7%s^7 moved ^7%s^7 to spectators\n\"",
        G_admin_adminPrintName( ent ), 
        vic->client->pers.netname ) );
    }
  }
  return qtrue;
}

qboolean G_admin_register(gentity_t *ent, int skiparg ){
  int level = 0;
  char name[ MAX_NAME_LENGTH ];

  if( !ent ) return qtrue;

  level = G_admin_level(ent);
  memcpy( name, ent->client->pers.netname, sizeof( name ) );

  if( level == 0 )
   level = 1;
  
  if( !Q_stricmp( ent->client->pers.guid, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" ) )
  {
    trap_SendServerCommand( ent->client->ps.clientNum, va(
      "print \"%s\n\"", g_outdatedClientMessage.string ) );
    return qfalse;
  }

  if( !Q_stricmp( Q_CleanStr( name ), "UnnamedPlayer" ) )
  {
    ADMP( va( "^3!register:^7 You cannot register 'UnnamedPlayer'.\n" ) );
    return qfalse;
  }

  if( g_newbieNumbering.integer
    && g_newbieNamePrefix.string[ 0 ]
    && !Q_stricmpn ( ent->client->pers.netname, g_newbieNamePrefix.string, strlen(g_newbieNamePrefix.string ) ) )
  {
    ADMP( va( "^3!register:^7 You cannot register names that begin with '%s^7'.\n",
      g_newbieNamePrefix.string ) );
    return qfalse;
  }

  trap_SendConsoleCommand( EXEC_APPEND,va( "!setlevel %d %d;",(int)(ent - g_entities), level) );
  
  AP( va( "print \"^3!register: ^7%s^7 is now a protected nickname.\n\"", ent->client->pers.netname) );
  
  return qtrue;
}

qboolean G_admin_rename( gentity_t *ent, int skiparg )
{
  int pids[ MAX_CLIENTS ];
  char name[ MAX_NAME_LENGTH ];
  char newname[ MAX_NAME_LENGTH ];
  char oldname[ MAX_NAME_LENGTH ];
  char err[ MAX_STRING_CHARS ];
  char userinfo[ MAX_INFO_STRING ];
  char *s;
  gentity_t *victim = NULL;

  if( G_SayArgc() < 3 + skiparg )
  {
    ADMP( "^3!rename: ^7usage: !rename [name] [newname]\n" );
    return qfalse;
  }
  G_SayArgv( 1 + skiparg, name, sizeof( name ) );
  s = G_SayConcatArgs( 2 + skiparg );
  Q_strncpyz( newname, s, sizeof( newname ) );
  if( G_ClientNumbersFromString( name, pids ) != 1 )
  {
    G_MatchOnePlayer( pids, err, sizeof( err ) );
    ADMP( va( "^3!rename: ^7%s\n", err ) );
    return qfalse;
  }
  victim = &g_entities[ pids[ 0 ] ] ;
  if( !admin_higher( ent, victim ) )
  {
    ADMP( "^3!rename: ^7sorry, but your intended victim has a higher admin"
        " level than you\n" );
    return qfalse;
  }
  if( !G_admin_name_check( victim, newname, err, sizeof( err ) ) )
  {
    G_admin_print( ent, va( "^3!rename: Invalid name: ^7%s\n", err ) );
    return qfalse;
  }
  level.clients[ pids[ 0 ] ].pers.nameChanges--;
  level.clients[ pids[ 0 ] ].pers.nameChangeTime = 0;
  trap_GetUserinfo( pids[ 0 ], userinfo, sizeof( userinfo ) );
  s = Info_ValueForKey( userinfo, "name" );
  Q_strncpyz( oldname, s, sizeof( oldname ) );
  Info_SetValueForKey( userinfo, "name", newname );
  trap_SetUserinfo( pids[ 0 ], userinfo );
  ClientUserinfoChanged( pids[ 0 ], qtrue );
  if( strcmp( oldname, level.clients[ pids[ 0 ] ].pers.netname ) )
    AP( va( "print \"^3!rename: ^7%s^7 has been renamed to %s^7 by %s\n\"",
        oldname,
        level.clients[ pids[ 0 ] ].pers.netname,
        G_admin_adminPrintName( ent ) ) );
  return qtrue;
}

qboolean G_admin_restart( gentity_t *ent, int skiparg )
{
  char layout[ MAX_CVAR_VALUE_STRING ] = { "" };
  char teampref[ MAX_CVAR_VALUE_STRING ] = { "" };
  int i;
  gclient_t *cl;

  if( G_SayArgc( ) > 1 + skiparg )
  {
    char map[ MAX_QPATH ];

    trap_Cvar_VariableStringBuffer( "mapname", map, sizeof( map ) );
    G_SayArgv( skiparg + 1, layout, sizeof( layout ) );

    if( Q_stricmp( layout, "keepteams" ) && Q_stricmp( layout, "keepteamslock" ) && Q_stricmp( layout, "switchteams" ) && Q_stricmp( layout, "switchteamslock" ) )
    {
      if( !Q_stricmp( layout, "*BUILTIN*" ) ||
        trap_FS_FOpenFile( va( "layouts/%s/%s.dat", map, layout ),
          NULL, FS_READ ) > 0 )
      {
        trap_Cvar_Set( "g_layouts", layout );
      }
      else
      {
        ADMP( va( "^3!restart: ^7layout '%s' does not exist\n", layout ) );
        return qfalse;
      }
    }
    else 
    {
      strcpy(layout,"");
      G_SayArgv( skiparg + 1, teampref, sizeof( teampref ) );    
    }
  }
  
  if( G_SayArgc( ) > 2 + skiparg ) 
  {
    G_SayArgv( skiparg + 2, teampref, sizeof( teampref ) );      
  }
  
  
  if( !Q_stricmp( teampref, "keepteams" ) || !Q_stricmp( teampref, "keepteamslock" ) )
  {
    for( i = 0; i < g_maxclients.integer; i++ )
    {
      cl = level.clients + i;
      if( cl->pers.connected != CON_CONNECTED )
        continue;

      if( cl->pers.teamSelection == PTE_NONE )
        continue;

      cl->sess.restartTeam = cl->pers.teamSelection;
    }
  } 
  else if(!Q_stricmp( teampref, "switchteams" ) ||  !Q_stricmp( teampref, "switchteamslock" ))
  {
    for( i = 0; i < g_maxclients.integer; i++ )
    {
      cl = level.clients + i;
      if( cl->pers.connected != CON_CONNECTED )
        continue;

      if( cl->pers.teamSelection == PTE_NONE )
        continue;

      if( cl->pers.teamSelection == PTE_ALIENS )
        cl->sess.restartTeam = PTE_HUMANS;
      else if(cl->pers.teamSelection == PTE_HUMANS )
        cl->sess.restartTeam = PTE_ALIENS;
    }    
  }
  
  if( !Q_stricmp( teampref, "switchteamslock" ) || !Q_stricmp( teampref, "keepteamslock" ) )
  {
    trap_Cvar_Set( "g_lockTeamsAtStart", "1" );
  }

  trap_SendConsoleCommand( EXEC_APPEND, "map_restart" );
  
  if(teampref[ 0 ])
    strcpy(teampref,va( "^7(with teams option: '%s^7')", teampref ));
  
  G_admin_maplog_result( "R" );
  
  AP( va( "print \"^3!restart: ^7map restarted by %s %s %s\n\"",
          G_admin_adminPrintName( ent ),
          ( layout[ 0 ] ) ? va( "^7(forcing layout '%s^7')", layout ) : "",
          teampref ) );
  return qtrue;
}

qboolean G_admin_nobuild( gentity_t *ent, int skiparg )
{
  char buffer[ MAX_STRING_CHARS ];
  int  i, tmp;
  
  if( G_SayArgc() < 2 + skiparg )
  {
    ADMP( "^3!nobuild: ^7usage: !nobuild (^5enable / disable / log / remove / save^7)\n" );
    return qfalse;
  }
  
  G_SayArgv( 1 + skiparg, buffer, sizeof( buffer ) );
  
  if( !Q_stricmp( buffer, "enable" ) || !Q_stricmp( buffer, "Enable" ) )
  {
  	if( G_SayArgc() < 4 + skiparg )
  	{
		ADMP( "^3!nobuild: ^7usage: !nobuild enable (^5area^7) (^5height^7)\n" );
		return qfalse;
  	}
	
  	if( !level.noBuilding )
  	{
	
  		level.noBuilding = qtrue;
		
		// Grab and set the area
		G_SayArgv( 2 + skiparg, buffer, sizeof( buffer ) );
		tmp = atoi( buffer );
		level.nbArea = tmp;
		
		// Grab and set the height
		G_SayArgv( 3 + skiparg, buffer, sizeof( buffer ) );
		tmp = atoi( buffer );
		level.nbHeight = tmp;
		
		ADMP( "^3!nobuild: ^7nobuild is now enabled, please place a buildable to spawn a marker\n" );
		return qtrue;
  	}
	else
	{
		ADMP( "^3!nobuild: ^7nobuild is already enabled. type !nobuild disable to disable nobuild mode.\n" );
		return qfalse;
	}
  }
  
  if( !Q_stricmp( buffer, "disable" ) || !Q_stricmp( buffer, "Disable" ) )
  {
  	if( level.noBuilding )
  	{
  		level.noBuilding = qfalse;
		level.nbArea = 0.0f;
		level.nbHeight = 0.0f;
		ADMP( "^3!nobuild: ^7nobuild is now disabled\n" );
		return qtrue;
  	}
	else
	{
		ADMP( "^3!nobuild: ^7nobuild is disabled. type !nobuild enable (^5area^7) (^5height^7) to enable nobuild mode.\n" );
		return qfalse;
	}
  }
  
  if( !Q_stricmp( buffer, "log" ) || !Q_stricmp( buffer, "Log" ) )
  {
 	ADMBP_begin();
	
	tmp = 0;
  	for( i = 0; i < MAX_GENTITIES; i++ )
  	{
  		if( level.nbMarkers[ i ].Marker == NULL )
  		continue;
		
		// This will display a start at 1, and not 0. This is to stop confusion by server ops
		ADMBP( va( "^7#%i at origin (^5%f %f %f^7)^7\n", i + 1, level.nbMarkers[ i ].Origin[0], level.nbMarkers[ i ].Origin[1], level.nbMarkers[ i ].Origin[2] ) );
		tmp++;
 	}
	ADMBP( va( "^3!nobuild:^7 displaying %i marker(s)\n", tmp ) );
	
  	ADMBP_end();
	return qtrue;
  }
  
  if( !Q_stricmp( buffer, "remove" ) || !Q_stricmp( buffer, "Remove" ) )
  {
 	if( G_SayArgc() < 3 + skiparg )
  	{
		ADMP( "^3!nobuild: ^7usage: !nobuild remove (^5marker #^7)\n" );
		return qfalse;
  	}
	
	G_SayArgv( 2 + skiparg, buffer, sizeof( buffer ) );
	tmp = atoi( buffer ) - 1;
	// ^ that was to work with the display number...
	
	if( level.nbMarkers[ tmp ].Marker == NULL )
	{
		ADMP( "^3!nobuild: ^7that is not a valid marker number\n" );
		return qfalse;
	}
	// Donno why im doing this, but lets clear this...
	level.nbMarkers[ tmp ].Marker->noBuild.isNB = qfalse;
	level.nbMarkers[ tmp ].Marker->noBuild.Area = 0.0f;
	level.nbMarkers[ tmp ].Marker->noBuild.Height = 0.0f;
	
	// Free the entitiy and null it out...
	G_FreeEntity( level.nbMarkers[ tmp ].Marker );
	level.nbMarkers[ tmp ].Marker = NULL;
	
	// That is to work with the display number...
	ADMP( va( "^3!nobuild:^7 marker %i has been removed\n", tmp + 1 ) );
	return qtrue;
  }
  
  if( !Q_stricmp( buffer, "save" ) || !Q_stricmp( buffer, "Save" ) )
  {
  	int  i, tmp;
	
 	G_NobuildSave( );
	
	tmp = 0;
  	for( i = 0; i < MAX_GENTITIES; i++ )
  	{
  		if( level.nbMarkers[ i ].Marker == NULL )
  		continue;
		
		tmp++;
 	}
	ADMP( va( "^3!nobuild:^7 %i nobuild markers have been saved\n", tmp ) );
	return qtrue;
  }
  return qfalse;
}

qboolean G_admin_nextmap( gentity_t *ent, int skiparg )
{
  AP( va( "print \"^3!nextmap: ^7%s^7 decided to load the next map\n\"",
    G_admin_adminPrintName( ent ) ) );
  level.lastWin = PTE_NONE;
  trap_SetConfigstring( CS_WINNER, "Evacuation" );
  LogExit( va( "nextmap was run by %s",
    G_admin_adminPrintName( ent ) ) );
  G_admin_maplog_result( "N" );
  return qtrue;
}

static const char *displaySchachtmeisterJudgement(const schachtmeisterJudgement_t *j,
                                                  g_admin_namelog_t *namelog)
{
	static char buffer[20];

    if (G_admin_permission_guid(namelog->guid, ADMF_INCOGNITO)) {
	    Com_sprintf(buffer, sizeof(buffer), "^2   +0");
    } else if (strcmp(namelog->guid, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX") &&
	    (G_admin_permission_guid(namelog->guid, ADMF_NOAUTOBAHN) ||
	     G_admin_permission_guid(namelog->guid, ADMF_IMMUNITY))) {
		Com_sprintf(buffer, sizeof(buffer), "^7 N/A ");
	} else if (!j->ratingTime) {
		Com_sprintf(buffer, sizeof(buffer), "^5 wait");
	} else {
		int color;

		if (j->rating >= g_schachtmeisterClearThreshold.integer)
			color = 2;
		else if (j->rating <= g_schachtmeisterAutobahnThreshold.integer)
			color = 1;
		else
			color = 3;

		Com_sprintf(buffer, sizeof(buffer), "^%i%+5i", color, j->rating);
	}

	return buffer;
}

qboolean G_admin_namelog( gentity_t *ent, int skiparg )
{
  int i, j;
  char search[ MAX_NAME_LENGTH ] = {""};
  char s2[ MAX_NAME_LENGTH ] = {""};
  char n2[ MAX_NAME_LENGTH ] = {""};
  char guid_stub[ 9 ];
  qboolean found = qfalse;
  int printed = 0;

  if( G_SayArgc() > 1 + skiparg )
  {
    G_SayArgv( 1 + skiparg, search, sizeof( search ) );
    G_SanitiseString( search, s2, sizeof( s2 ) );
  }
  ADMBP_begin();
  for( i = 0; i < MAX_ADMIN_NAMELOGS && g_admin_namelog[ i ]; i++ )
  {
    if( search[0] )
    {
      found = qfalse;
      for( j = 0; j < MAX_ADMIN_NAMELOG_NAMES && 
        g_admin_namelog[ i ]->name[ j ][ 0 ]; j++ )
      {
        G_SanitiseString( g_admin_namelog[ i ]->name[ j ], n2, sizeof( n2 ) );
        if( strstr( n2, s2 ) )
        {
          found = qtrue;
          break;
        }
      }
      if( !found )
        continue;
    }
    printed++;

    for( j = 0; j < 8; j++ )
    {
      if( ent && G_admin_permission_guid( g_admin_namelog[ i ]->guid, ADMF_INCOGNITO )
          && !admin_higher_guid( ent->client->pers.guid, g_admin_namelog[ i ]->guid ) 
          && !G_admin_permission( ent, ADMF_SEESINCOGNITO ) )
        guid_stub[ j ] = 'X';
      else
        guid_stub[ j ] = g_admin_namelog[ i ]->guid[ j + 24 ];
    }
    guid_stub[ j ] = '\0';

    if( g_admin_namelog[ i ]->slot > -1 )
       ADMBP( "^3" );
    ADMBP( va( "%-2s (*%s) %15s %s^7", 
      (g_admin_namelog[ i ]->slot > -1 ) ?
        va( "%d", g_admin_namelog[ i ]->slot ) : "-",
      guid_stub, g_admin_namelog[ i ]->ip,
      displaySchachtmeisterJudgement( &g_admin_namelog[ i ]->smj, g_admin_namelog[ i ] ) ) );
    for( j = 0; j < MAX_ADMIN_NAMELOG_NAMES && 
      g_admin_namelog[ i ]->name[ j ][ 0 ]; j++ )
    {
      ADMBP( va( " '%s^7'", g_admin_namelog[ i ]->name[ j ] ) );
    }
    ADMBP( "\n" ); 
  } 
  ADMBP( va( "^3!namelog:^7 %d recent clients found\n", printed ) );
  ADMBP_end();
  return qtrue;
}

qboolean G_admin_lock( gentity_t *ent, int skiparg )
{
  char teamName[2] = {""};
  pTeam_t team;

  if( G_SayArgc() < 2 + skiparg )
  {
    ADMP( "^3!lock: ^7usage: !lock [a|h]\n" );
    return qfalse;
  }
  G_SayArgv( 1 + skiparg, teamName, sizeof( teamName ) );
  if( teamName[ 0 ] == 'a' || teamName[ 0 ] == 'A' )
    team = PTE_ALIENS;
  else if( teamName[ 0 ] == 'h' || teamName[ 0 ] == 'H' )
    team = PTE_HUMANS;
  else
  {
    ADMP( va( "^3!lock: ^7invalid team\"%c\"\n", teamName[0] ) );
    return qfalse;
  }

  if( team == PTE_ALIENS )
  {
    if( level.alienTeamLocked )
    {
      ADMP( "^3!lock: ^7Alien team is already locked\n" );
      return qfalse;
    }
    else
      level.alienTeamLocked = qtrue;
  }
  else if( team == PTE_HUMANS ) {
    if( level.humanTeamLocked )
    {
      ADMP( "^3!lock: ^7Human team is already locked\n" );
      return qfalse;
    }
    else
      level.humanTeamLocked = qtrue;
  }

  AP( va( "print \"^3!lock: ^7%s team has been locked by %s\n\"",
    ( team == PTE_ALIENS ) ? "Alien" : "Human",
    G_admin_adminPrintName( ent ) ) );
  return qtrue;
} 

qboolean G_admin_unlock( gentity_t *ent, int skiparg )
{
  char teamName[2] = {""};
  pTeam_t team;

  if( G_SayArgc() < 2 + skiparg )
  {
    ADMP( "^3!unlock: ^7usage: !unlock [a|h]\n" );
    return qfalse;
  }
  G_SayArgv( 1 + skiparg, teamName, sizeof( teamName ) );
  if( teamName[ 0 ] == 'a' || teamName[ 0 ] == 'A' )
    team = PTE_ALIENS;
  else if( teamName[ 0 ] == 'h' || teamName[ 0 ] == 'H' )
    team = PTE_HUMANS;
  else
  {
    ADMP( va( "^3!unlock: ^7invalid team\"%c\"\n", teamName[0] ) );
    return qfalse;
  }
  
  if( team == PTE_ALIENS )
  {
    if( !level.alienTeamLocked )
    {
      ADMP( "^3!unlock: ^7Alien team is not currently locked\n" );
      return qfalse;
    }
    else
      level.alienTeamLocked = qfalse;
  }
  else if( team == PTE_HUMANS ) {
    if( !level.humanTeamLocked )
    {
      ADMP( "^3!unlock: ^7Human team is not currently locked\n" );
      return qfalse;
    }
    else
      level.humanTeamLocked = qfalse;
  }

  AP( va( "print \"^3!unlock: ^7%s team has been unlocked by %s\n\"",
    ( team == PTE_ALIENS ) ? "Alien" : "Human",
    G_admin_adminPrintName( ent ) ) );
  return qtrue;
} 

qboolean G_admin_designate( gentity_t *ent, int skiparg )
{
  int pids[ MAX_CLIENTS ];
  char name[ MAX_NAME_LENGTH ], err[ MAX_STRING_CHARS ];
  char command[ MAX_ADMIN_CMD_LEN ], *cmd;
  gentity_t *vic;

  if( G_SayArgc() < 2 + skiparg )
  {
    ADMP( "^3!designate: ^7usage: designate [name|slot#]\n" );
    return qfalse;
  }
  G_SayArgv( skiparg, command, sizeof( command ) );
  cmd = command;
  if( cmd && *cmd == '!' )
    cmd++;
  G_SayArgv( 1 + skiparg, name, sizeof( name ) );
  if( G_ClientNumbersFromString( name, pids ) != 1 )
  {
    G_MatchOnePlayer( pids, err, sizeof( err ) );
    ADMP( va( "^3!designate: ^7%s\n", err ) );
    return qfalse;
  }
  if( !admin_higher( ent, &g_entities[ pids[ 0 ] ] ) &&
    !Q_stricmp( cmd, "undesignate" ) )
  {
    ADMP( "^3!designate: ^7sorry, but your intended victim has a higher admin"
        " level than you\n" );
    return qfalse;
  }
  vic = &g_entities[ pids[ 0 ] ];
  if( vic->client->pers.designatedBuilder == qtrue )
  {
    if( !Q_stricmp( cmd, "designate" ) )
    {
      ADMP( "^3!designate: ^7player is already designated builder\n" );
      return qtrue;
    }
    vic->client->pers.designatedBuilder = qfalse;
    CPx( pids[ 0 ], "cp \"^1Your designation has been revoked\"" );
    AP( va(
      "print \"^3!designate: ^7%s^7's designation has been revoked by %s\n\"",
       vic->client->pers.netname,
       G_admin_adminPrintName( ent ) ) );
    G_CheckDBProtection( );
  }
  else
  {
    if( !Q_stricmp( cmd, "undesignate" ) )
    {
      ADMP( "^3!undesignate: ^7player is not currently designated builder\n" );
      return qtrue;
    }
    vic->client->pers.designatedBuilder = qtrue;
    CPx( pids[ 0 ], "cp \"^1You've been designated\"" );
    AP( va( "print \"^3!designate: ^7%s^7 has been designated by ^7%s\n\"",
      vic->client->pers.netname,
      G_admin_adminPrintName( ent ) ) );
  }
  return qtrue;
}

 //!Warn by Gate (Daniel Evans) 
qboolean G_admin_warn( gentity_t *ent, int skiparg )
{//mostly copy and paste with the proper lines altered from !mute and !kick
  int pids[ MAX_CLIENTS ];
  char name[ MAX_NAME_LENGTH ], *reason, err[ MAX_STRING_CHARS ];
  int minargc;
  gentity_t *vic;

  minargc = 3 + skiparg;
  if( G_admin_permission( ent, ADMF_UNACCOUNTABLE ) )
    minargc = 2 + skiparg;

  if( G_SayArgc() < minargc )
  {
    ADMP( "^3!warn: ^7usage: warn [name] [reason]\n" );
    return qfalse;
  }
  G_SayArgv( 1 + skiparg, name, sizeof( name ) );
  reason = G_SayConcatArgs( 2 + skiparg );
  if( G_ClientNumbersFromString( name, pids ) != 1 )
  {
    G_MatchOnePlayer( pids, err, sizeof( err ) );
    ADMP( va( "^3!warn: ^7%s\n", err ) );
    return qfalse;
  }
  if( !admin_higher( ent, &g_entities[ pids[ 0 ] ] ) )
  {
    ADMP( "^3!warn: ^7sorry, but your intended victim has a higher admin"
        " level than you.\n" );
    return qfalse;
  }
 
  vic = &g_entities[ pids[ 0 ] ];
  //next line is the onscreen warning
  CPx( pids[ 0 ],va("cp \"^1You have been warned by an administrator.\n ^3Cease immediately or face admin action!\n^1 %s%s\"",(*reason)? "REASON: " : "" ,(*reason)? reason : "") );
  AP( va( "print \"^3!warn: ^7%s^7 has been warned to cease and desist: %s by %s \n\"",
            vic->client->pers.netname, (*reason) ? reason : "his current activity",
            G_admin_adminPrintName( ent ) ) );//console announcement
  return qtrue;
}
 
qboolean G_admin_putmespec( gentity_t *ent, int skiparg )
{
  if( !ent )
  {
    ADMP( "!specme: sorry, but console isn't allowed on the spectators team\n");
    return qfalse;
  }

  if( level.paused )
  {
    ADMP("!specme: disabled when game is paused\n");
    return qfalse;
  }

  if( g_preventRagequit.integer > 0 
      && ( ( ent->client->pers.teamSelection == PTE_HUMANS && level.numHumanSpawns == 0 )
      || ( ent->client->pers.teamSelection == PTE_ALIENS && level.numAlienSpawns == 0 ) ) )
  {
    AP( va("print \"^3!specme: ^7%s^7 must gather their party before venturing forth from this place. "
                    "^3(ragequit not allowed!)\n\"", ent->client->pers.netname ) );
    return qfalse;
  }
  
  if(ent->client->pers.teamSelection == PTE_NONE)
    return qfalse;
  
    //guard against build timer exploit
  if( ent->client->pers.teamSelection != PTE_NONE && ent->client->sess.sessionTeam != TEAM_SPECTATOR && 
     ( ent->client->ps.stats[ STAT_PCLASS ] == PCL_ALIEN_BUILDER0 ||
       ent->client->ps.stats[ STAT_PCLASS ] == PCL_ALIEN_BUILDER0_UPG ||
       BG_InventoryContainsWeapon( WP_HBUILD, ent->client->ps.stats ) ||
       BG_InventoryContainsWeapon( WP_HBUILD2, ent->client->ps.stats ) ) &&
      ent->client->ps.stats[ STAT_MISC ] > 0 )
  {
    ADMP("!specme: You cannot leave your team until the build timer expires");
    return qfalse;
  }
  
  G_ChangeTeam( ent, PTE_NONE, qfalse );
  AP( va("print \"^3!specme: ^7%s^7 decided to join the spectators\n\"", ent->client->pers.netname ) );
  return qtrue;
}

qboolean G_admin_slap( gentity_t *ent, int skiparg )
{
  int pids[ MAX_CLIENTS ];
  char name[ MAX_NAME_LENGTH ], err[ MAX_STRING_CHARS ];
  gentity_t *vic;
  vec3_t dir;

  if( level.intermissiontime ) return qfalse;

  if( G_SayArgc() < 2 + skiparg )
  {
    ADMP( "^3!slap: ^7usage: !slap [name|slot#]\n" );
    return qfalse;
  }

  G_SayArgv( 1 + skiparg, name, sizeof( name ) );
  if( G_ClientNumbersFromString( name, pids ) != 1 )
  {
    G_MatchOnePlayer( pids, err, sizeof( err ) );
    ADMP( va( "^3!slap: ^7%s\n", err ) );
    return qfalse;
  }

  vic = &g_entities[ pids[ 0 ] ];
  if( !vic )
  {
    ADMP( "^3!slap: ^7bad target\n" );
    return qfalse;
  }
  if( vic == ent )
  {
    ADMP( "^3!slap: ^7sorry, you cannot slap yourself\n" );
    return qfalse;
  }
  if( !admin_higher( ent, vic ) )
  {
    ADMP( "^3!slap: ^7sorry, but your intended victim has a higher admin"
          " level than you\n" );
    return qfalse;
  }
  if( vic->client->pers.teamSelection == PTE_NONE ||
      vic->client->pers.classSelection == PCL_NONE )
  {
    ADMP( "^3!slap: ^7can't slap spectators\n" );
    return qfalse;
  }

  // knockback in a random direction
  dir[0] = crandom();
  dir[1] = crandom();
  dir[2] = random();
  G_Knockback( vic, dir, g_slapKnockback.integer );

  trap_SendServerCommand( vic-g_entities,
    va( "cp \"%s^7 is not amused\n\"",
        G_admin_adminPrintName( ent ) ) );

  if( g_slapDamage.integer > 0 )
  {
    int damage;

    if( G_SayArgc() > 2 + skiparg )
    {
      char dmg_str[ MAX_STRING_CHARS ];
      G_SayArgv( 2 + skiparg, dmg_str, sizeof( dmg_str ) );
      damage = atoi(dmg_str);
      if( damage < 0 ) damage = 0;
    }
    else
    {
      if( g_slapDamage.integer > 100 ) g_slapDamage.integer = 100;
      damage = BG_FindHealthForClass( vic->client->ps.stats[ STAT_PCLASS ] ) *
        g_slapDamage.integer / 100;
      if( damage < 1 ) damage = 1;
    }

    vic->health -= damage;
    vic->client->ps.stats[ STAT_HEALTH ] = vic->health;
    vic->lastDamageTime = level.time;
    if( vic->health <= 0 )
    {
      vic->flags |= FL_NO_KNOCKBACK;
      vic->enemy = &g_entities[ pids[ 0 ] ];
      vic->die( vic, ent, ent, damage, MOD_SLAP );
    }
    else if( vic->pain )
    {
      vic->pain( vic, &g_entities[ pids[ 0 ] ], damage );
    }
  }
  return qtrue;
}

qboolean G_admin_drop( gentity_t *ent, int skiparg )
{
  int pids[ MAX_CLIENTS ];
  char name[ MAX_NAME_LENGTH ], err[ MAX_STRING_CHARS ];

  if( G_SayArgc() < 2 + skiparg )
  {
    ADMP( "^3!drop: ^7usage: !drop [name|slot#] [message]\n" );
    return qfalse;
  }

  G_SayArgv( 1 + skiparg, name, sizeof( name ) );
  if( G_ClientNumbersFromString( name, pids ) != 1 )
  {
    G_MatchOnePlayer( pids, err, sizeof( err ) );
    ADMP( va( "^3!drop: ^7%s\n", err ) );
    return qfalse;
  }

  if( !admin_higher( ent, &g_entities[ pids[ 0 ] ] ) )
  {
    ADMP( "^3!drop: ^7sorry, but your intended victim has a higher admin"
          " level than you\n" );
    return qfalse;
  }

  // victim's message
  if( G_SayArgc() > 2 + skiparg )
    trap_SendServerCommand( pids[ 0 ],
      va( "disconnect \"You have been dropped.\n%s^7\n\"",
      G_SayConcatArgs( 2 + skiparg ) ) );
  else
    trap_SendServerCommand( pids[ 0 ], va( "disconnect" ) );

  // server message
  trap_DropClient( pids[ 0 ], va( "disconnected" ) );

  return qtrue;
}

qboolean G_admin_buildlog( gentity_t *ent, int skiparg )
{
#define LOG_DISPLAY_LENGTH 10
  buildHistory_t *ptr;
  gentity_t *builder = NULL;
  int skip = 0, start = 0, lastID = -1, firstID = -1, i, len, matchlen = 0;
  pTeam_t team = PTE_NONE;
  char message[ MAX_STRING_CHARS ], *teamchar; 
  char *name, *action, *buildablename, markstring[ MAX_STRING_CHARS ]; 
  if( !g_buildLogMaxLength.integer )
  {
    ADMP( "^3!buildlog: ^7build logging is disabled" );
    return qfalse;
  }
  if( G_SayArgc( ) >= 2 + skiparg )
  {
    for( i = 1; i + skiparg < G_SayArgc( ); i++ )
    {
      char argbuf[ 64 ], err[ MAX_STRING_CHARS ];
      int x = 0, pids[ MAX_CLIENTS ];
      G_SayArgv( i + skiparg, argbuf, sizeof argbuf );
      switch( argbuf[ 0 ])
      {
        case 'x':
          x = 1;
        default:
          skip = atoi( argbuf + x );
          start = 0;
          break;
        case '#':
          start = atoi( argbuf + 1 );
          skip = 0;
          break;
        case '-':
          if(G_ClientNumbersFromString(argbuf + 1, pids) != 1)
          {
           G_MatchOnePlayer(pids, err, sizeof(err));
           ADMP(va("^3!revert: ^7%s\n", err));
           return qfalse;
          }
          builder = g_entities + *pids;
          break;
        case 'A':
        case 'a':
          team = PTE_ALIENS;
          break;
        case 'H':
        case 'h':
          team = PTE_HUMANS;
          break;
      }
    }
  }
  // !buildlog can be abused, so let everyone know when it is used
  AP( va( "print \"^3!buildlog: ^7%s^7 requested a log of recent building"
      " activity\n\"", G_admin_adminPrintName( ent ) ) );
  len = G_CountBuildLog( ); // also clips the log if too long
  if( !len )
  {
    ADMP( "^3!buildlog: ^7no build log found\n" );
    return qfalse;
  }
  if( start )
  {
    // set skip based on start
    for( ptr = level.buildHistory; ptr && ptr->ID != start; 
        ptr = ptr->next, skip++ );
    if( !ptr )
    {
      ADMP( "^3!buildlog: ^7log ID not found\n" );
      skip = 0;
    }
  }
  // ensure skip is a useful value
  if( skip > len - LOG_DISPLAY_LENGTH )
    skip = len - LOG_DISPLAY_LENGTH;
  *message = '\0';
  // skip to start entry
  for( ptr = level.buildHistory, i = len; ptr && i > len - skip; 
      ptr = ptr->next )
  {
    // these checks could perhaps be done more efficiently but they are cheap
    // in processor time so I'm not worrying
    if( team != PTE_NONE && team != BG_FindTeamForBuildable( ptr->buildable ) )
      continue;
    if( builder && builder != ptr->ent )
      continue;
    matchlen++;
    i--;
  }
  for( ; i + LOG_DISPLAY_LENGTH > len - skip && i > 0; i--, ptr = ptr->next )
  {
    if( !ptr ) 
      break; // run out of log
    *markstring = '\0'; // reinit markstring
    // check team
    if( ( team != PTE_NONE && team != BG_FindTeamForBuildable( ptr->buildable ) )
        || ( builder && builder != ptr->ent ) )
    {
      skip++; // loop an extra time because we skipped one
      continue; 
    }
    if( lastID < 0 )
      lastID = ptr->ID;
    firstID = ptr->ID;
    matchlen++;
    // set name to the ent's current name or last recorded name
    if( ptr->ent )
    {
      if( ptr->ent->client )
        name = ptr->ent->client->pers.netname;
      else
        name = "<world>"; // any non-client action
    }
    else
      name = ptr->name;
    switch( ptr->fate )
    {
      case BF_BUILT:
        action = "^2built^7 a";
        break;
      case BF_DECONNED:
        action = "^3DECONSTRUCTED^7 a";
        break;
      case BF_DESTROYED:
        action = "destroyed a";
        break;
      case BF_TEAMKILLED:
        action = "^1TEAMKILLED^7 a";
        break;
      default:
        action = "\0"; // erm
        break;
    }
    // handle buildables removed by markdecon
    if( ptr->marked )
    {
      buildHistory_t *mark;
      int j, markdecon[ BA_NUM_BUILDABLES ], and = 2;
      char bnames[ 32 ], *article;
      mark = ptr;
      // count the number of buildables
      memset( markdecon, 0, sizeof( markdecon ) );
      while( ( mark = mark->marked ) )
        markdecon[ mark->buildable ]++;
      // reverse order makes grammar easier
      for( j = BA_NUM_BUILDABLES; j >= 0; j-- )
      {
        buildablename = BG_FindHumanNameForBuildable( j );
        // plural is easy
        if( markdecon[ j ] > 1 )
          Com_sprintf( bnames, 32, "%d %ss", markdecon[ j ], buildablename );
        // use an appropriate article
        else if( markdecon[ j ] == 1 )
        {
          if( BG_FindUniqueTestForBuildable( j ) )
            article = "the"; // if only one
          else if( strchr( "aeiouAEIOU", *buildablename ) )
            article = "an"; // if first char is vowel
          else
            article = "a";
          Com_sprintf( bnames, 32, "%s %s", article, buildablename );
        }
        else
          continue; // none of this buildable
        // C grammar: x, y, and z
        // the integer and is 2 initially, the test means it is used on the
        // second sprintf only, the reverse order makes this second to last
        // the comma is only printed if there is already some markstring i.e.
        // not the first time ( which would put it on the end of the string )
        Com_sprintf( markstring, sizeof( markstring ), "%s%s %s%s", bnames, 
            ( *markstring ) ? "," : "", ( and-- == 1 ) ? "and " : "", markstring );
      }
    }
    buildablename = BG_FindHumanNameForBuildable( ptr->buildable );
    switch( BG_FindTeamForBuildable( ptr->buildable ) )
    {
      case PTE_ALIENS: 
        teamchar = "^1A"; 
        break;
      case PTE_HUMANS: 
        teamchar = "^4H"; 
        break;
      default: 
        teamchar = " "; // space so it lines up neatly
        break;
    }
    // prepend the information to the string as we go back in buildhistory
    // so the earliest events are at the top
    Com_sprintf( message, MAX_STRING_CHARS, "%3d %s^7 %s^7 %s%s %s%s%s\n%s", 
        ptr->ID, teamchar, name, action, 
        ( strchr( "aeiouAEIOU", buildablename[ 0 ] ) ) ? "n" : "", 
        buildablename, ( markstring[ 0 ] ) ? ", removing " : "", 
        markstring, message );
  }
  for( ; ptr; ptr = ptr->next )
  {
    if( builder && builder != ptr->ent )
      continue;
    if( team != PTE_NONE && team != BG_FindTeamForBuildable( ptr->buildable ) )
      continue;
    matchlen++;
  }
  if( matchlen )
    ADMP( va( "%s^3!buildlog: showing log entries %d - %d of %d\n", message,
        firstID, lastID, matchlen ) );
  else
    ADMP( "^3!buildlog: ^7no log entries match those criteria\n" );
  return qtrue;
}

qboolean G_admin_revert( gentity_t *ent, int skiparg )
{
  int i = 0, j = 0, repeat = 1, ID = 0, len, matchlen=0;
  pTeam_t team = PTE_NONE;
  qboolean force = qfalse, reached = qfalse;
  gentity_t *builder = NULL, *targ;
  buildHistory_t *ptr, *tmp, *mark, *prev;
  vec3_t dist;
  char argbuf[ 64 ], *name, *bname, *action, *article;
  len = G_CountBuildLog( );
  if( !len )
  {
    ADMP( "^3!revert: ^7no build log found\n" );
    return qfalse;
  }
  if( G_SayArgc( ) < 2 + skiparg )
  {
    ADMP( "^3!revert: ^7usage: !revert (^5xnum^7) (^5#ID^7) (^5-name|num^7) (^5a|h^7)\n" );
    return qfalse;
  }
  for( i = 1; i + skiparg < G_SayArgc( ); i++ )
  {
    char arg[ 64 ], err[ MAX_STRING_CHARS ];
    int pids[ MAX_CLIENTS ];
    G_SayArgv( i + skiparg, arg, sizeof arg );
    switch( arg[ 0 ])
    {
      case 'x':
        repeat = atoi( arg + 1 );
        break;
      case '#':
        ID = atoi( arg + 1 );
        break;
      case '-':
        if(G_ClientNumbersFromString(arg + 1, pids) != 1)
        {
          G_MatchOnePlayer(pids, err, sizeof err);
          ADMP(va("^3!revert: ^7%s\n", err));
          return qfalse;
        }
        builder = g_entities + *pids;
        break;
      case 'A':
      case 'a':
        team = PTE_ALIENS;
        break;
      case 'H':
      case 'h':
        team = PTE_HUMANS;
        break;
      case '!':
        force = qtrue;
        break;
      default:
        ADMP( "^3!revert: ^7usage: !revert (^5xnum^7) (^5#ID^7) (^5-name|num^7) (^5a|h^7)\n" );
        return qfalse;
    }
  }
  if( repeat > 25 )
  {
    ADMP( "^3!revert: ^7to avoid flooding, can only revert 25 builds at a time\n" );
    repeat = 25;
  }
  for( i = 0, ptr = prev = level.buildHistory; repeat > 0; repeat--, j = 0 )
  {
    if( !ptr ) 
      break; // run out of bhist
    if( !reached && ID )
    {
      if( ptr->ID == ID )
        reached = qtrue;
      else
      {
        prev = ptr;
        ptr = ptr->next;
        repeat++;
        continue;
      }
    }
    if( ( team != PTE_NONE && 
        team != BG_FindTeamForBuildable( ptr->buildable ) ) || 
        ( builder && builder != ptr->ent ))
    {
      // team doesn't match, so skip this ptr and reset prev
      prev = ptr;
      ptr = ptr->next;
      // we don't want to count this one so counteract the decrement by the for
      repeat++;
      continue;
    }
    // get the ent's current or last recorded name
    if( ptr->ent )
    {
      if( ptr->ent->client )
        name = ptr->ent->client->pers.netname;
      else
        name = "<world>"; // non-client actions
    }
    else
      name = ptr->name;
    bname = BG_FindHumanNameForBuildable( ptr->buildable ); 
    action = "";
    switch( ptr->fate )
    {
      case BF_BUILT:
        action = "^2build^7";
        for( j = MAX_CLIENTS, targ = g_entities + j;
            j < level.num_entities; j++, targ++ )
        {
          // easy checks first to save time
          if( targ->s.eType != ET_BUILDABLE )
            continue;
          if( targ->s.modelindex != ptr->buildable )
            continue; 
          VectorSubtract( targ->s.pos.trBase, ptr->origin, dist );
#define FIND_BUILDABLE_TOLERANCE 5
          if( VectorLength( dist ) > FIND_BUILDABLE_TOLERANCE )
            continue; // number is somewhat arbitrary, watch for false pos/neg
          // if we didn't continue then it's this one, unlink it but we can't
          // free it yet, because the markdecon buildables might not place
          trap_UnlinkEntity( targ );
          break;
        }
        // if there are marked buildables to replace, and we aren't overriding 
        // space check, check they can fit before acting
        if( ptr->marked && !force )
        {
          for( mark = ptr->marked; mark; mark = mark->marked )
            if( !G_RevertCanFit( mark ) )
            {
              trap_LinkEntity( targ ); // put it back, we failed
              // scariest sprintf ever:
              Com_sprintf( argbuf, sizeof argbuf, "%s%s%s%s%s%s%s!",
                  ( repeat > 1 ) ? "x" : "", ( repeat > 1 ) ? va( "%d ", repeat ) : "",
                  ( ID ) ? "#" : "", ( ID ) ? va( "%d ", ptr->ID ) : "",
                  ( builder ) ? "-" : "", ( builder ) ? va( "%d ", (int)( builder - g_entities ) ) : "",
                  ( team == PTE_ALIENS ) ? "a " : ( team == PTE_HUMANS ) ? "h " : "" );
              ADMP( va( "^3!revert: ^7revert aborted: reverting this %s would conflict with "
                  "another buildable, use ^3!revert %s ^7to override\n", action, argbuf ) );
              return qfalse;
            }
         }
         // Prevent teleport glitch when reverting an occupied hovel
         if( targ->s.modelindex == BA_A_HOVEL &&
             targ->active )
         {
           gentity_t *builder = targ->builder;
           vec3_t    newOrigin;
           vec3_t    newAngles;

           VectorCopy( targ->s.angles, newAngles );
           newAngles[ ROLL ] = 0;

           VectorCopy( targ->s.origin, newOrigin );
           VectorMA( newOrigin, 1.0f, targ->s.origin2, newOrigin );

           //prevent lerping
           builder->client->ps.eFlags ^= EF_TELEPORT_BIT;
           builder->client->ps.eFlags &= ~EF_NODRAW;
           G_UnlaggedClear( builder );

           G_SetOrigin( builder, newOrigin );
           VectorCopy( newOrigin, builder->client->ps.origin );
           G_SetClientViewAngle( builder, newAngles );

           //client leaves hovel
           builder->client->ps.stats[ STAT_STATE ] &= ~SS_HOVELING;
         }

          // if we haven't returned yet then we're good to go, free it
          G_FreeEntity( targ );
          // put the marked buildables back and mark them again
          if( ptr->marked ) // there may be a more efficient way of doing this
          {
            for( mark = ptr->marked; mark; mark = mark->marked )
              G_SpawnRevertedBuildable( mark, qtrue ); 
          }
        break;
      case BF_DECONNED:
        if( !action[ 0 ] ) action = "^3deconstruction^7";
      case BF_TEAMKILLED:
        if( !action[ 0 ] ) action ="^1TEAMKILL^7";
      case BF_DESTROYED:
        if( !action[ 0 ] ) action = "destruction";
        // if we're not overriding and the replacement can't fit, as before
        if( !force && !G_RevertCanFit( ptr ) )
        {
          Com_sprintf( argbuf, sizeof argbuf, "%s%s%s%s%s%s%s!",
              ( repeat > 1 ) ? "x" : "", ( repeat > 1 ) ? va( "%d ", repeat ) : "",
              ( ID ) ? "#" : "", ( ID ) ? va( "%d ", ptr->ID ) : "",
              ( builder ) ? "-" : "", ( builder ) ? va( "%d ", (int)( builder - g_entities ) ) : "",
              ( team == PTE_ALIENS ) ? "a " : ( team == PTE_HUMANS ) ? "h " : "" );
          ADMP( va( "^3!revert: ^7revert aborted: reverting this %s would "
              "conflict with another buildable, use ^3!revert %s ^7to override\n",
              action, argbuf ) );
          return qfalse;
        }
        // else replace it but don't mark it ( it might have been marked before
        // but it isn't that important )
        G_SpawnRevertedBuildable( ptr, qfalse );
        break;
      default:
        // if this happens something has gone wrong
        ADMP( "^3!revert: ^7incomplete or corrupted build log entry\n" );
        /* quarantine and dispose of the log, it's dangerous
        trap_Cvar_Set( "g_buildLogMaxLength", "0" );
        G_CountBuildLog( );
        */
        return qfalse;
      }
      if( j == level.num_entities )
      {
        ADMP( va( "^3!revert: ^7could not find logged buildable #%d\n", ptr->ID ));
        prev = ptr;
        ptr = ptr->next;
        continue;
      }
      // this is similar to the buildlog stuff
      if( BG_FindUniqueTestForBuildable( ptr->buildable ) )
        article = "the";
      else if( strchr( "aeiouAEIOU", *bname ) )
        article = "an";
      else
        article = "a";
      AP( va( "print \"^3!revert: ^7%s^7 reverted %s^7'%s %s of %s %s\n\"", 
          G_admin_adminPrintName( ent ),
          name, strchr( "Ss", name[ strlen( name ) - 1 ] ) ? "" : "s",
          action, article, bname ) ); 
      matchlen++;
      // remove the reverted entry
      // ptr moves on, prev just readjusts ->next unless it is about to be 
      // freed, in which case it is forced to move on too
      tmp = ptr;
      if( ptr == level.buildHistory )
        prev = level.buildHistory = ptr = ptr->next;
      else
        prev->next = ptr = ptr->next;
      G_Free( tmp );
  }
  if( ID && !reached )
  {
    ADMP( "^3!revert: ^7no buildlog entry with that ID\n" );
    return qfalse;
  }
  
  if( !matchlen )
  {
     ADMP( "^3!revert: ^7no log entries match those criteria\n" );
     return qfalse;
  }
  else
  {
    ADMP( va( "^3!revert: ^7reverted %d buildlog events\n", matchlen ) );  
  }
  
  return qtrue;
}

void G_Unescape( char *input, char *output, int len );
qboolean G_StringReplaceCvars( char *input, char *output, int len );

qboolean G_admin_info( gentity_t *ent, int skiparg )
{
  fileHandle_t infoFile;
  int length;
  char filename[ MAX_OSPATH ], message[ MAX_STRING_CHARS ]; 
  if( G_SayArgc() == 2 + skiparg )
    G_SayArgv( 1 + skiparg, filename, sizeof( filename ) );
  else if( G_SayArgc() == 1 + skiparg )
    Q_strncpyz( filename, "default", sizeof( filename ) );
  else
  {
    ADMP( "^3!info: ^7usage: ^3!info ^7(^5subject^7)\n" );
    return qfalse;
  }
  Com_sprintf( filename, sizeof( filename ), "info/info-%s.txt", filename );
  length = trap_FS_FOpenFile( filename, &infoFile, FS_READ );
  if( length <= 0 || !infoFile )
  {
    trap_FS_FCloseFile( infoFile );
    ADMP( "^3!info: ^7no relevant information is available\n" );
    return qfalse;
  }
  else
  {
    int i;
    char *cr;
    trap_FS_Read( message, sizeof( message ), infoFile );
    if( length < sizeof( message ) )
      message[ length ] = '\0';
    else
      message[ sizeof( message ) - 1 ] = '\0';
    trap_FS_FCloseFile( infoFile );
    // strip carriage returns for windows platforms
    while( ( cr = strchr( message, '\r' ) ) )
      memmove( cr, cr + 1, strlen( cr + 1 ) + 1 );
#define MAX_INFO_PARSE_LOOPS 100
    for( i = 0; i < MAX_INFO_PARSE_LOOPS &&
        G_StringReplaceCvars( message, message, sizeof( message ) ); i++ );
    G_Unescape( message, message, sizeof( message ) );
    if( i == MAX_INFO_PARSE_LOOPS )
      G_Printf( S_COLOR_YELLOW "WARNING: %s exceeds MAX_INFO_PARSE_LOOPS\n", filename );
    ADMP( va( "%s\n", message ) );
    return qtrue;
  }
}

void G_Unescape( char *input, char *output, int len )
{
  // \n -> newline, \%c -> %c
  // output is terminated at output[len - 1]
  // it's OK for input to equal output, because our position in input is always
  // equal or greater than our position in output
  // however, if output is later in the same string as input, a crash is pretty
  // much inevitable
  int i, j;
  for( i = j = 0; input[i] && j + 1 < len; i++, j++ )
  {
    if( input[i] == '\\' )
    {
      if( !input[++i] )
      {
        output[j] = '\0';
        return;
      }
      else if( input[i] == 'n' )
        output[j] = '\n';
      else
        output[j] = input[i];
    }
    else
      output[j] = input[i];
  }
  output[j] = '\0';
}

qboolean G_StringReplaceCvars( char *input, char *output, int len )
{
  int i, outNum = 0;
  char cvarName[ 64 ], cvarValue[ MAX_CVAR_VALUE_STRING ];
  char *outputBuffer;
  qboolean doneAnything = qfalse;
  if( len <= 0 )
    return qfalse;
  // use our own internal buffer in case output == input
  outputBuffer = G_Alloc( len );
  len -= 1; // fit in a terminator
  while( *input && outNum < len )
  {
    if( *input == '\\' && input[1] && outNum < len - 1 )
    {
      outputBuffer[ outNum++ ] = *input++;
      outputBuffer[ outNum++ ] = *input++;
    }
    else if( *input == '$' )
    {
      doneAnything = qtrue;
      input++;
      if( *input == '{' ) 
        input++;
      for( i = 0; *input && ( isalnum( *input ) || *input == '_' ) && 
          i < 63; i++ )
        cvarName[ i ] = *input++;
      cvarName[ i ] = '\0';
      if( *input == '}' ) 
        input++;
      trap_Cvar_VariableStringBuffer( cvarName, cvarValue, sizeof( cvarValue ) );
      if( cvarValue[ 0 ] )
      {
        for( i = 0; cvarValue[ i ] && outNum < len; i++ )
          outputBuffer[ outNum++ ] = cvarValue[ i ];
      }
    }
    else
      outputBuffer[ outNum++ ] = *input++;
  }
  outputBuffer[ outNum ] = '\0';
  Q_strncpyz( output, outputBuffer, len );
  G_Free( outputBuffer );
  return doneAnything;
}

/*
================
 G_admin_print

 This function facilitates the ADMP define.  ADMP() is similar to CP except
 that it prints the message to the server console if ent is not defined.
================
*/
void G_admin_print( gentity_t *ent, char *m )
{
  if( ent )
    trap_SendServerCommand( ent - level.gentities, va( "print \"%s\"", m ) );
  else
  {
    char m2[ MAX_STRING_CHARS ];
    if( !trap_Cvar_VariableIntegerValue( "com_ansiColor" ) )
    {
      G_DecolorString( m, m2 );
      G_Printf( m2 );
    }
    else
      G_Printf( m );
  }
}

void G_admin_buffer_begin()
{
  g_bfb[ 0 ] = '\0';
}

void G_admin_buffer_end( gentity_t *ent )
{
  ADMP( g_bfb );
}

void G_admin_buffer_print( gentity_t *ent, char *m )
{
  // 1022 - strlen("print 64 \"\"") - 1
  if( strlen( m ) + strlen( g_bfb ) >= 1009 )
  {
    ADMP( g_bfb );
    g_bfb[ 0 ] = '\0';
  }
  Q_strcat( g_bfb, sizeof( g_bfb ), m );
}


void G_admin_cleanup()
{
  int i = 0;

  for( i = 0; i < MAX_ADMIN_LEVELS && g_admin_levels[ i ]; i++ )
  {
    G_Free( g_admin_levels[ i ] );
    g_admin_levels[ i ] = NULL;
  }
  for( i = 0; i < MAX_ADMIN_ADMINS && g_admin_admins[ i ]; i++ )
  {
    G_Free( g_admin_admins[ i ] );
    g_admin_admins[ i ] = NULL;
  }
  for( i = 0; i < MAX_ADMIN_BANS && g_admin_bans[ i ]; i++ )
  {
    G_Free( g_admin_bans[ i ] );
    g_admin_bans[ i ] = NULL;
  }
  for( i = 0; i < MAX_ADMIN_COMMANDS && g_admin_commands[ i ]; i++ )
  {
    G_Free( g_admin_commands[ i ] );
    g_admin_commands[ i ] = NULL;
  }
}

qboolean G_admin_L0(gentity_t *ent, int skiparg ){
  int pids[ MAX_CLIENTS ];
  char name[ MAX_NAME_LENGTH ] = {""};
  char testname[ MAX_NAME_LENGTH ] = {""};
  char err[ MAX_STRING_CHARS ];
  qboolean numeric = qtrue;
  int i;
  int id = -1;
  gentity_t *vic;

  if( G_SayArgc() < 2 + skiparg )
  {
    ADMP( "^3!L0: ^7usage: !L0 [name|slot#|admin#]\n" );
    return qfalse;
  }
  G_SayArgv( 1 + skiparg, testname, sizeof( testname ) );
  G_SanitiseString( testname, name, sizeof( name ) );
  for( i = 0; i < sizeof( name ) && name[ i ] ; i++ )
  {
    if( name[ i ] < '0' || name[ i ] > '9' )
    {
      numeric = qfalse;
      break;
    }
  }

  if( numeric )
  {
    id = atoi( name );
  }
  else
  {
    if( G_ClientNumbersFromString( name, pids ) != 1 )
    {
      G_MatchOnePlayer( pids, err, sizeof( err ) );
      ADMP( va( "^3!L0: ^7%s\n", err ) );
      return qfalse;
    }
    id = pids[ 0 ];
  }

  if (id >= 0 && id < level.maxclients)
  {
    vic = &g_entities[ id ];
    if( !vic || !(vic->client) || vic->client->pers.connected != CON_CONNECTED )
    {
      ADMP( "^3!L0:^7 no one connected by that slot number\n" );
      return qfalse;
    }

    if( G_admin_level( vic ) != 1 )
    {
      ADMP( "^3!L0:^7 intended victim is not level 1\n" );
      return qfalse;
    }
  }
  else if (id >= MAX_CLIENTS && id < MAX_CLIENTS + MAX_ADMIN_ADMINS
    && g_admin_admins[ id - MAX_CLIENTS ] )
  {
    if( g_admin_admins[ id - MAX_CLIENTS ]->level != 1 )
    {
      ADMP( "^3!L0:^7 intended victim is not level 1\n" );
      return qfalse;
    }
  }
  else
  {
    ADMP( "^3!L0:^7 no match.  use !listplayers or !listadmins to "
      "find an appropriate number to use instead of name.\n" );
    return qfalse;
  }

  trap_SendConsoleCommand( EXEC_APPEND, va( "!setlevel %d 0;", id ) );

  return qtrue;
}

qboolean G_admin_L1(gentity_t *ent, int skiparg ){
  int pids[ MAX_CLIENTS ];
  char name[ MAX_NAME_LENGTH ], err[ MAX_STRING_CHARS ];
  int minargc;

  minargc = 2 + skiparg;

  if( G_SayArgc() < minargc )
  {
    ADMP( "^3!L1: ^7usage: !L1 [name]\n" );
    return qfalse;
  }
  G_SayArgv( 1 + skiparg, name, sizeof( name ) );
  if( G_ClientNumbersFromString( name, pids ) != 1 )
  {
    G_MatchOnePlayer( pids, err, sizeof( err ) );
    ADMP( va( "^3!L1: ^7%s\n", err ) );
    return qfalse;
  }
  if( G_admin_level(&g_entities[ pids[ 0 ] ] )>0 )
  {
    ADMP( "^3!L1: ^7Sorry, but that person is already higher than level 0.\n" );
    return qfalse;
  }
 
  trap_SendConsoleCommand( EXEC_APPEND,va( "!setlevel %d 1;", pids[ 0 ] ) );
  return qtrue;
}

qboolean G_admin_invisible( gentity_t *ent, int skiparg )
{
  if( !ent )
  {
    ADMP( "!invisible: console can not become invisible.\n" );
    return qfalse;
  }
  
  if ( ent->client->sess.invisible != qtrue )
  {
    // Make the player invisible
    G_ChangeTeam( ent, PTE_NONE, qfalse );
    ent->client->sess.invisible = qtrue;
    ClientUserinfoChanged( ent-g_entities, qfalse );
    G_admin_namelog_update( ent->client, qtrue );
    trap_SendServerCommand( -1, va( "print \"%s" S_COLOR_WHITE " disconnected\n\"", ent->client->pers.netname ) );
  }
  else
  {
    // Make the player visible
    ent->client->sess.invisible = qfalse;
    ClientUserinfoChanged( ent-g_entities, qfalse );
    G_admin_namelog_update( ent->client, qfalse );
    trap_SendServerCommand( -1, va( "print \"%s" S_COLOR_WHITE " connected\n\"", ent->client->pers.netname ) );
    trap_SendServerCommand( -1, va( "print \"%s" S_COLOR_WHITE " entered the game\n\"", ent->client->pers.netname ) );
  }
  return qtrue;
}

qboolean G_admin_decon( gentity_t *ent, int skiparg )
{
  int repeat = 24, pids[ MAX_CLIENTS ], len, matchlen = 0;
  gentity_t *builder = NULL;
  buildHistory_t *ptr, *tmp, *prev;
  char arg[ 64 ], err[ MAX_STRING_CHARS ], *name, *bname, *action, *article, *reason;
  len = G_CountBuildLog( );

  if( !len )
  {
    ADMP( "^3!decon: ^7no build log found, aborting...\n" );
    return qfalse;
  }

  if( G_SayArgc( ) < 2 + skiparg )
  {
    ADMP( "^3!decon: ^7usage: !decon (^5name|num^7)\n" );
    return qfalse;
  }

  G_SayArgv( 1 + skiparg, arg, sizeof( arg ) );
  if( G_ClientNumbersFromString( arg, pids ) != 1 )
  {
    G_MatchOnePlayer( pids, err, sizeof( err ) );
    ADMP( va( "^3!decon: ^7%s\n", err ) );
    return qfalse;
  }

  builder = g_entities + *pids;
  if( builder->client->sess.invisible == qtrue )
  {
    ADMP( va( "^3!decon: ^7no connected player by the name or slot #\n" ) );
    return qfalse;
  }

  if( !admin_higher( ent, builder ) )
  {
    ADMP( "^3!decon: ^7sorry, but your intended victim has a higher admin"
        "level than you\n");
    return qfalse;
  }

  for( ptr = prev = level.buildHistory; repeat > 0; repeat-- )
  {
    if( !ptr )
        break;
    if( builder && builder != ptr->ent )
    {
      // team doesn't match, so skip this ptr and reset prev
      prev = ptr;
      ptr = ptr->next;
      // we don't want to count this one so counteract the decrement by the for
      repeat++;
      continue;
    }
    // get the ent's current or last recorded name
    if( ptr->ent )
    {
      if( ptr->ent->client )
        name = ptr->ent->client->pers.netname;
      else
        name = "<world>"; // non-client actions
    }
    else
      name = ptr->name;
    bname = BG_FindHumanNameForBuildable( ptr->buildable );
    action = "";
    switch( ptr->fate )
    {
      case BF_BUILT:
        prev = ptr;
        ptr = ptr->next;
        repeat++;
        continue;
      case BF_DESTROYED:
        prev = ptr;
        ptr = ptr->next;
        repeat++;
      case BF_DECONNED:
        if( !action[0] ) action = "^3deconstruction^7";
      case BF_TEAMKILLED:
        if( !action[0] ) action = "^1TEAMKILL^7";
        // if we're not overriding and the replacement can't fit, as before
        if( !G_RevertCanFit( ptr ) )
        {
          prev = ptr;
          ptr = ptr->next;
          repeat++;
          continue;
        }
        // else replace it but don't mark it ( it might have been marked before
        // but it isn't that important )
        G_SpawnRevertedBuildable( ptr, qfalse );
        break;
      default:
        // if this happens something has gone wrong
        ADMP( "^3!decon: ^7incomplete or corrupted build log entry\n" );
        /* quarantine and dispose of the log, it's dangerous
        trap_Cvar_Set( "g_buildLogMaxLength", "0" );
        G_CountBuildLog( );
        */
        return qfalse;
    }
      // this is similar to the buildlog stuff
    if( BG_FindUniqueTestForBuildable( ptr->buildable ) )
      article = "the";
    else if( strchr( "aeiouAEIOU", *bname ) )
      article = "an";
    else
      article = "a";
    AP( va( "print \"%s^7 reverted %s^7'%s %s of %s %s\n\"",
        G_admin_adminPrintName( ent ),
        name, strchr( "Ss", name[ strlen( name ) - 1 ] ) ? "" : "s",
        action, article, bname ) );
    matchlen++;
    // remove the reverted entry
    // ptr moves on, prev just readjusts ->next unles it is about to be
    // freed, in which case it is forced to move on too
    tmp = ptr;
    if( ptr == level.buildHistory )
      prev = level.buildHistory = ptr = ptr->next;
    else
      prev->next = ptr = ptr->next;
    G_Free( tmp );
  }

  if( !matchlen )
  {
    ADMP( "^3!decopn: ^7This user doesn't seem to have deconned anything...\n" );
    return qfalse;
  }

  ADMP( va( "^3!decon: ^7reverted %d buildlog events\n", matchlen ) );
  admin_create_ban( ent,
      builder->client->pers.netname,
      builder->client->pers.guid,
      builder->client->pers.ip, G_admin_parse_time( g_deconBanTime.string ),
      ( *reason ) ? reason : "^1Decon" );
  if( g_admin.string[ 0 ] )
    admin_writeconfig();

  trap_SendServerCommand( pids[ 0 ],
      va( "disconnect \"You have been kicked.\n%s^7\nreason:\n%s\"",
      ( ent ) ? va( "admin:\n%s", G_admin_adminPrintName( ent ) ) : "admin\nconsole",
      ( *reason ) ? reason : "^1Decon" ) );

  trap_DropClient( pids[ 0 ], va( "kicked%s^7, reason: %s",
      ( ent ) ? va( " by %s", G_admin_adminPrintName( ent ) ) : " by console", 
      ( *reason ) ? reason : "^1Decon" ) );

  return qtrue;
}

qboolean G_admin_setdevmode( gentity_t *ent, int skiparg )
{
  char str[ 5 ];

  if( G_SayArgc() != 2 + skiparg )
  {
    ADMP( "^3!setdevmode: ^7usage: !setdevmode [on|off]\n" );
    return qfalse;
  }
  G_SayArgv( 1 + skiparg, str, sizeof( str ) );

  if( !Q_stricmp( str, "on" ) )
  {
    if( g_cheats.integer )
    {
      ADMP( "^3!setdevmode: ^7developer mode is already on\n" );
      return qfalse;
    }
    trap_Cvar_Set( "sv_cheats", "1" );
    trap_Cvar_Update( &g_cheats );
    AP( va( "print \"^3!setdevmode: ^7%s ^7has switched developer mode on\n\"",
            G_admin_adminPrintName( ent ) ) );
  }
  else if( !Q_stricmp( str, "off" ) )
  {
    if( !g_cheats.integer )
    {
      ADMP( "^3!setdevmode: ^7developer mode is already off\n" );
      return qfalse;
    }
    trap_Cvar_Set( "sv_cheats", "0" );
    trap_Cvar_Update( &g_cheats );
    AP( va( "print \"^3!setdevmode: ^7%s ^7has switched developer mode off\n\"",
            G_admin_adminPrintName( ent ) ) );
  }
  else
  {
    ADMP( "^3!setdevmode: ^7usage: !setdevmode [on|off]\n" );
    return qfalse;
  }

  return qtrue;
}

qboolean G_admin_hstage( gentity_t *ent, int skiparg )
{
  char lvl_chr[ MAX_STRING_CHARS ];
  int minargc;
  int lvl;

  minargc = 2 + skiparg;

  if( G_SayArgc() < minargc )
  {
    ADMP( "^3!hstage: ^7usage: !hstage ^3#\n" );
    return qfalse;
  }

  G_SayArgv( 1 + skiparg, lvl_chr, sizeof( lvl_chr ) );

  lvl = atoi( lvl_chr );

  if( lvl < 1 || lvl > 3 )
  {
    ADMP( "^3!hstage: ^7invalid stage!\n" );
    return qfalse;
  }

  trap_SendConsoleCommand( EXEC_APPEND, va( "g_humanStage %i", lvl - 1 ) );

  AP( va( "print \"^3!hstage: ^7%s^7 gave humans stage ^3%i^7\n\"",
    G_admin_adminPrintName( ent ), lvl ) );

  return qtrue;
}

qboolean G_admin_astage( gentity_t *ent, int skiparg )
{
  char lvl_chr[ MAX_STRING_CHARS ];
  int minargc;
  int lvl;

  minargc = 2 + skiparg;

  if( G_SayArgc() < minargc )
  {
    ADMP( "^3!astage: ^7usage: !astage ^3#\n" );
    return qfalse;
  }

  G_SayArgv( 1 + skiparg, lvl_chr, sizeof( lvl_chr ) );

  lvl = atoi( lvl_chr );

  if( lvl < 1 || lvl > 3 )
  {
    ADMP( "^3!astage: ^7invalid stage!\n" );
    return qfalse;
  }

  trap_SendConsoleCommand( EXEC_APPEND, va( "g_alienStage %i", lvl - 1 ) );

  AP( va( "print \"^3!astage: ^7%s^7 gave aliens stage ^3%i^7\n\"",
    G_admin_adminPrintName( ent ), lvl ) );

  return qtrue;
}

qboolean G_admin_bubble( gentity_t *ent, int skiparg )
{
  int pids[ MAX_CLIENTS ];
  char name[ MAX_NAME_LENGTH ], err[ MAX_STRING_CHARS ];
  gentity_t *vic;

  if(g_Bubbles.integer)
  {
   if( G_SayArgc() < 2 + skiparg )
   {
     ADMP( "^3!bubble: ^7usage: !bubble [name|slot#]\n" );
     return qfalse;
   }
   G_SayArgv( 1 + skiparg, name, sizeof( name ) );
   if( G_ClientNumbersFromString( name, pids ) != 1 )
   {
     G_MatchOnePlayer( pids, err, sizeof( err ) );
     ADMP( va( "^3!bubble: ^7%s\n", err ) );
     return qfalse;
   }
  vic = &g_entities[ pids[ 0 ] ];
  if(vic->client->sess.invisible == qtrue)
 {
    ADMP( va( "^3!bubble: ^7no connected player by that name or slot #\n" ) );
    return qfalse;
 }
   if( !admin_higher( ent, &g_entities[ pids[ 0 ] ] ) )
   {
     ADMP( "^3!bubble: ^7sorry, but your intended victim has a higher admin"
         " level than you\n" );
     return qfalse;
  }


  if( vic->client->pers.bubbleTime )
    vic->client->pers.bubbleTime = 0;
  else
    vic->client->pers.bubbleTime = level.time + 500;

  AP( va( "print \"^3!bubble: ^7bubbles %s for %s^7 by %s\n\"",
    ( vic->client->pers.bubbleTime ) ? "enabled" : "disabled",
    vic->client->pers.netname,
    G_admin_adminPrintName( ent ) ) );
  }
  else
  {
     ADMP( "^3!bubble: ^7sorry, but bubbles have been disabled on this server.\n" );
     return qfalse;
  }
  return qtrue;

}

qboolean G_admin_scrim(gentity_t *ent, int skiparg )
{
  char state[5];
  
	if( G_SayArgc() < 2 + skiparg )
	{
	  ADMP( "^3!scrim: ^7usage: !scrim [on|off]\n" );
	  return qfalse;
	}
	
	G_SayArgv( 1 + skiparg, state, sizeof( state ) );
	  
	if( !Q_stricmp(state, "on") )
	{
		if( g_scrimMode.integer != 0 )
		{
			ADMP( "^3!scrim: ^7scrim mode is already enabled.\n" );
			return qfalse;
		}
		AP( va( "print \"^3!scrim: ^7%s ^7turned scrim mode ^2on^7\n\"", G_admin_adminPrintName( ent ) ) );
		trap_Cvar_Set( "g_scrimMode", "1" );
	} 
	else if( !Q_stricmp(state, "off") )
	{
		if( g_scrimMode.integer == 0 )
		{
			ADMP( "^3!scrim: ^7scrim mode is already disabled.\n" );
			return qfalse;
		}
		AP( va( "print \"^3!scrim: ^7%s ^7turned scrim mode ^1off^7\n\"", G_admin_adminPrintName( ent ) ) );
		trap_Cvar_Set( "g_scrimMode", "0" );
		
	} else {
		ADMP( "^3!scrim: ^7usage: !scrim [on|off]\n" );
		return qfalse;
	}
	
  return qtrue;
}

qboolean G_admin_give(gentity_t *ent, int skiparg)
{
	char arg_name_raw[MAX_NAME_LENGTH];
	char arg_name[MAX_NAME_LENGTH];
	char arg_amount[30];
	int target_id, amount;
	gentity_t *target;

	if (G_SayArgc() < 3 + skiparg) {
		ADMP("^3!give: ^7usage: !give [player] [amount]\n");
		return qfalse;
	}

	G_SayArgv(1 + skiparg, arg_name_raw, sizeof(arg_name_raw));
	G_SanitiseString(arg_name_raw, arg_name, sizeof(arg_name));

	if (is_numeric(arg_name)) {
		target_id = atoi(arg_name);

		if (target_id < 0 || target_id >= MAX_CLIENTS) {
			ADMP(va("^3!give: ^7invalid client number\n"));
			return qfalse;
		}
	} else {
		int pids[ MAX_CLIENTS ];

		if (G_ClientNumbersFromString(arg_name, pids) != 1) {
			char error[MAX_STRING_CHARS];

			G_MatchOnePlayer(pids, error, sizeof(error));
			ADMP(va("^3!give: ^7%s\n", error));
			return qfalse;
		}

		target_id = pids[0];
	}


	target = g_entities + target_id;

	if (!target->client ||
	    target->client->pers.connected != CON_CONNECTED) {
	invalid_target:
		ADMP("^3!give: ^7invalid target\n");
		return qfalse;
	}

	G_SayArgv(2 + skiparg, arg_amount, sizeof(arg_amount));
  
	amount = atoi(arg_amount);

	switch (target->client->pers.teamSelection) {
	case PTE_ALIENS:
		amount = floor(EVOS(atof(arg_amount)));
		if (amount < -ALIEN_MAX_KILLS || amount > ALIEN_MAX_KILLS) {
		too_big:
			ADMP("^3!give: ^7amount is too big\n");
			return qfalse;
		}

		AP(va("print \"^3!give: ^7%s^7 was given %.3f evo%s by ^7%s^7\n\"",
		   target->client->pers.netname, amount / EVO_TO_CREDS_RATE,
		   (abs(amount) != 1 ? "s" : ""),
		   G_admin_adminPrintName( ent ) ) );
		break;

	case PTE_HUMANS:
		if (amount < -HUMAN_MAX_CREDITS || amount > HUMAN_MAX_CREDITS)
			goto too_big;

		AP(va("print \"^3!give: ^7%s^7 was given %d credit%s by ^7%s^7\n\"",
		   target->client->pers.netname, amount, (abs(amount) != 1 ? "s" : ""),
		   G_admin_adminPrintName( ent ) ) );
		break;

	default:
		goto invalid_target;
	}

	G_AddCreditToClient(target->client, amount, qtrue);
	return qtrue;
}

extern mapRotations_t mapRotations;

qboolean G_admin_setrotation(gentity_t *ent, int skiparg)
{
  char new_rotation[MAX_NAME_LENGTH];
  int i;

  if (G_SayArgc() < 2 + skiparg)
  {
    ADMP("^3!setrotation: ^7usage: !setrotation [rotation]\n");
    ADMP("Available rotations:\n");
    goto rotationlist;
  }

  G_SayArgv(1 + skiparg, new_rotation, sizeof(new_rotation));

  for( i = 0; i < mapRotations.numRotations; i++ )
  {
    if( Q_stricmp( mapRotations.rotations[ i ].name, new_rotation ) == 0 )
    {
      G_StartMapRotation(new_rotation, qfalse);
      trap_SendServerCommand( -1, va("print \"^3!setrotation: ^7rotation ^3%s ^7was started by %s\n",
        new_rotation, G_admin_adminPrintName( ent ) ) );
      return qtrue;
    }
  }
  ADMP("^3!setrotation: ^7rotation not found. Available rotations:\n");
  goto rotationlist;
  rotationlist:
  {
    for( i = 0; i < mapRotations.numRotations; i++ )
    {
      ADMP(va("    %s\n", mapRotations.rotations[ i ].name));
    }
    ADMP(va("Number of available rotations: ^3%d\n", mapRotations.numRotations));
  }
  return qfalse;
}

qboolean G_admin_versions(gentity_t *ent, int skiparg)
{
	int i;

	ADMBP_begin();

	for (i = 0; i < level.maxclients; i++) {
		gclient_t *client = level.clients + i;
		char userinfo[ MAX_INFO_STRING ], *p;

		if (client->pers.connected == CON_DISCONNECTED)
			continue;

		ADMBP(va("%02i ", i));

		trap_GetUserinfo(i, userinfo, sizeof(userinfo));
		p = Info_ValueForKey(userinfo, "version");

		if (p[0])
			ADMBP(va("'%s'\n", p));
		else {
			p = Info_ValueForKey(userinfo, "cl_voip");

			if (p[0])
				ADMBP("probably GPP or newer\n");
			else
				ADMBP("probably stock 1.1\n");
		}
	}

	ADMBP_end();
	return qtrue;
}

static int calc_ff_pct( statsCounters_t *sc )
{
	if ( sc->dmgdone + sc->structdmgdone <= 0 )
	{
		if ( sc->ffdmgdone <= 0 )
			return 0;
		else
			return 100;
	}
	else
	{
		return round((float)sc->ffdmgdone / (sc->ffdmgdone + sc->dmgdone + sc->structdmgdone) * 100);
	}
}

qboolean G_admin_showff(gentity_t *ent, int skiparg)
{
	char arg_name_raw[MAX_NAME_LENGTH];
	char arg_name[MAX_NAME_LENGTH];
	int target_id, ffpct;
	gentity_t *target;
	statsCounters_t *sc;

	if (G_SayArgc() == 1 + skiparg) {
		int i;
		char team[4];
		gclient_t *client;

		ADMBP_begin();
		ADMBP("^3!showff:^7 friendly fire damage percentage for all connected players\n");

		for (i = 0; i < level.maxclients; i++) { 
			client = &level.clients[i];

			if (client->pers.connected != CON_CONNECTED)
				continue;

			if (client->pers.teamSelection == PTE_HUMANS)
				Com_sprintf( team, sizeof( team ), "^4H" );
			else if (client->pers.teamSelection == PTE_ALIENS)
				Com_sprintf( team, sizeof( team ), "^1A" );
			else
				Com_sprintf( team, sizeof( team ), "^3S" );

			ffpct = calc_ff_pct(&client->pers.statscounters);
			ADMBP(va("%2d %s ^1%3d%% ^7%s^7\n", i, team, ffpct, client->pers.netname));
		}

		ADMBP("^7for detailed information, use ^3!showff player|slot^7\n");
		ADMBP_end();
		return qtrue;
	}

	G_SayArgv(1 + skiparg, arg_name_raw, sizeof(arg_name_raw));
	G_SanitiseString(arg_name_raw, arg_name, sizeof(arg_name));

	if (is_numeric(arg_name)) {
		target_id = atoi(arg_name);

		if (target_id < 0 || target_id >= MAX_CLIENTS) {
			ADMP(va("^3!showff: ^7invalid client number\n"));
			return qfalse;
		}
	} else {
		int pids[MAX_CLIENTS];

		if (G_ClientNumbersFromString(arg_name, pids) != 1) {
			char error[MAX_STRING_CHARS];

			G_MatchOnePlayer(pids, error, sizeof(error));
			ADMP(va("^3!showff: ^7%s\n", error));
			return qfalse;
		}

		target_id = pids[0];
	}

	target = g_entities + target_id;
	sc     = &target->client->pers.statscounters;
	ffpct  = calc_ff_pct(sc);

	ADMP(va("^3!showff: ^7detailed FF information for %s^7:\n",
	        target->client->pers.netname));
	ADMP(va("^7damage to: Enemies: ^1%d^7, structures: ^1%d^7, friendlies: ^1%d\n",
	        sc->dmgdone, sc->structdmgdone, sc->ffdmgdone));
	ADMP(va("dealt ^1%d%%^7 of their total damage to the team\n", ffpct));

	return qtrue;
}

void G_admin_tklog_cleanup( void )
{
  int i;

  for( i = 0; i < MAX_ADMIN_TKLOGS && g_admin_tklog[ i ]; i++ )
  {
    G_Free( g_admin_tklog[ i ] );
    g_admin_tklog[ i ] = NULL;
  }

  admin_tklog_index = 0;
}

void G_admin_tklog_log( gentity_t *attacker, gentity_t *victim, int meansOfDeath )
{
  g_admin_tklog_t *tklog;
  int previous;
  int count = 1;

  if( !attacker )
    return;

  previous = admin_tklog_index - 1;
  if( previous < 0 )
    previous = MAX_ADMIN_TKLOGS - 1;

  if( g_admin_tklog[ previous ] )
    count = g_admin_tklog[ previous ]->id + 1;

  if( g_admin_tklog[ admin_tklog_index ] )
    tklog = g_admin_tklog[ admin_tklog_index ];
  else
    tklog = G_Alloc( sizeof( g_admin_tklog_t ) );

  memset( tklog, 0, sizeof( g_admin_tklog_t ) );
  tklog->id = count;
  tklog->time = level.time - level.startTime;
  Q_strncpyz( tklog->name, attacker->client->pers.netname, sizeof( tklog->name ) );

  if( victim )
  {
    Q_strncpyz( tklog->victim, victim->client->pers.netname, sizeof( tklog->victim ) );
    tklog->damage = victim->client->tkcredits[ attacker->s.number ];
    tklog->value = victim->client->ps.stats[ STAT_MAX_HEALTH ];
  }
  else
  {
    Q_strncpyz( tklog->victim, "^3BLEEDING", sizeof( tklog->victim ) );
    tklog->damage = attacker->client->pers.statscounters.spreebleeds;
    tklog->value = g_bleedingSpree.integer * 100;
  }

  tklog->team = attacker->client->ps.stats[ STAT_PTEAM ];
  if( meansOfDeath == MOD_GRENADE )
    tklog->weapon = WP_GRENADE;
  else if( tklog->team == PTE_HUMANS )
    tklog->weapon = attacker->s.weapon;
  else
    tklog->weapon = attacker->client->ps.stats[ STAT_PCLASS ];

  g_admin_tklog[ admin_tklog_index ] = tklog;
  admin_tklog_index++;
  if( admin_tklog_index >= MAX_ADMIN_TKLOGS )
    admin_tklog_index = 0;
}

qboolean G_admin_tklog( gentity_t *ent, int skiparg )
{
  g_admin_tklog_t *results[ 10 ];
  int result_index = 0;
  char *search_name = NULL;
  int index;
  int skip = 0;
  int skipped = 0;
  int checked = 0;
  char n1[ MAX_NAME_LENGTH ];
  char fmt_name[ 16 ];
  char argbuf[ 32 ];
  char *weaponName;
  int name_length = 10;
  int max_id = 0;
  int i;
  qboolean match;

  memset( results, 0, sizeof( results ) );

  index = admin_tklog_index;
  for( i = 0; i < 10; i++ )
  {
    int prev;

    prev = index - 1;
    if( prev < 0 )
      prev = MAX_ADMIN_TKLOGS - 1;
    if( !g_admin_tklog[ prev ] )
      break;
    if( g_admin_tklog[ prev ]->id > max_id )
      max_id = g_admin_tklog[ prev ]->id;
    index = prev;
  }

  if( G_SayArgc() > 1 + skiparg )
  {
    G_SayArgv( 1 + skiparg, argbuf, sizeof( argbuf ) );
    if( ( *argbuf >= '0' && *argbuf <= '9' ) || *argbuf == '-' )
    {
      int id;

      id = atoi( argbuf );
      if( id < 0 )
        id += ( max_id - 9 );
      else if( id <= max_id - MAX_ADMIN_TKLOGS )
        id = max_id - MAX_ADMIN_TKLOGS + 1;

      if( id + 9 >= max_id )
        id = max_id - 9;
      if( id < 1 )
        id = 1;
      for( i = 0; i < MAX_ADMIN_TKLOGS; i++ )
      {
        if( g_admin_tklog[ i ]->id == id )
        {
          index = i;
          break;
        }
      }
    }
    else
    {
      search_name = argbuf;
    }

    if( G_SayArgc() > 2 + skiparg && ( search_name ) )
    {
      char skipbuf[ 4 ];
      G_SayArgv( 2 + skiparg, skipbuf, sizeof( skipbuf ) );
      skip = atoi( skipbuf );
    }
  }

  if( search_name )
  {
    g_admin_tklog_t *result_swap[ 10 ];

    memset( &result_swap, 0, sizeof( result_swap ) );

    index = admin_tklog_index - 1;
    if( index < 0 )
      index = MAX_ADMIN_TKLOGS - 1;

    while( g_admin_tklog[ index ] &&
      checked < MAX_ADMIN_TKLOGS &&
      result_index < 10 )
    {
      match = qfalse;

      G_SanitiseString( g_admin_tklog[ index ]->name, n1, sizeof( n1 ) );
      if( strstr( n1, search_name ) )
        match = qtrue;

      if( match && skip > 0 )
      {
        match = qfalse;
        skip--;
        skipped++;
      }
      if( match )
      {
        result_swap[ result_index ] = g_admin_tklog[ index ];
        result_index++;
      }

      checked++;
      index--;
      if( index < 0 )
        index = MAX_ADMIN_TKLOGS - 1;
    }
    // search runs backwards, turn it around
    for( i = 0; i < result_index; i++ )
      results[ i ] = result_swap[ result_index - i - 1 ];
  }
  else
  {
    while( g_admin_tklog[ index ] && result_index < 10 )
    {
      results[ result_index ] = g_admin_tklog[ index ];
      result_index++;
      index++;
      if( index >= MAX_ADMIN_TKLOGS )
        index = 0;
    }
  }

  for( i = 0; results[ i ] && i < 10; i++ )
  {
    int l;

    G_DecolorString( results[ i ]->name, n1 );
    l = strlen( n1 );
    if( l > name_length )
      name_length = l;
  }
  ADMBP_begin( );
  for( i = 0; results[ i ] && i < 10; i++ )
  {
    int t;

    t = results[ i ]->time / 1000;

    G_DecolorString( results[ i ]->name, n1 );
    Com_sprintf( fmt_name, sizeof( fmt_name ), "%%%ds", 
      ( name_length + (int)( strlen( results[ i ]->name ) - strlen( n1 ) ) ) );
    Com_sprintf( n1, sizeof( n1 ), fmt_name, results[ i ]->name );

    if( results[ i ]->team == PTE_HUMANS )
      weaponName = BG_FindHumanNameForWeapon( results[ i ]->weapon );
    else
      weaponName = BG_FindHumanNameForClassNum( results[ i ]->weapon );

     ADMBP( va( "^3%3d %3d:%02d ^7%s^7 tk'd %s^7\n"
             "              with ^3%s^7 for ^3%d^7/^3%d^7 health.\n",
      results[ i ]->id,
      t / 60, t % 60,
      n1,
      results[ i ]->victim,
      weaponName,
      results[ i ]->damage,
      results[ i ]->value ) );
  }
  if( search_name )
  {
    ADMBP( va( "^3!tklog:^7 Showing %d matches for '%s^7'.",
      result_index,
      argbuf ) );
    if( checked < MAX_ADMIN_TKLOGS && g_admin_tklog[ checked ] )
      ADMBP( va( " run '!tklog %s^7 %d' to see more",
       argbuf,
       skipped + result_index ) );
    ADMBP( "\n" );
  }
  else if ( results[ 0 ] )
  {
    ADMBP( va( "^3!tklog:^7 Showing %d - %d of %d.\n",
      results[ 0 ]->id,
      results[ result_index - 1 ]->id,
      max_id ) );
  }
  else
  {
    ADMBP( "^3!tklog:^7 log is empty.\n" );
  }
  ADMBP_end( );

  return qtrue;
}

qboolean G_admin_sm( gentity_t *ent, int skiparg )
{
  const char *s;
  char feature[ 16 ];

  if( G_SayArgc() < 2 + skiparg )
  {
    usage:
    ADMP( "^3!sm: ^7usage: !sm ipa <IPA>\n" );
    return qfalse;
  }

  s = G_SayConcatArgs( 1 + skiparg );
  if( strchr( s, '\n' ) || strchr( s, '\r' ) )
  {
    ADMP( "^3!sm: ^7invalid character\n" );
    return qfalse;
  }

  G_SayArgv( 1 + skiparg, feature, sizeof( feature ) );

  if( !Q_stricmp( feature, "ipa" ) )
  {
    char ipa[ 32 ];
    int parts[ 4 ];

    if( G_SayArgc() > 3 + skiparg )
    {
      ADMP( "^3!sm: ^7excessive arguments\n" );
      goto usage;
    }
    G_SayArgv( 2 + skiparg, ipa, sizeof( ipa ) );

    // have a well-formed IPv4 address, because Schachtmeister silently drops all invalid requests

    if( sscanf( ipa, "%i.%i.%i.%i", &parts[0], &parts[1], &parts[2], &parts[3] ) != 4
        || parts[0] < 0 || parts[0] > 255
        || parts[1] < 0 || parts[1] > 255
        || parts[2] < 0 || parts[2] > 255
        || parts[3] < 0 || parts[3] > 255 )
    {
      ADMP( "^3!sm: ^7invalid IP address\n" );
      return qfalse;
    }

    Com_sprintf( ipa, sizeof( ipa ), "%i.%i.%i.%i", parts[0], parts[1], parts[2], parts[3] );

    if( rand() % 2 /* FIXME cache hit */ )
    {
      const char *answer = "interesting";
      ADMP( va( "^3!sm: ^7IP address %s is: %s\n", ipa, answer ) );
      return qtrue;
    }

    ADMP( "^3!sm: ^7hmm...\n" );
    trap_SendConsoleCommand( EXEC_APPEND, va( "smq ipa \"%s\"\n", ipa ) );
  }
  else
    goto usage;

  return qtrue;
}

qboolean G_admin_print2(gentity_t *ent, int skiparg )
{
  char *text;
  text = G_SayConcatArgs( 1 + skiparg );
  AP( va( "print \"%s\n\"", text ));
  return qtrue;
}

qboolean G_admin_switch( gentity_t *ent, int skiparg )
{
  int pids[ MAX_CLIENTS ];
  char name[ MAX_NAME_LENGTH ], err[ MAX_STRING_CHARS ];
  int minargc;
  gentity_t *vic;

  if( !ent )
  {
    ADMP( "^3!switch: ^7console cannot use this command\n" );
    return qfalse;
  }

  minargc = 2 + skiparg;

  if( G_SayArgc() < minargc )
  {
    ADMP( "^3!switch: ^7usage: !switch [name|slot#]\n" );
    return qfalse;
  }

  G_SayArgv( 1 + skiparg, name, sizeof( name ) );

  if( G_ClientNumbersFromString( name, pids ) != 1 )
  {
    G_MatchOnePlayer( pids, err, sizeof( err ) );
    ADMP( va( "^3!switch: ^7%s\n", err ) );
    return qfalse;
  }

  vic = &g_entities[ pids[ 0 ] ];

  //put them on noclip
  vic->client->noclip = qtrue;
  ent->client->noclip = qtrue;

  //switch places
  trap_UnlinkEntity( ent );
  VectorCopy( vic->s.origin, ent->client->ps.origin );

  //switch places
  trap_UnlinkEntity( vic );
  VectorCopy( ent->s.origin, vic->client->ps.origin );

  //spectator fix
  if( ent->client->sess.spectatorState == SPECTATOR_NOT )
    trap_LinkEntity (ent);

  if( vic->client->sess.spectatorState == SPECTATOR_NOT )
    trap_LinkEntity (vic);


  //take them off noclip
  vic->client->noclip = qfalse;
  ent->client->noclip = qfalse;

  trap_SendServerCommand( vic-g_entities, va( "print \"^7%s^7 switched with you\n\"", ent->client->pers.netname ) );
  trap_SendServerCommand( ent-g_entities, va( "print \"^7you switched with ^7%s^7\n\"", vic->client->pers.netname ) );

  return qtrue;

}

qboolean G_admin_drug( gentity_t *ent, int skiparg )
{
  int pids[ MAX_CLIENTS ];
  char name[ MAX_NAME_LENGTH ], err[ MAX_STRING_CHARS ];
  int minargc;
  gentity_t *vic;

  minargc = 2 + skiparg;

  if( G_SayArgc() < minargc )
  {
    ADMP( "^3!drug: ^7usage: !drug [name|slot#]\n" );
    return qfalse;
  }

  G_SayArgv( 1 + skiparg, name, sizeof( name ) );

  if( G_ClientNumbersFromString( name, pids ) != 1 )
  {
    G_MatchOnePlayer( pids, err, sizeof( err ) );
    ADMP( va( "^3!drug: ^7%s\n", err ) );
    return qfalse;
  }

  vic = &g_entities[ pids[ 0 ] ];

  if( !admin_higher( ent, &g_entities[ pids[ 0 ] ] ) )
  {
    ADMP( "^3!drug: ^7sorry, but that player has a higher admin"
        " level than you\n" );
    return qfalse;
  }

  vic->client->ps.stats[ STAT_STATE ] |= SS_POISONCLOUDED;
  vic->client->lastPoisonCloudedTime = level.time;
  trap_SendServerCommand( vic->client->ps.clientNum, "poisoncloud" );

  AP( va( "print \"^3!drug: ^7%s ^7was drugged by %s^7\n\"",
  vic->client->pers.netname,
  G_admin_adminPrintName( ent ) ) );

  return qtrue;

}

qboolean G_admin_god( gentity_t *ent, int skiparg )
{
	int pids[ MAX_CLIENTS ];
	char name[ MAX_NAME_LENGTH ], err[ MAX_STRING_CHARS ];
	int minargc;
	gentity_t *vic;

	minargc = 2 + skiparg;

	if( G_SayArgc() < minargc )
	{
		ADMP( "^3!god: ^7usage: !god [name|slot#]\n" );
		return qfalse;
	}

	G_SayArgv( 1 + skiparg, name, sizeof( name ) );

	if( G_ClientNumbersFromString( name, pids ) != 1 )
	{
		G_MatchOnePlayer( pids, err, sizeof( err ) );
		ADMP( va( "^3!god: ^7%s\n", err ) );
		return qfalse;
	}

	vic = &g_entities[ pids[ 0 ] ];

	if( !ent )
	{
		ADMP( "^3!god: ^7sorry, but console cannot do this" );
		return qfalse;
	}

	if( !admin_higher( ent, &g_entities[ pids[ 0 ] ] ) )
	{
		ADMP( "^3!god: ^7sorry, but that player has a higher admin"
			" level than you\n" );
		return qfalse;
	}

	vic->flags ^= FL_GODMODE;

	if( vic->client->pers.godMode )
		vic->client->pers.godMode = 0;
	else
		vic->client->pers.godMode = 1;

	AP( va( "print \"^3!god: ^7godmode for %s ^7for %s ^7by %s^7\n\"",
	( vic->client->pers.godMode ) ? "enabled" : "disabled",
	vic->client->pers.netname,
	G_admin_adminPrintName( ent ) ) );

	return qtrue;

}

qboolean G_admin_range( gentity_t *ent, int skiparg )
{
	int pids[ MAX_CLIENTS ];
	char name[ MAX_NAME_LENGTH ], err[ MAX_STRING_CHARS ];
	int minargc;
	gentity_t *vic;
	adminRangeBoosts_t *newRange;
	char rangeInt[ MAX_STRING_CHARS ];
	float value;
	minargc = 3 + skiparg;

	if( G_SayArgc() < minargc )
	{
		ADMP( "^3!range: ^7usage: !range [name|slot#] [range]\n" );
		return qfalse;
	}

	G_SayArgv( 1 + skiparg, name, sizeof( name ) );
	G_SayArgv( 2 + skiparg, rangeInt, sizeof( rangeInt ) );

	if( G_ClientNumbersFromString( name, pids ) != 1 )
	{
		G_MatchOnePlayer( pids, err, sizeof( err ) );
		ADMP( va( "^3!range: ^7%s\n", err ) );
		return qfalse;
	}

	vic = &g_entities[ pids[ 0 ] ];

	if( !admin_higher( ent, &g_entities[ pids[ 0 ] ] ) )
	{
		ADMP( "^3!range: ^7sorry, but that player has a higher admin"
			" level than you\n" );
		return qfalse;
	}

	newRange = &vic->client->newRange;
	value = atof( rangeInt );
	newRange->rangeBoost = value - 1.0f;

	AP( va( "print \"^3!range: ^7range for %s ^7was multipled by ^2%s ^7by %s^7\n\"",
	vic->client->pers.netname,
	rangeInt,
	G_admin_adminPrintName( ent ) ) );

	return qtrue;

}

qboolean G_admin_practise( gentity_t *ent, int skiparg )
{
	int minargc;
	char arg[ MAX_STRING_CHARS ];
	minargc = 2 + skiparg;

	if( G_SayArgc() < minargc )
	{
		ADMP( "^3!practise: ^7usage: !practise [on|off]\n" );
		return qfalse;
	}

	G_SayArgv( 1 + skiparg, arg, sizeof( arg ) );

	if( !Q_stricmp( arg, "on" ) )
	{
		if( g_practise.integer )
		{
			ADMP( "^3!practise: ^7practise mode is already on\n" );
			return qfalse;
		}
		trap_Cvar_Set( "g_practise", "1" );
		trap_Cvar_Set( "g_alienStage", "2" );
		trap_Cvar_Set( "g_humanStage", "2" );
		strcpy( arg, "^2enabled^7" );
	}
	else if( !Q_stricmp( arg, "off" ) )
	{
		if( !g_practise.integer )
		{
			ADMP( "^3!practise: ^7practise mode is already off\n" );
			return qfalse;
		}
		trap_Cvar_Set( "g_practise", "0" );
		strcpy( arg, "^1disabled^7" );
	}
	else
	{
		ADMP( "^3!practise: ^7usage: !practise [on|off]\n" );
		return qfalse;
	}

	AP( va( "print \"^3!practise: ^7practise mode was %s by %s^7\n\"",
	arg,
	G_admin_adminPrintName( ent ) ) );

	return qtrue;

}

qboolean G_admin_spawn( gentity_t *ent, int skiparg )
{
  char arg[ MAX_STRING_CHARS ];
  buildable_t buildable;
  vec3_t entityOrigin;
  vec3_t forward, normal, angles;

  if( G_SayArgc() < 2 )
  {
    ADMP( "^3!spawn: ^7usage: spawn ^7name\n" );
    return qfalse;
  }
  
  G_SayArgv( 1 + skiparg, arg, sizeof( arg ) );

  buildable = BG_FindBuildNumForName( arg );
  if( buildable <= BA_NONE || buildable >= BA_NUM_BUILDABLES )
  {
    ADMP( "^3!spawn: ^7no such buildable\n" );
    return qfalse;
  }

  if( !ent || !ent->client ) {
    ADMP( "^3!spawn: ^7the console cannot use this command.\n" );
    return qfalse;
  }

  if( BG_FindTrajectoryForBuildable( buildable ) == TR_BUOYANCY )
    VectorSet( normal, 0.0f, 0.0f, -1.0f );
  else
    VectorSet( normal, 0.0f, 0.0f, 1.0f );

  VectorSet( angles, 0.0f, 90.0f, 0.0f );

  AngleVectors( ent->client->ps.viewangles, forward, NULL, NULL );
  VectorNormalize( forward );
  VectorMA( ent->client->ps.origin, 100.0f, forward, entityOrigin );
  ADMP( va( "^3!spawn: ^7%s at ^3%.0f %.0f %.0f\n", arg, entityOrigin[0], entityOrigin[1], entityOrigin[2] ) );
  AP( va( "print \"^3!spawn: ^7buildable ^3%s^7 spawned by %s^7 at location ^3%.0f %.0f %.0f^7\n", 
    BG_FindHumanNameForBuildable( buildable ), G_admin_adminPrintName( ent ), entityOrigin[0], entityOrigin[1], entityOrigin[2] ) );
  G_InstantBuild( buildable, entityOrigin, angles, normal, angles );
  return qtrue;
}

qboolean G_admin_shuffle( gentity_t *ent, int skiparg )
{
  G_ShuffleTeams( );  
  AP( va( "print \"^3!shuffle: ^7teams have been shuffled by %s^7\n\"",
           G_admin_adminPrintName( ent ) ) );  
  return qtrue;
}
