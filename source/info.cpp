//
// info.cpp
// by Naomi Peori (naomi@peori.ca)
//

#include <stdio.h>
#include <stdint.h>

#include "SDK/VideoEq.h"
#include "info.h"

//
// Configuration
//

static const char *modelNames[ ] = { "None", "Basic", "CMS", "Pro", "MX", "Post" };

//
// Functions
//

bool INFO_t::print ( VideoEq *videoEq )
{
  if ( videoEq )
  {
    VideoEq::Model model = VideoEq::Model_None;
    const char *firmware = "unknown";
    const char *serial = "unknown";
    const char *manufacturer = "unknown";
    uint8_t hardware = 0;

    if ( videoEq->getModel ( model ) == VideoEq::NoError )
    {
      printf ( "Model: %s\n", modelNames[ model ] );
    }

    if ( videoEq->getManufacturer ( manufacturer ) == VideoEq::NoError )
    {
      printf ( "Manufacturer: %s\n", manufacturer );
    }

    if ( videoEq->getFirmwareVersion ( firmware ) == VideoEq::NoError )
    {
      printf ( "Firmware: %s\n", firmware );
    }

    if ( videoEq->getHardwareVersion ( hardware ) == VideoEq::NoError )
    {
      printf ( "Hardware: %u\n", hardware );
    }

    if ( videoEq->getSerialNumber ( serial ) == VideoEq::NoError )
    {
      printf ( "Serial: %s\n", serial );
    }

    return true;
  }

  return false;
}