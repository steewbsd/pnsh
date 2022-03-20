/* types.h:
 * global types for the shell, to be used at runtime
 */

#ifndef _PN_TYPES_H_
#define _PN_TYPES_H_

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>

#define PATHS_ROOT "/"
#define PATHS_DEFAULT "/home/rier"
#define MAX_TABLE_LEN 50

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

/* TABLE FIELDS DEFINITION */
/* Builtin ls command field structure */
struct pn_t_list_ls_field {
  int   perms;
  int   owner;
  int   group;
  char *filename;
};

typedef enum {BLTN_LS} TABLE_TYPE;
typedef struct {
  TABLE_TYPE type;
  int rows;
  void *lists; /* holds any pn_t_list_x type */
  size_t unit_size;
} pn_t_table;

typedef struct {
  int status;
} pn_t_exec_status;

typedef struct {
  pn_t_path loc;
} pn_state;

/* init funcs */
/* pn_t_path */
void       pn_print_table(pn_t_table table, int cols, ...);
pn_t_table create_table(TABLE_TYPE type, int rows);
pn_state  *pn_init_state();
void       pn_destroy_state(pn_state *pn);
pn_t_path  pn_new_path(char *literal);
FILE      *pn_new_fd(pn_t_path p);

#endif /* _PN_TYPES_H_ */

