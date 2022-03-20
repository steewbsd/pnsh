#include "libs/includes/builtins.h"
#include "libs/includes/read.h"
#include "libs/includes/types.h"
#include <histedit.h>
#include <locale.h>
#include <search.h>
#include <err.h>
#include <stdio.h>
#include <string.h>

EditLine *el;

int
main()
{
  char * line;

  /* initialize libedit */
  el = el_init("pnsh", stdin, stdout, stderr);
  /* set default editing mode as emacs style (author's choice) */
  el_set(el, EL_EDITOR, "emacs");
  /* stablish a prompt function */
  el_set(el, EL_PROMPT, pn_prompt);
  /* adopt system locale */
  setlocale(LC_CTYPE, "");

  /* fail if EditLine object is NULL */
  if (el == NULL) {
	  errx(1, "failed to initialize EditLine");
	  goto EMERGENCY_FREE;
  }

  pn_state *pn = pn_init_state();
  if (pn == NULL) {
	errx(1, "failed to initialize program state");
	goto EMERGENCY_FREE;
  }
  
  /* main loop to get user input */
  while ((line = pn_read(el)) != NULL) {
	ENTRY *command;
	ENTRY tofind;
	
	tofind.key = pn_strip_newline(line);
	command = hsearch(tofind, FIND);
	if (command == NULL) {
	  printf("command not registered: %s\n", tofind.key);
	  continue;
	}
	
	if (strcmp(pn_strip_newline(line), "ls") == 0) {
	  pn_t_table table = pn_builtins_ls(pn, "");
	  pn_print_table(table, 0);
	  free(table.lists);
	}
	else if (strcmp(pn_strip_newline(line), "cd") == 0)
	  pn_builtins_cd(pn, "/home/rier");
	else if (strcmp(pn_strip_newline(line), "q") == 0)
	  break;
	/* free line, as it was copied dynamically */
	free(line);
  }

 EMERGENCY_FREE:
  /* free EditLine object */
  el_end(el);
  /* free pnsh state */
  pn_destroy_state(pn);
  hdestroy();
}

