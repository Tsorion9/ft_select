/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 12:43:41 by mphobos           #+#    #+#             */
/*   Updated: 2020/01/16 12:43:42 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			ft_putint(int c)
{
	return (write(STDERR_FILENO, &c, 1));
}

/*
** Чистит окно
*/

void		clear_window(void)
{
	tputs(tgetstr("cl", NULL), 1, ft_putint);
}

/*
** Возвращает размер окна
*/

int			ret_winsize(int a)
{
	struct winsize	w;

	ioctl(STDERR_FILENO, TIOCGWINSZ, &w);
	if (a == 0)
		return (w.ws_col);
	return (w.ws_row);
}
