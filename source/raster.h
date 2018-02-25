//
// raster.h
// by Naomi Peori (naomi@peori.ca)
//

#pragma once

struct RASTER_t
{

	enum RASTER_TYPE_t
	{
    RASTER_TYPE_INPUT,
    RASTER_TYPE_OUTPUT
  };

  //
  // Functions
  //

  bool reset ( VideoEq *videoEq );

  bool set ( VideoEq *videoEq, RASTER_TYPE_t rasterType, unsigned int red, unsigned int green, unsigned int blue );

};
