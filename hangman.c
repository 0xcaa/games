#include <stdio.h>
#include <string.h>


int main(void)
{
    char word[20] = "apple";
    char *wp, *tp;
    char t[20];
    int i, x, z, len;
    len = strlen(word);
    char guess[len];

    wp = &word[0];
    tp = &t[0];

    for(i=0;i<len;i++)
        guess[i]='_';

    while(strcmp(wp, guess)!=0){
        printf("%s\n", guess);
        printf("\nguess: ");
        scanf("%s", &t);
        if(*t>2){
            if(strcmp(wp, guess)==0)
                break;
        }

        for(i=0;i<len;i++){
            if(*tp == wp[i]){
                for(x=0;x<len;++x){
                    if(*tp == wp[x]){
                        guess[x] = *tp;
                        for(z=x;z<len;z++)
                            if(*tp==wp[z])
                                guess[x] = *tp;
                    }

                }
            }
        }
    }

    printf("good job the word was %s\n", *wp);

    return 0;
}

