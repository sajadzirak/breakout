#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define n 20
#define n_block_line 3

// function prototypes
void initialize_map();
void print_map();
void print_line(int);
void clear_screen();
int positive_move(int);
int negative_move(int);
int match();
int check_win();
void print_won();
void print_lost();
void sleep(unsigned int);


int map[20][20]; // -1 border && -2 game over &&0 nothing && 1 block && 2 ball && 3 player-left && 4 player-mid && 5 player-right
int iball = n-2, jball = 1, iplayer = n-2, jplayer = 1;
int save = 3, score = 0;

int main()
{
    int result;
    char name[25];
    FILE* fp = fopen("scores.txt", "at");
    printf("Enter your name: ");
    scanf("%s", name);
    clear_screen();
    initialize_map();
    print_map();
    result = match();
    if(result == 1) print_won();
    else print_lost();
    fprintf(fp, "%s : %d\n", name, score);
    fclose(fp);
    return 0;
}

void initialize_map()
{
    int i, j;
    for(i = 0; i < n; ++i)
    {
        map[0][i] = -1;
    }
    for(i = 1; i <= n_block_line; ++i)
    {
        map[i][0] = -1;
        for(j = 1; j < n-1; ++j)
        {
            map[i][j] = 1;
        }
        map[i][n-1] = -1;
    }
    for(i = 1; i <= n_block_line; ++i)
    {
        map[i][1] = 0;
        map[i][2] = 0;
        map[i][n-3] = 0;
        map[i][n-2] = 0;
    }
    for(; i < n-1; ++i)
    {
        map[i][0] = -1;
        for(j = 1; j < n-1; ++j)
        {
            map[i][j] = 0;
        }
        map[i][n-1] = -1;
    }
    for(j = 0; j < n; ++j)
    {
        map[n-1][j] = -2;
    }
    map[iball][jball] = 2;
    map[iplayer][jplayer] = 3;
    map[iplayer][jplayer+1] = 3;
    map[iplayer][jplayer+2] = 4;
    map[iplayer][jplayer+3] = 5;
    map[iplayer][jplayer+4] = 5;
}

void print_map()
{
    int i, j;
    for(i = 1; i < n; ++i)
    {
        print_line(i);
    }
}

void print_line(int line)
{
    int i, j;
    printf(" ");
    for(i = 0; i < n; ++i)
    {
        switch(map[line][i])
        {
        case -2:
            printf(" ");
            break;
        case -1:
            printf("|");
            break;
        case 0:
            printf(" ");
            break;
        case 1:
            printf("=");
            break;
        case 2:
            printf("*");
            break;
        case 3:
            printf("-");
            break;
        case 4:
            printf("-");
            break;
        case 5:
            printf("-");
            break;
        }
    }
    printf("\n");
}

void clear_screen()
{
    system("cls");
}

int positive_move(int dir)
{
    int hold;
    if(dir == 1)
    {
        if(map[iball-1][jball+1] == -1) return -1;  // borders
        else if(map[iball-1][jball+1] == 1)  // a block
        {
            map[iball-1][jball+1] = 0;
            return 1;
        }
        map[iball][jball] = 0;
        iball--;
        jball++;
        map[iball][jball] = 2;
        if(save == 3)
        {
            save = 0;
            map[iball+1][jball-1] = 3;
        }
        else if(save == 4)
        {
            save = 0;
            map[iball+1][jball-1] = 4;
        }
        else if(save == 5)
        {
            save = 0;
            map[iball+1][jball-1] = 5;
        }
    }
    else if(dir == -1)
    {
        if(map[iball+1][jball-1] == -1) return -1;  // border
        hold = map[iball+1][jball-1];
        map[iball][jball] = 0;
        iball++;
        jball--;
        map[iball][jball] = 2;
        if(hold == -2) return -2;  // game over
        if(hold == 3)
        {
            save = 3;
            return 3;
        }
        else if(hold == 4)
        {
            save = 4;
            return 4;
        }
        else if(hold == 5)
        {
            save = 5;
            return 5;
        }
    }
    else if(dir == 0)  // up
    {
        if(map[iball-1][jball] == -1) return -1;  // border
        else if(map[iball-1][jball] == 1)  // a block
        {
            map[iball-1][jball] = 0;
            return 1;
        }
        map[iball][jball] = 0;
        iball--;
        map[iball][jball] = 2;
        if(save == 3)
        {
            save = 0;
            map[iball+1][jball] = 3;
        }
        else if(save == 4)
        {
            save = 0;
            map[iball+1][jball] = 4;
        }
        else if(save == 5)
        {
            save = 0;
            map[iball+1][jball] = 5;
        }
    }
    return 0;
}

