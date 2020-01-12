#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <unistd.h>
# include <termios.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include "../libft/includes/libft.h"

static struct termios   settings;
extern char             **environ;

#endif
