/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 12:54:20 by mphobos           #+#    #+#             */
/*   Updated: 2020/01/16 12:58:47 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static struct termios	g_settings;
t_lstr					*g_lstr;

/*
** main.c
*/

void					return_term_mode(void);
void					into_term_can_mode(void);
void					exit_program(int a);
void					print_result(t_lstr *lstr);

/*
** execute_command.c
*/

void					execute_command(t_lstr *lstr);
void					execute_command_sup1(t_lstr **lstr, long c);
void					execute_command_sup(t_lstr **lstr, long c);

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
void					display_lstr_sup(t_lstr *l, int w, int f, int s);
void					print_lstr(int s, int f, t_lstr *l, int w);
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

void					change_chose_left(t_lstr *lstr, int lin);
void					change_chose_right(t_lstr *lstr, int lin);
void					change_chose(t_lstr *lstr);
void					change_hover_over(t_lstr *lstr, int flag);
void					delete_lstr(t_lstr ***lstr);

/*
** signal.c
*/

void					set_signal(void);
void					signal_processing(int a);

/*
** other_functions.c
*/

int						ret_winsize(int a);
void					clear_window(void);
int						ft_putint(int c);

/*
** free.c
*/

void					free_lstr(t_lstr *lstr);

#endif
