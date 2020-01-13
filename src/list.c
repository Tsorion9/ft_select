/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 13:10:01 by mphobos           #+#    #+#             */
/*   Updated: 2020/01/13 14:55:07 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Создает новую структуру
*/

t_lstr		*create_lstr(char *name)
{
	t_lstr		*new_lstr;
	struct stat	str_stat;


	if (!(new_lstr = (t_lstr*)malloc(sizeof(t_lstr))))
		exit_program(0);
	new_lstr->name = ft_strdup(name);
	new_lstr->color = 0;
	if (stat(name, &str_stat) == 0)
	{
		if (S_ISDIR(str_stat.st_mode))
			new_lstr->color = 1;
		else if (access(name, X_OK) == 0)
			new_lstr->color = 2;
		else
			new_lstr->color = 0;
	}
	new_lstr->hover_over = 0;
	new_lstr->chose = 0;
	new_lstr->last = 0;
	new_lstr->prev = NULL;
	new_lstr->next = NULL;
	return (new_lstr);
}

/*
** Добавляет в конец списка новую структуру
*/

void		add_new_lstr(t_lstr *lstr, char *name)
{
	t_lstr	*new_lstr;

	new_lstr = create_lstr(name);
	while (lstr->next != NULL)
		lstr = lstr->next;
	lstr->next = new_lstr;
	new_lstr->prev = lstr;
}

/*
** Инициализирует список
*/

t_lstr		*init_lstr(char **av)
{
	t_lstr	*lstr;
	t_lstr	*head;

	lstr = create_lstr(*av);
	head = lstr;
	av++;
	while (*av != NULL)
	{
		add_new_lstr(lstr, *av);
		av++;
	}
	while (lstr->next != NULL)
        lstr = lstr->next;
	lstr->last = 1;
	lstr->next = head;
	return (head);
}
