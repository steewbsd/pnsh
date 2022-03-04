/* types.h:
 * global types for the shell, to be used at runtime
 */

#ifndef _PN_TYPES_H_
#define _PN_TYPES_H_

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>

typedef struct {
  FILE *_fd;
  char *literal;
} pn_t_path;

typedef struct {
  char *exec_path;
  bool _alias;
  /* TODO: competion callback with cuecoon */
} pn_t_cmd;

typedef enum {F_SHORT, F_LONG, F_BSD_STYLE} FLAG_T;
typedef struct {
  FLAG_T flag_type;
} pn_t_cmd_flag;

typedef struct {
  int pid;
  int _parent;
} pn_t_proc;

typedef struct {
  void *field;
} pn_t_list;

typedef struct {
  int rows;
  int cols;
  int key;
  pn_t_list *lists;
} pn_t_table;

typedef struct {
  int status;
} pn_t_exec_status;

/* init funcs */
/* pn_t_path */
pn_t_path pn_new_path(char *literal);
FILE * pn_new_fd(pn_t_path p);

#endif /* _PN_TYPES_H_ */

