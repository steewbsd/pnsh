#include "includes/types.h"
#include <err.h>
#include <dirent.h>
#include <search.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

pn_t_path
pn_new_path(char *literal)
{
  pn_t_path path;
  path.literal = literal;
  return path;
}

pn_state *
pn_init_state()
{
  pn_state * pn;
  pn = malloc(sizeof(pn_state));
  pn->loc.literal = PATHS_DEFAULT;
  
  DIR * d;
  struct dirent *dir;
  
  char * paths = getenv("PATH");
  char * token;
  ENTRY item;
  hcreate(100);
  while ((token = strsep(&paths, ":")) != NULL) {
	d = opendir(token);
	if (d) {
	  while ((dir = readdir(d)) != NULL) {
		item.key = strdup(dir->d_name);
		sprintf(item.data, "%s/%s", token, dir->d_name);
		hsearch(item, ENTER);
	  }
	  closedir(d);
	}
  }
  /* overwrite entries with builtin functions */
  for (int i = 0; i <= sizeof(builtin_commands)/sizeof(builtin_commands[0]); i++) {
	item.key = strdup(builtin_commands[i]);
	item.data = 0;
	hsearch(item, ENTER);
  }
  return pn;
}

void
pn_destroy_state(pn_state *pn)
{
  free(pn);
}

/* DEBUG: NEEDS_FREE */
/* create a new table with specified type and an approximate number of rows */
pn_t_table
create_table(TABLE_TYPE type, int rows)
{
  pn_t_table table;
  size_t malloc_size = 1;
  /* initialize table rows, with a minimum of 1 and max of MAX_TABLE_LEN */
  if (rows < 0 || rows > MAX_TABLE_LEN)
	rows = MAX_TABLE_LEN;
  /* calculate memory allocation requirements for each table type */
  switch (type) {
  case BLTN_LS:
	malloc_size = sizeof(struct pn_t_list_ls_field);
	break;
  default:
	errx(1, "create_table: Failed to initialize table with unknown type\n");
  }
  table.unit_size = malloc_size;
  table.rows = rows;
  table.type = type;
  table.lists = malloc(malloc_size*table.rows);
  if (table.lists == NULL)
	  errx(1, "create_table: Failed to allocate memory for the table\n");
	/* initialize memory region to 0 */
	bzero(table.lists, malloc_size*rows);
  return table;
}

void
pn_print_table(pn_t_table table, int cols, ...)
{
  switch (table.type) {
  case BLTN_LS:

	for (int i = 0; i <= table.rows; i++) {
	  struct pn_t_list_ls_field *field =
		(struct pn_t_list_ls_field *)(table.lists + table.unit_size * i);
	  if (field->filename == NULL)
		break;
	  printf("%d\t%s\t\t\t%d\t%d\n",
			 field->perms,
			 field->filename,
			 field->group,
			 field->owner);
	}
	break;
  default:
	errx(1, "pn_print_table: Unable to print table of unknown type\n");
  }
}
