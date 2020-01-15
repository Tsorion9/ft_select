/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:58:43 by mphobos           #+#    #+#             */
/*   Updated: 2020/01/15 17:52:56 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Меняет положение курсора
*/

void		absolute_cursor_pos(int col, int lin)
{
	tputs(tgoto(tgetstr("cm", NULL), col, lin), 1, ft_putint);
}

/*
** Печатает столбец строк
*/

void		print_lstr(int start, int finish, t_lstr *lstr, int width)
{
	int	i;

	i = 0;
	while (i < start)
	{
		lstr = lstr->next;
		i++;
	}
	i = 0;
	while (start++ < finish)
	{
		if (lstr->hover_over == 1)
			ft_putstr_fd("\033[4m", STDERR_FILENO);
		if (lstr->color == 1)
			ft_putstr_fd("\033[34m", STDERR_FILENO);
		else if (lstr->color == 2)
			ft_putstr_fd("\033[31m", STDERR_FILENO);
		if (lstr->chose == 1)
			ft_putstr_fd("\033[1m", STDERR_FILENO);
		ft_putstr_fd(lstr->name, STDERR_FILENO);
		ft_putstr_fd("\033[\033[0m", STDERR_FILENO);
		i++;
		absolute_cursor_pos(width, i);
		lstr = lstr->next;
	}
}

void		display_lstr_sup(t_lstr *lstr, int width, int finish, int start)
{
	int	c_lstr;
	int	z;

	c_lstr = count_lstr(lstr);
	z = finish;
	while (finish <= c_lstr)
	{
		print_lstr(start, finish, lstr, width);
		width = max_strlen(lstr, start, finish) + width + 1;
		absolute_cursor_pos(width, 0);
		if (finish == c_lstr)
			break ;
		start = finish;
		if ((finish += z) >= c_lstr)
			finish = c_lstr;
	}
}

/*
** Проверяет и выводит строки
*/

void		display_lstr(int col, int lin, t_lstr *lstr)
{
	int		c_lstr;
	int		start;
	int		finish;
	int		width;
	int		z;

	clear_window();
	if (check_winsize(col, lin, lstr) == 0)
	{
		write(2, "window is too small\n", 20);
		return ;
	}
	c_lstr = count_lstr(lstr);
	start = 0;
	finish = c_lstr;
	if (lin <= c_lstr)
		finish = (c_lstr - (c_lstr % lin)) / (c_lstr / lin);
	z = finish;
	width = 0;
	display_lstr_sup(lstr, width, finish, start);
	absolute_cursor_pos(0, 0);
}
