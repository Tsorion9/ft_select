/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 13:10:07 by mphobos           #+#    #+#             */
/*   Updated: 2020/01/15 15:04:42 by mphobos          ###   ########.fr       */
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

void        signal_processing(int a)
{
    if (a == SIGTSTP)
    {
        return_term_mode();
        signal(SIGTSTP, SIG_DFL);
	    ioctl(STDERR_FILENO, TIOCSTI, "\032");
    }
    else if (a == SIGCONT)
    {
        into_term_can_mode();
	    set_signal();
    }
    else if (a == SIGWINCH)
    {
        
    }
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
    signal(SIGTSTP, signal_processing);
    signal(SIGCONT, signal_processing);
    signal(SIGWINCH, signal_processing);
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

void        execute_command(t_lstr *lstr)
{
    char    c;

    while(21)
    {
        read(STDERR_FILENO, &c, 1);
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
            change_chose_right(lstr, tgetnum("li"));
            display_lstr(tgetnum("co"), tgetnum("li"), lstr);
        }
        else if (c == 68)
        {
            change_chose_left(lstr, tgetnum("li"));
            display_lstr(tgetnum("co"), tgetnum("li"), lstr);
        }
        else if (c == 10)
        {
            clear_window();
            return_term_mode();
            print_result(lstr);
            exit(0);
        }
        /*else if (c == 27)
        {
            clear_window();
            return_term_mode();
            exit(0);
        }*/
    }
}

int         main(int ac, char **av)
{
    t_lstr   *lstr;

    set_signal();
    into_term_can_mode();
    if (ac < 2)
    {
        ft_putstr_fd("usage: ", STDERR_FILENO);
        ft_putstr(av[0]);
        ft_putstr_fd(" [arg1] [arg2] ...\n", STDERR_FILENO);
        return_term_mode();
        return (1);
    }
    lstr = init_lstr(av + 1);
    display_lstr(tgetnum("co"), tgetnum("li"), lstr);
    execute_command(lstr);
    free_lstr(lstr);
    return_term_mode();
    return (0);
}
