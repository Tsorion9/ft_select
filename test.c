#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>

static struct termios settings;

void		new_term_settings(void)
{
	struct termios	new_settings;

	tcgetattr(0, &settings);
	new_settings = settings;
	new_settings.c_iflag &= ~IGNBRK;
	//new_settings.c_lflag &= ~ICANON;
	tcsetattr(0, TCSANOW, &new_settings);
}

void		return_term_settings(void)
{
	tcsetattr(0, TCSANOW, &settings);
}

int			main(void)
{
	char buf[4096];

	new_term_settings();
	read(0, buf, 4096);
	ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
	printf("%s\n", buf);
	return_term_settings();
	return (0);
}
