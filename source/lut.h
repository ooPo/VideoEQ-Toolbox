//
// lut.h
// by Naomi Peori (naomi@peori.ca)
//

#pragma once

struct LUT_t
{

  static const int LUT_ENTRIES = 1024;

  struct
  {
    uint16_t r[ LUT_ENTRIES ];
    uint16_t g[ LUT_ENTRIES ];
    uint16_t b[ LUT_ENTRIES ];
  }
  lutTable;

  //
  // Functions
  //

  bool reset ( );

  bool push ( VideoEq *videoEq );
  bool pull ( VideoEq *videoEq );

  bool load ( const char *filename );
  bool save ( const char *filename );

};
