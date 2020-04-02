#include <stdio.h>
#include <string.h>

#define SIZE 25
#define nu NULL

int main(void)
{
    char word[SIZE] = {'\0'};
    char *wp, *tp;
    char t[SIZE];
    int i, x, z, len, count=5, kontroll = 1;

    printf("type the word you wan to guess max 25 chars: ");
    fgets(word, SIZE, stdin);
    for(i=0;i<strlen(word);i++)
        if(word[i]=='\n')
            word[i]='\0';

    len = strlen(word);
    printf("%d", len);
    char guess[SIZE] = { '\0'};

    wp = &word[0];
    tp = &t[0];

    for(i=0;i<len;i++)
        guess[i]='_';

    while(1){
        if(strcmp(word, guess)==0)
            goto win;
        if(count == 0)
            goto lose;
        printf("\n%d guesses left\n%s\n", count, guess);
        printf("\nguess: ");
        scanf("%s", tp);
        kontroll = 0;
        if(strlen(t)>1){
            if(strcmp(wp, tp)==0)
                goto win;
            else
                count--;
        }
        else
            for(i=0;i<len;i++){
                if(*tp == wp[i]){
                    kontroll = 1;
                    for(x=0;x<len;++x)
                        if(*tp == wp[x]){
                            guess[x] = *tp;
                            for(z=x;z<len;z++)
                                if(*tp==wp[z])
                                    guess[x] = *tp;
                        }
                }
                else if(i>=len-1)
                    if(kontroll !=1)
                        count--;
            }
    }
    win:printf("you guessed right\n");
    return 0;

    lose:printf("\nyou lost. The word was %s", word);
    return 0;

}
