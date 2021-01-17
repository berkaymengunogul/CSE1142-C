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

void insertNode(student *std, student **head, int type){
    if(type == 1){
        if(*head == NULL){
            *head = std;
            return;
        }
        student *currentPtr = *head;
        student *previousNode = NULL;
        while ((currentPtr->name_next != NULL) && strcmp(std->name, currentPtr->name) > 0){
            previousNode = currentPtr;
            currentPtr = currentPtr->name_next;
        }
        if(strcmp(currentPtr->name, std->name) < 0){ // insert last
            currentPtr->name_next = std;
        } else if(previousNode == NULL){ // insert beginning
            std->name_next = currentPtr;
            (*head) = std;
        }else{ // insert in between
            previousNode->name_next = std;
            std->name_next = currentPtr;
        }
    }else if(type == 2){
        if(*head == NULL){
            *head = std;
            return;
        }
        student *currentPtr = *head;
        student *previousNode = NULL;
        while ((currentPtr->surname_next != NULL) && strcmp(std->surname, currentPtr->surname) > 0){
            previousNode = currentPtr;
            currentPtr = currentPtr->surname_next;
        }
        if(strcmp(currentPtr->surname, std->surname) < 0){ // insert last
            currentPtr->surname_next = std;
        } else if(previousNode == NULL){ // insert beginning
            std->surname_next = currentPtr;
            (*head) = std;
        }else{ // insert in between
            previousNode->surname_next = std;
            std->surname_next = currentPtr;
        }
    }else if(type == 3){
        if(*head == NULL){
            *head = std;
            return;
        }
        student *currentPtr = *head;
        student *previousNode = NULL;
        while ((currentPtr->ID_next != NULL) && (std->ID > currentPtr->ID)){
            previousNode = currentPtr;
            currentPtr = currentPtr->ID_next;
        }
        if(currentPtr->ID < std->ID){ // insert last
            currentPtr->ID_next = std;
        } else if(previousNode == NULL){ // insert beginning
            std->ID_next = currentPtr;
            (*head) = std;
        }else{ // insert in between
            previousNode->ID_next = std;
            std->ID_next = currentPtr;
        }
    }
}

void deleteNode(int id, student **nameOrder, student **surnameOrder, student **IDOrder){
    student *indexedNode = NULL;
    student *currentNode = *IDOrder;
    student *previousNode = NULL;
    // find the node by ID order
    while (currentNode->ID != id){
        previousNode = currentNode;
        indexedNode = currentNode->ID_next;
        currentNode = currentNode->ID_next;
    }
    if(previousNode == NULL){ // checks if it is first node
        indexedNode = currentNode; // updates the indexed node
        *IDOrder = currentNode->ID_next;
        //free(currentNode);
    }else if(previousNode != NULL){
        previousNode->ID_next = currentNode->ID_next;
    }

    // find the node by name order
    currentNode = *nameOrder;
    previousNode = NULL;
    while (currentNode->name != indexedNode->name){
        previousNode = currentNode;
        currentNode = currentNode->name_next;
    }
    if(previousNode == NULL){ // checks if it is first node
        *nameOrder = currentNode->name_next;
        //free(currentNode);
    }else if(previousNode != NULL){
        previousNode->name_next = currentNode->name_next;
    }

    // find the node by surname order
    currentNode = *surnameOrder;
    previousNode = NULL;
    while (currentNode->surname != indexedNode->surname){
        previousNode = currentNode;
        currentNode = currentNode->surname_next;
    }
    if(previousNode == NULL){ // checks if it is first node
        *surnameOrder = currentNode->surname_next;
        //free(currentNode);
    }else if(previousNode != NULL){
        previousNode->surname_next = currentNode->surname_next;
    }

    printf("The student %s %s %ld is deleted from the list!\n", indexedNode->name, indexedNode->surname, indexedNode->ID);

}
void printList(student *nameOrder, student *surnameOrder, student *IDOrder){
    int index;
    printf("The list in name-alphabetical order:\n");
    index = 1;
    while (nameOrder != NULL){
        printf("\t%d.%s %s\t%ld\n",index,nameOrder->name, nameOrder->surname, nameOrder->ID);
        nameOrder = nameOrder->name_next;
        index++;
    }
    printf("The list in surname-alphabetical order:\n");
    index = 1;
    while (surnameOrder != NULL){
        printf("\t%d.%s %s\t%ld\n",index,surnameOrder->name, surnameOrder->surname, surnameOrder->ID);
        surnameOrder = surnameOrder->surname_next;
        index++;
    }
    printf("The list in ID sorted order:\n");
    index = 1;
    while (IDOrder != NULL){
        printf("\t%d.%s %s\t%ld\n",index,IDOrder->name, IDOrder->surname, IDOrder->ID);
        IDOrder = IDOrder->ID_next;
        index++;
    }
}

