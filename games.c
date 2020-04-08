#include <stdio.h>

#include "hangman.h"
#include "tictactoe.h"


int main(void)
{
    int pick;
    while(1){
        printf("\n\n1 for hangman 2 for ticktactoe: ");
        scanf("%d", &pick);
        
        if(pick ==1){
            printf("\nStarting hangman...\n");
            hangman();
        }
        else if(pick ==2){
            printf("\nStarting tictacto...\n");
            tictactoe();
        }
        else{
            printf("exiting..");
            break;
        }
    }
    return 0;

}

