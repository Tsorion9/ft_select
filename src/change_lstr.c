/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_lstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:09:58 by mphobos           #+#    #+#             */
/*   Updated: 2020/01/15 14:23:21 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Меняет положение курсора, если пользователь нажал "↓"
** или "↑"
*/

void        change_hover_over(t_lstr *lstr, int flag)
{
    while (lstr->hover_over != 1)
        lstr = lstr->next;
    lstr->hover_over = 0;
    if (flag == 0)
        lstr->next->hover_over = 1;
    else if (flag == 1)
        lstr->prev->hover_over = 1;
}

/*
** Фиксирует выбор, если пользователь нажал space
*/

void        change_chose(t_lstr *lstr)
{
    while (lstr->hover_over != 1)
        lstr = lstr->next;
    if (lstr->chose == 1)
        lstr->chose = 0;
    else
        lstr->chose = 1;
    lstr->hover_over = 0;
    lstr->next->hover_over = 1;
}

/*
** Меняет положение курсора, если пользователь нажал "→"
*/

void        change_chose_right(t_lstr *lstr, int lin)
{
    int     column;
    int     c_lstr;
    int     i;
    t_lstr  *tmp;

    c_lstr = count_lstr(lstr);
    column = c_lstr;
    if (lin <= c_lstr)
        column = (c_lstr - (c_lstr % lin)) / (c_lstr / lin);
    while (lstr->hover_over != 1)
        lstr = lstr->next;
    tmp = lstr;
    i = 0;
    while (i < column)
    {
        if (lstr->last == 1)
            return ;
        lstr = lstr->next;
        i++;
    }
    tmp->hover_over = 0;
    lstr->hover_over = 1;
}

/*
** Меняет положение курсора, если пользователь нажал "←"
*/

void        change_chose_left(t_lstr *lstr, int lin)
{
    int     column;
    int     c_lstr;
    int     i;
    t_lstr  *tmp;

    c_lstr = count_lstr(lstr);
    column = c_lstr;
    if (lin <= c_lstr)
        column = (c_lstr - (c_lstr % lin)) / (c_lstr / lin);
    while (lstr->hover_over != 1)
        lstr = lstr->next;
    tmp = lstr;
    i = 0;
    while (i < column)
    {
        if (lstr->prev->last == 1)
            return ;
        lstr = lstr->prev;
        i++;
    }
    tmp->hover_over = 0;
    lstr->hover_over = 1;
}
