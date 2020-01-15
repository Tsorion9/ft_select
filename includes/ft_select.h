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

t_lstr					*lstr;

/*
** main.c
*/

void        			return_term_mode(void);
void        			into_term_can_mode(void);
void					exit_program(int a);
int						ret_winsize(int a);
int						ft_putint(int c);
void					clear_window(void);
void        			print_result(t_lstr *lstr);

/*
** execute_command.c
*/

void       				execute_command(t_lstr *lstr);
void        			execute_command_sup1(long c);
void        			execute_command_sup(long c);

/*
** list.c
*/

t_lstr					*create_lstr(char *name);
void					add_new_lstr(t_lstr *lstr, char *name);
t_lstr					*init_lstr(char **av);

/*
** display_str.c
*/

void					display_lstr(int col, int lin, t_lstr *lstr);
void					display_lstr_sup(t_lstr *lstr, int width, int finish, int start);
void					print_lstr(int start, int finish, t_lstr *lstr, int width);
void					absolute_cursor_pos(int col, int lin);

/*
** check_winsize.c
*/

int						check_winsize(int col, int lin, t_lstr *lstr);
int						max_strlen(t_lstr *lstr, int start, int finish);
int						count_lstr(t_lstr *lstr);

/*
** change_lstr.c
*/

void        			change_chose_left(t_lstr *lstr, int lin);
void        			change_chose_right(t_lstr *lstr, int lin);
void        			change_chose(t_lstr *lstr);
void        			change_hover_over(t_lstr *lstr, int flag);
void        			delete_lstr(t_lstr **lstr);

/*
** signal.c
*/

void        			set_signal(void);
void        			signal_processing(int a);

/*
** free.c
*/

void					free_lstr(t_lstr *lstr);

#endif
