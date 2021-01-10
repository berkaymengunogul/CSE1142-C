//
// Berkay Mengunogul 15011934
//
#include <stdio.h>
#include <string.h>

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
    char input[50];
    char exit[] = "exit";
    char quit[] = "quit"
    scanf("%s", input);
    while ((strcmp(input,"exit") != 0||strcmp(input,"quit") != 0)){
        if (strcmp(input, "stat") == 0){
            printf("here");
        }
        scanf("%s", input);
    }
    return 0;
}
