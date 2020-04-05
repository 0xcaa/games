#include <stdio.h>
#include <string.h>

#define SIZE 3
#define SIZE_B 4

int printboard(char board[SIZE][SIZE]);
int getinput(int *i, int *j);
int usage(void);

int main(void)
{
    char board[SIZE][SIZE] = { {'_','_','_'},
                               {'_','_','_'},
                               {'_','_','_'} };

    int i, j;
    char *bp = &board[0][0];

    //board[0][0] = 'o';
    //board[1][0] = 'x';

    usage(); 
    getinput(&i, &j);
    printf("%d %d", i, j);

    return 0;
}

int getinput(int *i, int *j)
{
    //int i, j;
    printf("type: ");
    scanf("%d", i);
    scanf("%d", j);


    if(*i<0||*i>2)
        usage();
    if(*j<0||*j>2)
        usage();

    return 0;
}

int usage(void)
{
    int i, j;

    printf("first number controls the x axis\nsecound number control the y axis\n");
    char board[SIZE_B][SIZE_B] = { {'x','0','1','2'},
                                   {'0','_','_','_'},
                                   {'1','_','_','_'},
                                   {'2','_','_','_'} };
    for(i=0;i<SIZE_B;i++){
        for(j=0;j<SIZE_B;j++)
            printf("%c  ", *(*(board + i) + j));

        printf("\n");
    }

    return 0;
}

int printboard(char board[SIZE][SIZE])
{
    int i, j;

    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++)
            printf("%c  ", *(*(board + i) + j));

        printf("\n");
    }

    return 0;
}

