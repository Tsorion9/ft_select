#include <unistd.h>
//#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <curses.h>
#include <term.h>
//#include <string.h>
#include <signal.h>

static struct termios settings;
char buf[100];
char *buffer;

void		new_term_settings(void)
{
	struct termios	new_settings;

	tcgetattr(STDIN_FILENO, &settings);
	new_settings = settings;
	new_settings.c_iflag &= ~IGNBRK;
	//new_settings.c_lflag &= ~ICANON;
	tcsetattr(0, TCSANOW, &new_settings);
}

void		return_term_settings(void)
{
	tcsetattr(0, TCSANOW, &settings);
}

void		test_tgetnum(void)
{
	int col;
	int li;

	col = tgetnum("co");
	li = tgetnum("li");
	printf("Columns = %d, lines = %d\n", col, li);
}

void		test_tgetflag(void)
{
	int flag_overstrike;
	int flag_home;
	
	flag_overstrike = tgetflag("os");
	flag_home = tgetflag("hz");
	if (flag_overstrike == 0)
		printf("При выводе символа, то, что было на той же позиции, стирается - не перегружается\n");
	else
		printf("При выводе символа, то, что было на той же позиции, не стирается - может перегружаться\n");
	if (flag_home == 0)
		printf("Терминал может печатать тильду\n");
	else
		printf("Терминал не может печатать тильду\n");
}

int			ft_putint(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

void		test_clean_screen(void)
{
	char *clean_screen;

	buffer = buf;
	clean_screen = tgetstr("cl", &buffer);
	tputs(clean_screen, 1, ft_putint);
	buffer = buf;
	bzero(buffer, 100);
}

void		test_absolute_cursor_position(void)
{
	buffer = buf;
	tputs(tgoto(tgetstr("cm", &buffer), 1, 2), 1, ft_putint);
	buffer = buf;
	bzero(buffer, 100);
	printf("\033[1;34mCursor was here\033[0m\n");
	tputs(tgoto(tgetstr("cm", &buffer), 1, 3), 1, ft_putint);
	buffer = buf;
	bzero(buffer, 100);
	printf("\033[1;34mCursor was here\033[0m\n");
}

void		resize(int a)
{
	test_clean_screen();
	//tputs(tgetstr("rc", NULL), 1, ft_putint);
	//tputs(tgetstr("cd", NULL), 1, ft_putint);
	buffer = buf;
	tputs(tgoto(tgetstr("cm", &buffer), 1, 2), 1, ft_putint);
	buffer = buf;
	bzero(buffer, 100);
	printf("\033[1;34mCursor was here\033[0m\n");
	tputs(tgoto(tgetstr("cm", &buffer), 1, 3), 1, ft_putint);
	buffer = buf;
	bzero(buffer, 100);
	printf("\033[1;34mCursor was here\033[0m\n");
}

int			main(int ac, char **av)
{
	char buf[4096];
	char *termtype;
	char room_termtype[2048];

	signal(SIGWINCH, resize);
	read(STDIN_FILENO, buf, 4096);
	new_term_settings();
	termtype = getenv("TERM");
	if (termtype == NULL || tgetent(room_termtype, termtype) != 1 || ac < 2)
	{
		printf("error\n");
		return (0);
	}
	if (strcmp(av[1], "tgetnum") == 0)
		test_tgetnum();
	else if (strcmp(av[1], "tgetflag") == 0)
		test_tgetflag();
	else if (strcmp(av[1], "full_screen") == 0)
	{
		test_clean_screen();
		read(STDIN_FILENO, buf, 4096);
	}
	else if (strcmp(av[1], "absolute_position") == 0)
	{
		test_clean_screen();
		test_absolute_cursor_position();
	}
	return_term_settings();
	return (0);
}
