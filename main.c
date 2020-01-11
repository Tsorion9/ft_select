#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char **argv)
{
  struct termios savetty;
  struct termios tty;
  char ch;
  int x, y;

  printf ("Enter start position (x y): ");
  scanf ("%d %d", &x, &y);

  if ( !isatty(0) ) {
    fprintf (stderr, "stdin not terminal\n");
    return (0);
    };

  tcgetattr (0, &tty);
  savetty = tty;
  tty.c_lflag &= ~(ICANON|ECHO|ISIG);
  tty.c_cc[VMIN] = 1;
  tcsetattr (0, TCSANOW, &tty);

  printf ("%c[2J", 27);
  fflush (stdout);

  printf ("%c[%d;%dH", 27, y, x);
  fflush (stdout);

  for(;;)
    {
    read (0, &ch, 1);
    if (ch == 'q')
      break;
    switch (ch)
      {
      case 'u':
        printf ("%c[1A", 27);
        fflush (stdout);
        break;
      case 'd':
        printf ("%c[1B", 27);
        fflush (stdout);
        break;
      case 'r':
        printf ("%c[1C", 27);
        fflush (stdout);
        break;
      case 'l':
        printf ("%c[1D", 27);
        fflush (stdout);
        break;
      };
    };

  tcsetattr (0, TCSAFLUSH, &savetty);
  return (0);
  }