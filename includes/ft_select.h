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
# include <sys/stat.h>

static struct termios   settings;
extern char             **environ;

typedef struct			s_lstr
{
	char				*name;
	char				last;
	char				color;
	char				hover_over;
	char				chose;
	struct s_lstr		*prev;
	struct s_lstr		*next;
}						t_lstr;

/*
** main.c
*/

void					exit_program(int a);

/*
** list.c
*/

t_lstr					*create_lstr(char *name);
void					add_new_lstr(t_lstr *lstr, char *name);
t_lstr					*init_lstr(char **av);

/*
** display_str.c
*/

int						check_winsize(int col, int len, t_lstr *lstr);
int						max_strlen(t_lstr *lstr, int start, int finish);
int						count_lstr(t_lstr *lstr);

/*
** free.c
*/

void					free_lstr(t_lstr *lstr);

#endif
