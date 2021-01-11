//
// Berkay Mengunogul 15011934
//
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int len;
} String;
int charAt(String *s, int index){
    return 0;
}
String *concat(String *s1, String *s2){
    return 0;
}
unsigned int strSearch(String *s1, String *s2){
    return 0;
}
unsigned int findScore(String *s1){
    return 0;
}
int main(void){
    FILE *fPtr;
    if ((fPtr = fopen("input.txt", "r")) !=NULL){
        char input[50];
        fscanf(fPtr, "%49[^\n]", input);
        sscanf("%s", input);
        fclose(fPtr);
        return 0;
        int numOfWords = 0, index;
        long int lenInput = 0;
        while (!((strcmp(input,"exit") == 0 )|| (strcmp(input,"quit") == 0))){
            if (strcmp(input, "stat") == 0){
                printf("The number of words: %d\n", numOfWords);
                printf("The number of alphabetic letters: %lu\n", lenInput);
            }else{
                numOfWords = 0;
                lenInput = 0;
                char *token = strtok(input, " ");
                while(token != NULL){
                    for(index = 0; index<strlen(token); index++){
                        if(isalpha(token[index])){
                            lenInput++;
                        }
                    }
                    numOfWords++;
                    token = strtok(NULL, " ");
                }
            }
            scanf(" %49[^\n]", input);
        }
    }else{
        printf("error");
    }
    return 0;
}
