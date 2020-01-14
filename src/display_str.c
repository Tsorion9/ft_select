/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:58:43 by mphobos           #+#    #+#             */
/*   Updated: 2020/01/13 17:57:23 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Возвращяет количество строк
*/

int			count_lstr(t_lstr *lstr)
{
	int	count;

	count = 0;
	while (lstr->last != 1)
	{
		count++;
		lstr = lstr->next;
	}
	return (count + 1);
}

/*
** Возвращает размер самой длиной строки
*/

int			max_strlen(t_lstr *lstr, int start, int finish)
{
	int	strlen;
	int	i;

	strlen = 0;
	i = 0;
	while (i < start)
	{
		lstr = lstr->next;
		i++;
	}
	while (start < finish)
	{
		if (ft_strlen(lstr->name) > (size_t)strlen)
			strlen = ft_strlen(lstr->name);
		if (lstr->last == 1 && (start < finish))
		{
			if (ft_strlen(lstr->name) > (size_t)strlen)
				strlen = ft_strlen(lstr->name);
			break ;
		}
		lstr = lstr->next;
	}
	return (strlen);
}

/*
** Проверяет на возможность записи строк в окне
*/

int			check_winsize(int col, int lin, t_lstr *lstr)
{
	int		c_lstr;
	int		start;
	int		finish;
	int		width;
	int		z;

	c_lstr = count_lstr(lstr);
	start = 0;
	finish = c_lstr;
	if (lin <= c_lstr)
		finish = (c_lstr - (c_lstr % lin)) / (c_lstr / lin);
	z = finish;
	width = 0;
	while (finish <= c_lstr)
	{
		width = max_strlen(lstr, start, finish) + width;
		if (width + 1 > col)
			return (0);
		if (finish == c_lstr)
			break ;
		start = finish;
		if ((finish += z) >= c_lstr)
			finish = c_lstr;
	}
	return (1);
}

int			ft_putint(int c)
{
	return (write(STDIN_FILENO, &c, 1));
}

/*
** Чистит окно
*/

void		clear_window(void)
{
	tputs(tgetstr("cl", NULL), 1, ft_putint);
}

/*
**  Меняет положение курсора
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
	while (start < finish)
	{
		if (lstr->hover_over == 1)
			ft_putstr("\033[4m");
		if (lstr->color == 1)
			ft_putstr("\033[34m");
		else if (lstr->color == 2)
			ft_putstr("\033[31m");
		if (lstr->chose == 1)
			ft_putstr("\033[1m");
		ft_putstr(lstr->name);
		ft_putstr("\033[\033[0m");
		i++;
		absolute_cursor_pos(width, i);
		lstr = lstr->next;
		start++;
	}
}

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
		write (1, "window is too small\n", 20);
		return ;
	}
	c_lstr = count_lstr(lstr);
	start = 0;
	finish = c_lstr;
	if (lin <= c_lstr)
		finish = (c_lstr - (c_lstr % lin)) / (c_lstr / lin);
	z = finish;
	width = 0;
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