void printListToFile(char *output, student *nameOrder, student *surnameOrder, student *IDOrder){
    FILE *outputFilePtr;

    if ((outputFilePtr = fopen(output, "w")) !=NULL) {
        int index;
        fprintf(outputFilePtr, "The list in name-alphabetical order:\n");
        index = 1;
        while (nameOrder != NULL) {
            fprintf(outputFilePtr, "\t%d.%s %s\t%ld\n", index, nameOrder->name, nameOrder->surname, nameOrder->ID);
            nameOrder = nameOrder->name_next;
            index++;
        }
        fprintf(outputFilePtr, "The list in surname-alphabetical order:\n");
        index = 1;
        while (surnameOrder != NULL) {
            fprintf(outputFilePtr, "\t%d.%s %s\t%ld\n", index, surnameOrder->name, surnameOrder->surname, surnameOrder->ID);
            surnameOrder = surnameOrder->surname_next;
            index++;
        }
        fprintf(outputFilePtr, "The list in ID sorted order:\n");
        index = 1;
        while (IDOrder != NULL) {
            fprintf(outputFilePtr, "\t%d.%s %s\t%ld\n", index, IDOrder->name, IDOrder->surname, IDOrder->ID);
            IDOrder = IDOrder->ID_next;
            index++;
        }
        fclose(outputFilePtr);
    } else{
        printf("File could not saved");
    }
}
int main(int argc, char* argv[]){
    FILE *inputFilePtr;
    student *nameHead = NULL;
    student *surnameHead = NULL;
    student *IDHead = NULL;
    //IDHead = malloc(sizeof(student));

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
            strcpy(node->surname, tokenSurname);
            node->ID = atol(tokenID);
            insertNode(node, &nameHead, 1);
            insertNode(node, &surnameHead, 2);
            insertNode(node, &IDHead, 3);
            }
        printList(nameHead, surnameHead, IDHead);
        fclose(inputFilePtr);
        }else{
        printf("File could not open");
    }
    int menuInput, deleteID;
    char newStudentName[50];
    char newStudentSurname[50];
    char newStudentID[50];
    char outputFile[50];
    while (menuInput != 5){
        printf("Enter your choice:\n"
               "   1 to insert a student into the list.\n"
               "   2 to delete a student from the list.\n"
               "   3 to print the students in the list.\n"
               "   4 to print the students to an output file.\n"
               "   5 to end.\n");
        scanf("%d", &menuInput);
        switch (menuInput) {
            case 1:
                printf("Enter a student name, surname, and ID:\n");
                scanf("%s %s\t%s", newStudentName, newStudentSurname, newStudentID);
                node = malloc(sizeof(student));
                strcpy(node->name, newStudentName);
                strcpy(node->surname, newStudentSurname);
                node->ID = atol(newStudentID);
                insertNode(node, &nameHead, 1);
                insertNode(node, &surnameHead, 2);
                insertNode(node, &IDHead, 3);
                break;
            case 2:
                printf("Enter a student ID:\n");
                scanf("%d", &deleteID);
                deleteNode(deleteID, &nameHead, &surnameHead, &IDHead);
                break;
            case 3:
                printList(nameHead, surnameHead, IDHead);
                break;
            case 4:
                printf("Enter a file name:\n");
                scanf("%s", outputFile);
                printListToFile(outputFile, nameHead, surnameHead, IDHead);
                printf("Output is printed to the file %s\n", outputFile);
                break;
            case 5:
                break;
            default:
                printf("invalid");
                break;
        }
    }
    return 0;
}