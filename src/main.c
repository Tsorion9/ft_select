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

int         main(int ac, char **av)
{
    t_lstr   *lstr;
    char    buf[10];

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
    read(0, buf, 1);
    clear_window();
    free_lstr(lstr);
    return_term_mode();
    return (0);
}
