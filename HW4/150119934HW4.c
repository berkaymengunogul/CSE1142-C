//
// Berkay Mengunogul 150119934
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Student data-type created here
typedef struct student{
    char name[50];
    char surname[50];
    long int ID;

    struct student *name_next;
    struct student *surname_next;
    struct student *ID_next;
}student;

// to insert a node to the linked list, node itself, starting head pointer, and type of the pointer used
// (1 for name order starting pointer, 2 for surname order starting pointer and 3 for ID order starting pointer)
void insertNode(student *std, student **head, int type){
    if(type == 1){ // if it is name order,
        if(*head == NULL){ // if starting pointer doesnt indicate  any adress first node will be directed to the starting pointer
            *head = std;
            return;
        }
        student *currentPtr = *head; // starting pointer created as currentPtr
        student *previousNode = NULL; // to save the previous node, previousNode pointer created
        while ((currentPtr->name_next != NULL) && strcmp(std->name, currentPtr->name) > 0){
            // currentPtr and previousNode will be updated till right position found by checking
            // the next pointer and their compared values
            previousNode = currentPtr;
            currentPtr = currentPtr->name_next;
        }
        // if current node indicates the last node and
        // after comparing the values if the value is bigger it will be added to the last node
        if(strcmp(currentPtr->name, std->name) < 0){ // insert last
            currentPtr->name_next = std;
        // if previousNode still null then it means new node should be inserted to the beginning of linked list
        } else if(previousNode == NULL){ // insert beginning
            std->name_next = currentPtr;
            (*head) = std;
        // any other case means node should be inserted in between two nodes which are previous node and next node
        }else{ // insert in between
            previousNode->name_next = std;
            std->name_next = currentPtr;
        }
     // Same process happening for inserting a node by name order repeats here for surname order
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
    // Same process happening for inserting a node by name order repeats here for ID order
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

// for deleting a node, id of the node and starting addresses of the linked list used
void deleteNode(int id, student **nameOrder, student **surnameOrder, student **IDOrder){
    student *indexedNode = NULL; // indexed node created to save the node from its id
    student *currentNode = *IDOrder; // current node created with first node of ID order
    student *previousNode = NULL;
    // find the node by ID order
    while (currentNode->ID != id){ // all the nodes starting from Id order is scanned till a node with given id found
        previousNode = currentNode;
        indexedNode = currentNode->ID_next; // indexed node updated every node
        currentNode = currentNode->ID_next;
    }
    if(previousNode == NULL){ // checks if it is first node by checking previous node
        indexedNode = currentNode; // updates the indexed node so it can be used to find the same node with name and surname order
        *IDOrder = currentNode->ID_next; // starting point moved to the next node
    }else if(previousNode != NULL){
        previousNode->ID_next = currentNode->ID_next;
    }

    // find the node by name order
    currentNode = *nameOrder; // current node created with first node of name order
    previousNode = NULL;
    while (currentNode->name != indexedNode->name){ // all the nodes starting from Id order is scanned till
        previousNode = currentNode;                 // a matching node found with indexed node
        currentNode = currentNode->name_next;
    }
    if(previousNode == NULL){ // checks if it is first node
        *nameOrder = currentNode->name_next; // starting point moved to the next node
    }else if(previousNode != NULL){
        previousNode->name_next = currentNode->name_next;
    }

    // find the node by surname order
    currentNode = *surnameOrder; // current node created with first node of surname order
    previousNode = NULL;
    while (currentNode->surname != indexedNode->surname){ // all the nodes starting from Id order is scanned till
        previousNode = currentNode;                        // a matching node found with indexed node
        currentNode = currentNode->surname_next;
    }
    if(previousNode == NULL){ // checks if it is first node
        *surnameOrder = currentNode->surname_next; // starting point moved to the next node
    }else if(previousNode != NULL){
        previousNode->surname_next = currentNode->surname_next;
    }

    printf("The student %s %s %ld is deleted from the list!\n", indexedNode->name, indexedNode->surname, indexedNode->ID);

}
// with the given starting points, all the nodes scanned and printed till next node is null
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
// with the given starting points, all the nodes scanned and written to given file till next node is null
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

    student *node = NULL;
    // input file opened here
    if ((inputFilePtr = fopen(argv[1], "r")) !=NULL) {
        char input[100];
        while (!feof(inputFilePtr)) {
            fscanf(inputFilePtr, "%[^\n]\n", input); // each line saved to input array

            node = malloc(sizeof(student)); // size of student data-type allocated in memory
            char *tokenName = strtok(input, " "); // name tokenized copied to node
            char *tokenSurname = strtok(NULL, "\t"); // surname tokenized copied to node
            char *tokenID = strtok(NULL, ""); // ID tokenized copied to node
            strcpy(node->name, tokenName);
            strcpy(node->surname, tokenSurname);
            node->ID = atol(tokenID); // tokenized id turned into a long integer
            insertNode(node, &nameHead, 1); // node inserted to linked list and and it is pointers to next node for name order updated here
            insertNode(node, &surnameHead, 2); // node inserted to linked list and and it is pointers to next node for surname order updated here
            insertNode(node, &IDHead, 3); // node inserted to linked list and and it is pointers to next node for ID order updated here
            }
        printList(nameHead, surnameHead, IDHead); // linked list printed
        fclose(inputFilePtr); // input file closed
        }else{
        printf("File could not open");
    }
    int menuInput, deleteID;
    char newStudentName[50];
    char newStudentSurname[50];
    char newStudentID[50];
    char outputFile[50];
    // menu functions handled here
    while (menuInput != 5){
        printf("Enter your choice:\n"
               "   1 to insert a student into the list.\n"
               "   2 to delete a student from the list.\n"
               "   3 to print the students in the list.\n"
               "   4 to print the students to an output file.\n"
               "   5 to end.\n");
        scanf("%d", &menuInput); // user input for menu read here
        switch (menuInput) {
            case 1: // new student information inserted into list here
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
            case 2: // With the given student id, related node deleted here
                printf("Enter a student ID:\n");
                scanf("%d", &deleteID);
                deleteNode(deleteID, &nameHead, &surnameHead, &IDHead);
                break;
            case 3: // linked list printed here
                printList(nameHead, surnameHead, IDHead);
                break;
            case 4: // linked list written to document here
                printf("Enter a file name:\n");
                scanf("%s", outputFile);
                printListToFile(outputFile, nameHead, surnameHead, IDHead);
                printf("Output is printed to the file %s\n", outputFile);
                break;
            case 5:
                break;
            default:
                printf("Invalid input\n");
                break;
        }
    }
    return 0;
}