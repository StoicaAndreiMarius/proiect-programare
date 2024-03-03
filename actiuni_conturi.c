#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int accesare_cont(char *nume){
    char buffer[1024];
    FILE *file = fopen("date_conturi.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }
    while (fgets(buffer, 1024, file)) {
        if (strstr(buffer, nume)) {
            printf("%s\n", buffer);
        }
    }
    fclose(file);
    return 0;
}