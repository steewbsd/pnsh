#include "includes/builtins.h"
#include "libs/includes/types.h"
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

pn_t_table
pn_builtins_ls(pn_state *pn, char *args, ...)
{
  pn_t_table table;
  table = create_table(BLTN_LS, MAX_TABLE_LEN);
	
  DIR * d;
  struct dirent *dir;
  d = opendir(pn->loc.literal);
  int file_index = 0;
  if (d) {
	while ((dir = readdir(d)) != NULL) {
	  struct stat s;
	  stat(dir->d_name, &s);
	  struct pn_t_list_ls_field field =
		{
		  .perms    = s.st_mode,
		  .filename = dir->d_name,
		  .group    = s.st_gid,
		  .owner    = s.st_uid,
		};
	  memcpy(table.lists + table.unit_size * file_index,
			 &field, sizeof(struct pn_t_list_ls_field));
	  file_index++;
	}
  }
  closedir(d);
  return table;
}
void
pn_builtins_cd(pn_state *pn, char *dir)
{
  pn->loc.literal = dir;
}
