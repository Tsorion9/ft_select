/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 18:08:31 by mphobos           #+#    #+#             */
/*   Updated: 2020/01/15 19:00:16 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		execute_command_sup(t_lstr **lstr, long c)
{
	if (c == 32)
	{
		change_chose(*lstr);
		display_lstr(ret_winsize(0), ret_winsize(1), *lstr);
	}
	else if (c == 4414235)
	{
		change_chose_right(*lstr, ret_winsize(1));
		display_lstr(ret_winsize(0), ret_winsize(1), *lstr);
	}
	else if (c == 4479771)
	{
		change_chose_left(*lstr, ret_winsize(1));
		display_lstr(ret_winsize(0), ret_winsize(1), *lstr);
	}
	else if (c == 10)
	{
		clear_window();
		return_term_mode();
		print_result(*lstr);
		exit(0);
	}
}

void		execute_command_sup1(t_lstr **lstr, long c)
{
	if (c == 27)
	{
		clear_window();
		return_term_mode();
		exit(0);
	}
	else if (c == 127)
	{
		delete_lstr(&lstr);
		display_lstr(ret_winsize(0), ret_winsize(1), *lstr);
	}
}

/*
** Обработка комманд
*/

void		execute_command(t_lstr *lstr)
{
	long	c;

	while (21)
	{
		c = 0;
		read(STDERR_FILENO, &c, 8);
		if (c == 4348699)
		{
			change_hover_over(lstr, 0);
			display_lstr(ret_winsize(0), ret_winsize(1), lstr);
		}
		else if (c == 4283163)
		{
			change_hover_over(lstr, 1);
			display_lstr(ret_winsize(0), ret_winsize(1), lstr);
		}
		execute_command_sup(&lstr, c);
		execute_command_sup1(&lstr, c);
	}
}
