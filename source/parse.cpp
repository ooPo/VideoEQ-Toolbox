//
// parse.cpp
// by Naomi Peori (naomi@peori.ca)
//

#include <stdlib.h>

#include "parse.h"

//
// Functions
//

bool parseArgument(const char *text, unsigned int *value, unsigned int max) {
  char *endptr;
  long parsed = strtol(text, &endptr, 10);

  if (endptr != text && *endptr == '\0' && parsed >= 0 && parsed <= max) {
    *value = (unsigned int)parsed;
    return true;
  }

  return false;
}