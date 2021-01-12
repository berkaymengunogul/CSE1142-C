//
// Berkay Mengunogul 15011934
//


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
    char data[50];
    unsigned int len;
} String;

int charAt(String *s, int index){
    if ((index >= 0)&&(index < s->len)){
        return toupper(s->data[index]);
    }
    return -1;
}

String *concat(String *s1, String *s2){
    String *concatResult = malloc(sizeof(String));
    unsigned int resultIndex = 0, stringIndex;
    // pass first string to result.data;
    for(stringIndex = 0; stringIndex < (*s1).len; stringIndex++){
        (*concatResult).data[stringIndex] = s1->data[stringIndex];
        resultIndex++;
        //printf("%c\n", s1->data[stringIndex]);
    }
    (*concatResult).data[resultIndex] = ' ';
    for(stringIndex = 0; stringIndex < (s2->len); stringIndex++){
        resultIndex++;
        (*concatResult).data[resultIndex] = s2->data[stringIndex];
    }
    (*concatResult).len = resultIndex;
    return concatResult;
}

unsigned int strSearch(String *s1, String *s2){
    unsigned int result = 0, indexFirst, indexSecond;
    char *tokenFirstString = strtok(s1->data, " ");
    while (tokenFirstString != NULL){
        for(indexFirst = 0; indexFirst < strlen(tokenFirstString); indexFirst++) {
            for (indexSecond = 0; indexSecond < s2->len; indexSecond++) {
                if (tokenFirstString[indexFirst] == s2->data[indexSecond]) {
                    result++;
                }
            }
        }if(result == strlen(tokenFirstString)){
            return result;
        }
        result = 0;
        tokenFirstString = strtok(NULL, " ");
    }
    return result;
}
unsigned int findScore(String *s1){
    char onePoint[] = "AEIOULNRST";
    char twoPoint[] = "DG";
    char threePoint[] = "BCMP";
    char fourPoint[] = "FHVWY";
    char fivePoint = 'K';
    char eightPoint[] = "JX";
    char tenPoint[] = "QZ";

    int score = 0, indexString = 0, indexPoints = 0;
    for(indexString = 0; indexString < s1->len; indexString++){
        // scan 1 pts
        for(indexPoints = 0; indexPoints < strlen(onePoint); indexPoints++){
            if(onePoint[indexPoints] == toupper(s1->data[indexString])){
                score++;
            }
        }
        // scan 2 pts
        for(indexPoints = 0; indexPoints < strlen(twoPoint); indexPoints++){
            if(twoPoint[indexPoints] == toupper(s1->data[indexString])){
                score += 2;
            }
        }
        // scan 3 pts
        for(indexPoints = 0; indexPoints < strlen(threePoint); indexPoints++){
            if(threePoint[indexPoints] == toupper(s1->data[indexString])){
                score += 3;
            }
        }
        // scan 4 pts
        for(indexPoints = 0; indexPoints < strlen(fourPoint); indexPoints++){
            if(fourPoint[indexPoints] == toupper(s1->data[indexString])){
                score += 4;
            }
        }
        // check 5 pts
        if(fivePoint == toupper(s1->data[indexString])){
            score += 5;
        }
        // scan 8 pts
        for(indexPoints = 0; indexPoints < strlen(eightPoint); indexPoints++){
            if(eightPoint[indexPoints] == toupper(s1->data[indexString])){
                score += 8;
            }
        }
        // scan 10 pts
        for(indexPoints = 0; indexPoints < strlen(tenPoint); indexPoints++){
            if(tenPoint[indexPoints] == toupper(s1->data[indexString])){
                score += 10;
            }
        }
    }

    return score;
}
int main(void){
    FILE *fPtr;
    // file opened here, if succeed operations will continue
    if ((fPtr = fopen("input.txt", "r")) !=NULL){
        char input[100];
        char *tokenSentence, *tokenInstructions;
        int numOfWords = 0, index;
        long int lenInput = 0;

        while (!feof(fPtr)) {
            fscanf(fPtr, "%[^\n]\n", input);

            tokenSentence = strtok(input, ":"); // Sentence is read till ":"
            tokenInstructions = strtok(NULL, ","); // Part after the ":" stored here

            // String node created here and values assigned to it.
            String *node = malloc(sizeof(String));
            strcpy((*node).data, tokenSentence);
            (*node).len = strlen(tokenSentence);

            if (strcmp(tokenInstructions, "1") == 0){
                int result = charAt(node, atoi(strtok(NULL, ",")));
                printf("%c\n", result);
            }else if(strcmp(tokenInstructions, "2") == 0){
                String *string1 = malloc(sizeof(String));
                strcpy((*string1).data, strtok(NULL, ","));
                (*string1).len = strlen(string1->data);
                printf("%s\n", (*concat(node, string1)).data);
            }else if(strcmp(tokenInstructions, "3") == 0){
                String *string1 = malloc(sizeof(String));
                strcpy((*string1).data, strtok(NULL, ","));
                (*string1).len = strlen(string1->data);
                printf("%d\n", strSearch(node, string1));
            }//TODO finish state and exit part
            else if(strcmp(tokenInstructions, "4") == 0){
                printf("%d\n", findScore(node));
            }else if (strcmp(input, "stat") == 0){
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
//            free(node);
//            free(string1);
        }

//        while (tokenInstructions != NULL){
//            printf("%s\n", tokenInstructions);
//            tokenInstructions = strtok(NULL, ",");
//        }

        fclose(fPtr);
    }else{
        printf("error");
    }

    return 0;
}
