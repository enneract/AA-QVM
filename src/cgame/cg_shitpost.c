#include "cg_local.h"

void CG_HumanGib( vec3_t origin, vec3_t dir )
{
  particleSystem_t  *ps;

  trap_S_StartSound( origin, ENTITYNUM_WORLD, CHAN_AUTO, cgs.media.alienBuildableExplosion );

  //particle system
  ps = CG_SpawnNewParticleSystem( cgs.media.humanGibPS );

  if( CG_IsParticleSystemValid( &ps ) )
  {
    CG_SetAttachmentPoint( &ps->attachment, origin );
    CG_SetParticleSystemNormal( ps, dir );
    CG_AttachToPoint( &ps->attachment );
  }
}
