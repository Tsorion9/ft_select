/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:31:08 by mphobos           #+#    #+#             */
/*   Updated: 2020/01/15 18:02:44 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Обработка сигналов
*/

void		signal_processing(int a)
{
	if (a == SIGTSTP)
	{
		return_term_mode();
		signal(SIGTSTP, SIG_DFL);
		ioctl(STDERR_FILENO, TIOCSTI, "\032");
	}
	else if (a == SIGCONT)
	{
		into_term_can_mode();
		set_signal();
		display_lstr(ret_winsize(0), ret_winsize(1), lstr);
	}
	else if (a == SIGWINCH)
	{
		into_term_can_mode();
		set_signal();
		display_lstr(ret_winsize(0), ret_winsize(1), lstr);
	}
}

/*
** Настройка сигналов и внесение терминала в БД termcap
*/

void		set_signal(void)
{
	char *termtype;
	char room_termtype[2048];

	termtype = getenv("TERM");
	if (termtype == NULL || tgetent(room_termtype, termtype) != 1)
	{
		ft_putstr("error\n");
		exit_program(0);
	}
	signal(SIGINT, exit_program);
	signal(SIGTSTP, signal_processing);
	signal(SIGCONT, signal_processing);
	signal(SIGWINCH, signal_processing);
}
