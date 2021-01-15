//
// Berkay Mengunogul 150119934
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct student{
    char name[50];
    char surname[50];
    long int ID;

    struct student *name_next;
    struct student *surname_next;
    struct student *ID_next;
}student;

void insertNode(student *std, student *header){
    while (her)
}
void deleteNode(student *std){
    free(std);
}
void printList(){
    printf("The list in name-alphabetical order:\n");
    printf("The list in surname-alphabetical order:\n");
    printf("The list in ID sorted order:\n");
}
int main(int argc, char* argv[]){
    FILE *inputFilePtr;
//    student *nameHead = NULL;
//    student *surnameHead = NULL;
//    student *IDHead = NULL;
    student *node = NULL;
    if ((inputFilePtr = fopen(argv[1], "r")) !=NULL) {
        char input[100];
        while (!feof(inputFilePtr)) {
            fscanf(inputFilePtr, "%[^\n]\n", input);
            node = malloc(sizeof(student));
            char *tokenName = strtok(input, " ");
            char *tokenSurname = strtok(NULL, "\t");
            char *tokenID = strtok(NULL, "");
            strcpy(node->name, tokenName);
            strcpy(node->surname,tokenSurname);
            node->ID = atol(tokenID);
            printf("%s %s\t%lu\n", node->name, node->surname, node->ID);
            }
        fclose(inputFilePtr);
        } else{
        printf("File could not open");
    }
    return 0;
}