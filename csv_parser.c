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


int parola_corecta(const char *username, const char *password) {
    FILE *file = fopen("conturi.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char *token;
        // Ignorăm ID-ul deoarece nu ne interesează
        token = strtok(line, ",");
        // Obținem numele de utilizator
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        char *file_username = token;
        // Obținem parola
        token = strtok(NULL, ",");
        if (token == NULL) continue;
        char *file_password = token;
        // Eliminăm newline-ul de la sfârșitul parolei, dacă există
        file_password[strcspn(file_password, "\n")] = 0;

        if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0) {
            fclose(file);
            return 1; // Utilizatorul și parola se potrivesc
        }
    }

    fclose(file);
    return 0; // Nu s-a găsit o potrivire
}




