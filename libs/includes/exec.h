/* exec.h:
 * utils for executing a command
 */

#ifndef _PN_EXEC_H_
#define _PN_EXEC_H_

#include <search.h>
#include <unistd.h>

char *pn_get_hashed_path(char *shorthand);
int pn_exec(char * path);

#endif /* _PN_EXEC_H_ */
