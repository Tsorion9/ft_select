/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 13:10:07 by mphobos           #+#    #+#             */
/*   Updated: 2020/01/15 18:38:36 by mphobos          ###   ########.fr       */
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
    tputs(tgetstr("ti", NULL), 1, ft_putint);
	tputs(tgetstr("vi", NULL), 1, ft_putint);
}

/*
** Возвращает настройки терминала (канонический ввод)
*/

void        return_term_mode(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &settings);
	tputs(tgetstr("ve", NULL), 1, ft_putint);
	tputs(tgetstr("te", NULL), 1, ft_putint);
}

/*
** Выход из программы
*/

void        exit_program(int a)
{
    (void)a;
    clear_window();
    return_term_mode();
    exit(0);
}

/*
** Печать результата
*/

void        print_result(t_lstr *lstr)
{
    while (lstr->last != 1)
    {
        if (lstr->chose == 1)
        {
            ft_putstr(lstr->name);
            write (1, " ", 1);
        }
        lstr = lstr->next;
    }
    if (lstr->chose == 1)
    {
        ft_putstr(lstr->name);
        write (1, " ", 1);
    }
}

int         main(int ac, char **av)
{
    if (ac < 2)
    {
        ft_putstr("usage: ");
        ft_putstr(av[0]);
        ft_putstr(" [arg1] [arg2] ...\n");
        return (0);
    }
    set_signal();
    into_term_can_mode();
    lstr = init_lstr(av + 1);
    display_lstr(ret_winsize(0), ret_winsize(1), lstr);
    execute_command(lstr);
    //free_lstr(lstr);
    //return_term_mode();
    return (0);
}
