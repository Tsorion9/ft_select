#include "ft_select.h"

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

void        return_term_mode(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &settings);
}

void        exit_program(int a)
{
    (void)a;
    return_term_mode();
    exit(0);
}

void        set_signal(void)
{
    signal(SIGINT, exit_program);
}

int         main(int ac, char **av)
{
    into_term_can_mode();
    if (ac < 2)
    {
        ft_putstr("usage: ");
        ft_putstr(av[0]);
        ft_putstr(" [arg1] [arg2] ...\n");
        exit_program(0);
    }
    //printf("%s your text here %s", tgetstr("us", NULL), tgetstr("ue", NULL));
    return_term_mode();
    return (0);
}