int negative_move(int dir)
{
    int hold;
    if(dir == 1)
    {
        if(map[iball-1][jball-1] == -1) return -1;  // border
        else if(map[iball-1][jball-1] == 1)   // a block
        {
            map[iball-1][jball-1] = 0;
            return 1;
        }
        map[iball][jball] = 0;
        iball--;
        jball--;
        map[iball][jball] = 2;
        if(save == 3)
        {
            save = 0;
            map[iball+1][jball+1] = 3;
        }
        else if(save == 4)
        {
            save = 0;
            map[iball+1][jball+1] = 4;
        }
        else if(save == 5)
        {
            save = 0;
            map[iball+1][jball+1] = 5;
        }
    }
    else if(dir == -1)
    {
        if(map[iball+1][jball+1] == -1) return -1; // border
        hold = map[iball+1][jball+1];
        map[iball][jball] = 0;
        iball++;
        jball++;
        map[iball][jball] = 2;
        if(hold == -2) return -2;   // game over
        if(hold == 3)
        {
            save = 3;
            return 3;
        }
        else if(hold == 4)
        {
            save = 4;
            return 4;
        }
        else if(hold == 5)
        {
            save = 5;
            return 5;
        }
    }
    else if(dir == 0)    // down
    {
        hold = map[iball+1][jball];
        map[iball][jball] = 0;
        iball++;
        map[iball][jball] = 2;
        if(hold == -2) return -2; // game over
        else if(hold == 3)
        {
            save = 3;
            return 3;
        }
        else if(hold == 4)
        {
            save = 4;
            return 4;
        }
        else if(hold == 5)
        {
            save = 5;
            return 5;
        }
    }
}

