//
// cms.h
// by Naomi Peori (naomi@peori.ca)
//

#pragma once

struct CMS_t
{

  static const int CMS_ENTRIES = 6;

	enum CMS_TYPE_t
  {
    CMS_TYPE_HSV,
    CMS_TYPE_RGB
  };

  union
  {
    VEqHsv hsv[ CMS_ENTRIES ];
    VEqRgb rgb[ CMS_ENTRIES ];
    float  raw[ CMS_ENTRIES ][ 3 ];
  }
  cmsTable;

  //
  // Functions
  //

  bool reset ( void );

  bool push ( VideoEq *videoEq, CMS_TYPE_t cmsType );
  bool pull ( VideoEq *videoEq, CMS_TYPE_t cmsType );

  bool load ( const char *filename );
  bool save ( const char *filename );

};
