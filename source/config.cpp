//
// config.cpp
// by Naomi Peori (naomi@peori.ca)
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "SDK/VideoEq.h"
#include "config.h"

//
// Functions
//

bool CONFIG_t::reset ( VideoEq *videoEq )
{
  if ( videoEq )
  {
    if ( deepColorForce ( videoEq, false ) && hdcpForce ( videoEq, false ) )
    {
      return true;
    }
  }

  return false;
}

bool CONFIG_t::deepColorForce ( VideoEq *videoEq, bool enable )
{
  if ( videoEq )
  {
    videoEq->setDeepColorForce ( enable );

    if ( videoEq->getDeepColorForce ( ) == enable )
    {
      return true;
    }
  }

  return false;
}

bool CONFIG_t::hdcpForce ( VideoEq *videoEq, bool enable )
{
  if ( videoEq )
  {
    videoEq->setHdcpForceOn ( enable );

    if ( videoEq->getHdcpForceOn ( ) == enable )
    {
      return true;
    }
  }

  return false;
}
