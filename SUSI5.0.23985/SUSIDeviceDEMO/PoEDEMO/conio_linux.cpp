#include "conio_linux.h"
 
void terminal_lnbuf(int yn) {
   struct termios oldt, newt;
   tcgetattr(0, &oldt);
   newt = oldt;
   if (!yn) newt.c_lflag &= ~ICANON;
   else newt.c_lflag |= ICANON;
   tcsetattr(0, TCSANOW, &newt);
}
 
void terminal_echo(int yn) {
   struct termios oldt, newt;
   tcgetattr(0, &oldt);
   newt = oldt;
   if (!yn) newt.c_lflag &= ~ECHO;
   else newt.c_lflag |= ECHO;
   tcsetattr(0, TCSANOW, &newt);
}
 
void gotoxy(int x, int y) { printf("\x1B[%d;%df", y, x); }
 
void clrscr() { printf("\x1B[2J\x1B[0;0f"); }
 
int getch() {
   register int ch;
   terminal_lnbuf(0);
   terminal_echo(0);
   ch = getchar();
   terminal_lnbuf(1);
   terminal_echo(1);
   return ch;
}
 
int getche() {
   register int ch;
   terminal_lnbuf(0);
   ch = getchar();
   terminal_lnbuf(1);
   return ch;
}
 
int kbhit() {
   register int ret;
   fd_set fds;
   terminal_lnbuf(0);
   terminal_echo(0);
   struct timeval tv;
   tv.tv_sec = 0;
   tv.tv_usec = 0;
   FD_ZERO(&fds);
   FD_SET(0, &fds);
   select(1, &fds, 0, 0, &tv);
   ret = FD_ISSET(0, &fds);
   terminal_lnbuf(1);
   terminal_echo(1);
   return ret;
}
