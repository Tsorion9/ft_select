/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 13:10:07 by mphobos           #+#    #+#             */
/*   Updated: 2020/01/16 12:58:06 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Настраивает терминал (неканонический ввод)
*/

void		into_term_can_mode(void)
{
	struct termios	new_settings;

	tcgetattr(STDIN_FILENO, &g_settings);
	new_settings = g_settings;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
	tputs(tgetstr("ti", NULL), 1, ft_putint);
	tputs(tgetstr("vi", NULL), 1, ft_putint);
}

/*
** Возвращает настройки терминала (канонический ввод)
*/

void		return_term_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_settings);
	tputs(tgetstr("ve", NULL), 1, ft_putint);
	tputs(tgetstr("te", NULL), 1, ft_putint);
}

/*
** Выход из программы
*/

void		exit_program(int a)
{
	(void)a;
	clear_window();
	return_term_mode();
	exit(0);
}

/*
** Печать результата
*/

void		print_result(t_lstr *lstr)
{
	while (lstr->last != 1)
	{
		if (lstr->chose == 1)
		{
			ft_putstr(lstr->name);
			write(1, " ", 1);
		}
		lstr = lstr->next;
	}
	if (lstr->chose == 1)
	{
		ft_putstr(lstr->name);
		write(1, " ", 1);
	}
}

int			main(int ac, char **av)
{
	if (ac < 2)
	{
		ft_putstr("usage: ");
		ft_putstr(av[0]);
		ft_putstr(" [arg1] [arg2] ...\n");
		return (0);
	}
	set_signal();
	into_term_can_mode();
	g_lstr = init_lstr(av + 1);
	display_lstr(ret_winsize(0), ret_winsize(1), g_lstr);
	execute_command(g_lstr);
	return (0);
}
