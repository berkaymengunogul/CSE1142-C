//
// Berkay Mengunogul 150119934
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
    if ((index >= 0)&&(index < s->len)){ // if index less than or equal to 0 and less length of word
        return toupper(s->data[index]);  // this function will return the indexed char as uppercase
    }
    return -1;                          // otherwise, it will return -1
}

String *concat(String *s1, String *s2){
    String *concatResult = malloc(sizeof(String));   // String size memory allocated to use outside of function for result value
    unsigned int resultIndex = 0, stringIndex;       // One by one all the chars in string one written to result
    // pass first string to result.data;             // resultIndex tracks the position of result
    for(stringIndex = 0; stringIndex < (*s1).len; stringIndex++){
        (*concatResult).data[stringIndex] = s1->data[stringIndex];
        resultIndex++;
    }
    (*concatResult).data[resultIndex] = ' ';        // After copying the first string a space added here and second string copied
    for(stringIndex = 0; stringIndex < (s2->len); stringIndex++){
        resultIndex++;
        (*concatResult).data[resultIndex] = s2->data[stringIndex];
    }
    (*concatResult).len = resultIndex;
    return concatResult;
}

unsigned int strSearch(String *s1, String *s2){
    unsigned int result = 0, indexFirst, indexSecond;
    char *tokenFirstString = strtok(s1->data, " "); // String one divided to its words as token
    while (tokenFirstString != NULL){
        for(indexFirst = 0; indexFirst < strlen(tokenFirstString); indexFirst++) { //for each word
            for (indexSecond = 0; indexSecond < s2->len; indexSecond++) {          //each char of the searched word
                if (tokenFirstString[indexFirst] == s2->data[indexSecond]) {       // compared and recorded in int result.
                    result++;
                }
            }
        }if(result == strlen(tokenFirstString)){   // if len of word and number of matched words(int result) equal
            return result;                          // it will return as result.
        }
        result = 0;                                 // result is declared as 0 after each word
        tokenFirstString = strtok(NULL, " ");
    }
    return result;
}
unsigned int findScore(String *s1){ // Chars are stored in array by their values.
    char onePoint[] = "AEIOULNRST"; // Each char of the given string the is compared with all the
    char twoPoint[] = "DG";         // chars in the arrays, if any char matches, value of the string will be updated
    char threePoint[] = "BCMP";     // and recorded in int score variable
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
int main(int argc, char *argv[]){
    FILE *inputFilePtr;
    FILE *outputFilePtr;
    // input file opened here, if succeed operations will continue
    if ((inputFilePtr = fopen(argv[1], "r")) !=NULL){
        // output file created here, if succeed operations will continue
        if((outputFilePtr = fopen(argv[2], "w")) !=NULL){
            char input[100];
            char *tokenSentence, *tokenInstructions;
            int numOfWords = 0, index;
            long int lenInput = 0;

            while (!feof(inputFilePtr)) {
                fscanf(inputFilePtr, "%[^\n]\n", input); //each line of the input file stored in input


                tokenSentence = strtok(input, ":"); // Sentence is read till ":"
                tokenInstructions = strtok(NULL, ","); // Part after the ":" stored here

                // String node created here and values assigned to it.
                String *node = malloc(sizeof(String));
                strcpy((*node).data, tokenSentence); // tokenized sentence stored
                (*node).len = strlen(tokenSentence); // and its length stored

                String *string1 = malloc(sizeof(String)); // Another String type created for instruction strings

                if (strcmp(input, "stat") == 0) {
                    // when user gives "stat" as input, related info will be written to output file here
                    fprintf(outputFilePtr,"The number of words: %d\n", numOfWords);
                    fprintf(outputFilePtr,"The number of alphabetic letters: %lu\n", lenInput);
                }else if((strcmp(input, "exit") == 0) || (strcmp(input, "quit") == 0)){
                    // if input is either exit or quit, program will stop
                    fprintf(outputFilePtr,"Program ends. Bye\n");
                    return 0;
                }else if (strcmp(tokenInstructions, "1") == 0){
                    // if user chose 1st function,
                    int result = charAt(node, atoi(strtok(NULL, ",")));
                    if(result == -1){ // with the given index changed to int by using atoi() func charAt func called
                        fprintf(outputFilePtr, "%d\n", result);
                    }else {  // depending on the return, corresponding result will be written to output file
                        fprintf(outputFilePtr, "%c\n", result);
                    }
                }else if(strcmp(tokenInstructions, "2") == 0){
                    // if user chose 2nd function, string1 variable updated from the inputs
                    strcpy((*string1).data, strtok(NULL, ",")); // sentence updated here
                    (*string1).len = strlen(string1->data); // length updated here
                    fprintf(outputFilePtr,"%s\n", (*concat(node, string1)).data); // result of concat function written to output file here
                }else if(strcmp(tokenInstructions, "3") == 0){
                    // if user chose 3rd function, string1 variable updated from the inputs
                    strcpy((*string1).data, strtok(NULL, ",")); // sentence updated here
                    (*string1).len = strlen(string1->data);  // length updated here
                    fprintf(outputFilePtr,"%d\n", strSearch(node, string1));  // result of strSearch function written to output file here
                }else if(strcmp(tokenInstructions, "4") == 0){
                    // if user chose 4th function, result of findScore function written to output file here
                    fprintf(outputFilePtr,"%d\n", findScore(node));
                }
                // while reading each line of input file, numOfWords and lenInput variables updated every loop
                // first given sentence is tokenized to its words in tokenState
                // for each word, each letter checked and lenInput updated if it is alphabetical char
                // then numOfWords updated while scanning tokenized words
                char *tokenState = strtok(tokenSentence, " ");
                while(tokenState != NULL){
                    for(index = 0; index<strlen(tokenState); index++){
                        if(isalpha(tokenState[index])){
                            lenInput++;
                        }
                    }
                    numOfWords++;
                    tokenState = strtok(NULL, " "); // getting the next word here
                }
                // instruction parts of the inputs checked here, with the same principle above
                tokenState = strtok(string1->data, " ");
                while(tokenState != NULL){
                    for(index = 0; index<strlen(tokenState); index++){
                        if(isalpha(tokenState[index])){
                            lenInput++;
                        }
                    }
                    numOfWords++;
                    tokenState = strtok(NULL, ",");
                }
                free(node); // Allocated memories freed here
                free(string1);
            }
            fclose(inputFilePtr); // input and output files closed here
            fclose(outputFilePtr);
        }else{
            printf("error");
        }
    }else{
        printf("error");
    }
    return 0;
}
