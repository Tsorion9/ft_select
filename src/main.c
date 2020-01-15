/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 13:10:07 by mphobos           #+#    #+#             */
/*   Updated: 2020/01/13 16:33:19 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
** Настраивает терминал (неканонический ввод)
*/

void        into_term_can_mode(void)
{
    struct termios  new_settings;

    tcgetattr(STDIN_FILENO, &settings);
    new_settings = settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
}

/*
** Возвращает настройки терминала (канонический ввод)
*/

void        return_term_mode(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &settings);
}

/*
** Выход из программы
*/

void        exit_program(int a)
{
    (void)a;
    return_term_mode();
    exit(0);
}

/*
** Настройка сигналов и внесение терминала в БД termcap
*/

void        set_signal(void)
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
}

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

void        change_chose(t_lstr *lstr)
{
    while (lstr->hover_over != 1)
        lstr = lstr->next;
    if (lstr->chose == 1)
        lstr->chose = 0;
    else
        lstr->chose = 1;
}

void        change_chose_left_right(t_lstr *lstr, int lin, int flag)
{
    int     column;
    int     c_lstr;
    int     i;
    t_lstr  *tmp;

    c_lstr = count_lstr(lstr);
    printf("%d", c_lstr);
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
        if (flag == 1)
        {
            lstr = lstr->prev->prev;
            if (lstr->next->last == 1)
                return ;
        }
        i++;
    }
    tmp->hover_over = 0;
    lstr->hover_over = 1;
}

void        execute_command(t_lstr *lstr)
{
    char    c;

    while(21)
    {
        read(STDERR_FILENO, &c, 1);
        printf("%d\n", c);
        if (c == 66)
        {
            change_hover_over(lstr, 0);
            display_lstr(tgetnum("co"), tgetnum("li"), lstr);
        }
        else if (c == 65)
        {
            change_hover_over(lstr, 1);
            display_lstr(tgetnum("co"), tgetnum("li"), lstr);
        }
        else if (c == 32)
        {
            change_chose(lstr);
            display_lstr(tgetnum("co"), tgetnum("li"), lstr);
        }
        else if (c == 67)
        {
            change_chose_left_right(lstr, tgetnum("li"), 0);
            display_lstr(tgetnum("co"), tgetnum("li"), lstr);
        }
        else if (c == 68)
        {
            change_chose_left_right(lstr, tgetnum("li"), 1);
            display_lstr(tgetnum("co"), tgetnum("li"), lstr); 
        }
    }
}

int         main(int ac, char **av)
{
    t_lstr   *lstr;

    into_term_can_mode();
    set_signal();
    if (ac < 2)
    {
        ft_putstr("usage: ");
        ft_putstr(av[0]);
        ft_putstr(" [arg1] [arg2] ...\n");
        exit_program(0);
    }
    lstr = init_lstr(av + 1);
    display_lstr(tgetnum("co"), tgetnum("li"), lstr);
    execute_command(lstr);
    free_lstr(lstr);
    return_term_mode();
    return (0);
}
