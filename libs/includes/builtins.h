#ifndef _PN_BUILTINS_
#define _PN_BUILTINS_

#include "types.h"
#include <sys/_timeval.h>
#include <sys/stat.h>

pn_t_table pn_builtins_ls(pn_state *pn, char *args, ...);
pn_t_path  pn_builtins_pwd(pn_state *pn);
void       pn_builtins_cd(pn_state *pn, char *dir);

#endif /* _PN_BUILTINS_ */
