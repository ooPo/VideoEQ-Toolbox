//
// profile.h
// by Naomi Peori (naomi@peori.ca)
//

#pragma once

struct PROFILE_t
{

  //
  // Functions
  //

  bool reset ( VideoEq *videoEq );

  bool get ( VideoEq *videoEq, unsigned int *index );

  bool set ( VideoEq *videoEq, unsigned int index );

};
