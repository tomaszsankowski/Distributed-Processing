//
// Created by tomasz on 07.05.24.
//
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
    int x = 0;
    puts("Otwieram");
    const int f = open("test", O_RDONLY);
    read(f, &x, sizeof(x));
    printf("Odebralem %d i koncze", x);
    close(f);
}
