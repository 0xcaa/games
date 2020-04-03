#include <stdio.h>

#define SIZE 3

int printboard(char board[SIZE][SIZE]);

int main(void)
{
    char board[SIZE][SIZE] = { {'_','_','_'},
                               {'_','_','_'},
                               {'_','_','_'} };

    char *bp = &board[0][0];

    board[0][0] = 'o';
    board[1][0] = 'x';
    
    printboard(board); 

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

