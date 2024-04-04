#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int exista_cont(char *nume){
    char buffer[1024];
    FILE *file = fopen("conturi.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    while (fgets(buffer, 1024, file)) {
        if (strstr(buffer, nume)) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int parola_corecta(char *nume, char *parola){
    char buffer[1024];
    FILE *file = fopen("conturi.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    while (fgets(buffer, 1024, file)) {
        if (strstr(buffer, nume) && strstr(buffer, parola)) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}


void adaugare_cont(char *nume, char *parola){
    char buffer[1024];
    FILE *file = fopen("conturi.txt", "r");
    int i = 1;

    if (file != NULL) {
        while(fgets(buffer, 1024, file)){
            i++;
        }
        fclose(file);
    }

    FILE *file_w = fopen("conturi.txt", "a");
    if (file_w == NULL) {
        perror("Eroare la deschiderea fisierului");
        return;
    }

    if (i > 1) {
        fprintf(file_w, "\n");
    }
    sprintf(buffer, "%d,%s,%s,%d", i, nume, parola, 1);
    fprintf(file_w, "%s", buffer);
    fclose(file_w);

    printf("\nCont adaugat cu succes!");
}