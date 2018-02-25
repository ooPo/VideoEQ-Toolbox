//
// cms.h
// by Naomi Peori (naomi@peori.ca)
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "SDK/VideoEq.h"
#include "cms.h"

//
// Functions
//

bool CMS_t::reset ( )
{
  for ( int loop = 0; loop < CMS_ENTRIES; loop++ )
  {
    cmsTable.raw[ loop ][ 0 ] = 0.00f;
    cmsTable.raw[ loop ][ 1 ] = 1.00f;
    cmsTable.raw[ loop ][ 2 ] = 1.00f;    
  }

  return true;
}

bool CMS_t::push ( VideoEq *videoEq, CMS_TYPE_t cmsType )
{
  if ( videoEq )
  {
    uint8_t currentCms[ VideoEq::kCmsSize ] = { 0 };

    ( cmsType == CMS_TYPE_HSV ) ? videoEq->hsvToVEq ( currentCms, cmsTable.hsv ) : videoEq->rgbToVEq ( currentCms, cmsTable.rgb );

    if ( videoEq->setCurrentCms ( currentCms ) == VideoEq::NoError )
    {
      return true;
    }
  }

  return false;
}

bool CMS_t::pull ( VideoEq *videoEq, CMS_TYPE_t cmsType )
{
  if ( videoEq )
  {
    uint8_t currentCms[ VideoEq::kCmsSize ] = { 0 };

    if ( videoEq->getCurrentCms ( currentCms ) == VideoEq::NoError )
    {
      ( cmsType == CMS_TYPE_HSV ) ? videoEq->veqToHSV ( cmsTable.hsv, currentCms ) : videoEq->veqToRGB ( cmsTable.rgb, currentCms );

      return true;
    }
  }

  return false;
}

bool CMS_t::load ( char *filename )
{
  if ( filename )
  {
    FILE *infile = fopen ( filename, "r" );

    if ( infile )
    {
      for ( int loop = 0; loop < CMS_ENTRIES; loop++ )
      {
        fscanf ( infile, "%f, %f, %f\r\n", &cmsTable.raw[ loop ][ 0 ], &cmsTable.raw[ loop ][ 1 ], &cmsTable.raw[ loop ][ 2 ] );
      }

      fclose ( infile );

      return true;
    }
  }

  return false;
}

bool CMS_t::save ( char *filename )
{
  if ( filename )
  {
    FILE *outfile = fopen ( filename, "w" );

    if ( outfile )
    {
      for ( int loop = 0; loop < CMS_ENTRIES; loop++ )
      {
        fprintf ( outfile, "%f, %f, %f\r\n", cmsTable.raw[ loop ][ 0 ], cmsTable.raw[ loop ][ 1 ], cmsTable.raw[ loop ][ 2 ] );
      }

      fclose ( outfile );

      return true;
    }
  }

  return false;
}
