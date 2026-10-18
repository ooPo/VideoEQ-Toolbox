//
// profile.cpp
// by Naomi Peori (naomi@peori.ca)
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDK/VideoEq.h"
#include "profile.h"

//
// Functions
//

bool PROFILE_t::reset(VideoEq *videoEq) {
  return this->set(videoEq, 0);
}

bool PROFILE_t::get(VideoEq *videoEq, unsigned int *index) {
  if (videoEq) {
    if (videoEq->getCurrentProfile(*index) == VideoEq::NoError) {
      return true;
    }
  }

  return false;
}

bool PROFILE_t::set(VideoEq *videoEq, unsigned int index) {
  if (videoEq) {
    VideoEq::VEqError error = videoEq->setCurrentProfile(index);

    if (error == VideoEq::NoError) {
      // TODO: Wait 5 seconds?
      return true;
    }

    if (error == VideoEq::InvalidProfile) {
      printf("Error: invalid profile index %u.\n", index);
    }
  }

  return false;
}
