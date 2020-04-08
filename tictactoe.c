#include <stdio.h>
#include <string.h>

#define SIZE 4

int printboard(char board[SIZE][SIZE]);
int getinput(int *i, int *j);
int usage(void);
//int ai(char board[SIZE][SIZE], int *a, int *b);

int tictactoe(void)
{
    char board[SIZE][SIZE] = { {'_','_','_'},
                               {'_','_','_'},
                               {'_','_','_'} };

    int i=0, j=0, a=0, b=0;
    //char *bp = &board[0][0];

    //board[i][j] j controlls x i controlls y
    
    //board[2][2] = 'o';
    //board[1][0] = 'x';
    
    usage(); 
    printboard(board);

    while(1){//while loop should check if there is 3 in a row
        getinput(&i, &j);
        board[j][i] = 'o';
        //ai(board, &a, &b);
        //ai will look at the board and send put the move in a and b
        //board[a][b] = 'x';
        printboard(board);


    }

    return 0;
}

//int ai(char board[SIZE][SIZE], int *a, int *b)
//{
//ai needs to iterate over the board to get to players positions
//
//}



int getinput(int *i, int *j)
{
    printf("Your move: ");
    scanf("%d", i);
    scanf("%d", j);


    if(*i<0||*i>2)
        usage();
    else if(*j<0||*j>2)
        usage();

    return 0;
}

int usage(void)
{
    printf("\nFirst number controls the x axis\nSecound number control the y axis\n");
    char board[SIZE][SIZE] = { {'x','0','1','2'},
                               {'0','_','_','_'},
                               {'1','_','_','_'},
                               {'2','_','_','_'} };

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
    printf("------------------------------------\n");

    return 0;
}
