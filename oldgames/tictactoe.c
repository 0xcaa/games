#include <stdio.h>
#include <string.h>


#define SIZE 4

int printboard(char board[SIZE][SIZE]);
int getinput(int *i, int *j);
int usage(void);
int ai(char board[SIZE][SIZE], int *a, int *b);

int tictactoe(void)
{
    char board[SIZE][SIZE] = { {'_','_','_'},
                               {'_','_','_'},
                               {'_','_','_'} };

    int i=0, j=0, a=0, b=0;

    //board[i][j] j controlls x i controlls y
    
    usage(); 
    printboard(board);

    while(1){//while loop should check if there is 3 in a row
        getinput(&i, &j);
        board[j][i] = 'o';
        a = 0;
        b = 0;
        if(ai(board, &a, &b)!=0)
            break;
        //ai will look at the board and send put the move in a and b
        board[a][b] = 'x';
        printboard(board);


    }
    printf("game over!");

    return 0;
}

int ai(char board[SIZE][SIZE], int *a, int *b)
{
    //ai needs to iterate over the board to get to players positions
    int i, x, count=0;
    for(i=0;i<3;i++){
        for(x=0;x<3;x++){
            if(board[i][x] =='o'&&board[i][x+1] =='o'){
                *a = x+2;
                *b= i;
                return 0;
            }
            else if(board[i][x] =='o'&&board[i][x+2]=='o'){
                *a = x+1;
                *b= i;
                return 0;
            }
        }
    }
    for(x=0;x<3;x++){
        for(i=0;i<3;i++){
            if(board[i][x] =='o'&&board[i][x+1] =='o'){
                *a = x;
                *b= i+2;
                return 0;
            }
            else if(board[i][x] =='o'&&board[i][x+2]=='o'){
                *a = x;
                *b= i+1;
                return 0;
            }
        }
    }

    for(i=0;i<3;i++)
        for(x=0;x<3;x++){
            if(board[i][x]=='_'){
                *a = x;
                *b = i;
                return 0;
            }
            else{
                count++;
                if(count==9)
                    return 1;
            }
    }

    return 0;
}



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



int printboard(char board[SIZE][SIZE])
{
    int i, j;

    printf("\n");

    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++)
            printf("%c  ", *(*(board + i) + j));

        printf("\n");
    }
    printf("------------------------------------\n");

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