int match()
{
    int x, move = 1, stats, lose = 0;
    positive_move(1);
    while(lose == 0)
    {
        if(kbhit() != 0)
        {
            x = getch();
            if(x == 224)
            {
                x = getch();
                if(x == 72 && iplayer > n_block_line)  // moving up
                {
                    map[iplayer][jplayer] = 0;
                    map[iplayer][jplayer+1] = 0;
                    map[iplayer][jplayer+2] = 0;
                    map[iplayer][jplayer+3] = 0;
                    map[iplayer][jplayer+4] = 0;
                    --iplayer;
                    map[iplayer][jplayer] = 3;
                    map[iplayer][jplayer+1] = 3;
                    map[iplayer][jplayer+2] = 4;
                    map[iplayer][jplayer+3] = 5;
                    map[iplayer][jplayer+4] = 5;
                }
                if(x == 80 && iplayer < n-2)  // moving down
                {
                    map[iplayer][jplayer] = 0;
                    map[iplayer][jplayer+1] = 0;
                    map[iplayer][jplayer+2] = 0;
                    map[iplayer][jplayer+3] = 0;
                    map[iplayer][jplayer+4] = 0;
                    ++iplayer;
                    map[iplayer][jplayer] = 3;
                    map[iplayer][jplayer+1] = 3;
                    map[iplayer][jplayer+2] = 4;
                    map[iplayer][jplayer+3] = 5;
                    map[iplayer][jplayer+4] = 5;
                }
                if(x == 75 && jplayer > 1)  // moving left
                {
                    map[iplayer][jplayer+4] = 0;
                    jplayer--;
                    map[iplayer][jplayer] = 3;
                    map[iplayer][jplayer+1] = 3;
                    map[iplayer][jplayer+2] = 4;
                    map[iplayer][jplayer+3] = 5;
                    map[iplayer][jplayer+4] = 5;
                }
                else if(x == 77 && jplayer < n-6)  // moving right
                {
                    map[iplayer][jplayer] = 0;
                    jplayer++;
                    map[iplayer][jplayer] = 3;
                    map[iplayer][jplayer+1] = 3;
                    map[iplayer][jplayer+2] = 4;
                    map[iplayer][jplayer+3] = 5;
                    map[iplayer][jplayer+4] = 5;
                }
            }
        }
        switch(move)
        {
        case -1:
            stats = negative_move(0);
            if(stats == -2)
            {
                lose = 1; // game over
            }
            else if(stats == 3)
            {
                move = 2;
            }
            else if(stats == 4)
            {
                move = 0;
            }
            else if(stats == 5)
            {
                move = 1;
            }
            break;
        case 0:
            stats = positive_move(0);
            if(stats == -1) 
            {
                move = -1;
            }
            else if(stats == 1)
            {
                move = -1;
                score++;
            }
            break;
        case 1:
            stats = positive_move(1);
            if(stats == -1 && jball > 3 && iball != 1)
            {
                move = 2;
            }
            else if((stats == -1 && iball == 1))
            {
                move = 4;
            }
            else if(stats == 1)
            {
                move = 4;
                score++;
            }
            break;
        case 2:
            stats = negative_move(1);
            if(stats == -1 && jball == 1)
            {
                move = 1;
            }
            else if((stats == -1 && iball == 1))
            {
                move = 3;
            }
            else if(stats == 1)
            {
                move = 3;
                score++;
            }
            break;
        case 3:
            stats = positive_move(-1);
            if(stats == -1)
            {
                move = 4;
            }
            else if(stats == -2)
            {
                lose = 1; // game over
            }
            else if(stats == 3)
            {
                move = 2;
            }
            else if(stats == 4)
            {
                move = 0;
            }
            else if(stats == 5)
            {
                move = 1;
            }
            break;
        case 4:
            stats = stats = negative_move(-1);
            if(stats == -1)
            {
                move = 3;
            }
            else if(stats == -2)
            {
                lose = 1; // game over
            }
            else if(stats == 3)
            {
                move = 2;
            }
            else if(stats == 4)
            {
                move = 0;
            }
            else if(stats == 5)
            {
                move = 1;
            }
            break;
        }
        sleep(130);
        if(check_win() == 1)
        {
            return 1;
        }
        clear_screen();
        print_map();
    }
    if(lose == 1) return 0;
}

int check_win()
{
    int i, j;
    for(i = 1; i <= n_block_line; ++i)
    {
        for(j = 0; j < n; ++j)
        {
            if(map[i][j] == 1) return 0;
        }
    }
    return 1;
}

void print_won()
{
    clear_screen();
    printf("__     __          __          __           _\n");
    printf("\\ \\\   / /          \\ \\        / /          | |\n");
    printf(" \\ \\_/ /__  _   _   \\ \\  /\\  / /__  _ __   | |\n");
    printf("  \\   / _ \\| | | |   \\ \\/  \\/ / _ \\| '_ \\  | |\n");
    printf("   | | (_) | |_| |    \\  /\\  / (_) | | | | |_|\n");
    printf("   |_|\\___/ \\__,_|     \\/  \\/ \\___/|_| |_| (_)\n");
}

void print_lost()
{
    clear_screen();
    printf("__     __           _           _     _ \n");
    printf("\\ \\   / /          | |         | |   | |\n");
    printf(" \\ \\_/ /__  _   _  | | ___  ___| |_  | |\n");
    printf("  \\   / _ \\| | | | | |/ _ \\/ __| __| | |\n");
    printf("   | | (_) | |_| | | | (_) \\__ \\ |_  |_|\n");
    printf("   |_|\\___/ \\__,_| |_|\\___/|___/\\__| (_)\n");
}

void sleep(unsigned int mseconds)
{
	clock_t goal = mseconds + clock();
	while (goal > clock());
}
