//
// profile.cpp
// by Naomi Peori (naomi@peori.ca)
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "SDK/VideoEq.h"
#include "profile.h"

//
// Functions
//

bool PROFILE_t::reset ( VideoEq *videoEq )
{
  return this->set ( videoEq, 0 );
}

bool PROFILE_t::set ( VideoEq *videoEq, unsigned int index )
{
  if ( videoEq )
  {
    if ( videoEq->setCurrentProfile ( index ) == VideoEq::NoError )
    {
      // TODO: Wait 5 seconds?
      return true;
    }
  }

  return false;
}
