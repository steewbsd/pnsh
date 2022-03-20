#include "includes/exec.h"
#include <search.h>

char *pn_get_hashed_path(char *shorthand) {
  ENTRY cmd;
  ENTRY *full_path;
  cmd.key = shorthand;
  full_path = hsearch(cmd, FIND);
  return NULL;
}
