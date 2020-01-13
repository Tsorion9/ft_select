/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:05:21 by mphobos           #+#    #+#             */
/*   Updated: 2020/01/13 14:53:19 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		free_lstr(t_lstr *lstr)
{
	t_lstr	*next_lstr;
	while (lstr->last == 0)
	{
		next_lstr = lstr->next;
		free(lstr->name);
		free(lstr);
		lstr = next_lstr;
	}
	free(lstr->name);
	free(lstr);
}
