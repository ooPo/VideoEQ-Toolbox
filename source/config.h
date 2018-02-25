//
// config.h
// by Naomi Peori (naomi@peori.ca)
//

#pragma once

struct CONFIG_t
{

  //
  // Functions
  //

  bool reset ( VideoEq *videoEq );

  bool deepColorForce ( VideoEq *videoEq, bool enable );

  bool hdcpForce ( VideoEq *videoEq, bool enable );

};
