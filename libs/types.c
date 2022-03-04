#include "includes/types.h"
#include <fcntl.h>

pn_t_path
pn_new_path(char *literal) {
  pn_t_path path;
  path.literal = literal;
  return path;
}
