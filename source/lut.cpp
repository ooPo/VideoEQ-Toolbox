//
// lut.cpp
// by Naomi Peori (naomi@peori.ca)
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "SDK/VideoEq.h"
#include "lut.h"

//
// Functions
//

bool LUT_t::reset ( )
{
  for ( int loop = 0; loop < LUT_ENTRIES; loop++ )
  {
    lutTable.r[ loop ] = loop;
    lutTable.g[ loop ] = loop;
    lutTable.b[ loop ] = loop;
  }

  return true;
}

bool LUT_t::push ( VideoEq *videoEq )
{
  if ( videoEq )
  {
    if ( videoEq->setCurrentLut ( lutTable.r, lutTable.g, lutTable.b ) == VideoEq::NoError )
    {
      return true;
    }
  }

  return false;
}

bool LUT_t::pull ( VideoEq *videoEq )
{
  if ( videoEq )
  {
    if ( videoEq->getCurrentLut ( lutTable.r, lutTable.g, lutTable.b ) == VideoEq::NoError )
    {
      return true;
    }
  }

  return false;
}

bool LUT_t::load ( char *filename )
{
  if ( filename )
  {
    FILE *infile = fopen ( filename, "r" );

    if ( infile )
    {
      for ( int loop = 0; loop < LUT_ENTRIES; loop++ )
      {
        fscanf ( infile, "%hu, %hu, %hu\r\n", &lutTable.r[ loop ], &lutTable.g[ loop ], &lutTable.b[ loop ] );
      }

      fclose ( infile );

      return true;
    }
  }

  return false;
}

bool LUT_t::save ( char *filename )
{
  if ( filename )
  {
    FILE *outfile = fopen ( filename, "w" );

    if ( outfile )
    {
      for ( int loop = 0; loop < LUT_ENTRIES; loop++ )
      {
        fprintf ( outfile, "%hu, %hu, %hu\r\n", lutTable.r[ loop ], lutTable.g[ loop ], lutTable.b[ loop ] );
      }

      fclose ( outfile );

      return true;
    }
  }

  return false;
}
