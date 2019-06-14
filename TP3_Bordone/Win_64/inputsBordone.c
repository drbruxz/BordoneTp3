#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <conio.h>
#include <ctype.h>
#include "inputsBordone.h"

int getChar(char* input, char message[],char eMessage[],char lowLimit, char hiLimit){
    int i=0, intentos=4, returnV = 0;
    printf("%s\n",message);
    fflush(stdin);
    *input=getch();
    *input=toupper(*input);
    while(*input<lowLimit || *input>hiLimit)
        {
        printf("%s",eMessage);
        fflush(stdin);
        *input=getch();
        *input=toupper(*input);

        i++;
        if(i>intentos){
            returnV = 1;
            break;
        }
    }
    return returnV;
}

int getAB(char* input,char message[],char eMessage[], char valueOne, char valueTwo){
    int i = 0, intentos = 4,returnV = 0;

    printf("\n%s", message);
    fflush(stdin);
    *input=getch();
    *input=toupper(*input);

    while(*input!=valueOne && *input!=valueTwo){
        printf("\n%s\n",eMessage);
        fflush(stdin);
        *input=getch();
        *input=toupper(*input);

        i++;
        if(i>intentos){
            printf("Demasiados intentos, comience de nuevo\n");
            returnV = 1;
            break;
        }
    }
    return returnV;

}

int getNum(int* input, char message[],char eMessage[],int lowLimit, int hiLimit){
    int i=0,returnV=0;
    int intentos = 4;
    printf("\n%s\n",message);
    scanf("%d", &*input);

       while(*input<lowLimit || *input>hiLimit){
                printf("\n%s\n",eMessage);
                scanf("%d",&*input);
                i++;
                if(i>intentos){
                    printf("\nDemasiados intentos, reingrese datos\n");
                    returnV = 1;
                    getch();
                    break;
                }
            }
        return returnV;

    return returnV;

}

int getCharLen(char input[], char message[], char eMessage[], int lowLimit, int hiLimit){
    int intentos=0,returnV=0;
    printf("\n%s\n",message);
    scanf("%s",&*input);
    while((strlen(&*input))> hiLimit || (strlen(&*input))<lowLimit){
        printf("\n%s",eMessage);
        scanf("%s",&*input);
        intentos ++;
        if(intentos>4){
            returnV = 1;
            printf("\nDemasiados intentos, vuelva a intentarlo\n");
            break;
        }
    }


    return returnV;


}

