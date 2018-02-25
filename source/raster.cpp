//
// raster.cpp
// by Naomi Peori (naomi@peori.ca)
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "SDK/VideoEq.h"
#include "raster.h"

//
// Functions
//

bool RASTER_t::reset ( VideoEq *videoEq )
{
  if ( videoEq )
  {
    if ( videoEq->setRasterWindow ( VideoEq::RW_Off, 0, 0, 0 ) == VideoEq::NoError )
    {
      return true;
    }
  }

  return false;
}

bool RASTER_t::set ( VideoEq *videoEq, RASTER_TYPE_t rasterType, unsigned int red, unsigned int green, unsigned int blue )
{
  if ( videoEq )
  {
    if ( videoEq->setRasterWindow ( ( rasterType == RASTER_TYPE_INPUT ) ? VideoEq::RW_Input : VideoEq::RW_Output, red, green, blue ) == VideoEq::NoError )
    {
      return true;
    }
  }

  return false;
}
