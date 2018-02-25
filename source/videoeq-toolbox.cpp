//
// videoeq-toolbox.cpp
// by Naomi Peori (naomi@peori.ca)
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "sdk/VideoEq.h"

#include "config.h"
#include "cms.h"
#include "lut.h"
#include "profile.h"
#include "raster.h"

//
// Configuration
//

#define STRING_NAME       "VideoEQ MX Toolbox"
#define STRING_VERSION    "v1.0.0"
#define STRING_AUTHOR     "Naomi Peori (naomi@peori.ca)"

//
// Helper Functions
//

bool stringCompare ( const char *first, const char *second )
{
  bool success = false;

  if ( strlen ( first ) == strlen ( second ) )
  {
    if ( strcmp ( first, second ) == 0 )
    {
      success = true;
    }
  }

  return success;
}

#define argumentCompare(index, value) ( ( argc > index ) ? stringCompare ( value, argv[ index ] ) : false )

//
// Main Program
//

int main ( int argc, char *argv[ ] )
{
  bool success = false;

  VideoEq *videoEq = new VideoEq ( );

  if ( videoEq->connect() == VideoEq::NoError )
  {
    //
    // Config Commands
    //

    if ( argumentCompare ( 1, "config" ) )
    {
      CONFIG_t config;

      if ( argumentCompare ( 2, "reset" ) )
      {
        success = config.reset ( videoEq );
      }
      else if ( argc > 3 )
      {
        if ( argumentCompare ( 2, "deepColorForce" ) )
        {
          success = config.deepColorForce ( videoEq, argumentCompare ( 3, "enable" ) ? true : false );
        }
        else if ( argumentCompare ( 2, "hdcpForce" ) )
        {
          success = config.hdcpForce ( videoEq, argumentCompare ( 3, "enable" ) ? true : false );
        }
      }
    }

    //
    // CMS Commands
    //

    if ( argumentCompare ( 1, "cms" ) )
    {
      CMS_t cms;

      if ( argumentCompare ( 2, "reset" ) )
      {
        if ( cms.reset ( ) && cms.push ( videoEq, CMS_t::CMS_TYPE_HSV ) )
        {
          success = true;
        }
      }
      else if ( argc > 4 )
      {
        CMS_t::CMS_TYPE_t cmsType = argumentCompare ( 3, "rgb" ) ? CMS_t::CMS_TYPE_RGB : CMS_t::CMS_TYPE_HSV;

        if ( argumentCompare ( 2, "load" ) )
        {
          if ( cms.load ( argv[ 4 ] ) && cms.push ( videoEq, cmsType ) )
          {
            success = true;
          }
        }
        else if ( argumentCompare ( 2, "save" ) )
        {
          if ( cms.pull ( videoEq, cmsType ) && cms.save ( argv[ 4 ] ) )
          {
            success = true;
          }
        }
      }
    }

    //
    // LUT Commands
    //

    else if ( argumentCompare ( 1, "lut" ) )
    {
      LUT_t lut;

      if ( argumentCompare ( 2, "reset" ) )
      {
        if ( lut.reset ( ) && lut.push ( videoEq ) )
        {
          success = true;
        }
      }
      else if ( argc > 3 )
      {
        if ( argumentCompare ( 2, "load" ) )
        {
          if ( lut.load ( argv[ 3 ] ) && lut.push ( videoEq ) )
          {
            success = true;
          }
        }
        else if ( argumentCompare ( 2, "save" ) )
        {
          if ( lut.pull ( videoEq ) && lut.save ( argv[ 3 ] ) )
          {
            success = true;
          }
        }
      }
    }

    //
    // Profile Commands
    //

    else if ( argumentCompare ( 1, "profile" ) )
    {
      PROFILE_t profile;

      if ( argumentCompare ( 2, "reset" ) )
      {
        success = profile.reset ( videoEq );
      }
      else if ( argc > 3 )
      {
        if ( argumentCompare ( 2, "set" ) )
        {
          success = profile.set ( videoEq, atoi ( argv[ 3 ] ) );
        }
      }
    }

    //
    // Raster Commands
    //

    else if ( argumentCompare ( 1, "raster" ) )
    {
      RASTER_t raster;

      if ( argumentCompare ( 2, "reset" ) )
      {
        success = raster.reset ( videoEq );
      }
      else if ( argc > 5 )
      {
        if ( argumentCompare ( 2, "set" ) )
        {
          success = raster.set ( videoEq, argumentCompare ( 3, "input" ) ? RASTER_t::RASTER_TYPE_INPUT : RASTER_t::RASTER_TYPE_OUTPUT, atoi ( argv[ 4 ] ), atoi ( argv[ 5 ] ), atoi ( argv[ 6 ] ) );
        }
      }
    }

    videoEq->disconnect ( );
  }

  //
  // Usage Text
  //

  if ( ! success )
  {
    printf ( "%s %s - by %s\n\n", STRING_NAME, STRING_VERSION, STRING_AUTHOR );

    printf ( "USAGE:\n" );
    printf ( "  %s <module> <command> [arguments]\n", argv[ 0 ] );
    printf ( "\n" );
    printf ( "CONFIG:\n" );
    printf ( "  config reset\n" );
    printf ( "  config deepColorForce <enable|disable>\n" );
    printf ( "  config hdcpForce <enable|disable>\n" );
    printf ( "\n" );
    printf ( "CMS:\n" );
    printf ( "  cms reset\n" );
    printf ( "  cms load <hsv|rgb> <filename.csv>\n" );
    printf ( "  cms save <hsv|rgb> <filename.csv>\n" );
    printf ( "\n" );
    printf ( "LUT:\n" );
    printf ( "  lut reset\n" );
    printf ( "  lut load <filename.csv>\n" );
    printf ( "  lut save <filename.csv>\n" );
    printf ( "\n" );
    printf ( "PROFILE:\n" );
    printf ( "  profile reset\n" );
    printf ( "  profile set <index>\n" );
    printf ( "\n" );
    printf ( "RASTER:\n" );
    printf ( "  raster reset\n" );
    printf ( "  raster set <input|output> <red> <green> <blue>\n" );
  }

  return success ? 0 : -1;
}
