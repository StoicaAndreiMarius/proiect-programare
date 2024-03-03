#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    while(fgets(buffer, 1024, file)){
        i++;
    }
    fclose(file);
    char id[100];
    FILE *file_w = fopen("conturi.txt", "a");
    sprintf(id, "%d", i);
    strcpy(buffer, id);
    strcat(buffer, ",");
    strcat(buffer, nume);
    strcat(buffer, ",");
    strcat(buffer, parola);
    strcat(buffer, ",0");
    fprintf(file_w, "%s", "\n");
    fprintf(file_w, "%s", buffer);
    fclose(file_w);
    printf("Cont adaugat cu succes!");
}


void parse_csv(const char *file_path) {
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];

    FILE *file = fopen(file_path, "r");
    if (!file) {
        perror("Unable to open file");
        return;
    }

    while (fgets(buffer, BUFFER_SIZE, file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        char *token = strtok(buffer, ",");
        while (token) {
            printf("%s ", token);
            token = strtok(NULL, ",");
        }
    }

    fclose(file);
}
