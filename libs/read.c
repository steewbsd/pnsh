#include "includes/read.h"

/* default prompt to be displayed in stdout */
char
*pn_prompt(EditLine *el)
{
  return ">> ";
}

char *
pn_strip_newline(char *line)
{
  char * stripped = line;
  stripped[strcspn(stripped, "\n")] = 0;
  return stripped;
}

/* DEBUG: NEEDS_FREE
 * read returns the input in the TTY received by editline, allocating
 * enough space to return it dynamically
 */
char *
pn_read(EditLine *el)
{
  /* safeguard to clean the input buffer */
  fflush(stdin);
  int count = 0;
  /* read line and store it in a temporary (stack) variable */
  const char *stackline = el_gets(el, &count);
  /* return if nothing was read */
  if (count < 1 || stackline == NULL)
	return NULL;
  /* allocate exactly the number of chars read by el_gets */
  char *line = malloc(count);
  /* copy memory region over to heap */
  memcpy(line, stackline, count);
  return line;
  return NULL;
}
