#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void print_progress(int percent)
{
    // Spinning animation
    static int spin_index = 0;
    static char* spinning = "-\\|/";

    // Total bar, soild, void length
    int bar_len = 50;
    int bar_soild = percent >> 1;
    int bar_void = bar_len - bar_soild;
    char* bar = malloc(bar_len + 1);

    //Fill the progress
    memset(bar, '=', bar_soild);
    memset(bar + bar_soild, ' ', bar_void);
    bar[bar_len] = 0;

    printf("Loading: [%*s] %3d%% %c\n",
        bar_len, bar,
        percent,
        percent == 100 ? ' ' : spinning[spin_index]);
    fflush(stdout);

    ++spin_index;
    if(spin_index >= strlen(spinning))
        spin_index = 0;

    free(bar);
}

int main()
{
    int rnd = 0;
    int percent = 0;
    int step[] = {0, 0, 0, 0, 1, 1, 2, 3, 5, 8, 13};

    srand(time(NULL));

    printf("Loading animation\n");
    do
    {
        percent += step[rand() % (sizeof(step) / sizeof(int))];
        if(percent > 100)
            percent = 100;

        print_progress(percent);

        // 1 sec = 1 000 000
        usleep(100000);
    }
    while(percent < 100);

    printf("\nFinished\n");

    return 0;
}