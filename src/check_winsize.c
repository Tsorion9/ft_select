/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_winsize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:07:33 by mphobos           #+#    #+#             */
/*   Updated: 2020/01/15 14:08:44 by mphobos          ###   ########.fr       */
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
