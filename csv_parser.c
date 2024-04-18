#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int exista_cont(char *nume) {
    char buffer[1024];
    FILE *file = fopen("conturi.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    if (nume == NULL || strlen(nume) == 0) {
        fclose(file);
        return 0;
    }

    while (fgets(buffer, 1024, file)) {
        char *token = strtok(buffer, ",");
        token = strtok(NULL, ",");
        if (token != NULL && strcmp(token, nume) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}


int parola_corecta(char *nume, char *parola) {
    char buffer[1024];
    FILE *file = fopen("conturi.txt", "r");
    char *token;
    char *nume_fisier;
    char *parola_fisier;

    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    if (nume == NULL || parola == NULL || strlen(nume) == 0 || strlen(parola) == 0) {
        fclose(file);
        return 0;
    }

    while (fgets(buffer, 1024, file)) {
        token = strtok(buffer, ",");
        nume_fisier = strtok(NULL, ",");
        parola_fisier = strtok(NULL, ",");

        if (nume_fisier != NULL && parola_fisier != NULL &&
            strcmp(nume_fisier, nume) == 0 && strcmp(parola_fisier, parola) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}




